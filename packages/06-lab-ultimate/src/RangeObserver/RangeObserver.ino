/*
 * RangeObserver v0.2
 * ------------------
 * nRF24 RPD presence logger + ESP-NOW sync from LabUltimate TX.
 * When TX sends MARKER, we log local RPD% with the same tag for range walks.
 */

#include "config.h"
#include "lab_now.h"

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#if ENABLE_ESPNOW
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#endif

#if USE_OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

static const uint8_t PIN_CE = 16, PIN_CSN = 15, PIN_SCK = 14, PIN_MISO = 12, PIN_MOSI = 13;
static const uint8_t PIN_LED = 27;

#if USE_OLED
static const uint8_t PIN_SDA = 4, PIN_SCL = 5;
static Adafruit_SSD1306 display(128, 64, &Wire, -1);
#endif

static SPIClass spiH(HSPI);
static RF24 radio(PIN_CE, PIN_CSN, RF24_SPI_HZ);
static bool radio_ok = false;
static uint8_t g_ch = OBS_CHANNEL;
static uint32_t g_bootMs = 0;
static float g_lastRpdPct = 0;
static uint32_t g_markerCount = 0;
static char g_lastTag[8] = "-";
static uint32_t g_txSeq = 0;
static uint8_t g_txMode = 0;
static bool g_txArmed = false;

static rf24_datarate_e rateEnum() {
  switch (RF_DATA_RATE_SEL) {
    case 0: return RF24_1MBPS;
    case 2: return RF24_250KBPS;
    default: return RF24_2MBPS;
  }
}
static const char* rateName() {
  switch (RF_DATA_RATE_SEL) {
    case 0: return "1M";
    case 2: return "250k";
    default: return "2M";
  }
}

static bool beginRadio() {
  spiH.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CSN);
  delay(20);
  for (int i = 0; i < RADIO_BEGIN_RETRIES; i++) {
    if (radio.begin(&spiH)) {
      Serial.printf("[OBS] begin OK try %d\n", i + 1);
      return true;
    }
    delay(80);
  }
  Serial.println(F("[OBS] begin FAIL"));
  return false;
}

static void configureRx(uint8_t ch) {
  radio.stopListening();
  radio.powerUp();
  delayMicroseconds(1500);
  radio.setAutoAck(false);
  radio.setRetries(0, 0);
  radio.setPALevel(RF24_PA_MIN, true);
  radio.setDataRate(rateEnum());
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.setChannel(ch);
  radio.startListening();
  g_ch = ch;
}

static float sampleRpdPct() {
  if (!radio_ok) return 0;
  uint16_t hits = 0;
  for (uint16_t i = 0; i < RPD_SAMPLES; i++) {
    radio.stopListening();
    radio.startListening();
    delayMicroseconds(130);
    if (radio.testRPD()) hits++;
  }
  return 100.0f * (float)hits / (float)RPD_SAMPLES;
}

#if ENABLE_ESPNOW
static uint8_t kBroadcastAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint32_t g_nowSeqOut = 0;
static bool g_nowTxOk = false;

static void labNowSend(uint8_t type, const char* tag, uint8_t chH, uint8_t chV, float rpd);
static void labNowCmd(uint8_t cmd, uint8_t chH, uint8_t chV, const char* tag);

static void handleNowPkt(const uint8_t* data, int len) {
  if (len < (int)sizeof(LabNowPkt)) return;
  LabNowPkt p;
  memcpy(&p, data, sizeof(p));
  if (p.magic != LAB_NOW_MAGIC) return;

  g_txSeq = p.seq;
  g_txMode = p.mode;
  g_txArmed = p.armed != 0;

  if (p.chH <= 125 && p.mode == 7 /* ST_FIXED */ && p.chH != g_ch) {
    configureRx(p.chH);
    Serial.printf("[NOW] follow ch -> %u\n", (unsigned)p.chH);
  }

  if (p.type == LABNOW_MARKER) {
    g_markerCount++;
    strncpy(g_lastTag, p.tag, sizeof(g_lastTag) - 1);
    g_lastTag[sizeof(g_lastTag) - 1] = 0;
    float pct = sampleRpdPct();
    g_lastRpdPct = pct;
    Serial.printf("MARKER_RX,t=%lu,tag=%s,tx_seq=%lu,tx_chH=%u,rpd_pct=%.1f,obs_ch=%u\n",
                  (unsigned long)millis(), p.tag, (unsigned long)p.seq,
                  (unsigned)p.chH, pct, (unsigned)g_ch);
    Serial.printf("CSV_MARK,%lu,%s,%u,%.1f,%lu\n",
                  (unsigned long)millis(), p.tag, (unsigned)g_ch, pct,
                  (unsigned long)g_markerCount);
    // ACK back to TX with measured RPD
    labNowSend(LABNOW_ACK, p.tag, p.chH, p.chV, pct);
  } else if (p.type == LABNOW_ARM) {
    Serial.printf("[NOW] ARM tag=%s armed=%u\n", p.tag, (unsigned)p.armed);
  } else if (p.type == LABNOW_MODE) {
    Serial.printf("[NOW] MODE %u tag=%s chH=%u\n", (unsigned)p.mode, p.tag, (unsigned)p.chH);
  }
}

