/*
 * Lab Ultimate TX v0.5
 * -------------------
 * v0.1–0.4: FIXED/SLOW, CSA, ESP-NOW, BLE, SoftAP, INA, log, OTA, protect
 * v0.5: Experiment sequencer, profiles, WDT, boot reason, ESP-NOW RX cmds
 *
 * LEGAL: Authorized / shielded lab only.
 */

#include "config.h"
#include "ieee_maps.h"
#include "soft_csa.h"
#include "lab_now.h"
#include "lab_ina219.h"
#include "lab_filelog.h"
#include "lab_experiment.h"

#include <Arduino.h>
#include <esp_task_wdt.h>
#include <SPI.h>
#include <Wire.h>
#include <Preferences.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp_system.h>
#include <string.h>
#include <stdlib.h>

#if ENABLE_ESPNOW || ENABLE_SOFTAP
#include <WiFi.h>
#include <esp_wifi.h>
#endif
#if ENABLE_ESPNOW
#include <esp_now.h>
#endif
#if ENABLE_SOFTAP
#include "lab_web.h"
#endif

#if ENABLE_BLE_SCAN
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#endif

#if !REBUILD_SAFE
#include <RF24.h>
#include <nRF24L01.h>
#endif

#include "bitmaps.h"
#include "OrigSerialArt.h"

static const uint8_t PIN_CE1 = 16, PIN_CSN1 = 15, PIN_SCK1 = 14, PIN_MISO1 = 12, PIN_MOSI1 = 13;
static const uint8_t PIN_CE2 = 22, PIN_CSN2 = 21, PIN_SCK2 = 18, PIN_MISO2 = 19, PIN_MOSI2 = 23;
static const uint8_t PIN_LED = 27, PIN_BOOT = 0, PIN_SDA = 4, PIN_SCL = 5;
static const uint8_t OLED_ADDR = 0x3C;

static const uint32_t SERIAL_BAUD = 115200;
static const uint32_t SPLASH_MS = 1400;
static const uint32_t LONG_PRESS_MS = 500;
static const uint32_t DEBOUNCE_MS = 30;
static const uint32_t LED_PULSE_MS = 150, LED_GAP_MS = 1000;
static const uint32_t PAUSE_POLL_MS = 10, RADIO_HEALTH_MS = 4000;

enum : int {
  ST_IDLE = 0,
  ST_BT = 1,
  ST_BLE = 2,
  ST_WIFI = 3,
  ST_RC = 4,
  ST_154 = 5,
  ST_COEXIST = 6,
  ST_FIXED = 7,
  ST_SLOW = 8,
  ST_CSA1 = 9,      // soft AFH CSA#1
  ST_CSA2 = 10,     // soft AFH CSA#2
  ST_BLESCAN = 11,  // native BLE scan (no nRF TX)
  ST_EXP = 12,      // experiment sequencer
  ST_MODE_MAX = 12
};

#if LAB_ENGINE == 0
static const int ST_CYCLE_MAX = ST_RC;
#elif ENABLE_EXPERIMENT
static const int ST_CYCLE_MAX = ST_EXP;
#else
static const int ST_CYCLE_MAX = ST_BLESCAN;
#endif

volatile int  g_state = INITIAL_STATE;
volatile bool g_pauseRf = false;
volatile bool g_dutyGate = true;
volatile bool g_armed = (REQUIRE_RF_ARM == 0);
volatile bool g_nrfTxHold = false;  // BLE scan holds nRF TX
volatile int  g_coexistFamily = 1;

volatile uint8_t  g_chH = 0, g_chV = 0;
volatile uint32_t g_hopCount = 0;
volatile uint16_t g_uniqueApprox = 0;
volatile float    g_vccRail = 0.0f;
volatile uint32_t g_markerSeq = 0;
volatile uint32_t g_bleDevices = 0;
volatile int      g_bleBestRssi = -127;

static int g_uiState = -1;
static int g_savedState = ST_BT;
static uint32_t g_lastOledMs = 0, g_lastStatsMs = 0, g_lastHopSnap = 0;
static uint32_t g_covBits[4] = {0};
static portMUX_TYPE statsMux = portMUX_INITIALIZER_UNLOCKED;

static uint8_t g_ledOn = 0;
static int g_ledCount = 0, g_ledTarget = 0;
static uint32_t g_ledTs = 0;

static bool btnStable = false, btnRawPrev = false, btnLongDone = false;
static uint32_t btnChangeMs = 0, btnDownMs = 0;
static uint8_t  g_armPresses = 0;
static uint32_t g_armWindowStart = 0;
static uint32_t g_lastShortMs = 0;
static uint8_t  g_doubleTapArmed = 0;

static uint16_t g_idxH = 0, g_idxV = 0;
static uint8_t  g_slowCh = 0;
static uint32_t g_bootMs = 0;
static uint32_t g_nowSeq = 0;
static float    g_lastHopRate = 0;
static float    g_busV = 0, g_currA = 0, g_powerW = 0;
static int      g_fixedH = FIXED_CH_H;
static int      g_fixedV = FIXED_CH_V;
static uint32_t g_currentTrips = 0;
static uint8_t  g_overHits = 0;
static uint32_t g_statsMs = EDU_STATS_MS;
static uint8_t  g_profile = 1;  // 0 original-like · 1 edu · 2 range
static uint32_t g_bootCount = 0;
static const char* g_expTag = "-";
static uint8_t g_expSubMode = ST_BT;
#if DUTY_RUNTIME_ENABLE
static volatile uint32_t g_dutyOnMs = RANGE_DUTY_ON_MS;
static volatile uint32_t g_dutyOffMs = RANGE_DUTY_OFF_MS;
#endif
#if ENABLE_EXPERIMENT
static ExpRunner g_exp;
#endif

static Csa1State g_csa1;
static Csa2State g_csa2;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Preferences prefs;

#if ENABLE_INA219
static LabIna219 g_ina(INA219_ADDR, INA219_SHUNT_OHMS);
static bool g_inaOk = false;
#endif
#if ENABLE_FILE_LOG
static LabFileLog g_flog;
#endif
#if ENABLE_SOFTAP
static LabWebHooks g_webHooks;
static LabWeb* g_web = nullptr;
#endif

#if !REBUILD_SAFE
static SPIClass spiH(HSPI), spiV(VSPI);
static RF24 radioH(PIN_CE1, PIN_CSN1, RF24_SPI_HZ);
static RF24 radioV(PIN_CE2, PIN_CSN2, RF24_SPI_HZ);
static bool radioH_ok = false, radioV_ok = false;
static portMUX_TYPE radioMux = portMUX_INITIALIZER_UNLOCKED;
#endif

#if ENABLE_ESPNOW
static uint8_t kBroadcastAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static bool g_espnowOk = false;
#endif

static inline uint8_t hwRandMod(uint8_t m) {
  return m ? (uint8_t)(esp_random() % m) : 0;
}

static const char* stateName(int s) {
  switch (s) {
    case ST_IDLE: return "Idle & Status";
    case ST_BT: return "BT classic (edu)";
    case ST_BLE: return "BLE Core Spec map";
    case ST_WIFI: return "IEEE 802.11 2.4";
    case ST_RC: return "ISM / RC wide";
    case ST_154: return "IEEE 802.15.4";
    case ST_COEXIST: return "IEEE coexist";
    case ST_FIXED: return "FIXED carrier";
    case ST_SLOW: return "SLOW sweep";
    case ST_CSA1: return "Soft CSA#1 AFH";
    case ST_CSA2: return "Soft CSA#2 AFH";
    case ST_BLESCAN: return "Native BLE scan";
    case ST_EXP: return "Experiment sequencer";
    default: return "?";
  }
}

static const char* resetReasonStr() {
  switch (esp_reset_reason()) {
    case ESP_RST_POWERON: return "POWERON";
    case ESP_RST_SW: return "SW";
    case ESP_RST_PANIC: return "PANIC";
    case ESP_RST_INT_WDT: return "INT_WDT";
    case ESP_RST_TASK_WDT: return "TASK_WDT";
    case ESP_RST_WDT: return "WDT";
    case ESP_RST_BROWNOUT: return "BROWNOUT";
    case ESP_RST_SDIO: return "SDIO";
    default: return "OTHER";
  }
}

