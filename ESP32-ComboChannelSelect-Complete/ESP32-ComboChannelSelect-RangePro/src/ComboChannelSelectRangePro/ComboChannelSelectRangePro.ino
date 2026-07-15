/*
 * ComboChannelSelect Range Pro
 * ----------------------------
 * Educational long-range / hardware-upgrade rebuild based on RE of
 * Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin + Pro EDU hop maps.
 *
 * Tuned for:
 *  - Stock nRF24, PA+LNA SMA modules, or high-gain antenna labs
 *  - Link-budget friendly PHY (250 kbps option, PA_MAX+LNA)
 *  - Power settle, retries, dual separation (reduce PA self-desense)
 *  - Optional duty cycle for PA thermal / lab safety
 *  - Protocol-aware EDU hops + lab stats + OLED range HUD
 *
 * See docs/RANGE_LEARNING.md and hardware/HARDWARE_RANGE.md
 *
 * LEGAL: PA modules + const carrier can create strong interference.
 * Authorized / shielded lab only. Prefer REBUILD_SAFE=1 for UI work.
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

// ---- Pins (original firmware RE) ----
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
static const uint32_t RADIO_HEALTH_MS = 4000;

static const uint8_t MOD_BT = 79, MOD_BLE = 39, MOD_WIFI = 14, MOD_RC = 125;

enum : int { ST_IDLE = 0, ST_BT = 1, ST_BLE = 2, ST_WIFI = 3, ST_RC = 4 };

volatile int  g_state = INITIAL_STATE;
volatile bool g_pauseRf = false;
volatile bool g_radioNeedReinit = false;
volatile bool g_dutyGate = true;  // false during optional duty OFF window

volatile uint8_t  g_chH = 0, g_chV = 0;
volatile uint32_t g_hopCount = 0;
volatile uint32_t g_hopWindow = 0;
volatile uint16_t g_uniqueApprox = 0;
volatile float    g_vccRail = 0.0f;

static int g_uiState = -1;
static int g_savedState = ST_BT;
static uint32_t g_idleAnim = 0;
static uint32_t g_lastOledMs = 0;
static uint32_t g_lastStatsMs = 0;
static uint32_t g_lastHopCountSnap = 0;

static uint32_t g_covBits[4] = {0, 0, 0, 0};
static portMUX_TYPE statsMux = portMUX_INITIALIZER_UNLOCKED;

static uint8_t g_ledOn = 0;
static int g_ledCount = 0, g_ledTarget = 0;
static uint32_t g_ledTs = 0;

static bool btnStable = false, btnRawPrev = false, btnLongDone = false;
static uint32_t btnChangeMs = 0, btnDownMs = 0;

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

static const char* hwProfileName() {
  switch (HW_PROFILE) {
    case 0: return "STOCK nRF24";
    case 1: return "PA+LNA SMA";
    case 2: return "PA+LNA + high-gain";
    default: return "CUSTOM";
  }
}

static const char* dataRateName() {
  switch (RF_DATA_RATE_SEL) {
    case 0: return "1Mbps";
    case 1: return "2Mbps";
    case 2: return "250kbps";
    default: return "?";
  }
}

#if !REBUILD_SAFE
static rf24_datarate_e dataRateEnum() {
  switch (RF_DATA_RATE_SEL) {
    case 0: return RF24_1MBPS;
    case 2: return RF24_250KBPS;
    default: return RF24_2MBPS;
  }
}

static rf24_pa_dbm_e paLevelEnum() {
  switch (RF_PA_LEVEL) {
    case 0: return RF24_PA_MIN;
    case 1: return RF24_PA_LOW;
    case 2: return RF24_PA_HIGH;
    default: return RF24_PA_MAX;
  }
}
#endif

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
    case ST_BT:   *pri = MAP_BT_PRI;   *priN = MAP_BT_PRI_N;   *fullMod = MAP_BT_FULL_MOD; break;
    case ST_BLE:  *pri = MAP_BLE_PRI;  *priN = MAP_BLE_PRI_N;  *fullMod = MAP_BLE_FULL_MOD; break;
    case ST_WIFI: *pri = MAP_WIFI_PRI; *priN = MAP_WIFI_PRI_N; *fullMod = MAP_WIFI_FULL_MOD; break;
    case ST_RC:   *pri = MAP_RC_PRI;   *priN = MAP_RC_PRI_N;   *fullMod = MAP_RC_FULL_MOD; break;
    default:      *pri = MAP_BT_PRI;   *priN = 0;              *fullMod = 0; break;
  }
}

static void saveMode(int s) {
#if REMEMBER_LAST_MODE
  if (s >= ST_BT && s <= ST_RC) prefs.putUChar("mode", (uint8_t)s);
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

static void covReset() { memset(g_covBits, 0, sizeof(g_covBits)); }

// =============================================================================
// Hop engine (EDU + min dual separation for PA desense)
// =============================================================================
static uint8_t pickChannel(int state, bool forRadioH, uint8_t peerCh) {
  uint8_t ch = 0;

#if HOP_STRATEGY == 0
  {
    uint8_t mod = hopModOriginal(state);
    if (mod == 0) return 0;
    ch = hwRandMod(mod);
  }
#elif HOP_STRATEGY == 2
  {
    const uint8_t* pri; uint8_t priN, fullMod;
    mapForState(state, &pri, &priN, &fullMod);
    if (fullMod == 0) return 0;
    uint16_t idx = g_sweepIdx + (forRadioH ? 0 : (fullMod / 2));
    ch = (uint8_t)(idx % fullMod);
    if (forRadioH) g_sweepIdx++;
  }
#else
  {
    const uint8_t* pri; uint8_t priN, fullMod;
    mapForState(state, &pri, &priN, &fullMod);
    if (fullMod == 0) return 0;

    bool usePri = (priN > 0) && ((esp_random() % 100) < (uint32_t)HOP_PRIORITY_PCT);
    if (usePri) {
      uint16_t* pIdx = forRadioH ? &g_priIdxH : &g_priIdxV;
      uint16_t base = forRadioH ? 0 : (priN / 2);
      ch = pri[(*pIdx + base) % priN];
      (*pIdx)++;
    } else {
      ch = hwRandMod(fullMod);
    }

#if COMPLEMENTARY_DUAL
    if (peerCh != 0xFF) {
      int tries = 0;
      while (tries < 8) {
        int d = (int)ch - (int)peerCh;
        if (d < 0) d = -d;
        if (d >= (int)DUAL_MIN_SEPARATION) break;
        // Push away by min separation (wrap in full band)
        ch = (uint8_t)((peerCh + DUAL_MIN_SEPARATION + tries) % fullMod);
        tries++;
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
  Serial.println(F("---- RANGE EDU mode map ----"));
  Serial.printf("HW profile: %s\n", hwProfileName());
  Serial.printf("PHY: PA=%d LNA=%d rate=%s SPI=%lu\n",
                (int)RF_PA_LEVEL, (int)RF_PA_LNA_ENABLE, dataRateName(),
                (unsigned long)RF24_SPI_HZ);
  Serial.printf("Strategy: %s  dual_sep>=%u  duty_on=%u off=%u\n",
                hopStrategyName(HOP_STRATEGY), (unsigned)DUAL_MIN_SEPARATION,
                (unsigned)RANGE_DUTY_ON_MS, (unsigned)RANGE_DUTY_OFF_MS);
  switch (s) {
    case ST_BT:
      Serial.println(F("BT: nRF 0..78 classic band; priority spaced samples"));
      break;
    case ST_BLE:
      Serial.println(F("BLE: adv nRF 2/26/80 + data; 250kbps helps lab SNR demos"));
      break;
    case ST_WIFI:
      Serial.println(F("WiFi: centers nRF 12..72 (real ch1-13), not original %14"));
      break;
    case ST_RC:
      Serial.println(F("RC: full 0..125 grid; dual sep reduces PA self-noise"));
      break;
    default: break;
  }
  Serial.println(F("Link budget tip: height + clear LOS + solid 3.3V > random hop rate"));
  Serial.println(F("----------------------------"));
}

static void sampleVcc() {
#if VCC_SENSE_PIN < 255
  // One-shot average
  uint32_t acc = 0;
  for (int i = 0; i < 8; i++) acc += analogRead(VCC_SENSE_PIN);
  float mid = (acc / 8.0f) * (3.3f / 4095.0f);
  float ratio = (VCC_SENSE_R_TOP_KOHM + VCC_SENSE_R_BOT_KOHM) / VCC_SENSE_R_BOT_KOHM;
  g_vccRail = mid * ratio;
#else
  g_vccRail = 0.0f;
#endif
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
  const char* credit = "RangePro EDU";
  int16_t x1, y1; uint16_t tw, th;
  display.getTextBounds(credit, 0, 0, &x1, &y1, &tw, &th);
  display.setCursor((int16_t)((128 - tw) / 2), 2);
  display.print(credit);
  display.drawBitmap(0, 12, bmp, 128, 50, SSD1306_WHITE);

#if EDU_OLED_HUD
  display.fillRect(0, 56, 128, 8, SSD1306_BLACK);
  display.setCursor(0, 56);
  display.printf("H%u V%u %s", (unsigned)g_chH, (unsigned)g_chV, dataRateName());
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
  display.printf("%s", hwProfileName());
  display.setCursor(0, 22);
  display.printf("ch H=%u V=%u", (unsigned)g_chH, (unsigned)g_chV);
  display.setCursor(0, 32);
  display.printf("%s PA%d sep%u", dataRateName(), (int)RF_PA_LEVEL, (unsigned)DUAL_MIN_SEPARATION);
  display.setCursor(0, 42);
  if (g_vccRail > 0.1f) display.printf("Vcc~%.2f hops=%lu", g_vccRail, (unsigned long)g_hopCount);
  else display.printf("hops=%lu uniq~%u", (unsigned long)g_hopCount, (unsigned)g_uniqueApprox);

  display.setCursor(0, 54);
  if (g_pauseRf) display.print(F("[RF PAUSED]"));
  else if (!g_dutyGate) display.print(F("[DUTY OFF]"));
  else display.print(F("BOOT=mode hold=pause"));
  display.display();
}

static bool oledFrameDue() {
  uint32_t now = millis();
  if ((now - g_lastOledMs) < OLED_MIN_FRAME_MS) return false;
  g_lastOledMs = now;
  return true;
}

// =============================================================================
// LED
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
// UI / button
// =============================================================================
static void enterStateUi(int s) {
  if (g_uiState == s) {
    if (s == ST_IDLE) {
      if (oledFrameDue()) oledIdle();
    } else {
      ledService();
#if EDU_OLED_HUD
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
  sampleVcc();

  uint32_t hops = g_hopCount;
  uint32_t delta = hops - g_lastHopCountSnap;
  g_lastHopCountSnap = hops;
  float rate = (float)delta * 1000.0f / (float)EDU_STATS_MS;
  int sep = (int)g_chH - (int)g_chV;
  if (sep < 0) sep = -sep;

  Serial.println(F("==== RANGE LAB STATS ===="));
  Serial.printf("profile=%s  mode=%s\n", hwProfileName(), stateName((int)g_state));
  Serial.printf("rate=%s PA=%d LNA=%d SPI=%luHz\n",
                dataRateName(), (int)RF_PA_LEVEL, (int)RF_PA_LNA_ENABLE,
                (unsigned long)RF24_SPI_HZ);
  Serial.printf("chH=%u chV=%u sep=%d duty_gate=%d\n",
                (unsigned)g_chH, (unsigned)g_chV, sep, (int)g_dutyGate);
  Serial.printf("hop_rate≈%.0f/s total=%lu unique≈%u\n",
                rate, (unsigned long)hops, (unsigned)g_uniqueApprox);
  if (g_vccRail > 0.1f) Serial.printf("Vcc_sense≈%.2f V (PA modules need solid 3.3V)\n", g_vccRail);
  Serial.println(F("========================="));
#endif
}

// =============================================================================
// RF
// =============================================================================
#if !REBUILD_SAFE

static bool beginOne(RF24& r, SPIClass& spi, const char* tag) {
  for (int i = 0; i < RADIO_BEGIN_RETRIES; i++) {
    if (r.begin(&spi)) {
      Serial.printf("[%s] begin OK (try %d)\n", tag, i + 1);
      return true;
    }
    delay(80);
  }
  Serial.printf("[%s] begin FAIL — check 3.3V current & wiring\n", tag);
  return false;
}

static void radioConfigure(RF24& r) {
  r.stopListening();
  r.powerUp();
  delayMicroseconds(1500);
  r.setAutoAck(false);
  r.setRetries(0, 0);
  r.setPALevel(paLevelEnum(), RF_PA_LNA_ENABLE != 0);
  r.setDataRate(dataRateEnum());
  r.setCRCLength(RF24_CRC_DISABLED);
  r.startConstCarrier(paLevelEnum(), INITIAL_CARRIER_CH);
}

static void radioStop(RF24& r) {
  r.stopConstCarrier();
  r.powerDown();
}

static void radioRestart(RF24& r) {
  r.powerUp();
  delayMicroseconds(1500);
  r.setPALevel(paLevelEnum(), RF_PA_LNA_ENABLE != 0);
  r.setDataRate(dataRateEnum());
  r.startConstCarrier(paLevelEnum(), INITIAL_CARRIER_CH);
}

static bool initRadios() {
  Serial.printf("[RF] profile=%s settle=%ums SPI=%lu\n",
                hwProfileName(), (unsigned)RADIO_POWER_SETTLE_MS,
                (unsigned long)RF24_SPI_HZ);

  spiH.begin(PIN_SCK1, PIN_MISO1, PIN_MOSI1, PIN_CSN1);
  delay(RADIO_POWER_SETTLE_MS);
  spiV.begin(PIN_SCK2, PIN_MISO2, PIN_MOSI2, PIN_CSN2);
  delay(RADIO_POWER_SETTLE_MS);

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
  uint32_t dutyMark = millis();
  bool dutyOn = true;
  g_dutyGate = true;

  for (;;) {
    // Optional duty cycle (PA thermal / lab safety education)
#if (RANGE_DUTY_ON_MS > 0) && (RANGE_DUTY_OFF_MS > 0)
    {
      uint32_t nowd = millis();
      if (dutyOn && (nowd - dutyMark) >= (uint32_t)RANGE_DUTY_ON_MS) {
        dutyOn = false;
        dutyMark = nowd;
        g_dutyGate = false;
        portENTER_CRITICAL(&radioMux);
        if (radioH_ok) radioStop(radioH);
        if (radioV_ok) radioStop(radioV);
        portEXIT_CRITICAL(&radioMux);
      } else if (!dutyOn && (nowd - dutyMark) >= (uint32_t)RANGE_DUTY_OFF_MS) {
        dutyOn = true;
        dutyMark = nowd;
        g_dutyGate = true;
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
      dutyOn = true;
      g_dutyGate = true;
      dutyMark = millis();
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
        Serial.println(F("[HSPI] lost — reinit (check PA 3.3V sag)"));
        radioH_ok = beginOne(radioH, spiH, "HSPI");
        if (radioH_ok) radioConfigure(radioH);
      }
      if (radioV_ok && !v) {
        Serial.println(F("[VSPI] lost — reinit (check PA 3.3V sag)"));
        radioV_ok = beginOne(radioV, spiV, "VSPI");
        if (radioV_ok) radioConfigure(radioV);
      }
    }

    const int st = (int)g_state;
    if (st >= ST_BT && st <= ST_RC && !g_pauseRf && g_dutyGate) {
      for (uint32_t i = 0; i < HOP_BATCH; i++) {
        uint8_t chH = pickChannel(st, true, 0xFF);
        uint8_t chV = pickChannel(st, false, chH);
#if COMPLEMENTARY_DUAL
        {
          const uint8_t* pri; uint8_t priN, fullMod;
          mapForState(st, &pri, &priN, &fullMod);
          if (fullMod > 1) {
            int d = (int)chH - (int)chV;
            if (d < 0) d = -d;
            if (d < (int)DUAL_MIN_SEPARATION) {
              chV = (uint8_t)((chH + DUAL_MIN_SEPARATION) % fullMod);
            }
          }
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
  Serial.println(F("[REBUILD_SAFE] no RF TX — range hop sim only"));
  OrigSerialArt::printHSPIFail();
  OrigSerialArt::printVSPIFail();
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
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(50);
  Serial.println(F("\n=== ComboChannelSelect Range Pro ==="));
  Serial.println(F("Long-range hardware profiles + EDU hop maps"));
  Serial.printf("Profile: %s | rate=%s | strategy=%s\n",
                hwProfileName(), dataRateName(), hopStrategyName(HOP_STRATEGY));

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_BOOT, INPUT_PULLUP);

#if VCC_SENSE_PIN < 255
  analogReadResolution(12);
  pinMode(VCC_SENSE_PIN, INPUT);
#endif

  prefs.begin("ccsrange", false);
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

  Serial.printf("UI core=%d Radio core=%d batch=%u delay=%ums sep>=%u\n",
                xPortGetCoreID(), RADIO_TASK_CORE,
                (unsigned)HOP_BATCH, (unsigned)HOP_DELAY_MS,
                (unsigned)DUAL_MIN_SEPARATION);
  Serial.println(F("Read hardware/HARDWARE_RANGE.md + docs/RANGE_LEARNING.md"));
#if REBUILD_SAFE
  Serial.println(F("REBUILD_SAFE=1 — no RF TX"));
#endif
}

void loop() {
  serviceButton();
  enterStateUi((int)g_state);
  printLabStats();
  delay(5);
}
