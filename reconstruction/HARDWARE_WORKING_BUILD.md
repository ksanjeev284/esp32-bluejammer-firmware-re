# Hardware-Working Build Guide

This document is the **“flash it and the device behaves correctly”** guide for the reconstructed firmware.

## What “works correctly” means

On the same hardware as ESP32-BlueJammer (ESP32 + 2× nRF24 + 0.96" SSD1306 + LED on GPIO27 + BOOT button):

| Feature | Expected |
| --- | --- |
| Power on | OLED splash (original bitmap), ~2 s, serial banners |
| BOOT short press | Cycles **BT → BLE → WiFi → RC → BT…**, OLED icon + serial state line, LED blinks 1–4 times |
| BOOT long press (~0.5 s) | Idle status screen, **RF pause** (carriers off) |
| Short press while paused | Resume previous mode, RF restarts |
| Dual nRF24 | HSPI + VSPI init messages; if modules present → SUCCESS art lines |
| RF (when `REBUILD_SAFE=0`) | Constant carrier + independent random hop per radio in mode ranges |
| Missing OLED | Serial: `SSD1306 allocation failed`, hang (same as original) |
| Missing nRF24 | FAIL banners; UI still works |

This is **functional parity** with the original closed-source combo firmware.

It will **not** have the same SHA256 as the original `.bin`. That is normal.

---

## Required hardware wiring

### HSPI nRF24 (#1)

| nRF24 | ESP32 |
| --- | --- |
| CE | GPIO 16 |
| CSN | GPIO 15 |
| SCK | GPIO 14 |
| MOSI | GPIO 13 |
| MISO | GPIO 12 |
| VCC | 3.3 V (+ 10–100 µF cap recommended) |
| GND | GND |

### VSPI nRF24 (#2)

| nRF24 | ESP32 |
| --- | --- |
| CE | GPIO 22 |
| CSN | GPIO 21 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| VCC | 3.3 V + cap |
| GND | GND |

### OLED SSD1306 0.96" I2C

| OLED | ESP32 |
| --- | --- |
| SDA | GPIO 4 |
| SCL | GPIO 5 |
| VCC | 3.3 V |
| GND | GND |

### LED + button

| Part | ESP32 |
| --- | --- |
| Status LED (+) via ~1–4.7 kΩ | GPIO 27 |
| Status LED (−) | GND |
| BOOT button | GPIO 0 to GND (built-in BOOT on DevKit) |

---

## Software setup (must match original era)

| Item | Version / value |
| --- | --- |
| Arduino-ESP32 core | **2.0.10** |
| Board | ESP32 Dev Module |
| Flash Mode | **DIO** |
| Flash Freq | **80 MHz** |
| Flash Size | **4 MB** |
| CPU | 240 MHz |
| Libraries | RF24 (TMRh20), Adafruit SSD1306, Adafruit GFX |

### config.h

```cpp
#define REBUILD_SAFE 0   // full hardware RF path
#define INITIAL_STATE 0  // Idle at boot (like original BSS)
```

For UI-only bench testing without radios: `REBUILD_SAFE 1`.

---

## Build & flash

### Arduino IDE

1. Install core **esp32 2.0.10**  
2. Install libraries RF24, Adafruit SSD1306, Adafruit GFX  
3. Open `reconstruction/ComboChannelSelect/ComboChannelSelect.ino`  
4. Set board options (table above)  
5. Upload  

### arduino-cli

```bash
arduino-cli core install esp32:esp32@2.0.10
arduino-cli lib install "RF24" "Adafruit SSD1306" "Adafruit GFX Library"

arduino-cli compile -e --fqbn esp32:esp32:esp32:FlashMode=dio,FlashFreq=80,FlashSize=4M \
  reconstruction/ComboChannelSelect

arduino-cli upload -p COMx --fqbn esp32:esp32:esp32:FlashMode=dio,FlashFreq=80,FlashSize=4M \
  reconstruction/ComboChannelSelect
```

Compiled binary (IDE/cli export) will be under `build/` — that is the **new .bin** you flash.

### esptool (manual)

```bash
esptool.py --chip esp32 --port COMx write_flash -z 0x10000 ComboChannelSelect.ino.bin
```

(Offset depends on partition table; Arduino upload handles this.)

---

## Power-on acceptance test (5 minutes)

1. USB serial **115200** → see firmware banner + GitHub URL.  
2. OLED shows splash then Idle / status.  
3. Press BOOT → `State 1: Bluetooth`, LED 1 blink, OLED bitmap1.  
4. Press again → BLE / WiFi / RC similarly.  
5. Hold BOOT 0.5 s+ → Idle, `[RF PAUSED]`.  
6. Short press → resumes last mode.  
7. With nRF24s fitted → HSPI/VSPI SUCCESS lines (not FAIL).  

If step 7 fails: check 3.3 V, caps, wiring CE/CSN, module orientation.

---

## Legal

Full dual-radio constant-carrier operation on 2.4 GHz is **jamming-class behavior**.  
Illegal without authorization. Prefer `REBUILD_SAFE 1` unless you have a lawful test environment.

---

## Spec cross-reference

All numbers and sequences come from Ghidra decompilation of the original binary:

- `radioTask` `0x400D236C`  
- `setup` `0x400D2714`  
- `loop` `0x400D2BFC`  
- radio ctor `0x400D29F8` / `0x400D30A8`  

See `SPEC_FOR_REBUILD.md` and `artifacts/ghidra/decomp/`.