static const char* hwName() {
  switch (HW_PROFILE) {
    case 0: return "STOCK";
    case 1: return "PA+LNA";
    case 2: return "PA+LNA-HG";
    default: return "CUSTOM";
  }
}
static const char* rateName() {
  switch (RF_DATA_RATE_SEL) {
    case 0: return "1M";
    case 2: return "250k";
    default: return "2M";
  }
}
static const char* hopStratName() {
  switch (HOP_STRATEGY) {
    case 0: return "ORIGINAL";
    case 2: return "SLOW";
    case 3: return "FIXED";
    default: return "EDU";
  }
}

#if !REBUILD_SAFE
static rf24_datarate_e rateEnum() {
  switch (RF_DATA_RATE_SEL) {
    case 0: return RF24_1MBPS;
    case 2: return RF24_250KBPS;
    default: return RF24_2MBPS;
  }
}
static rf24_pa_dbm_e paEnum() {
  switch (RF_PA_LEVEL) {
    case 0: return RF24_PA_MIN;
    case 1: return RF24_PA_LOW;
    case 2: return RF24_PA_HIGH;
    default: return RF24_PA_MAX;
  }
}
#endif

static void saveMode(int s) {
#if REMEMBER_LAST_MODE
  if (s >= ST_BT && s <= ST_CYCLE_MAX) prefs.putUChar("mode", (uint8_t)s);
#endif
}
static int loadMode() {
#if REMEMBER_LAST_MODE
  uint8_t m = prefs.getUChar("mode", (uint8_t)INITIAL_STATE);
  if (m >= ST_BT && m <= ST_CYCLE_MAX) return (int)m;
#endif
  return INITIAL_STATE;
}

static void covMark(uint8_t ch) {
  if (ch > 125) return;
  g_covBits[ch >> 5] |= (1u << (ch & 31));
}
static uint16_t covPop() {
  uint16_t n = 0;
  for (int i = 0; i < 4; i++) n += (uint16_t)__builtin_popcount(g_covBits[i]);
  return n;
}
static void covReset() { memset(g_covBits, 0, sizeof(g_covBits)); }

static void csaReloadMaps() {
  uint32_t lo, hi;
  if (CSA_MAP_PRESET == 1) csaMapAvoidWifi1611(&lo, &hi);
  else csaMapAll(&lo, &hi);
  csa1Init(&g_csa1, (uint8_t)CSA1_HOP_INC, lo, hi);
  csa2Init(&g_csa2, (uint16_t)CSA2_CHANNEL_ID, lo, hi);
}

// ---- ESP-NOW ----
#if ENABLE_ESPNOW
static void labNowSend(uint8_t type, const char* tag) {
  if (!g_espnowOk) return;
  LabNowPkt p;
  memset(&p, 0, sizeof(p));
  p.magic = LAB_NOW_MAGIC;
  p.seq = ++g_nowSeq;
  p.t_ms = millis();
  p.type = type;
  p.mode = (uint8_t)g_state;
  p.chH = g_chH;
  p.chV = g_chV;
  p.armed = g_armed ? 1 : 0;
  p.hopRate = (uint8_t)(g_lastHopRate > 25500 ? 255 : (g_lastHopRate / 100.0f));
  p.uniqueApprox = g_uniqueApprox;
  p.rpdPct = 0;
  if (tag) {
    strncpy(p.tag, tag, sizeof(p.tag) - 1);
  }
  esp_err_t e = esp_now_send(kBroadcastAddr, (uint8_t*)&p, sizeof(p));
  if (e != ESP_OK) {
    Serial.printf("[NOW] send err %d\n", (int)e);
  } else if (type == LABNOW_MARKER) {
    Serial.printf("[NOW] MARKER seq=%lu tag=%s chH=%u\n",
                  (unsigned long)p.seq, p.tag, (unsigned)p.chH);
  }
}

// Arduino-ESP32 3.x send callback uses wifi_tx_info_t*
static void onNowSent(const wifi_tx_info_t* /*info*/, esp_now_send_status_t /*st*/) {}

// Forward decls used by ESP-NOW RX
static void setMode(int s);
static void setArmed(bool on);
static void setFixedCh(int h, int v);
static void fireMarker(const char* tag);

#if ENABLE_ESPNOW_RX
static void handleNowCmd(const LabNowPkt& p) {
  switch (p.mode) {
    case LABCMD_SET_CH:
      if (p.chH <= 125) {
        setFixedCh(p.chH, p.chV <= 125 ? p.chV : p.chH);
        Serial.printf("[NOW-RX] SET_CH %u/%u\n", (unsigned)p.chH, (unsigned)p.chV);
      }
      break;
    case LABCMD_REQ_FIXED:
      setFixedCh(p.chH, p.chV);
      setMode(ST_FIXED);
      Serial.println(F("[NOW-RX] REQ_FIXED"));
      break;
    case LABCMD_MARKER:
      fireMarker(p.tag[0] ? p.tag : "OBS");
      break;
    case LABCMD_ARM:
      setArmed(true);
      Serial.println(F("[NOW-RX] ARM"));
      break;
    case LABCMD_DISARM:
      setArmed(false);
      Serial.println(F("[NOW-RX] DISARM"));
      break;
    default:
      Serial.printf("[NOW-RX] unknown cmd %u\n", (unsigned)p.mode);
      break;
  }
}

static void onNowRecv(const esp_now_recv_info_t* /*info*/, const uint8_t* data, int len) {
  if (len < (int)sizeof(LabNowPkt)) return;
  LabNowPkt p;
  memcpy(&p, data, sizeof(p));
  if (p.magic != LAB_NOW_MAGIC) return;
  if (p.type == LABNOW_CMD) {
    handleNowCmd(p);
  } else if (p.type == LABNOW_ACK) {
    Serial.printf("[NOW-RX] ACK tag=%s rpd=%.1f\n", p.tag, p.rpdPct);
  }
}
#endif

static bool labNowInit() {
#if ENABLE_SOFTAP
  WiFi.mode(WIFI_AP_STA);
#else
  WiFi.mode(WIFI_STA);
#endif
  WiFi.disconnect();
  // Fixed channel for lab predictability (match SoftAP channel)
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(SOFTAP_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  if (esp_now_init() != ESP_OK) {
    Serial.println(F("[NOW] init FAIL"));
    return false;
  }
  esp_now_register_send_cb(onNowSent);
#if ENABLE_ESPNOW_RX
  esp_now_register_recv_cb(onNowRecv);
#endif
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcastAddr, 6);
  peer.channel = SOFTAP_CHANNEL;
  peer.encrypt = false;
  if (esp_now_add_peer(&peer) != ESP_OK) {
    // peer may already exist
  }
  Serial.print(F("[NOW] OK MAC="));
  Serial.println(WiFi.macAddress());
  return true;
}
#else
static void labNowSend(uint8_t, const char*) {}
static bool labNowInit() { return false; }
#endif

static void fireMarker(const char* tag) {
  g_markerSeq++;
  char buf[8];
  if (!tag || !tag[0]) {
    snprintf(buf, sizeof(buf), "M%lu", (unsigned long)(g_markerSeq % 1000));
    tag = buf;
  }
  Serial.printf("MARKER,%lu,%s,%u,%u,%d\n",
                (unsigned long)millis(), tag,
                (unsigned)g_chH, (unsigned)g_chV, (int)g_state);
  labNowSend(LABNOW_MARKER, tag);
}

