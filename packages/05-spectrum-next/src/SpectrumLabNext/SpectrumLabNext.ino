/*
 * SpectrumLab Next (IEEE NextLab)
 * --------------------------------
 * Next-generation educational dual-nRF24 firmware informed by:
 *  - IEEE 802.11ax / 802.11be 2.4 GHz channelization & coexistence notes
 *  - Bluetooth Core Spec advertising map
 *  - IEEE 802.15.4-2020 2.4 GHz channel set (Zigbee/Thread family)
 *  - Dual-core FreeRTOS + PA hardware profiles + lab telemetry
 *
 * Same BlueJammer-class pinout for drop-in lab boards.
 * Modes: Idle, BT, BLE, 802.11, RC, 802.15.4, IEEE coexist scheduler.
 *
 * LEGAL: Continuous-carrier RF can be unlawful interference.
 * Authorized / shielded education only. Prefer REBUILD_SAFE=1.
 *
 * Docs: research/IEEE_RESEARCH.md, docs/NEXTLAB_LEARNING.md, hardware/
 */

#include "config.h"
#include "ieee_maps.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Preferences.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp_system.h>
#include <string.h>

#if !REBUILD_SAFE
#include <RF24.h>
#include <nRF24L01.h>
#endif

#include "bitmaps.h"
#include "OrigSerialArt.h"

static const uint8_t PIN_CE1 = 16, PIN_CSN1 = 15, PIN_SCK1 = 14, PIN_MISO1 = 12, PIN_MOSI1 = 13;
static const uint8_t PIN_CE2 = 22, PIN_CSN2 = 21, PIN_SCK2 = 18, PIN_MISO2 = 19, PIN_MOSI2 = 23;
static const uint8_t PIN_LED = 27;
static const uint8_t PIN_BOOT = 0;
static const uint8_t PIN_SDA = 4, PIN_SCL = 5;
static const uint8_t OLED_ADDR = 0x3C;

static const uint32_t SERIAL_BAUD = 115200;
static const uint32_t SPLASH_MS = 1800;
static const uint32_t LONG_PRESS_MS = 500;
static const uint32_t DEBOUNCE_MS = 30;
static const uint32_t LED_PULSE_MS = 150;
static const uint32_t LED_GAP_MS = 1000;
static const uint32_t PAUSE_POLL_MS = 10;
static const uint32_t RADIO_HEALTH_MS = 4000;

// Modes
enum : int {
  ST_IDLE = 0,
  ST_BT = 1,
  ST_BLE = 2,
  ST_WIFI = 3,
  ST_RC = 4,
  ST_154 = 5,      // IEEE 802.15.4
  ST_COEXIST = 6,  // multi-standard time slices
  ST_MODE_MAX = 6
};

#if LAB_ENGINE == 0
static const int ST_CYCLE_MAX = ST_RC;
#else
static const int ST_CYCLE_MAX = ST_COEXIST;
#endif

volatile int  g_state = INITIAL_STATE;
volatile bool g_pauseRf = false;
volatile bool g_dutyGate = true;
volatile int  g_coexistFamily = 1;  // active family inside COEXIST

volatile uint8_t  g_chH = 0, g_chV = 0;
volatile uint32_t g_hopCount = 0;
volatile uint16_t g_uniqueApprox = 0;
volatile float    g_vccRail = 0.0f;

static int g_uiState = -1;
static int g_savedState = ST_BT;
static uint32_t g_lastOledMs = 0;
static uint32_t g_lastStatsMs = 0;
static uint32_t g_lastHopSnap = 0;
static uint32_t g_covBits[4] = {0};
static portMUX_TYPE statsMux = portMUX_INITIALIZER_UNLOCKED;

static uint8_t g_ledOn = 0;
static int g_ledCount = 0, g_ledTarget = 0;
static uint32_t g_ledTs = 0;

