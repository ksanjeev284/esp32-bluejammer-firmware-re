/*
 * ComboChannelSelect Pro
 * ---------------------
 * Optimized + effectiveness-tuned rebuild from RE of
 * Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin (ESP32-BlueJammer combo).
 *
 * Runtime reliability:
 *  - Dual-core RadioTask / UI split, SPI 10 MHz default, begin retries
 *  - Health re-init, debounced button, OLED frame limit, NVS mode
 *  - Clean RF pause (stop carrier + powerDown)
 *
 * Educational effectiveness (see EFFECTIVENESS.md):
 *  - Protocol-aware hop maps (BT / BLE adv / real Wi-Fi centers / RC grid)
 *  - Complementary dual-nRF24 (two different channels every hop)
 *  - Priority + fill mix, optional deterministic SWEEP for lab/SDR
 *  - Serial lab stats + OLED live channel HUD
 *
 * LEGAL: RF continuous-carrier on 2.4 GHz can be unlawful interference.
 * Authorized / shielded lab education only. Prefer REBUILD_SAFE=1 for UI.
 */

#include "config.h"
#include "hop_maps.h"

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

// ---- Pins (from original firmware RE) ----
static const uint8_t PIN_CE1 = 16, PIN_CSN1 = 15, PIN_SCK1 = 14, PIN_MISO1 = 12, PIN_MOSI1 = 13;
static const uint8_t PIN_CE2 = 22, PIN_CSN2 = 21, PIN_SCK2 = 18, PIN_MISO2 = 19, PIN_MOSI2 = 23;
static const uint8_t PIN_LED = 27;
static const uint8_t PIN_BOOT = 0;
static const uint8_t PIN_SDA = 4, PIN_SCL = 5;
static const uint8_t OLED_ADDR = 0x3C;

static const uint32_t SERIAL_BAUD = 115200;
static const uint32_t SPLASH_MS = 2000;
static const uint32_t LONG_PRESS_MS = 500;
static const uint32_t DEBOUNCE_MS = 30;
static const uint32_t LED_PULSE_MS = 150;
static const uint32_t LED_GAP_MS = 1000;
static const uint32_t PAUSE_POLL_MS = 10;
static const uint32_t RADIO_HEALTH_MS = 5000;

// Legacy moduli (strategy ORIGINAL only) — recovered from original radioTask
static const uint8_t MOD_BT = 79, MOD_BLE = 39, MOD_WIFI = 14, MOD_RC = 125;

enum : int { ST_IDLE = 0, ST_BT = 1, ST_BLE = 2, ST_WIFI = 3, ST_RC = 4 };

// ---- Shared state (volatile where cross-core) ----
volatile int  g_state = INITIAL_STATE;
volatile bool g_pauseRf = false;
volatile bool g_radioNeedReinit = false;

// Live hop telemetry (RadioTask writes, UI reads)
volatile uint8_t  g_chH = 0, g_chV = 0;
volatile uint32_t g_hopCount = 0;
volatile uint32_t g_hopWindow = 0;      // hops in current stats window
volatile uint16_t g_uniqueApprox = 0;   // approx unique channels (bloom-ish bitset popcount)

static int g_uiState = -1;
static int g_savedState = ST_BT;
static uint32_t g_idleAnim = 0;
static uint32_t g_lastOledMs = 0;
static uint32_t g_lastStatsMs = 0;
static uint32_t g_lastHopCountSnap = 0;

// Coverage bitset for lab stats: 128 bits covers nRF 0..125
static uint32_t g_covBits[4] = {0, 0, 0, 0};
static portMUX_TYPE statsMux = portMUX_INITIALIZER_UNLOCKED;

// LED
static uint8_t g_ledOn = 0;
static int g_ledCount = 0, g_ledTarget = 0;
static uint32_t g_ledTs = 0;

// Button
static bool btnStable = false, btnRawPrev = false, btnLongDone = false;
static uint32_t btnChangeMs = 0, btnDownMs = 0;

// Sweep / priority indices (RadioTask)
static uint16_t g_sweepIdx = 0;
static uint16_t g_priIdxH = 0, g_priIdxV = 0;

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