// ---- channel pick ----
static uint8_t pickFamily(int family, bool isH, uint8_t peer) {
  uint8_t ch = 0;
  uint8_t fullMod = 126;

  if (HOP_STRATEGY == 0) {
    switch (family) {
      case ST_BT: ch = hwRandMod(79); fullMod = 79; break;
      case ST_BLE: ch = hwRandMod(39); fullMod = 39; break;
      case ST_WIFI: ch = hwRandMod(14); fullMod = 14; break;
      case ST_154: ch = IEEE_154_CH[esp_random() % IEEE_154_CH_N]; fullMod = 81; break;
      default: ch = hwRandMod(125); fullMod = 125; break;
    }
  } else {
    switch (family) {
      case ST_BT: {
        fullMod = IEEE_BT_FULL_MOD;
        if ((esp_random() % 100) < HOP_PRIORITY_PCT) {
          uint16_t* ix = isH ? &g_idxH : &g_idxV;
          uint16_t base = isH ? 0 : (IEEE_BT_GRID_N / 2);
          ch = IEEE_BT_GRID[(*ix + base) % IEEE_BT_GRID_N];
          (*ix)++;
        } else ch = hwRandMod(fullMod);
        break;
      }
      case ST_BLE: {
        fullMod = IEEE_BLE_FULL_MOD;
        if ((esp_random() % 100) < 45) ch = IEEE_BLE_ADV[esp_random() % IEEE_BLE_ADV_N];
        else if ((esp_random() % 100) < HOP_PRIORITY_PCT)
          ch = IEEE_BLE_DATA[esp_random() % IEEE_BLE_DATA_N];
        else ch = hwRandMod(fullMod);
        break;
      }
      case ST_WIFI: {
        fullMod = 83;
        if ((esp_random() % 100) < WIFI_NOLAP_WEIGHT_PCT)
          ch = IEEE_WIFI_NOLAP[esp_random() % IEEE_WIFI_NOLAP_N];
        else if ((esp_random() % 100) < 50)
          ch = IEEE_WIFI_ALL[esp_random() % IEEE_WIFI_ALL_N];
        else ch = IEEE_WIFI_DENSE[esp_random() % IEEE_WIFI_DENSE_N];
        break;
      }
      case ST_154: {
        fullMod = 81;
        if ((esp_random() % 100) < HOP_PRIORITY_PCT)
          ch = IEEE_154_PREFERRED[esp_random() % IEEE_154_PREFERRED_N];
        else ch = IEEE_154_CH[esp_random() % IEEE_154_CH_N];
        break;
      }
      default: {
        fullMod = IEEE_RC_FULL_MOD;
        if ((esp_random() % 100) < HOP_PRIORITY_PCT)
          ch = IEEE_RC_GRID[esp_random() % IEEE_RC_GRID_N];
        else ch = hwRandMod(fullMod);
        break;
      }
    }
  }

#if COMPLEMENTARY_DUAL
  if (peer != 0xFF && fullMod > 1) {
    int tries = 0;
    while (tries < 10) {
      int d = (int)ch - (int)peer;
      if (d < 0) d = -d;
      if (d >= (int)DUAL_MIN_SEPARATION) break;
      ch = (uint8_t)((peer + DUAL_MIN_SEPARATION + tries * 3) % fullMod);
      tries++;
    }
  }
#endif
  return ch;
}

static uint8_t pickChannel(int state, bool isH, uint8_t peer) {
  if (state == ST_FIXED || HOP_STRATEGY == 3)
    return isH ? (uint8_t)FIXED_CH_H : (uint8_t)FIXED_CH_V;
  if (state == ST_SLOW || HOP_STRATEGY == 2) {
    if (isH) return g_slowCh;
    return (uint8_t)((g_slowCh + DUAL_MIN_SEPARATION) % (SLOW_SWEEP_MAX_CH + 1));
  }
  if (state == ST_CSA1) {
    (void)isH; (void)peer;
    return csa1NextNrf(&g_csa1);  // each call = one event (H then V)
  }
  if (state == ST_CSA2) {
    (void)isH; (void)peer;
    return csa2NextNrf(&g_csa2);
  }
  if (state == ST_BLESCAN) return isH ? g_chH : g_chV;
  if (state == ST_COEXIST) return pickFamily((int)g_coexistFamily, isH, peer);
  return pickFamily(state, isH, peer);
}

static void noteHop(uint8_t a, uint8_t b) {
  portENTER_CRITICAL(&statsMux);
  g_chH = a; g_chV = b;
  g_hopCount++;
  covMark(a); covMark(b);
  g_uniqueApprox = covPop();
  portEXIT_CRITICAL(&statsMux);
}

static void printModeEdu(int s) {
  Serial.println(F("---- LabUltimate mode ----"));
  Serial.printf("mode=%s\n", stateName(s));
  Serial.printf("hw=%s rate=%s strat=%s\n", hwName(), rateName(), hopStratName());
  Serial.printf("armed=%s nrf_hold=%d\n", g_armed ? "YES" : "NO", (int)g_nrfTxHold);
  switch (s) {
    case ST_FIXED:
      Serial.printf("FIXED H=%u V=%u MHz %u/%u\n", (unsigned)FIXED_CH_H, (unsigned)FIXED_CH_V,
                    2400u + FIXED_CH_H, 2400u + FIXED_CH_V);
      break;
    case ST_SLOW:
      Serial.printf("SLOW dwell=%ums\n", (unsigned)SLOW_DWELL_MS);
      break;
    case ST_CSA1:
      Serial.printf("CSA#1 hopInc=%u map=%s nUsed=%u dwell=%ums\n",
                    (unsigned)g_csa1.hopInc, csaMapName(CSA_MAP_PRESET),
                    (unsigned)g_csa1.nUsed, (unsigned)CSA_DWELL_MS);
      Serial.println(F("Period ~37 events on full map — watch SDR"));
      break;
    case ST_CSA2:
      Serial.printf("CSA#2 CI=0x%04X map=%s nUsed=%u\n",
                    (unsigned)g_csa2.channelId, csaMapName(CSA_MAP_PRESET),
                    (unsigned)g_csa2.nUsed);
      break;
    case ST_BLESCAN:
      Serial.println(F("Native BLE scan — nRF TX held; lists nearby advertisers"));
      break;
    case ST_EXP:
      Serial.println(F("Experiment playlist — exp0 default tour, exp1 range fixeds"));
      Serial.printf("current step tag=%s\n", g_expTag);
      break;
    case ST_WIFI:
      Serial.println(F("802.11 centers; weight non-overlap 1/6/11"));
      break;
    case ST_BLE:
      Serial.println(F("BLE adv nRF 2/26/80"));
      break;
    default: break;
  }
  Serial.println(F("cmd: help | m | arm | modes | fixed | csa1 | csa2 | map0 | map1"));
  Serial.println(F("--------------------------"));
}

static void sampleVcc() {
#if VCC_SENSE_PIN < 255
  uint32_t acc = 0;
  for (int i = 0; i < 8; i++) acc += analogRead(VCC_SENSE_PIN);
  float mid = (acc / 8.0f) * (3.3f / 4095.0f);
  g_vccRail = mid * ((VCC_SENSE_R_TOP_KOHM + VCC_SENSE_R_BOT_KOHM) / VCC_SENSE_R_BOT_KOHM);
#else
  g_vccRail = 0;
#endif
}

static void oledSplash() {
  display.clearDisplay();
  display.drawBitmap(0, 0, bitmapboot, 128, 64, SSD1306_WHITE);
  display.display();
}

static void oledTextMode(int mode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.printf("LabUlt %s", FW_VERSION);
  display.setCursor(0, 12);
  display.println(stateName(mode));
  display.setCursor(0, 28);
  if (mode == ST_BLESCAN)
    display.printf("BLE n=%lu rssi=%d", (unsigned long)g_bleDevices, g_bleBestRssi);
  else
    display.printf("H%u V%u %s", (unsigned)g_chH, (unsigned)g_chV, rateName());
  display.setCursor(0, 40);
  display.printf("%s %s", hwName(), hopStratName());
  display.setCursor(0, 52);
  if (!g_armed) display.print(F("DISARMED 3xBOOT"));
  else if (g_pauseRf) display.print(F("[PAUSED]"));
  else if (g_nrfTxHold) display.print(F("[nRF HOLD]"));
  else display.print(F("TX dblBOOT=mark"));
  display.display();
}

static void oledBitmapMode(const uint8_t* bmp, int mode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  const char* t = "LabUltimate";
  int16_t x1, y1; uint16_t tw, th;
  display.getTextBounds(t, 0, 0, &x1, &y1, &tw, &th);
  display.setCursor((int16_t)((128 - tw) / 2), 2);
  display.print(t);
  display.drawBitmap(0, 12, bmp, 128, 50, SSD1306_WHITE);
#if EDU_OLED_HUD
  display.fillRect(0, 56, 128, 8, SSD1306_BLACK);
  display.setCursor(0, 56);
  display.printf("H%u V%u %s%s", (unsigned)g_chH, (unsigned)g_chV, rateName(),
                 g_armed ? "" : " !");
#endif
  display.display();
  (void)mode;
}

static void oledIdle() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("R1="));
#if !REBUILD_SAFE
  display.print((radioH_ok && radioH.isChipConnected()) ? F("OK") : F("FAIL"));
#else
  display.print(F("SAFE"));
#endif
  display.setCursor(64, 0);
  display.print(F("R2="));
#if !REBUILD_SAFE
  display.print((radioV_ok && radioV.isChipConnected()) ? F("OK") : F("FAIL"));