static bool btnStable = false, btnRawPrev = false, btnLongDone = false;
static uint32_t btnChangeMs = 0, btnDownMs = 0;

static uint16_t g_idxH = 0, g_idxV = 0;
static uint32_t g_bootMs = 0;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Preferences prefs;

#if !REBUILD_SAFE
static SPIClass spiH(HSPI);
static SPIClass spiV(VSPI);
static RF24 radioH(PIN_CE1, PIN_CSN1, RF24_SPI_HZ);
static RF24 radioV(PIN_CE2, PIN_CSN2, RF24_SPI_HZ);
static bool radioH_ok = false, radioV_ok = false;
static portMUX_TYPE radioMux = portMUX_INITIALIZER_UNLOCKED;
#endif

static inline uint8_t hwRandMod(uint8_t m) {
  return m ? (uint8_t)(esp_random() % m) : 0;
}

static const char* stateName(int s) {
  switch (s) {
    case ST_IDLE: return "Idle & Status";
    case ST_BT: return "BT classic (edu AFH grid)";
    case ST_BLE: return "BLE Core Spec (adv+data)";
    case ST_WIFI: return "IEEE 802.11 2.4 GHz";
    case ST_RC: return "ISM / RC wide grid";
    case ST_154: return "IEEE 802.15.4 (Zigbee/Thread map)";
    case ST_COEXIST: return "IEEE coexist multi-sched";
    default: return "?";
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
  for (int i = 0; i < 4; i++) {
#if defined(__GNUC__)
    n += (uint16_t)__builtin_popcount(g_covBits[i]);
#else
    uint32_t v = g_covBits[i];
    while (v) { n += (uint16_t)(v & 1u); v >>= 1; }
#endif
  }
  return n;
}
static void covReset() { memset(g_covBits, 0, sizeof(g_covBits)); }

// Pick channel for one "family" used by modes and coexist slices
static uint8_t pickFamily(int family, bool isH, uint8_t peer) {
  uint8_t ch = 0;
  uint8_t fullMod = 126;

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
      // Heavy weight on advertising channels (scanner-visible lesson)
      if ((esp_random() % 100) < 45) {
        ch = IEEE_BLE_ADV[esp_random() % IEEE_BLE_ADV_N];
      } else if ((esp_random() % 100) < HOP_PRIORITY_PCT) {
        ch = IEEE_BLE_DATA[esp_random() % IEEE_BLE_DATA_N];
      } else ch = hwRandMod(fullMod);
      break;
    }
    case ST_WIFI: {
      fullMod = 83;
      // IEEE teaching: non-overlapping 1/6/11 dominate in real BSS planning
      if ((esp_random() % 100) < WIFI_NOLAP_WEIGHT_PCT) {
        ch = IEEE_WIFI_NOLAP[esp_random() % IEEE_WIFI_NOLAP_N];
      } else if ((esp_random() % 100) < 50) {
        ch = IEEE_WIFI_ALL[esp_random() % IEEE_WIFI_ALL_N];
      } else {
        ch = IEEE_WIFI_DENSE[esp_random() % IEEE_WIFI_DENSE_N];
      }
      break;
    }
    case ST_154: {
      fullMod = 81;
      if ((esp_random() % 100) < HOP_PRIORITY_PCT) {
        ch = IEEE_154_PREFERRED[esp_random() % IEEE_154_PREFERRED_N];
      } else {
        ch = IEEE_154_CH[esp_random() % IEEE_154_CH_N];
      }
      break;
    }
    case ST_RC:
    default: {
      fullMod = IEEE_RC_FULL_MOD;
      if ((esp_random() % 100) < HOP_PRIORITY_PCT) {
        ch = IEEE_RC_GRID[esp_random() % IEEE_RC_GRID_N];
      } else ch = hwRandMod(fullMod);
      break;
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
  if (state == ST_COEXIST) {
    return pickFamily((int)g_coexistFamily, isH, peer);
  }
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
  Serial.println(F("---- IEEE NextLab mode ----"));
  Serial.printf("mode=%s (%s)\n", stateName(s), ieeeModeLabel(s));
  Serial.printf("hw=%s rate=%s engine=%d sep>=%u\n",
                hwName(), rateName(), (int)LAB_ENGINE, (unsigned)DUAL_MIN_SEPARATION);
  switch (s) {
    case ST_WIFI:
      Serial.println(F("802.11: centers ch1-13; weight on non-overlap 1/6/11"));
      Serial.println(F("802.11ax/be keep 2.4 GHz channelization; denser BSS use OFDMA"));
      break;
    case ST_BLE:
      Serial.println(F("BLE adv 2402/2426/2480 MHz = nRF 2/26/80 (Core Spec)"));
      break;
    case ST_BT:
      Serial.println(F("BT classic edu grid across 79×1 MHz slots"));
      break;
    case ST_154:
      Serial.println(F("802.15.4 ch11-26 → nRF 5,10,...,80 (Zigbee/Thread map)"));
      break;
    case ST_COEXIST:
      Serial.println(F("Time-sliced BT/BLE/802.11/802.15.4 — coexistence lesson"));
      Serial.println(F("IEEE docs stress CCA/CSMA; we demo spectral family rotation"));
      break;
    case ST_RC:
      Serial.println(F("Wide ISM 0..125 educational grid"));
      break;
    default: break;
  }
  Serial.println(F("---------------------------"));
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

// ---- OLED ----
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
  display.println(F("SpectrumLab Next"));
  display.setCursor(0, 12);
  display.println(stateName(mode));
  display.setCursor(0, 28);
  display.printf("IEEE map: %s", ieeeModeLabel(mode));
  display.setCursor(0, 40);
  display.printf("H%u V%u %s", (unsigned)g_chH, (unsigned)g_chV, rateName());
  display.setCursor(0, 52);
  display.printf("%s eng%d", hwName(), (int)LAB_ENGINE);
  display.display();
}

static void oledBitmapMode(const uint8_t* bmp, int mode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  const char* t = "IEEE NextLab";
  int16_t x1, y1; uint16_t tw, th;
  display.getTextBounds(t, 0, 0, &x1, &y1, &tw, &th);
  display.setCursor((int16_t)((128 - tw) / 2), 2);
  display.print(t);
  display.drawBitmap(0, 12, bmp, 128, 50, SSD1306_WHITE);
#if EDU_OLED_HUD
  display.fillRect(0, 56, 128, 8, SSD1306_BLACK);
  display.setCursor(0, 56);
  display.printf("H%u V%u %s", (unsigned)g_chH, (unsigned)g_chV, rateName());
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
  display.printf("NextLab %s", hwName());
  display.setCursor(0, 22);
  display.printf("ch H=%u V=%u", (unsigned)g_chH, (unsigned)g_chV);
  display.setCursor(0, 32);
  display.printf("hops=%lu u~%u", (unsigned long)g_hopCount, (unsigned)g_uniqueApprox);
  display.setCursor(0, 42);
  display.printf("heap=%u %s", (unsigned)ESP.getFreeHeap(), rateName());
  display.setCursor(0, 54);
  if (g_pauseRf) display.print(F("[RF PAUSED]"));
  else if (!g_dutyGate) display.print(F("[DUTY OFF]"));
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
    case ST_154: oledTextMode(s); ledReset(5); break;
    case ST_COEXIST: oledTextMode(s); ledReset(6); break;
    default: ledReset(0); oledIdle(); break;
  }
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
  }
  g_state = s;
  g_uiState = -1;
}

