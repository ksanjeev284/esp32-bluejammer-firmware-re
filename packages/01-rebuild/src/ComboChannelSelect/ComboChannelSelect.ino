/*
 * ComboChannelSelect — hardware-faithful reconstruction
 * =====================================================
 * Reverse-engineered from Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
 * (ESP32-BlueJammer closed-source firmware).
 *
 * When built with REBUILD_SAFE=0 (default in config.h) and flashed to
 * matching hardware (dual nRF24 + SSD1306 + LED27 + BOOT), behavior is
 * intended to match the original device:
 *   - boot splash + serial banners
 *   - BOOT short = cycle BT/BLE/WiFi/RC
 *   - BOOT long  = pause RF / idle status
 *   - dual nRF24 constant-carrier + independent channel hop
 *   - OLED mode bitmaps extracted from original DROM
 *
 * NOT bit-identical to the original .bin (different compiler/link/SDK hash),
 * but designed so the flashed rebuild *works correctly on hardware*.
 *
 * LEGAL: Jamming is illegal in most jurisdictions. You are responsible for
 * lawful use only. See DISCLAIMER.md in the repository root.
 */

#include "config.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if !REBUILD_SAFE
#include <RF24.h>
#include <nRF24L01.h>
#endif

#include "bitmaps.h"
#include "OrigSerialArt.h"  // exact UTF-8 banners from original DROM

// =============================================================================
// Pins — every value confirmed from Ghidra decompilation of the original bin
// =============================================================================
// HSPI nRF24
static const uint8_t PIN_CE1   = 16;
static const uint8_t PIN_CSN1  = 15;
static const uint8_t PIN_SCK1  = 14;
static const uint8_t PIN_MISO1 = 12;
static const uint8_t PIN_MOSI1 = 13;

// VSPI nRF24
static const uint8_t PIN_CE2   = 22;
static const uint8_t PIN_CSN2  = 21;
static const uint8_t PIN_SCK2  = 18;
static const uint8_t PIN_MISO2 = 19;
static const uint8_t PIN_MOSI2 = 23;

static const uint8_t PIN_LED  = 27;
static const uint8_t PIN_BOOT = 0;   // active LOW, INPUT_PULLUP

static const uint8_t PIN_SDA = 4;
static const uint8_t PIN_SCL = 5;
static const uint8_t OLED_ADDR = 0x3C;

// Literal-pool constants from original IROM
static const uint32_t SERIAL_BAUD   = 115200;
static const uint32_t RF24_SPI_HZ   = 16000000UL;  // 0x400D012C
static const uint32_t RADIO_STACK   = 8192;          // 0x2000
static const UBaseType_t RADIO_PRIO = 1;

static const uint32_t SPLASH_MS      = 2000;
static const uint32_t LONG_PRESS_MS  = 500;
static const uint32_t LED_PULSE_MS   = 150;   // 0x96
static const uint32_t LED_GAP_MS     = 1000;
static const uint32_t HOP_BATCH      = 100;
static const uint32_t HOP_DELAY_MS   = 1;
static const uint32_t PAUSE_POLL_MS  = 10;
static const uint32_t SPI_SETTLE_MS  = 5;

// randomChannel(N) → 0 .. N-1
static const uint8_t MOD_BT   = 79;   // 0x4F
static const uint8_t MOD_BLE  = 39;   // 0x27
static const uint8_t MOD_WIFI = 14;   // 0x0E
static const uint8_t MOD_RC   = 125;  // 0x7D

static const int SCREEN_W = 128;
static const int SCREEN_H = 64;

// =============================================================================
// State (names match recovered globals)
// =============================================================================
enum : int {
  ST_IDLE = 0,
  ST_BT   = 1,
  ST_BLE  = 2,
  ST_WIFI = 3,
  ST_RC   = 4,
};

volatile int  g_state = INITIAL_STATE;
volatile bool g_pauseRf = false;