#else
  display.print(F("SAFE"));
#endif
  display.setCursor(0, 12);
  display.printf("v%s %s", FW_VERSION, hwName());
  display.setCursor(0, 22);
  display.printf("ch H=%u V=%u", (unsigned)g_chH, (unsigned)g_chV);
  display.setCursor(0, 32);
  display.printf("hops=%lu mk=%lu", (unsigned long)g_hopCount, (unsigned long)g_markerSeq);
  display.setCursor(0, 42);
  if (g_vccRail > 0.1f) display.printf("Vcc=%.2f", g_vccRail);
  else display.printf("heap=%u", (unsigned)ESP.getFreeHeap());
  display.setCursor(0, 54);
  if (!g_armed) display.print(F("DISARMED 3x short"));
  else if (g_pauseRf) display.print(F("[PAUSED] short=go"));
  else display.print(F("BOOT=mode hold=pause"));
  display.display();
}

static bool oledDue() {
  uint32_t n = millis();
  if (n - g_lastOledMs < OLED_MIN_FRAME_MS) return false;
  g_lastOledMs = n;
  return true;
}

static void ledReset(int b) {
  g_ledTarget = b; g_ledCount = 0; g_ledOn = 0; g_ledTs = millis();
  digitalWrite(PIN_LED, LOW);
}
static void ledService() {
  if (g_ledTarget <= 0) return;
  uint32_t n = millis();
  uint32_t need = (g_ledOn && g_ledCount >= g_ledTarget) ? LED_GAP_MS : LED_PULSE_MS;
  if (n - g_ledTs < need) return;
  g_ledTs = n; g_ledOn ^= 1;
  digitalWrite(PIN_LED, g_ledOn ? HIGH : LOW);
  if (g_ledOn) { g_ledCount++; if (g_ledCount > g_ledTarget) g_ledCount = 1; }
}

static void showModeUi(int s) {
  switch (s) {
    case ST_BT: oledBitmapMode(bitmap1, s); ledReset(1); break;
    case ST_BLE: oledBitmapMode(bitmap2, s); ledReset(2); break;
    case ST_WIFI: oledBitmapMode(bitmap3, s); ledReset(3); break;
    case ST_RC: oledBitmapMode(bitmap4, s); ledReset(4); break;
    default: oledTextMode(s); ledReset(s > 0 ? (s > 8 ? 8 : s) : 0); break;
  }
}

static void applyModeSideEffects(int s) {
  g_nrfTxHold = (s == ST_BLESCAN);
  if (s == ST_CSA1 || s == ST_CSA2) csaReloadMaps();
  labNowSend(LABNOW_MODE, stateName(s));
}

static void enterStateUi(int s) {
  if (g_uiState == s) {
    if (s == ST_IDLE) { if (oledDue()) oledIdle(); }
    else {
      ledService();
#if EDU_OLED_HUD
      if (oledDue()) showModeUi(s);
#endif
    }
    return;
  }
  g_uiState = s;
  Serial.println(stateName(s));
  saveMode(s);
  if (s >= ST_BT && s <= ST_CYCLE_MAX) {
    printModeEdu(s);
    applyModeSideEffects(s);
    portENTER_CRITICAL(&statsMux);
    covReset(); g_uniqueApprox = 0;
    portEXIT_CRITICAL(&statsMux);
  }
  showModeUi(s);
}

static void cycleMode() {
  int s = g_state;
  if (s < ST_BT || s > ST_CYCLE_MAX) s = ST_BT;
  else {
    s++;
    if (s > ST_CYCLE_MAX) s = ST_BT;
#if !ENABLE_BLE_SCAN
    if (s == ST_BLESCAN) s = ST_BT;
#endif
  }
  g_state = s;
  g_uiState = -1;
}

static void tryArmOnShortPress() {
#if REQUIRE_RF_ARM
  if (g_armed) return;
  uint32_t now = millis();
  if (g_armPresses == 0 || (now - g_armWindowStart) > (uint32_t)ARM_WINDOW_MS) {
    g_armPresses = 1;
    g_armWindowStart = now;
    Serial.printf("[ARM] %u/%d\n", (unsigned)g_armPresses, (int)ARM_PRESS_COUNT);
    return;
  }
  g_armPresses++;
  Serial.printf("[ARM] %u/%d\n", (unsigned)g_armPresses, (int)ARM_PRESS_COUNT);
  if (g_armPresses >= (uint8_t)ARM_PRESS_COUNT) {
    g_armed = true;
    g_armPresses = 0;
    g_pauseRf = false;
    if ((int)g_state == ST_IDLE) g_state = g_savedState >= ST_BT ? g_savedState : ST_BT;
    g_uiState = -1;
    Serial.println(F("[ARM] RF ARMED"));
    labNowSend(LABNOW_ARM, "ARMED");
  }
#endif
}

static void printStats() {
  if (g_statsMs == 0) return;
  uint32_t now = millis();
  if (now - g_lastStatsMs < g_statsMs) return;
  g_lastStatsMs = now;
  sampleVcc();
#if ENABLE_INA219
  if (g_inaOk) {
    Ina219Sample s = g_ina.read();
    if (s.ok) {
      g_busV = s.busV;
      g_currA = s.currentA;
      g_powerW = s.powerW;
    }
  }
  checkCurrentLimit();
#endif
  uint32_t hops = g_hopCount;
  uint32_t d = hops - g_lastHopSnap;
  g_lastHopSnap = hops;
  g_lastHopRate = (float)d * 1000.0f / (float)g_statsMs;
  int sep = (int)g_chH - (int)g_chV; if (sep < 0) sep = -sep;

  Serial.println(F("==== LAB ULTIMATE STATS ===="));
  Serial.printf("fw=%s %s armed=%d profile=%u\n", FW_BANNER, FW_VERSION,
                (int)g_armed, (unsigned)g_profile);
  Serial.printf("mode=%s\n", stateName((int)g_state));
  if ((int)g_state == ST_EXP)
    Serial.printf("exp step=%s submode=%s\n", g_expTag, stateName((int)g_expSubMode));
  if ((int)g_state == ST_COEXIST)
    Serial.printf("coexist_family=%s\n", ieeeModeLabel((int)g_coexistFamily));
  if ((int)g_state == ST_CSA1)
    Serial.printf("csa1_evt=%u prev=%u\n", (unsigned)g_csa1.eventCounter, (unsigned)g_csa1.prev);
  if ((int)g_state == ST_CSA2)
    Serial.printf("csa2_evt=%u CI=0x%04X\n", (unsigned)g_csa2.eventCounter, (unsigned)g_csa2.channelId);
  if ((int)g_state == ST_BLESCAN)
    Serial.printf("ble_devs=%lu best_rssi=%d\n", (unsigned long)g_bleDevices, g_bleBestRssi);
  Serial.printf("chH=%u chV=%u sep=%d hop/s≈%.0f unique≈%u\n",
                (unsigned)g_chH, (unsigned)g_chV, sep, g_lastHopRate, (unsigned)g_uniqueApprox);
  Serial.printf("hw=%s rate=%s heap=%u mk=%lu trips=%lu\n",
                hwName(), rateName(), (unsigned)ESP.getFreeHeap(),
                (unsigned long)g_markerSeq, (unsigned long)g_currentTrips);
  if (g_vccRail > 0.1f) Serial.printf("Vcc≈%.2fV\n", g_vccRail);
#if ENABLE_INA219
  if (g_inaOk)
    Serial.printf("INA219 bus=%.2fV I=%.3fA P=%.2fW lim=%.2fA\n",
                  g_busV, g_currA, g_powerW, CURRENT_LIMIT_A);
#endif

#if JSON_TELEMETRY
  Serial.printf(
      "{\"lab\":\"lab-ultimate\",\"fw\":\"%s\",\"mode\":%d,\"armed\":%d,"
      "\"chH\":%u,\"chV\":%u,\"hops\":%lu,\"hop_rate\":%.1f,\"unique\":%u,"
      "\"markers\":%lu,\"ble_n\":%lu,\"ble_rssi\":%d,\"heap\":%u,\"vcc\":%.2f,"
      "\"busV\":%.2f,\"currA\":%.3f,\"powerW\":%.2f,\"trips\":%lu}\n",
      FW_VERSION, (int)g_state, (int)g_armed,
      (unsigned)g_chH, (unsigned)g_chV, (unsigned long)hops, g_lastHopRate,
      (unsigned)g_uniqueApprox, (unsigned long)g_markerSeq,
      (unsigned long)g_bleDevices, g_bleBestRssi,
      (unsigned)ESP.getFreeHeap(), g_vccRail, g_busV, g_currA, g_powerW,
      (unsigned long)g_currentTrips);
#endif
#if CSV_TELEMETRY
  Serial.printf("CSV,%lu,%d,%u,%u,%.1f,%u,%.2f,%u,%d,%lu,%.2f,%.3f\n",
                (unsigned long)now, (int)g_state,
                (unsigned)g_chH, (unsigned)g_chV, g_lastHopRate,
                (unsigned)g_uniqueApprox, g_vccRail,
                (unsigned)ESP.getFreeHeap(), (int)g_armed, (unsigned long)g_markerSeq,
                g_busV, g_currA);
#endif
#if ENABLE_FILE_LOG && FILE_LOG_EVERY_STATS
  if (g_flog.ok()) {
    g_flog.logLine(now, (int)g_state, g_chH, g_chV, g_lastHopRate, g_uniqueApprox,
                   g_vccRail, ESP.getFreeHeap(), (int)g_armed, g_markerSeq,
                   g_busV, g_currA);
  }
#endif
  labNowSend(LABNOW_BEACON, "BEACON");
  Serial.println(F("============================"));
}