static void printStats() {
#if EDU_STATS_MS > 0
  uint32_t now = millis();
  if (now - g_lastStatsMs < (uint32_t)EDU_STATS_MS) return;
  g_lastStatsMs = now;
  sampleVcc();
  uint32_t hops = g_hopCount;
  uint32_t d = hops - g_lastHopSnap;
  g_lastHopSnap = hops;
  float rate = (float)d * 1000.0f / (float)EDU_STATS_MS;
  int sep = (int)g_chH - (int)g_chV; if (sep < 0) sep = -sep;

  Serial.println(F("==== IEEE NEXTLAB STATS ===="));
  Serial.printf("mode=%s family=%s\n", stateName((int)g_state), ieeeModeLabel((int)g_state));
  if ((int)g_state == ST_COEXIST)
    Serial.printf("coexist_slice_family=%s\n", ieeeModeLabel((int)g_coexistFamily));
  Serial.printf("chH=%u chV=%u sep=%d hop/s≈%.0f unique≈%u\n",
                (unsigned)g_chH, (unsigned)g_chV, sep, rate, (unsigned)g_uniqueApprox);
  Serial.printf("hw=%s rate=%s heap=%u uptime=%lus\n",
                hwName(), rateName(), (unsigned)ESP.getFreeHeap(),
                (unsigned long)((now - g_bootMs) / 1000UL));
  if (g_vccRail > 0.1f) Serial.printf("Vcc≈%.2fV\n", g_vccRail);

#if JSON_TELEMETRY
  // Machine-readable line for lab notebooks / Python parsers
  Serial.printf(
      "{\"lab\":\"ieee-nextlab\",\"mode\":%d,\"label\":\"%s\",\"chH\":%u,\"chV\":%u,"
      "\"hops\":%lu,\"hop_rate\":%.1f,\"unique\":%u,\"heap\":%u,\"rate\":\"%s\",\"hw\":\"%s\"}\n",
      (int)g_state, ieeeModeLabel((int)g_state), (unsigned)g_chH, (unsigned)g_chV,
      (unsigned long)hops, rate, (unsigned)g_uniqueApprox, (unsigned)ESP.getFreeHeap(),
      rateName(), hwName());
#endif
  Serial.println(F("============================"));
#endif
}

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
  uint32_t lastHealth = millis();
  uint32_t dutyMark = millis();
  bool dutyOn = true;
  g_dutyGate = true;
  uint32_t sliceMark = millis();
  // Coexist family rotation: BT → BLE → WIFI → 154
  static const int kFam[] = { ST_BT, ST_BLE, ST_WIFI, ST_154 };
  int famIdx = 0;
  g_coexistFamily = kFam[0];

  for (;;) {
#if (RANGE_DUTY_ON_MS > 0) && (RANGE_DUTY_OFF_MS > 0)
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
        if (!g_pauseRf) {
          portENTER_CRITICAL(&radioMux);
          if (radioH_ok) radioRestart(radioH);
          if (radioV_ok) radioRestart(radioV);
          portEXIT_CRITICAL(&radioMux);
        }
      }
    }