// =============================================================================
// Helpers
// =============================================================================
static inline uint8_t hwRandMod(uint8_t mod) {
  if (mod == 0) return 0;
  return (uint8_t)(esp_random() % mod);
}

static const char* stateName(int s) {
  switch (s) {
    case ST_IDLE: return "State 0: Idle & Status";
    case ST_BT:   return "State 1: Bluetooth";
    case ST_BLE:  return "State 2: Bluetooth Low Energy";
    case ST_WIFI: return "State 3: WiFi";
    case ST_RC:   return "State 4: RC";
    default:      return "State ?";
  }
}

static uint8_t hopModOriginal(int s) {
  switch (s) {
    case ST_BT: return MOD_BT;
    case ST_BLE: return MOD_BLE;
    case ST_WIFI: return MOD_WIFI;
    case ST_RC: return MOD_RC;
    default: return 0;
  }
}

static void mapForState(int s, const uint8_t** pri, uint8_t* priN, uint8_t* fullMod) {
  switch (s) {
    case ST_BT:
      *pri = MAP_BT_PRI; *priN = MAP_BT_PRI_N; *fullMod = MAP_BT_FULL_MOD;
      break;
    case ST_BLE:
      *pri = MAP_BLE_PRI; *priN = MAP_BLE_PRI_N; *fullMod = MAP_BLE_FULL_MOD;
      break;
    case ST_WIFI:
      *pri = MAP_WIFI_PRI; *priN = MAP_WIFI_PRI_N; *fullMod = MAP_WIFI_FULL_MOD;
      break;
    case ST_RC:
      *pri = MAP_RC_PRI; *priN = MAP_RC_PRI_N; *fullMod = MAP_RC_FULL_MOD;
      break;
    default:
      *pri = MAP_BT_PRI; *priN = 0; *fullMod = 0;
      break;
  }
}

static void saveMode(int s) {
#if REMEMBER_LAST_MODE
  if (s >= ST_BT && s <= ST_RC) {
    prefs.putUChar("mode", (uint8_t)s);
  }
#endif
}

static int loadMode() {
#if REMEMBER_LAST_MODE
  uint8_t m = prefs.getUChar("mode", (uint8_t)INITIAL_STATE);
  if (m >= ST_BT && m <= ST_RC) return (int)m;
#endif
  return INITIAL_STATE;
}

static void covMark(uint8_t ch) {
  if (ch > 125) return;
  g_covBits[ch >> 5] |= (1u << (ch & 31));
}

static uint16_t covPopcount() {
  uint16_t n = 0;
  for (int i = 0; i < 4; i++) {
    uint32_t v = g_covBits[i];
#if defined(__GNUC__)
    n += (uint16_t)__builtin_popcount(v);
#else
    while (v) { n += (uint16_t)(v & 1u); v >>= 1; }
#endif
  }
  return n;
}

static void covReset() {
  memset(g_covBits, 0, sizeof(g_covBits));
}

// =============================================================================
// Educational hop engine
// =============================================================================
// Returns a channel for one radio. peerCh is the other radio's channel (or 0xFF).
static uint8_t pickChannel(int state, bool forRadioH, uint8_t peerCh) {
  uint8_t ch = 0;

#if HOP_STRATEGY == 0
  // ORIGINAL: recovered math — independent random % mod
  {
    uint8_t mod = hopModOriginal(state);
    if (mod == 0) return 0;
    ch = hwRandMod(mod);
  }
#elif HOP_STRATEGY == 2
  // SWEEP: deterministic walk across full educational band
  {
    const uint8_t* pri; uint8_t priN, fullMod;
    mapForState(state, &pri, &priN, &fullMod);
    if (fullMod == 0) return 0;
    // Offset second radio by half-band for simultaneous dual coverage
    uint16_t idx = g_sweepIdx + (forRadioH ? 0 : (fullMod / 2));
    ch = (uint8_t)(idx % fullMod);
    if (forRadioH) g_sweepIdx++;
  }
#else
  // EDU (default): priority protocol map + full-band fill + dual complement
  {
    const uint8_t* pri; uint8_t priN, fullMod;
    mapForState(state, &pri, &priN, &fullMod);
    if (fullMod == 0) return 0;

    bool usePri = (priN > 0) && ((esp_random() % 100) < (uint32_t)HOP_PRIORITY_PCT);
    if (usePri) {
      uint16_t* pIdx = forRadioH ? &g_priIdxH : &g_priIdxV;
      // Second radio starts mid-table so dual hits different priority centers first
      uint16_t base = forRadioH ? 0 : (priN / 2);
      ch = pri[(*pIdx + base) % priN];
      (*pIdx)++;
    } else {
      ch = hwRandMod(fullMod);
    }

#if COMPLEMENTARY_DUAL
    // Guarantee spectral diversity: never park both modules on same channel
    if (peerCh != 0xFF && ch == peerCh) {
      ch = (uint8_t)((ch + 1 + (fullMod / 3)) % fullMod);
      // Prefer a different priority center if available
      if (priN > 1) {
        uint8_t alt = pri[(esp_random() % priN)];
        if (alt != peerCh) ch = alt;
      }
    }
#endif
  }
#endif

  return ch;
}