static void labNowSend(uint8_t type, const char* tag, uint8_t chH, uint8_t chV, float rpd) {
  if (!g_nowTxOk) return;
  LabNowPkt p;
  memset(&p, 0, sizeof(p));
  p.magic = LAB_NOW_MAGIC;
  p.seq = ++g_nowSeqOut;
  p.t_ms = millis();
  p.type = type;
  p.mode = 0;
  p.chH = chH;
  p.chV = chV;
  p.rpdPct = rpd;
  if (tag) strncpy(p.tag, tag, sizeof(p.tag) - 1);
  esp_now_send(kBroadcastAddr, (uint8_t*)&p, sizeof(p));
}

static void labNowCmd(uint8_t cmd, uint8_t chH, uint8_t chV, const char* tag) {
  if (!g_nowTxOk) return;
  LabNowPkt p;
  memset(&p, 0, sizeof(p));
  p.magic = LAB_NOW_MAGIC;
  p.seq = ++g_nowSeqOut;
  p.t_ms = millis();
  p.type = LABNOW_CMD;
  p.mode = cmd;
  p.chH = chH;
  p.chV = chV;
  if (tag) strncpy(p.tag, tag, sizeof(p.tag) - 1);
  esp_err_t e = esp_now_send(kBroadcastAddr, (uint8_t*)&p, sizeof(p));
  Serial.printf("[NOW-TX] cmd=%u ch=%u/%u err=%d\n", (unsigned)cmd, (unsigned)chH,
                (unsigned)chV, (int)e);
}

// Arduino-ESP32 3.x callback
static void onNowRecvV3(const esp_now_recv_info_t* info, const uint8_t* data, int len) {
  (void)info;
  handleNowPkt(data, len);
}

static void onNowSent(const wifi_tx_info_t* /*info*/, esp_now_send_status_t /*st*/) {}

static bool labNowInit() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  if (esp_now_init() != ESP_OK) {
    Serial.println(F("[NOW] init FAIL"));
    return false;
  }
  esp_now_register_recv_cb(onNowRecvV3);
  esp_now_register_send_cb(onNowSent);
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcastAddr, 6);
  peer.channel = 1;
  peer.encrypt = false;
  esp_now_add_peer(&peer);
  g_nowTxOk = true;
  Serial.print(F("[NOW] RX+TX OK MAC="));
  Serial.println(WiFi.macAddress());
  return true;
}
#endif

static void oledShow(float pct, uint16_t hits, uint16_t samples) {
#if USE_OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("RangeObserver v5"));
  display.setCursor(0, 12);
  display.printf("ch=%u %s", (unsigned)g_ch, rateName());
  display.setCursor(0, 24);
  display.printf("RPD %.0f%%", pct);
  display.setCursor(0, 36);
  display.printf("%u/%u mk=%lu", (unsigned)hits, (unsigned)samples,
                 (unsigned long)g_markerCount);
  display.setCursor(0, 48);
  display.printf("TX seq=%lu a=%d", (unsigned long)g_txSeq, (int)g_txArmed);
  display.setCursor(0, 56);
  display.printf("tag %s", g_lastTag);
  display.display();
#else
  (void)pct; (void)hits; (void)samples;
#endif
}

void setup() {
  Serial.begin(115200);
  delay(40);
  g_bootMs = millis();
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  Serial.println(F("\n=== RangeObserver v0.5 ==="));
  Serial.printf("fw=%s ch=%u rate=%s\n", FW_VERSION, (unsigned)OBS_CHANNEL, rateName());
  Serial.println(F("CSV_HEADER,t_ms,ch,rpd_hits,rpd_samples,rpd_pct,connected,tx_seq"));
  Serial.println(F("Markers: CSV_MARK | cmds: ch N | fixed H V | marker | arm | disarm"));

#if ENABLE_ESPNOW
  labNowInit();
#endif

#if USE_OLED
  Wire.begin(PIN_SDA, PIN_SCL);
  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("RangeObserver"));
    display.display();
  }