#endif

    if (g_pauseRf) {
      portENTER_CRITICAL(&radioMux);
      if (radioH_ok) radioStop(radioH);
      if (radioV_ok) radioStop(radioV);
      portEXIT_CRITICAL(&radioMux);
      while (g_pauseRf) vTaskDelay(pdMS_TO_TICKS(PAUSE_POLL_MS));
      portENTER_CRITICAL(&radioMux);
      if (radioH_ok) radioRestart(radioH);
      if (radioV_ok) radioRestart(radioV);
      portEXIT_CRITICAL(&radioMux);
      dutyOn = true; g_dutyGate = true; dutyMark = millis();
    }

    // Coexist time slices
    if ((int)g_state == ST_COEXIST && !g_pauseRf) {
      uint32_t n = millis();
      if (n - sliceMark >= (uint32_t)COEXIST_SLICE_MS) {
        sliceMark = n;
        famIdx = (famIdx + 1) % 4;
        g_coexistFamily = kFam[famIdx];
      }
    }

    uint32_t now = millis();
    if (now - lastHealth >= RADIO_HEALTH_MS && !g_pauseRf) {
      lastHealth = now;
      if (radioH_ok && !radioH.isChipConnected()) {
        Serial.println(F("[HSPI] reinit"));
        radioH_ok = beginOne(radioH, spiH, "HSPI");
        if (radioH_ok) radioConfigure(radioH);
      }
      if (radioV_ok && !radioV.isChipConnected()) {
        Serial.println(F("[VSPI] reinit"));
        radioV_ok = beginOne(radioV, spiV, "VSPI");
        if (radioV_ok) radioConfigure(radioV);
      }
    }

    int st = (int)g_state;
    if (st >= ST_BT && st <= ST_CYCLE_MAX && !g_pauseRf && g_dutyGate) {
      for (uint32_t i = 0; i < HOP_BATCH; i++) {
        uint8_t chH = pickChannel(st, true, 0xFF);
        uint8_t chV = pickChannel(st, false, chH);
        if (radioH_ok) radioH.setChannel(chH);
        if (radioV_ok) radioV.setChannel(chV);
        noteHop(chH, chV);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(HOP_DELAY_MS));
  }
}
#else
static void radioTask(void*) {
  Serial.println(F("[SAFE] no RF TX — IEEE hop sim"));
  OrigSerialArt::printHSPIFail();
  OrigSerialArt::printVSPIFail();
  uint32_t sliceMark = millis();
  static const int kFam[] = { ST_BT, ST_BLE, ST_WIFI, ST_154 };
  int famIdx = 0;
  g_coexistFamily = kFam[0];
  for (;;) {
    if ((int)g_state == ST_COEXIST) {
      uint32_t n = millis();
      if (n - sliceMark >= (uint32_t)COEXIST_SLICE_MS) {
        sliceMark = n; famIdx = (famIdx + 1) % 4; g_coexistFamily = kFam[famIdx];
      }
    }
    int st = (int)g_state;
    if (st >= ST_BT && st <= ST_CYCLE_MAX && !g_pauseRf) {
      uint8_t a = pickChannel(st, true, 0xFF);
      uint8_t b = pickChannel(st, false, a);
      noteHop(a, b);
    }
    vTaskDelay(pdMS_TO_TICKS(5));
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
  } else if (raw && btnStable && !btnLongDone && !g_pauseRf) {
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
    } else if (g_pauseRf && held < LONG_PRESS_MS) {
      g_state = g_savedState; g_pauseRf = false; g_uiState = -1;
      Serial.println(F("[BTN] resume"));
    } else if (!g_pauseRf && held < LONG_PRESS_MS) {
      if ((int)g_state == ST_IDLE) { g_state = ST_BT; g_uiState = -1; }
      else cycleMode();
      Serial.println(F("[BTN] next mode"));
    }
    btnLongDone = false;
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(40);
  g_bootMs = millis();
  Serial.println(F("\n=== SpectrumLab Next / IEEE NextLab ==="));
  Serial.println(F("802.11 + BLE + 802.15.4 informed educational dual-nRF24"));
  Serial.printf("engine=%d hw=%s rate=%s\n", (int)LAB_ENGINE, hwName(), rateName());

  pinMode(PIN_LED, OUTPUT); digitalWrite(PIN_LED, LOW);
  pinMode(PIN_BOOT, INPUT_PULLUP);
#if VCC_SENSE_PIN < 255
  analogReadResolution(12);
#endif
  prefs.begin("nextlab", false);
  g_state = loadMode();
  if ((int)g_state < ST_BT || (int)g_state > ST_CYCLE_MAX) g_state = INITIAL_STATE;

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(400000);
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

  Serial.println(F("Modes: BT BLE 802.11 RC 802.15.4 COEXIST | docs in package"));
#if REBUILD_SAFE
  Serial.println(F("REBUILD_SAFE=1"));
#endif
}

void loop() {
  serviceButton();
  enterStateUi((int)g_state);
  printStats();
  delay(5);
}
