# Build the reconstructed firmware

## Safety

Default sketch has `#define REBUILD_SAFE 1` — **no RF transmit APIs**.

To compile the full RF path (still for lab/education only on a shielded bench you control):

```cpp
#define REBUILD_SAFE 0
```

**Jamming is illegal. Do not operate as a jammer.**

---

## Arduino IDE / arduino-cli

### 1. Install core

Board Manager → **esp32 by Espressif Systems** → version **2.0.10** (closest to original).

### 2. Libraries

Library Manager:

- **RF24** by TMRh20 (need `startConstCarrier` support)
- **Adafruit SSD1306**
- **Adafruit GFX Library**

### 3. Board options

| Setting | Value |
| --- | --- |
| Board | ESP32 Dev Module |
| Upload Speed | 921600 |
| CPU Frequency | 240 MHz |
| Flash Frequency | **80 MHz** |
| Flash Mode | **DIO** |
| Flash Size | **4MB (32Mb)** |
| Partition Scheme | Default 4MB |
| PSRAM | Disabled |

### 4. Open & upload

Open `reconstruction/ComboChannelSelect/ComboChannelSelect.ino`  
(folder name must match `.ino` name).

---

## arduino-cli example

```bash
arduino-cli core install esp32:esp32@2.0.10
arduino-cli lib install "RF24" "Adafruit SSD1306" "Adafruit GFX Library"
arduino-cli compile --fqbn esp32:esp32:esp32:FlashMode=dio,FlashFreq=80,FlashSize=4M \
  reconstruction/ComboChannelSelect
arduino-cli upload -p COMx --fqbn esp32:esp32:esp32 reconstruction/ComboChannelSelect
```

---

## Expected serial (safe mode)

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
...
Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)
...
[REBUILD_SAFE] radioTask stub — no RF transmit code compiled.
HSPI ... could NOT be initialized ...
VSPI ... could NOT be initialized ...
```

OLED shows splash then Idle / mode icons when button pressed.

---

## Comparing to original bin

| Check | Original | Rebuild |
| --- | --- | --- |
| SHA256 | `2e26452f…` | different |
| esptool chip | ESP32 | ESP32 |
| App behavior | closed | matches SPEC_FOR_REBUILD.md |

To compare RF register programming, use a logic analyzer on CSN/MOSI while both firmwares run in a **shielded** test (not against live networks).