static void noteHop(uint8_t chH, uint8_t chV) {
  portENTER_CRITICAL(&statsMux);
  g_chH = chH;
  g_chV = chV;
  g_hopCount++;
  g_hopWindow++;
  covMark(chH);
  covMark(chV);
  g_uniqueApprox = covPopcount();
  portEXIT_CRITICAL(&statsMux);
}

static void printModeEducation(int s) {
  Serial.println(F("---- EDU mode map ----"));
  Serial.printf("Strategy: %s\n", hopStrategyName(HOP_STRATEGY));
  switch (s) {
    case ST_BT:
      Serial.println(F("BT: 79×1 MHz classic band (nRF 0..78)"));
      Serial.println(F("  EDU priority = spaced samples for fast AFH-style coverage"));
      break;
    case ST_BLE:
      Serial.println(F("BLE: adv centers nRF 2/26/80 (2402/2426/2480 MHz)"));
      Serial.println(F("  + data-band samples; ORIGINAL only used random%39"));
      break;
    case ST_WIFI:
      Serial.println(F("WiFi: nRF maps of ch1..13 centers (12,17,...,72)"));
      Serial.println(F("  ORIGINAL random%14 only hit ~2400-2413 MHz (weak)"));
      break;
    case ST_RC:
      Serial.println(F("RC: full nRF 0..125 with 5 MHz grid priority"));
      break;
    default:
      Serial.println(F("Idle: no hop"));
      break;
  }
#if COMPLEMENTARY_DUAL
  Serial.println(F("Dual: complementary — R1 and R2 forced onto different ch"));
#endif
  Serial.println(F("----------------------"));
}

// =============================================================================
// OLED
// =============================================================================
static void oledSplash() {
  display.clearDisplay();
  display.drawBitmap(0, 0, bitmapboot, 128, 64, SSD1306_WHITE);
  display.display();
}

static void oledMode(const uint8_t* bmp, int mode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  const char* credit = "by @emensta";
  int16_t x1, y1; uint16_t tw, th;
  display.getTextBounds(credit, 0, 0, &x1, &y1, &tw, &th);
  display.setCursor((int16_t)((128 - tw) / 2), 2);
  display.print(credit);
  display.drawBitmap(0, 12, bmp, 128, 50, SSD1306_WHITE);

#if EDU_OLED_HUD
  // Live channel HUD (bottom strip over bitmap area — small, educational)
  display.fillRect(0, 56, 128, 8, SSD1306_BLACK);
  display.setCursor(0, 56);
  display.printf("H%u V%u", (unsigned)g_chH, (unsigned)g_chV);
  display.setCursor(64, 56);
  switch (mode) {
    case ST_BT: display.print(F("BT+")); break;
    case ST_BLE: display.print(F("BLE+")); break;
    case ST_WIFI: display.print(F("WF+")); break;
    case ST_RC: display.print(F("RC+")); break;
  }
#endif
  display.display();
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
  display.print(F("USB Pro EDU"));
  display.setCursor(0, 22);
  display.printf("ch H=%u V=%u", (unsigned)g_chH, (unsigned)g_chV);
  display.setCursor(0, 32);
  display.printf("hops=%lu uniq~%u", (unsigned long)g_hopCount, (unsigned)g_uniqueApprox);

  display.setCursor(0, 44);
  display.print(g_pauseRf ? F("[RF PAUSED]") : F("State 0: Idle"));
  display.setCursor(0, 56);
  display.print(F("BOOT=mode hold=pause"));
  display.display();
}