// ---- serial console ----
static void printHelp() {
  Serial.println(F("Commands:"));
  Serial.println(F("  help | m | arm | disarm | pause | resume | modes"));
  Serial.println(F("  fixed|slow|csa1|csa2|blescan|bt|ble|wifi|rc|154|coex|exp"));
  Serial.println(F("  exp0 | exp1         default / range playlists"));
  Serial.println(F("  map0 | map1 | ch H V | profile 0|1|2"));
  Serial.println(F("  duty ON OFF | stats MS | factory"));
  Serial.println(F("  logdump | logclear | status | save | web | ota"));
}

static void applyProfile(uint8_t p) {
  g_profile = p;
  switch (p) {
    case 0:  // original-like
      // hop strategy is compile-time; document intent
      Serial.println(F("[PROFILE] 0 ORIGINAL-like (use HOP_STRATEGY 0 rebuild for full)"));
      g_statsMs = 2000;
      break;
    case 1:  // edu default
      g_statsMs = 2000;
      Serial.println(F("[PROFILE] 1 EDU"));
      break;
    case 2:  // range
      g_statsMs = 1000;
      setFixedCh(FIXED_CH_H, FIXED_CH_V);
      setMode(ST_FIXED);
      Serial.println(F("[PROFILE] 2 RANGE → FIXED"));
      break;
    default:
      Serial.println(F("[PROFILE] unknown"));
      break;
  }
}

static void setMode(int s) {
  if (s < ST_BT || s > ST_CYCLE_MAX) return;
  g_state = s;
  g_pauseRf = false;
  g_uiState = -1;
#if ENABLE_EXPERIMENT
  if (s == ST_EXP) {
    if (!g_exp.steps) expInit(&g_exp, kDefaultExperiment, kDefaultExperimentN, true);
    expStart(&g_exp, millis());
    Serial.println(F("[EXP] started"));
  } else {
    expStop(&g_exp);
  }
#endif
}

static void setArmed(bool on) {
  if (on) {
    g_armed = true;
    g_pauseRf = false;
    if ((int)g_state == ST_IDLE) g_state = g_savedState >= ST_BT ? g_savedState : ST_BT;
    labNowSend(LABNOW_ARM, "ARMED");
  } else {
    g_armed = false;
    g_pauseRf = true;
    g_state = ST_IDLE;
    labNowSend(LABNOW_ARM, "DISARM");
  }
  g_uiState = -1;
}

static void setPaused(bool on) {
  if (on) {
    g_savedState = (g_state >= ST_BT && g_state <= ST_CYCLE_MAX) ? (int)g_state : ST_BT;
    g_state = ST_IDLE;
    g_pauseRf = true;
  } else {
    g_state = g_savedState;
    g_pauseRf = false;
  }
  g_uiState = -1;
}

static void saveSettings() {
#if ENABLE_NVS_SETTINGS
  prefs.putUChar("fxH", (uint8_t)g_fixedH);
  prefs.putUChar("fxV", (uint8_t)g_fixedV);
#if DUTY_RUNTIME_ENABLE
  prefs.putUInt("dutyOn", (uint32_t)g_dutyOnMs);
  prefs.putUInt("dutyOff", (uint32_t)g_dutyOffMs);
#endif
#endif
}

static void loadSettings() {
#if ENABLE_NVS_SETTINGS
  g_fixedH = prefs.getUChar("fxH", (uint8_t)FIXED_CH_H);
  g_fixedV = prefs.getUChar("fxV", (uint8_t)FIXED_CH_V);
#if DUTY_RUNTIME_ENABLE
  g_dutyOnMs = prefs.getUInt("dutyOn", (uint32_t)RANGE_DUTY_ON_MS);
  g_dutyOffMs = prefs.getUInt("dutyOff", (uint32_t)RANGE_DUTY_OFF_MS);
#endif
  Serial.printf("[NVS] fixed=%d/%d duty=%lu/%lu\n", g_fixedH, g_fixedV,
                (unsigned long)g_dutyOnMs, (unsigned long)g_dutyOffMs);
#endif
}

static void setFixedCh(int h, int v) {
  if (h < 0) h = 0; if (h > 125) h = 125;
  if (v < 0) v = h; if (v > 125) v = 125;
  g_fixedH = h;
  g_fixedV = v;
  saveSettings();
}

static void checkCurrentLimit() {
#if ENABLE_INA219 && CURRENT_LIMIT_ENABLE
  if (!g_inaOk || CURRENT_LIMIT_A <= 0.01f) return;
  if (g_currA > CURRENT_LIMIT_A) {
    g_overHits++;
    if (g_overHits >= (uint8_t)CURRENT_LIMIT_HITS) {
      g_overHits = 0;
      g_currentTrips++;
      Serial.printf("[PROTECT] overcurrent I=%.3fA > %.2fA — DISARM trip=%lu\n",
                    g_currA, CURRENT_LIMIT_A, (unsigned long)g_currentTrips);
      g_armed = false;
      g_pauseRf = true;
      g_state = ST_IDLE;
      g_uiState = -1;
      labNowSend(LABNOW_ARM, "I-TRIP");
    }
  } else {
    g_overHits = 0;
  }
#endif
}