static int      g_uiPrintedState = -1;
static int      g_stateBeforePause = ST_BT;
static int      g_ledTarget = 0;
static int      g_ledCount = 0;
static uint8_t  g_ledOn = 0;
static uint32_t g_ledTs = 0;
static uint32_t g_idleAnim = 0;

// Button edge detector
static bool     btnDown = false;
static bool     btnLongFired = false;
static uint32_t btnDownAt = 0;

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

#if !REBUILD_SAFE
// Dedicated SPI buses (matches radioTask HSPI=bus2 / VSPI=bus3)
static SPIClass spiH(HSPI);
static SPIClass spiV(VSPI);

// CE/CSN as recovered in FUN_400d29f8 / FUN_400d30a8
static RF24 radioH(PIN_CE1, PIN_CSN1, RF24_SPI_HZ);
static RF24 radioV(PIN_CE2, PIN_CSN2, RF24_SPI_HZ);

static bool radioH_ok = false;
static bool radioV_ok = false;
#endif

// =============================================================================
// Serial banners — exact UTF-8 lines from original DROM (OrigSerialArt.h)
// =============================================================================
static void serialSplash() {
  OrigSerialArt::printSep();
  OrigSerialArt::printBootBanner();  // # lines, BY EMENSTA art, firmware, disclaimers
}

static void serialHSPI(bool ok) {
  OrigSerialArt::printSep();
  if (ok) OrigSerialArt::printHSPISuccess();
  else OrigSerialArt::printHSPIFail();
}

static void serialVSPI(bool ok) {
  OrigSerialArt::printSep();
  if (ok) OrigSerialArt::printVSPISuccess();
  else OrigSerialArt::printVSPIFail();
}

static const char* stateString(int s) {
  switch (s) {
    case ST_IDLE: return "State 0: Idle & Status";
    case ST_BT:   return "State 1: Bluetooth";
    case ST_BLE:  return "State 2: Bluetooth Low Energy";
    case ST_WIFI: return "State 3: WiFi";
    case ST_RC:   return "State 4: RC";
    default:      return "State ?";
  }
}

// =============================================================================
// OLED (initOLED 0x400D2D68, drawModeBitmap 0x400D2DAC)
// =============================================================================
static void oledDrawSplash() {
  display.clearDisplay();
  display.drawBitmap(0, 0, bitmapboot, 128, 64, SSD1306_WHITE);
  display.display();
}

static void oledDrawMode(const uint8_t* bmp) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  // Center "by @emensta" at y=2
  const char* credit = "by @emensta";
  int16_t x1, y1;
  uint16_t tw, th;
  display.getTextBounds(credit, 0, 0, &x1, &y1, &tw, &th);
  display.setCursor((int16_t)((128 - tw) / 2), 2);
  display.print(credit);
  // Mode art 128x50 @ y=12
  display.drawBitmap(0, 12, bmp, 128, 50, SSD1306_WHITE);
  display.display();
}

static void oledDrawIdle() {
  // Labels recovered exactly: "R1=", "R2=", "USB", "Connected", "OK"/"FAIL"
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
  display.print(F("USB"));

  display.setCursor(0, 28);
  display.print(F("Connected"));
  g_idleAnim++;
  for (uint8_t i = 0; i < (g_idleAnim % 4); i++) display.print('.');

  display.setCursor(0, 44);
  display.print(F("State 0: Idle & Status"));
  display.setCursor(0, 56);
  display.print(g_pauseRf ? F("[RF PAUSED]") : F("BOOT=mode hold=pause"));
  display.display();
}

// =============================================================================
// LED blink (statusLedBlink 0x400D2868)
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
  uint32_t need = LED_PULSE_MS;
  if (g_ledOn && g_ledCount >= g_ledTarget) need = LED_GAP_MS;
  if ((now - g_ledTs) < need) return;

  g_ledTs = now;
  g_ledOn ^= 1;
  digitalWrite(PIN_LED, g_ledOn ? HIGH : LOW);

  if (g_ledOn) {
    g_ledCount++;
    if (g_ledCount > g_ledTarget) {
      // After finishing a group, restart count for next group (matches wrap logic)
      g_ledCount = 1;
    }
  }
}