static bool oledFrameDue() {
  uint32_t now = millis();
  if ((now - g_lastOledMs) < OLED_MIN_FRAME_MS) return false;
  g_lastOledMs = now;
  return true;
}

// =============================================================================
// LED (non-blocking)
// =============================================================================
static void ledReset(int blinks) {
  g_ledTarget = blinks;
  g_ledCount = 0;
  g_ledOn = 0;
  g_ledTs = millis();
  digitalWrite(PIN_LED, LOW);
}

static void ledService() {
  if (g_ledTarget <= 0) return;
  uint32_t now = millis();
  uint32_t need = (g_ledOn && g_ledCount >= g_ledTarget) ? LED_GAP_MS : LED_PULSE_MS;
  if ((now - g_ledTs) < need) return;
  g_ledTs = now;
  g_ledOn ^= 1;
  digitalWrite(PIN_LED, g_ledOn ? HIGH : LOW);
  if (g_ledOn) {
    g_ledCount++;
    if (g_ledCount > g_ledTarget) g_ledCount = 1;
  }
}

// =============================================================================
// State entry / UI
// =============================================================================
static void enterStateUi(int s) {
  if (g_uiState == s) {
    if (s == ST_IDLE) {
      if (oledFrameDue()) oledIdle();
    } else {
      ledService();
#if EDU_OLED_HUD
      // Refresh HUD with live channels at frame rate
      if (oledFrameDue()) {
        const uint8_t* bmp = bitmap1;
        if (s == ST_BLE) bmp = bitmap2;
        else if (s == ST_WIFI) bmp = bitmap3;
        else if (s == ST_RC) bmp = bitmap4;
        oledMode(bmp, s);
      }
#endif
    }
    return;
  }

  g_uiState = s;
  Serial.println(stateName(s));
  saveMode(s);
  if (s >= ST_BT && s <= ST_RC) {
    printModeEducation(s);
    // Reset coverage window when changing mode (cleaner lab stats)
    portENTER_CRITICAL(&statsMux);
    covReset();
    g_hopWindow = 0;
    g_uniqueApprox = 0;
    portEXIT_CRITICAL(&statsMux);
  }

  switch (s) {
    case ST_BT:   oledMode(bitmap1, s); ledReset(1); break;
    case ST_BLE:  oledMode(bitmap2, s); ledReset(2); break;
    case ST_WIFI: oledMode(bitmap3, s); ledReset(3); break;
    case ST_RC:   oledMode(bitmap4, s); ledReset(4); break;
    default:      ledReset(0); if (oledFrameDue()) oledIdle(); break;
  }
}

static void cycleMode() {
  int s = g_state;
  if (s < ST_BT || s > ST_RC) s = ST_BT;
  else {
    s++;
    if (s > ST_RC) s = ST_BT;
  }
  g_state = s;
  g_uiState = -1;
}

static void printLabStats() {
#if EDU_STATS_MS > 0
  uint32_t now = millis();
  if ((now - g_lastStatsMs) < (uint32_t)EDU_STATS_MS) return;
  g_lastStatsMs = now;

  uint32_t hops = g_hopCount;
  uint32_t delta = hops - g_lastHopCountSnap;
  g_lastHopCountSnap = hops;
  float rate = (float)delta * 1000.0f / (float)EDU_STATS_MS;

  Serial.println(F("==== LAB STATS (education) ===="));
  Serial.printf("mode=%s  strategy=%s\n", stateName((int)g_state), hopStrategyName(HOP_STRATEGY));
  Serial.printf("chH=%u  chV=%u  dual_diff=%s\n",
                (unsigned)g_chH, (unsigned)g_chV,
                (g_chH != g_chV) ? "yes" : "no");
  Serial.printf("hop_rate≈%.0f/s  total=%lu  unique_in_mode≈%u\n",
                rate, (unsigned long)hops, (unsigned)g_uniqueApprox);
  Serial.printf("pause=%d  batch=%u delay=%ums pri%%=%u\n",
                (int)g_pauseRf, (unsigned)HOP_BATCH, (unsigned)HOP_DELAY_MS,
                (unsigned)HOP_PRIORITY_PCT);
  Serial.println(F("================================"));
#endif
}