static void handleSerialLine(char* line) {
  // trim
  while (*line == ' ' || *line == '\t') line++;
  char* e = line + strlen(line);
  while (e > line && (e[-1] == '\r' || e[-1] == '\n' || e[-1] == ' ')) *--e = 0;
  if (!line[0]) return;

  if (!strcasecmp(line, "help") || !strcasecmp(line, "?")) { printHelp(); return; }
  if (!strcasecmp(line, "m") || !strcasecmp(line, "marker")) { fireMarker(nullptr); return; }
  if (!strcasecmp(line, "arm")) {
    setArmed(true);
    Serial.println(F("[ARM] forced"));
    return;
  }
  if (!strcasecmp(line, "disarm")) {
    setArmed(false);
    Serial.println(F("[ARM] disarmed"));
    return;
  }
  if (!strcasecmp(line, "pause")) { setPaused(true); Serial.println(F("[BTN] pause")); return; }
  if (!strcasecmp(line, "resume")) { setPaused(false); Serial.println(F("[BTN] resume")); return; }
  if (!strcasecmp(line, "web") || !strcasecmp(line, "ota")) {
#if ENABLE_SOFTAP
    Serial.printf("[WEB] SSID=%s pass=%s → http://192.168.4.1/\n",
                  SOFTAP_SSID, SOFTAP_PASS);
#if ENABLE_WEB_OTA
    Serial.println(F("[OTA] http://192.168.4.1/ota  (upload .bin app image)"));
#endif
#else
    Serial.println(F("[WEB] disabled"));
#endif
    return;
  }
  if (!strcasecmp(line, "save")) {
    saveSettings();
    Serial.println(F("[NVS] saved"));
    return;
  }
  if (!strcasecmp(line, "factory")) {
    prefs.clear();
    g_fixedH = FIXED_CH_H;
    g_fixedV = FIXED_CH_V;
#if DUTY_RUNTIME_ENABLE
    g_dutyOnMs = RANGE_DUTY_ON_MS;
    g_dutyOffMs = RANGE_DUTY_OFF_MS;
#endif
    g_statsMs = EDU_STATS_MS;
    Serial.println(F("[NVS] factory reset — reboot recommended"));
    return;
  }
  if (!strcasecmp(line, "exp") || !strcasecmp(line, "exp0")) {
#if ENABLE_EXPERIMENT
    expInit(&g_exp, kDefaultExperiment, kDefaultExperimentN, true);
    setMode(ST_EXP);
#else
    Serial.println(F("[EXP] disabled"));
#endif
    return;
  }
  if (!strcasecmp(line, "exp1")) {
#if ENABLE_EXPERIMENT
    expInit(&g_exp, kRangeExperiment, kRangeExperimentN, true);
    setMode(ST_EXP);
#else
    Serial.println(F("[EXP] disabled"));
#endif
    return;
  }
  if (!strncasecmp(line, "profile ", 8)) {
    applyProfile((uint8_t)atoi(line + 8));
    return;
  }
  if (!strncasecmp(line, "stats ", 6)) {
    g_statsMs = (uint32_t)atoi(line + 6);
    Serial.printf("[STATS] interval=%lu ms (0=off)\n", (unsigned long)g_statsMs);
    return;
  }
  if (!strcasecmp(line, "logdump")) {
#if ENABLE_FILE_LOG
    g_flog.dumpTail(4096);
#else
    Serial.println(F("[LOG] disabled"));
#endif
    return;
  }
  if (!strcasecmp(line, "logclear")) {
#if ENABLE_FILE_LOG
    g_flog.clear();
    Serial.println(F("[LOG] cleared"));
#else
    Serial.println(F("[LOG] disabled"));
#endif
    return;
  }
  if (!strcasecmp(line, "status")) {
    Serial.printf("armed=%d pause=%d mode=%s ch=%u/%u hop=%.0f I=%.3fA\n",
                  (int)g_armed, (int)g_pauseRf, stateName((int)g_state),
                  (unsigned)g_chH, (unsigned)g_chV, g_lastHopRate, g_currA);
    return;
  }
  if (!strncasecmp(line, "duty ", 5)) {
#if DUTY_RUNTIME_ENABLE
    unsigned on = 0, off = 0;
    if (sscanf(line + 5, "%u %u", &on, &off) >= 1) {
      g_dutyOnMs = on;
      g_dutyOffMs = off;
      saveSettings();
      Serial.printf("[DUTY] on=%u off=%u ms (saved)\n", on, off);
    }
#else
    Serial.println(F("[DUTY] runtime disabled"));
#endif
    return;
  }
  if (!strcasecmp(line, "modes")) {
    for (int i = ST_BT; i <= ST_CYCLE_MAX; i++)
      Serial.printf("  %d %s\n", i, stateName(i));
    return;
  }
  if (!strcasecmp(line, "fixed")) { setMode(ST_FIXED); return; }
  if (!strcasecmp(line, "slow")) { setMode(ST_SLOW); return; }
  if (!strcasecmp(line, "csa1")) { setMode(ST_CSA1); return; }
  if (!strcasecmp(line, "csa2")) { setMode(ST_CSA2); return; }
  if (!strcasecmp(line, "blescan")) { setMode(ST_BLESCAN); return; }
  if (!strcasecmp(line, "exp")) { /* handled above */ }
  if (!strcasecmp(line, "bt")) { setMode(ST_BT); return; }
  if (!strcasecmp(line, "ble")) { setMode(ST_BLE); return; }
  if (!strcasecmp(line, "wifi")) { setMode(ST_WIFI); return; }
  if (!strcasecmp(line, "rc")) { setMode(ST_RC); return; }
  if (!strcasecmp(line, "154")) { setMode(ST_154); return; }
  if (!strcasecmp(line, "coex") || !strcasecmp(line, "coexist")) { setMode(ST_COEXIST); return; }
  if (!strcasecmp(line, "map0")) {
    // force preset all — re-init
    uint32_t lo, hi; csaMapAll(&lo, &hi);
    csa1Init(&g_csa1, (uint8_t)CSA1_HOP_INC, lo, hi);
    csa2Init(&g_csa2, (uint16_t)CSA2_CHANNEL_ID, lo, hi);
    Serial.println(F("[CSA] map=all-37"));
    return;
  }
  if (!strcasecmp(line, "map1")) {
    uint32_t lo, hi; csaMapAvoidWifi1611(&lo, &hi);
    csa1Init(&g_csa1, (uint8_t)CSA1_HOP_INC, lo, hi);
    csa2Init(&g_csa2, (uint16_t)CSA2_CHANNEL_ID, lo, hi);
    Serial.printf("[CSA] map=avoid-wifi nUsed=%u\n", (unsigned)g_csa1.nUsed);
    return;
  }
  if (!strncasecmp(line, "ch ", 3)) {
    int h = 0, v = 0;
    if (sscanf(line + 3, "%d %d", &h, &v) >= 1) {
      setFixedCh(h, v);
      Serial.printf("[FIXED runtime] H=%d V=%d (use FIXED mode)\n", g_fixedH, g_fixedV);
    }
    return;
  }
  Serial.printf("unknown cmd: %s (help)\n", line);
}

static void serviceSerial() {
  static char buf[96];
  static uint8_t n = 0;
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      buf[n] = 0;
      handleSerialLine(buf);
      n = 0;
    } else if (n < sizeof(buf) - 1) {
      buf[n++] = c;
    }
  }
}

// ---- BLE scan ----
#if ENABLE_BLE_SCAN
class LabAdvertised : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice d) override {
    g_bleDevices++;
    if (d.haveRSSI() && d.getRSSI() > g_bleBestRssi) g_bleBestRssi = d.getRSSI();
  }
};
static LabAdvertised g_bleCb;

static void runBleScanOnce() {
  static bool inited = false;
  if (!inited) {
    BLEDevice::init("LabUltimate");
    inited = true;
  }
  g_bleDevices = 0;
  g_bleBestRssi = -127;
  BLEScan* scan = BLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(&g_bleCb, false);
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(80);
  Serial.println(F("[BLE] scan start"));
  // Arduino-ESP32 2.x returns BLEScanResults by value; 3.x may differ — use count via callback
  scan->start(BLE_SCAN_TIME_SEC, false);
  Serial.printf("[BLE] done count≈%lu best_rssi=%d\n",
                (unsigned long)g_bleDevices, g_bleBestRssi);
  scan->clearResults();
}
#endif

// ---- RF ----
#if !REBUILD_SAFE
static bool beginOne(RF24& r, SPIClass& spi, const char* tag) {
  for (int i = 0; i < RADIO_BEGIN_RETRIES; i++) {
    if (r.begin(&spi)) {
      Serial.printf("[%s] begin OK try %d\n", tag, i + 1);
      return true;
    }
    delay(80);
  }
  Serial.printf("[%s] begin FAIL\n", tag);
  return false;
}
static void radioConfigure(RF24& r) {
  r.stopListening();
  r.powerUp();
  delayMicroseconds(1500);
  r.setAutoAck(false);
  r.setRetries(0, 0);
  r.setPALevel(paEnum(), RF_PA_LNA_ENABLE != 0);
  r.setDataRate(rateEnum());
  r.setCRCLength(RF24_CRC_DISABLED);
  r.startConstCarrier(paEnum(), INITIAL_CARRIER_CH);
}
static void radioStop(RF24& r) { r.stopConstCarrier(); r.powerDown(); }
static void radioRestart(RF24& r) {
  r.powerUp(); delayMicroseconds(1500);
  r.setPALevel(paEnum(), RF_PA_LNA_ENABLE != 0);
  r.setDataRate(rateEnum());
  r.startConstCarrier(paEnum(), INITIAL_CARRIER_CH);
}
static bool initRadios() {
  spiH.begin(PIN_SCK1, PIN_MISO1, PIN_MOSI1, PIN_CSN1);
  delay(RADIO_POWER_SETTLE_MS);
  spiV.begin(PIN_SCK2, PIN_MISO2, PIN_MOSI2, PIN_CSN2);
  delay(RADIO_POWER_SETTLE_MS);
  radioH_ok = beginOne(radioH, spiH, "HSPI");
  OrigSerialArt::printSep();
  if (radioH_ok) { OrigSerialArt::printHSPISuccess(); radioConfigure(radioH); }
  else OrigSerialArt::printHSPIFail();
  radioV_ok = beginOne(radioV, spiV, "VSPI");
  OrigSerialArt::printSep();
  if (radioV_ok) { OrigSerialArt::printVSPISuccess(); radioConfigure(radioV); }
  else OrigSerialArt::printVSPIFail();
  return radioH_ok || radioV_ok;
}