#endif

  radio_ok = beginRadio();
  if (radio_ok) configureRx(OBS_CHANNEL);
}

static void serviceObsSerial() {
#if ALLOW_SERIAL_CH
  static char buf[48];
  static uint8_t n = 0;
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      buf[n] = 0;
      n = 0;
      if (!buf[0]) continue;
      if (!strncasecmp(buf, "ch ", 3)) {
        int ch = atoi(buf + 3);
        if (ch < 0) ch = 0;
        if (ch > 125) ch = 125;
        configureRx((uint8_t)ch);
        Serial.printf("[OBS] channel -> %d\n", ch);
#if ENABLE_ESPNOW
        labNowCmd(LABCMD_SET_CH, (uint8_t)ch, (uint8_t)ch, "SETCH");
#endif
      } else if (!strcasecmp(buf, "help")) {
        Serial.println(F("OBS: ch N | fixed H V | marker | arm | disarm | help"));
      } else if (!strncasecmp(buf, "fixed ", 6)) {
        int h = 0, v = 0;
        if (sscanf(buf + 6, "%d %d", &h, &v) >= 1) {
          if (v <= 0) v = h;
          configureRx((uint8_t)h);
#if ENABLE_ESPNOW
          labNowCmd(LABCMD_REQ_FIXED, (uint8_t)h, (uint8_t)v, "FIXED");
#endif
        }
      } else if (!strcasecmp(buf, "marker")) {
#if ENABLE_ESPNOW
        labNowCmd(LABCMD_MARKER, g_ch, g_ch, "OBSM");
#endif
      } else if (!strcasecmp(buf, "arm")) {
#if ENABLE_ESPNOW
        labNowCmd(LABCMD_ARM, 0, 0, "ARM");
#endif
      } else if (!strcasecmp(buf, "disarm")) {
#if ENABLE_ESPNOW
        labNowCmd(LABCMD_DISARM, 0, 0, "DISARM");
#endif
      } else {
        Serial.printf("[OBS] unknown: %s\n", buf);
      }
    } else if (n < sizeof(buf) - 1) {
      buf[n++] = c;
    }
  }
#endif
}

void loop() {
  serviceObsSerial();
  if (!radio_ok) {
    delay(1000);
    radio_ok = beginRadio();
    if (radio_ok) configureRx(g_ch);
    return;
  }

#if SCAN_ENABLE
  static uint8_t scanCh = SCAN_CH_MIN;
  configureRx(scanCh);
  uint16_t hits = 0;
  for (uint16_t i = 0; i < RPD_SAMPLES; i++) {
    if (radio.testRPD()) hits++;
    delayMicroseconds(200);
  }
  float pct = 100.0f * (float)hits / (float)RPD_SAMPLES;
  g_lastRpdPct = pct;
  Serial.printf("CSV,%lu,%u,%u,%u,%.1f,%d,%lu\n",
                (unsigned long)millis(), (unsigned)scanCh, (unsigned)hits,
                (unsigned)RPD_SAMPLES, pct, radio.isChipConnected() ? 1 : 0,
                (unsigned long)g_txSeq);
  oledShow(pct, hits, RPD_SAMPLES);
  digitalWrite(PIN_LED, pct > 20.0f ? HIGH : LOW);
  scanCh++;
  if (scanCh > (uint8_t)SCAN_CH_MAX) scanCh = SCAN_CH_MIN;
  delay(50);
#else
  uint16_t hits = 0;
  uint32_t t0 = millis();
  for (uint16_t i = 0; i < RPD_SAMPLES; i++) {
    radio.stopListening();
    radio.startListening();
    delayMicroseconds(130);
    if (radio.testRPD()) hits++;
  }
  float pct = 100.0f * (float)hits / (float)RPD_SAMPLES;
  g_lastRpdPct = pct;
  uint32_t t = millis();
  bool conn = radio.isChipConnected();

  Serial.printf("CSV,%lu,%u,%u,%u,%.1f,%d,%lu\n",
                (unsigned long)t, (unsigned)g_ch, (unsigned)hits,
                (unsigned)RPD_SAMPLES, pct, conn ? 1 : 0, (unsigned long)g_txSeq);
  Serial.printf("OBS ch=%u RPD=%.0f%% tx_seq=%lu tag=%s\n",
                (unsigned)g_ch, pct, (unsigned long)g_txSeq, g_lastTag);

  oledShow(pct, hits, RPD_SAMPLES);
  digitalWrite(PIN_LED, pct > 20.0f ? HIGH : LOW);

  uint32_t elapsed = millis() - t0;
  if (elapsed < (uint32_t)STATS_MS) delay((uint32_t)STATS_MS - elapsed);
#endif
}