// =============================================================================
// RF (core 0)
// =============================================================================
#if !REBUILD_SAFE

static bool beginOne(RF24& r, SPIClass& spi, const char* tag) {
  for (int i = 0; i < RADIO_BEGIN_RETRIES; i++) {
    if (r.begin(&spi)) {
      Serial.printf("[%s] begin OK (try %d)\n", tag, i + 1);
      return true;
    }
    delay(50);
  }
  Serial.printf("[%s] begin FAIL\n", tag);
  return false;
}

static void radioConfigure(RF24& r) {
  r.stopListening();
  r.powerUp();
  r.setAutoAck(false);
  r.setRetries(0, 0);
  r.setPALevel(RF24_PA_MAX, true);
  r.setDataRate(RF24_2MBPS);
  r.setCRCLength(RF24_CRC_DISABLED);
  r.startConstCarrier(RF24_PA_MAX, INITIAL_CARRIER_CH);
}

static void radioStop(RF24& r) {
  r.stopConstCarrier();
  r.powerDown();
}

static void radioRestart(RF24& r) {
  r.powerUp();
  delayMicroseconds(1500);
  r.startConstCarrier(RF24_PA_MAX, INITIAL_CARRIER_CH);
}

static bool initRadios() {
  spiH.begin(PIN_SCK1, PIN_MISO1, PIN_MOSI1, PIN_CSN1);
  delay(5);
  spiV.begin(PIN_SCK2, PIN_MISO2, PIN_MOSI2, PIN_CSN2);
  delay(5);

  radioH_ok = beginOne(radioH, spiH, "HSPI");
  OrigSerialArt::printSep();
  if (radioH_ok) {
    OrigSerialArt::printHSPISuccess();
    radioConfigure(radioH);
  } else {
    OrigSerialArt::printHSPIFail();
  }

  radioV_ok = beginOne(radioV, spiV, "VSPI");
  OrigSerialArt::printSep();
  if (radioV_ok) {
    OrigSerialArt::printVSPISuccess();
    radioConfigure(radioV);
  } else {
    OrigSerialArt::printVSPIFail();
  }
  return radioH_ok || radioV_ok;
}