static void radioTask(void*) {
  initRadios();
  if (!g_armed || g_pauseRf || g_nrfTxHold) {
    portENTER_CRITICAL(&radioMux);
    if (radioH_ok) radioStop(radioH);
    if (radioV_ok) radioStop(radioV);
    portEXIT_CRITICAL(&radioMux);
  }

  uint32_t lastHealth = millis();
  uint32_t dutyMark = millis();
  bool dutyOn = true;
  g_dutyGate = true;
  uint32_t sliceMark = millis();
  uint32_t slowMark = millis();
  static const int kFam[] = { ST_BT, ST_BLE, ST_WIFI, ST_154 };
  int famIdx = 0;
  g_coexistFamily = kFam[0];
  g_slowCh = 0;

  for (;;) {
#if DUTY_RUNTIME_ENABLE
    {
      uint32_t don = g_dutyOnMs, doff = g_dutyOffMs;
      if (don > 0 && doff > 0) {
        uint32_t n = millis();
        if (dutyOn && n - dutyMark >= don) {
          dutyOn = false; dutyMark = n; g_dutyGate = false;
          portENTER_CRITICAL(&radioMux);
          if (radioH_ok) radioStop(radioH);
          if (radioV_ok) radioStop(radioV);
          portEXIT_CRITICAL(&radioMux);
        } else if (!dutyOn && n - dutyMark >= doff) {
          dutyOn = true; dutyMark = n; g_dutyGate = true;
          if (!g_pauseRf && g_armed && !g_nrfTxHold) {
            portENTER_CRITICAL(&radioMux);
            if (radioH_ok) radioRestart(radioH);
            if (radioV_ok) radioRestart(radioV);
            portEXIT_CRITICAL(&radioMux);
          }
        }
      } else {
        g_dutyGate = true;
      }
    }
#elif (RANGE_DUTY_ON_MS > 0) && (RANGE_DUTY_OFF_MS > 0)
    {
      uint32_t n = millis();
      if (dutyOn && n - dutyMark >= (uint32_t)RANGE_DUTY_ON_MS) {
        dutyOn = false; dutyMark = n; g_dutyGate = false;
        portENTER_CRITICAL(&radioMux);
        if (radioH_ok) radioStop(radioH);
        if (radioV_ok) radioStop(radioV);
        portEXIT_CRITICAL(&radioMux);
      } else if (!dutyOn && n - dutyMark >= (uint32_t)RANGE_DUTY_OFF_MS) {
        dutyOn = true; dutyMark = n; g_dutyGate = true;
        if (!g_pauseRf && g_armed && !g_nrfTxHold) {
          portENTER_CRITICAL(&radioMux);
          if (radioH_ok) radioRestart(radioH);
          if (radioV_ok) radioRestart(radioV);
          portEXIT_CRITICAL(&radioMux);
        }
      }
    }
#endif

    if (!g_armed || g_pauseRf || g_nrfTxHold) {
      portENTER_CRITICAL(&radioMux);
      if (radioH_ok) radioStop(radioH);
      if (radioV_ok) radioStop(radioV);
      portEXIT_CRITICAL(&radioMux);
      while (!g_armed || g_pauseRf || g_nrfTxHold)
        vTaskDelay(pdMS_TO_TICKS(PAUSE_POLL_MS));
      portENTER_CRITICAL(&radioMux);
      if (radioH_ok) radioRestart(radioH);
      if (radioV_ok) radioRestart(radioV);
      portEXIT_CRITICAL(&radioMux);
      dutyOn = true; g_dutyGate = true; dutyMark = millis();
    }

    if ((int)g_state == ST_COEXIST && g_armed && !g_pauseRf) {
      uint32_t n = millis();
      if (n - sliceMark >= (uint32_t)COEXIST_SLICE_MS) {
        sliceMark = n;
        famIdx = (famIdx + 1) % 4;
        g_coexistFamily = kFam[famIdx];
      }
    }

    if (((int)g_state == ST_SLOW || HOP_STRATEGY == 2) && g_armed && !g_pauseRf) {
      uint32_t n = millis();
      if (n - slowMark >= (uint32_t)SLOW_DWELL_MS) {
        slowMark = n;
        g_slowCh++;
        if (g_slowCh > (uint8_t)SLOW_SWEEP_MAX_CH) g_slowCh = 0;
      }
    }

    uint32_t now = millis();
    if (now - lastHealth >= RADIO_HEALTH_MS && g_armed && !g_pauseRf && !g_nrfTxHold) {
      lastHealth = now;
      if (radioH_ok && !radioH.isChipConnected()) {
        radioH_ok = beginOne(radioH, spiH, "HSPI");
        if (radioH_ok) radioConfigure(radioH);
      }
      if (radioV_ok && !radioV.isChipConnected()) {
        radioV_ok = beginOne(radioV, spiV, "VSPI");
        if (radioV_ok) radioConfigure(radioV);
      }
    }

    int st = (int)g_state;
#if ENABLE_EXPERIMENT
    if (st == ST_EXP) st = (int)g_expSubMode;
#endif
    if (st >= ST_BT && st <= ST_CYCLE_MAX && st != ST_BLESCAN && st != ST_EXP &&
        g_armed && !g_pauseRf && g_dutyGate && !g_nrfTxHold) {
      uint32_t batch = HOP_BATCH;
      if (st == ST_FIXED || st == ST_SLOW || st == ST_CSA1 || st == ST_CSA2 ||
          HOP_STRATEGY == 2 || HOP_STRATEGY == 3)
        batch = 1;

      // FIXED uses runtime ch if set via serial
      if (st == ST_FIXED) {
        uint8_t chH = (uint8_t)g_fixedH;
        uint8_t chV = (uint8_t)g_fixedV;
        if (radioH_ok) radioH.setChannel(chH);
        if (radioV_ok) radioV.setChannel(chV);
        noteHop(chH, chV);
      } else {
        for (uint32_t i = 0; i < batch; i++) {
          uint8_t chH = pickChannel(st, true, 0xFF);
          uint8_t chV = pickChannel(st, false, chH);
          if (radioH_ok) radioH.setChannel(chH);
          if (radioV_ok) radioV.setChannel(chV);
          noteHop(chH, chV);
        }
      }
    }

    uint32_t delayMs = HOP_DELAY_MS;
    if (st == ST_SLOW || HOP_STRATEGY == 2) delayMs = 20;
    if (st == ST_FIXED || HOP_STRATEGY == 3) delayMs = 50;
    if (st == ST_CSA1 || st == ST_CSA2) delayMs = CSA_DWELL_MS;
    vTaskDelay(pdMS_TO_TICKS(delayMs));
#if ENABLE_WATCHDOG
    esp_task_wdt_reset();
#endif
  }
}
#else
static void radioTask(void*) {
  for (;;) {
    int st = (int)g_state;
    if (st >= ST_BT && st <= ST_CYCLE_MAX && st != ST_BLESCAN && !g_pauseRf) {
      uint8_t a = pickChannel(st, true, 0xFF);
      uint8_t b = pickChannel(st, false, a);
      noteHop(a, b);
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}
#endif

static void serviceButton() {
  const bool raw = (digitalRead(PIN_BOOT) == LOW);
  const uint32_t now = millis();
  if (raw != btnRawPrev) { btnRawPrev = raw; btnChangeMs = now; }
  if (now - btnChangeMs < DEBOUNCE_MS) return;

  if (raw && !btnStable) {
    btnStable = true; btnLongDone = false; btnDownMs = now;
  } else if (raw && btnStable && !btnLongDone && g_armed && !g_pauseRf) {
    if (now - btnDownMs >= LONG_PRESS_MS) {
      btnLongDone = true;
      g_savedState = (g_state >= ST_BT && g_state <= ST_CYCLE_MAX) ? (int)g_state : ST_BT;
      g_state = ST_IDLE; g_pauseRf = true; g_uiState = -1;
      Serial.println(F("[BTN] pause"));
    }
  } else if (!raw && btnStable) {
    uint32_t held = now - btnDownMs;
    btnStable = false;
    if (btnLongDone) {
    } else if (held < LONG_PRESS_MS) {
      if (!g_armed) {
        tryArmOnShortPress();
        g_uiState = -1;
      } else if (g_pauseRf) {
        g_state = g_savedState; g_pauseRf = false; g_uiState = -1;
        Serial.println(F("[BTN] resume"));
      } else {
        // Double-tap → marker; single → next mode
        if (g_doubleTapArmed && (now - g_lastShortMs) < 400) {
          g_doubleTapArmed = 0;
          fireMarker(nullptr);
        } else {
          g_doubleTapArmed = 1;
          g_lastShortMs = now;
          // defer mode cycle slightly — handled below if no second tap
        }
      }
    }
    btnLongDone = false;
  }

  // Complete single-tap mode change after double-tap window
  if (g_doubleTapArmed && g_armed && !g_pauseRf &&
      (millis() - g_lastShortMs) >= 400) {
    g_doubleTapArmed = 0;
    if ((int)g_state == ST_IDLE) { g_state = ST_BT; g_uiState = -1; }
    else cycleMode();
    Serial.println(F("[BTN] next mode"));
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(40);
  g_bootMs = millis();
  // g_fixedH/V loaded from NVS after prefs.begin (defaults until then)
  csaReloadMaps();

  Serial.println(F("\n=== Lab Ultimate TX v0.5 ==="));
  Serial.printf("fw=%s %s\n", FW_BANNER, FW_VERSION);
  Serial.println(F("ROI5: EXP sequencer | profiles | WDT | NOW-RX | factory | stats"));
  Serial.printf("engine=%d hw=%s rate=%s safe=%d reset=%s\n",
                (int)LAB_ENGINE, hwName(), rateName(), (int)REBUILD_SAFE, resetReasonStr());

#if CSV_TELEMETRY
  Serial.println(F("CSV_HEADER,t_ms,mode,chH,chV,hop_rate,unique,vcc,heap,armed,markers,busV,currA"));
#endif

  pinMode(PIN_LED, OUTPUT); digitalWrite(PIN_LED, LOW);
  pinMode(PIN_BOOT, INPUT_PULLUP);
#if VCC_SENSE_PIN < 255
  analogReadResolution(12);
#endif

  prefs.begin("labult", false);
  g_bootCount = prefs.getUInt("boots", 0) + 1;
  prefs.putUInt("boots", g_bootCount);
  Serial.printf("[BOOT] count=%lu reason=%s\n", (unsigned long)g_bootCount, resetReasonStr());
  loadSettings();
  g_state = loadMode();
  if ((int)g_state < ST_BT || (int)g_state > ST_CYCLE_MAX) g_state = INITIAL_STATE;
  g_savedState = (int)g_state;
#if ENABLE_EXPERIMENT
  expInit(&g_exp, kDefaultExperiment, kDefaultExperimentN, true);
#endif

#if ENABLE_WATCHDOG
  esp_task_wdt_config_t wdtcfg = {
      .timeout_ms = (uint32_t)WDT_TIMEOUT_S * 1000u,
      .idle_core_mask = 0,
      .trigger_panic = true,
  };
  esp_task_wdt_reconfigure(&wdtcfg);
  esp_task_wdt_add(NULL);  // loop task
  Serial.printf("[WDT] %ds\n", (int)WDT_TIMEOUT_S);
#endif

#if REQUIRE_RF_ARM
  g_armed = false;
  g_pauseRf = true;
  Serial.println(F("*** RF DISARMED *** 3x short BOOT to arm | serial: arm | web /arm"));
#else
  g_armed = true;
#endif

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(400000);

#if ENABLE_INA219
  g_inaOk = g_ina.begin();
  Serial.printf("[INA219] %s @0x%02X\n", g_inaOk ? "OK" : "not found (optional)",
                (unsigned)INA219_ADDR);
#endif

#if ENABLE_FILE_LOG
  if (g_flog.begin()) Serial.println(F("[LOG] LittleFS /labult.csv OK"));
  else Serial.println(F("[LOG] LittleFS FAIL"));
#endif

#if ENABLE_ESPNOW
  g_espnowOk = labNowInit();
#elif ENABLE_SOFTAP
  WiFi.mode(WIFI_AP);
#endif

#if ENABLE_SOFTAP
  g_webHooks.stateName = stateName;
  g_webHooks.getState = []() -> int { return (int)g_state; };
  g_webHooks.setMode = setMode;
  g_webHooks.getArmed = []() -> bool { return g_armed; };
  g_webHooks.arm = setArmed;
  g_webHooks.marker = []() { fireMarker(nullptr); };
  g_webHooks.pause = setPaused;
  g_webHooks.getPause = []() -> bool { return g_pauseRf; };
  g_webHooks.chH = []() -> uint8_t { return g_chH; };
  g_webHooks.chV = []() -> uint8_t { return g_chV; };
  g_webHooks.setFixed = setFixedCh;
  g_webHooks.hopRate = []() -> float { return g_lastHopRate; };
  g_webHooks.hops = []() -> uint32_t { return g_hopCount; };
  g_webHooks.unique = []() -> uint16_t { return g_uniqueApprox; };
  g_webHooks.vcc = []() -> float { return g_vccRail; };
  g_webHooks.busV = []() -> float { return g_busV; };
  g_webHooks.currA = []() -> float { return g_currA; };
  g_webHooks.markers = []() -> uint32_t { return g_markerSeq; };
  g_webHooks.heap = []() -> uint32_t { return ESP.getFreeHeap(); };
  g_webHooks.trips = []() -> uint32_t { return g_currentTrips; };
  g_webHooks.fwVersion = FW_VERSION;
  g_webHooks.hwName = hwName();
  g_webHooks.rateName = rateName();
  static LabWeb web(&g_webHooks);
  g_web = &web;
  g_web->begin(SOFTAP_SSID, SOFTAP_PASS, SOFTAP_CHANNEL);
  Serial.println(F("[WEB] portal http://192.168.4.1/  OTA /ota"));
#endif

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 fail"));
    while (true) delay(1000);
  }
  oledSplash();
  delay(SPLASH_MS);
  OrigSerialArt::printSep();
  OrigSerialArt::printBootBanner();

  xTaskCreatePinnedToCore(radioTask, "RadioTask", RADIO_TASK_STACK, nullptr,
                          RADIO_TASK_PRIO, nullptr, RADIO_TASK_CORE);

  Serial.println(F("Modes: … CSA1 CSA2 BLESCAN EXP | exp0 exp1 | profile 0-2"));
  Serial.println(F("dbl BOOT=MARKER | serial help | phone→LabUltimate Wi-Fi"));
  printHelp();
}

void loop() {
  serviceSerial();
  serviceButton();
#if ENABLE_SOFTAP
  if (g_web) g_web->loop();
#endif

#if ENABLE_EXPERIMENT
  if (g_armed && !g_pauseRf && (int)g_state == ST_EXP && g_exp.running) {
    uint8_t md = 0, h = 0, v = 0;
    const char* tag = "-";
    bool changed = expTick(&g_exp, millis(), &md, &h, &v, &tag);
    g_expSubMode = md;
    g_expTag = tag;
    if (md == ST_FIXED) {
      g_fixedH = h;
      g_fixedV = v;
    }
    if (changed) {
      Serial.printf("[EXP] → %s mode=%s ch=%u/%u\n", tag, stateName(md),
                    (unsigned)h, (unsigned)v);
      g_uiState = -1;
      labNowSend(LABNOW_MODE, tag);
      // Apply CSA map reloads when entering CSA steps
      if (md == ST_CSA1 || md == ST_CSA2) csaReloadMaps();
      g_nrfTxHold = (md == ST_BLESCAN);
    }
  }
#endif

#if ENABLE_BLE_SCAN
  static uint32_t lastBle = 0;
  int bleMode = (int)g_state;
#if ENABLE_EXPERIMENT
  if (bleMode == ST_EXP) bleMode = (int)g_expSubMode;
#endif
  if (g_armed && !g_pauseRf && bleMode == ST_BLESCAN) {
    if (millis() - lastBle >= (uint32_t)BLE_SCAN_INTERVAL_MS) {
      lastBle = millis();
      g_nrfTxHold = true;
      runBleScanOnce();
    }
  }
#endif

  if (!g_armed) enterStateUi(ST_IDLE);
  else enterStateUi((int)g_state);
  printStats();
#if ENABLE_WATCHDOG
  esp_task_wdt_reset();
#endif
  delay(5);
}