// =============================================================================
// State entry
// =============================================================================
static void enterState(int s) {
  if (g_uiPrintedState != s) {
    Serial.println(stateString(s));
    g_uiPrintedState = s;

    switch (s) {
      case ST_BT:   oledDrawMode(bitmap1); ledReset(1); break;
      case ST_BLE:  oledDrawMode(bitmap2); ledReset(2); break;
      case ST_WIFI: oledDrawMode(bitmap3); ledReset(3); break;
      case ST_RC:   oledDrawMode(bitmap4); ledReset(4); break;
      case ST_IDLE:
      default:
        ledReset(0);
        digitalWrite(PIN_LED, LOW);
        break;
    }
  }

  if (s == ST_IDLE) {
    oledDrawIdle();
  } else {
    ledService();
  }
}

// FUN_400d2844: state = state+1; if (state>4) state=1;
static void cycleMode() {
  int s = g_state + 1;
  if (s > ST_RC) s = ST_BT;
  if (s < ST_BT) s = ST_BT;
  g_state = s;
  g_uiPrintedState = -1;  // force UI refresh
}

// =============================================================================
// RF path (radioTask 0x400D236C) — only when REBUILD_SAFE==0
// =============================================================================
#if !REBUILD_SAFE

static void radioConfigure(RF24& r) {
  // Order from successful branch of radioTask after begin():
  r.stopListening();
  r.powerUp();
  r.setAutoAck(false);
  r.setRetries(0, 0);                         // FUN_400d34b0(...,0)
  r.setPALevel(RF24_PA_MAX, true);            // FUN_400d32f4(...,3,1)
  r.setDataRate(RF24_2MBPS);                  // FUN_400d3328(...,1)
  r.setCRCLength(RF24_CRC_DISABLED);          // FUN_400d3460(...,0)
  // begin() path sets ch 76; app then startConstCarrier with .data value 45
  r.startConstCarrier(RF24_PA_MAX, INITIAL_CARRIER_CH);
}

static void radioStop(RF24& r) {
  r.stopConstCarrier();
}

static void radioRestart(RF24& r) {
  r.powerUp();
  r.startConstCarrier(RF24_PA_MAX, INITIAL_CARRIER_CH);
}

static uint8_t modulusFor(int st) {
  switch (st) {
    case ST_BT:   return MOD_BT;
    case ST_BLE:  return MOD_BLE;
    case ST_WIFI: return MOD_WIFI;
    case ST_RC:   return MOD_RC;
    default:      return 0;
  }
}

static void radioTask(void* /*arg*/) {
  // SPI begin — pins from spi_setPins in radioTask
  spiH.begin(PIN_SCK1, PIN_MISO1, PIN_MOSI1, PIN_CSN1);
  delay(SPI_SETTLE_MS);
  spiV.begin(PIN_SCK2, PIN_MISO2, PIN_MOSI2, PIN_CSN2);
  delay(SPI_SETTLE_MS);

  radioH_ok = radioH.begin(&spiH);
  serialHSPI(radioH_ok);
  if (radioH_ok) radioConfigure(radioH);

  radioV_ok = radioV.begin(&spiV);
  serialVSPI(radioV_ok);
  if (radioV_ok) radioConfigure(radioV);

  for (;;) {
    for (uint32_t n = 0; n < HOP_BATCH; n++) {
      // Pause path: stop both carriers, wait, restart
      if (g_pauseRf) {
        if (radioH_ok) radioStop(radioH);
        if (radioV_ok) radioStop(radioV);
        while (g_pauseRf) {
          vTaskDelay(pdMS_TO_TICKS(PAUSE_POLL_MS));
        }
        if (radioH_ok) radioRestart(radioH);
        if (radioV_ok) radioRestart(radioV);
      }

      const uint8_t mod = modulusFor(g_state);
      if (mod != 0) {
        // Two independent randomChannel() calls in original
        if (radioH_ok) radioH.setChannel((uint8_t)random(mod));
        if (radioV_ok) radioV.setChannel((uint8_t)random(mod));
      }
    }
    vTaskDelay(pdMS_TO_TICKS(HOP_DELAY_MS));
  }
}