static void radioTask(void*) {
  initRadios();
  uint32_t lastHealth = millis();

  for (;;) {
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
    }

    if (g_radioNeedReinit) {
      g_radioNeedReinit = false;
      initRadios();
    }

    uint32_t now = millis();
    if ((now - lastHealth) >= RADIO_HEALTH_MS && !g_pauseRf) {
      lastHealth = now;
      bool h = radioH_ok && radioH.isChipConnected();
      bool v = radioV_ok && radioV.isChipConnected();
      if (radioH_ok && !h) {
        Serial.println(F("[HSPI] lost — reinit"));
        radioH_ok = beginOne(radioH, spiH, "HSPI");
        if (radioH_ok) radioConfigure(radioH);
      }
      if (radioV_ok && !v) {
        Serial.println(F("[VSPI] lost — reinit"));
        radioV_ok = beginOne(radioV, spiV, "VSPI");
        if (radioV_ok) radioConfigure(radioV);
      }
    }

    const int st = (int)g_state;
    if (st >= ST_BT && st <= ST_RC && !g_pauseRf) {
      for (uint32_t i = 0; i < HOP_BATCH; i++) {
        // Pick H first, then V with knowledge of H → complementary dual
        uint8_t chH = pickChannel(st, true, 0xFF);
        uint8_t chV = pickChannel(st, false, chH);
#if COMPLEMENTARY_DUAL
        if (chV == chH) {
          const uint8_t* pri; uint8_t priN, fullMod;
          mapForState(st, &pri, &priN, &fullMod);
          if (fullMod > 1) chV = (uint8_t)((chH + fullMod / 2) % fullMod);
        }
#endif
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
  Serial.println(F("[REBUILD_SAFE] RF path disabled — UI / EDU telemetry only."));
  OrigSerialArt::printHSPIFail();
  OrigSerialArt::printVSPIFail();
  // Soft-sim hops for education when SAFE (no RF TX)
  for (;;) {
    int st = (int)g_state;
    if (st >= ST_BT && st <= ST_RC && !g_pauseRf) {
      uint8_t chH = pickChannel(st, true, 0xFF);
      uint8_t chV = pickChannel(st, false, chH);
      noteHop(chH, chV);
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

#endif

// =============================================================================
// Button FSM (debounced short / long)
// =============================================================================
static void serviceButton() {
  const bool raw = (digitalRead(PIN_BOOT) == LOW);
  const uint32_t now = millis();

  if (raw != btnRawPrev) {
    btnRawPrev = raw;
    btnChangeMs = now;
  }
  if ((now - btnChangeMs) < DEBOUNCE_MS) return;

  if (raw && !btnStable) {
    btnStable = true;
    btnLongDone = false;
    btnDownMs = now;
  } else if (raw && btnStable && !btnLongDone && !g_pauseRf) {
    if ((now - btnDownMs) >= LONG_PRESS_MS) {
      btnLongDone = true;
      g_savedState = (g_state >= ST_BT && g_state <= ST_RC) ? (int)g_state : ST_BT;
      g_state = ST_IDLE;
      g_pauseRf = true;
      g_uiState = -1;
      Serial.println(F("[BTN] long → pause"));
    }
  } else if (!raw && btnStable) {
    const uint32_t held = now - btnDownMs;
    btnStable = false;
    if (btnLongDone) {
      // stay paused until short click
    } else if (g_pauseRf && held < LONG_PRESS_MS) {
      g_state = g_savedState;
      g_pauseRf = false;
      g_uiState = -1;
      Serial.println(F("[BTN] short → resume"));
    } else if (!g_pauseRf && held < LONG_PRESS_MS) {
      if ((int)g_state == ST_IDLE) {
        g_state = ST_BT;
        g_uiState = -1;
      } else {
        cycleMode();
      }
      Serial.println(F("[BTN] short → next mode"));
    }
    btnLongDone = false;
  }
}

// =============================================================================
// Arduino
// =============================================================================
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(50);
  Serial.println(F("\n=== ComboChannelSelect Pro EDU ==="));
  Serial.println(F("Optimized + protocol-aware effectiveness rebuild"));
  Serial.printf("Hop strategy: %s\n", hopStrategyName(HOP_STRATEGY));

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_BOOT, INPUT_PULLUP);

  prefs.begin("ccspro", false);
  g_state = loadMode();
  if ((int)g_state < ST_BT || (int)g_state > ST_RC) g_state = INITIAL_STATE;

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(400000);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true) delay(1000);
  }
  display.clearDisplay();
  display.display();

  oledSplash();
  delay(SPLASH_MS);
  OrigSerialArt::printSep();
  OrigSerialArt::printBootBanner();

  xTaskCreatePinnedToCore(
      radioTask, "RadioTask", RADIO_TASK_STACK, nullptr,
      RADIO_TASK_PRIO, nullptr, RADIO_TASK_CORE);

  Serial.printf("UI core=%d  Radio core=%d  SPI=%lu Hz\n",
                xPortGetCoreID(), RADIO_TASK_CORE, (unsigned long)RF24_SPI_HZ);
  Serial.printf("hop batch=%u delay=%ums pri%%=%u complement=%d\n",
                (unsigned)HOP_BATCH, (unsigned)HOP_DELAY_MS,
                (unsigned)HOP_PRIORITY_PCT, (int)COMPLEMENTARY_DUAL);
#if REBUILD_SAFE
  Serial.println(F("REBUILD_SAFE=1 — no RF TX (sim hop stats only)"));
#endif
  Serial.println(F("Lab tip: open Serial 115200 for mode maps + hop_rate stats"));
}

void loop() {
  serviceButton();
  enterStateUi((int)g_state);
  printLabStats();
  delay(5);
}