#else  // REBUILD_SAFE

static void radioTask(void* /*arg*/) {
  Serial.println(F("[REBUILD_SAFE=1] radioTask stub — RF transmit not compiled."));
  serialHSPI(false);
  serialVSPI(false);
  for (;;) vTaskDelay(pdMS_TO_TICKS(1000));
}

#endif

// =============================================================================
// BOOT button (loop 0x400D2BFC)
// =============================================================================
static void serviceButton() {
  const bool down = (digitalRead(PIN_BOOT) == LOW);
  const uint32_t now = millis();

  if (down) {
    if (!btnDown) {
      btnDown = true;
      btnLongFired = false;
      btnDownAt = now;
    } else if (!btnLongFired && !g_pauseRf && (now - btnDownAt) >= LONG_PRESS_MS) {
      // Long press → pause RF, idle UI
      btnLongFired = true;
      g_stateBeforePause = (g_state >= ST_BT && g_state <= ST_RC) ? g_state : ST_BT;
      g_state = ST_IDLE;
      g_pauseRf = true;
      g_uiPrintedState = -1;
    }
  } else if (btnDown) {
    // Release
    const uint32_t held = now - btnDownAt;
    btnDown = false;

    if (btnLongFired) {
      // End of long-press gesture already handled; short release while paused
      // restores previous mode (original short-release-while-paused path)
      if (g_pauseRf && held >= LONG_PRESS_MS) {
        // Still held long overall — stay paused until a *short* click restores.
        // Match original: restore only when press duration < 500 while paused.
      }
    } else if (g_pauseRf && held < LONG_PRESS_MS) {
      // Short click while paused → resume
      g_state = g_stateBeforePause;
      g_pauseRf = false;
      g_uiPrintedState = -1;
    } else if (!g_pauseRf && held < LONG_PRESS_MS) {
      // Short click → cycle 1..4
      if (g_state == ST_IDLE) {
        g_state = ST_BT;
      } else {
        cycleMode();
      }
      g_uiPrintedState = -1;
    }
    btnLongFired = false;
  }
}

// =============================================================================
// Arduino entry points
// =============================================================================
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(100);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_BOOT, INPUT_PULLUP);

  Wire.begin(PIN_SDA, PIN_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true) delay(1000);
  }
  display.clearDisplay();
  display.display();

  // Splash (bitmapboot 128x64) + 2s delay + banners
  oledDrawSplash();
  delay(SPLASH_MS);
  serialSplash();

  // RadioTask — stack 8192, prio 1 (xTaskCreate* recovered args)
  xTaskCreatePinnedToCore(radioTask, "RadioTask", RADIO_STACK, nullptr, RADIO_PRIO, nullptr, 0);

  Serial.println(F("setup() complete — use BOOT to change mode, hold BOOT to pause RF."));
#if REBUILD_SAFE
  Serial.println(F("NOTE: REBUILD_SAFE=1 — no RF TX. Set REBUILD_SAFE 0 in config.h for full hardware path."));
#endif
}

void loop() {
  serviceButton();

  switch (g_state) {
    case ST_BT:   enterState(ST_BT);   break;
    case ST_BLE:  enterState(ST_BLE);  break;
    case ST_WIFI: enterState(ST_WIFI); break;
    case ST_RC:   enterState(ST_RC);   break;
    default:      enterState(ST_IDLE); break;
  }

  delay(5);
}
