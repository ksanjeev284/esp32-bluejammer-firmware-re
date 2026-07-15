# Firmware Reverse Engineering Analysis

**Target:** `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`  
**Project identity:** ESP32-BlueJammer — Combo Channel Select (BT / BLE / WiFi / RC)  
**Author string:** `by @emensta` · `https://github.com/EmenstaNougat/ESP32-BlueJammer`

> **Legal note:** This firmware implements intentional 2.4 GHz interference. Jamming is illegal in most jurisdictions. This document is for educational reverse-engineering only (understanding format, structure, and UI logic). Do not use findings to build or operate jamming devices.

---

## 1. Firmware format identification

### Tools used

```text
esptool image-info Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
python analyze_fw.py
```

### Result: valid ESP32 application image

| Field | Value |
| --- | --- |
| Magic | `0xE9` (ESP image) |
| Detected chip | **ESP32** (chip ID 0) |
| Image version | 1 |
| Entry point | **`0x40082F0C`** (IRAM) |
| Segments | 5 |
| Flash size | **4 MB** |
| Flash freq | **80 MHz** |
| Flash mode | **DIO** |
| Checksum | valid (`0x13`) |
| Validation hash | valid |
| Project name | `arduino-lib-builder` |
| ESP-IDF | **v4.4.5** (`ac5d805d0e`) |
| Compile time | **Jun 12 2023 16:41:45** |
| Arduino-ESP32 core | **2.0.10** (from path strings) |
| App version string | `esp-idf: v4.4.5 ac5d805d0e` |
| Binary size | 877,232 bytes (~857 KB) |

### Flash segments (map these in Ghidra)

| # | Load address | Size | File offset | Memory type | Role |
| --- | ---: | ---: | ---: | --- | --- |
| 0 | `0x3F400020` | `0x1CFB0` (118,704) | `0x000020` | **DROM** | `.rodata` — strings, bitmaps, const tables |
| 1 | `0x3FFBDB60` | `0x03040` (12,352) | `0x01CFD8` | **DRAM** | `.data` initialized |
| 2 | `0x400D0020` | `0x99060` (626,784) | `0x020020` | **IROM** | `.text` — most application + library code |
| 3 | `0x3FFC0BA0` | `0x02F78` (12,152) | `0x0B9088` | **DRAM** | more `.data` |
| 4 | `0x40080000` | `0x1A278` (107,128) | `0x0BC008` | **IRAM** | vectors, critical code, entry |

### File identity

- Extension `.ino.bin` = Arduino sketch build artifact (not a full flash dump with bootloader/partitions).
- Flash as app image only (typical offset `0x10000` with bootloader + partition table), or use the project’s web flasher.

---

## 2. String extraction findings

```text
python analyze_fw.py          # full dump
# outputs: firmware_strings.txt, firmware_strings_interesting.txt
python map_strings.py         # VAs + pointer xrefs for Ghidra
```

### Application identity (high signal)

| String | DROM VA |
| --- | --- |
| `esp-idf: v4.4.5 ac5d805d0e` | `0x3F400030` |
| `Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)` | `0x3F400E40` |
| `https://github.com/EmenstaNougat/ESP32-BlueJammer` | `0x3F401577` |
| `by @emensta` | `0x3F401714` |

### RF module init messages

| String | VA |
| --- | --- |
| `Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY!` | `0x3F4002C4` |
| HSPI init failure message | `0x3F400482` |
| `Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY!` | `0x3F400608` |
| VSPI init failure message | `0x3F4007CB` |

### State machine names (serial / UI)

| State | String | VA |
| --- | --- | --- |
| 0 | `State 0: Idle & Status` | `0x3F4016CD` |
| 1 | `State 1: Bluetooth` | `0x3F401662` |
| 2 | `State 2: Bluetooth Low Energy` | `0x3F40167D` |
| 3 | `State 3: WiFi` | `0x3F4016A3` |
| 4 | `State 4: RC` | `0x3F4016B9` |

### Tasks / display / assets

| Symbol-like string | VA | Meaning |
| --- | --- | --- |
| `RadioTask` | `0x3F401658` | FreeRTOS task name for radio work |
| `loopTask` | `0x3F403649` | Arduino `loop()` task |
| `SSD1306 allocation failed` | `0x3F4016FA` | OLED driver (Adafruit-style) |
| `bitmapboot`, `bitmap1`…`bitmap4` | nearby DROM | Splash + per-state icons |
| `Connected` | `0x3F4016F0` | Status text |

### Libraries visible via path/assert strings

- ESP-IDF: `driver/gpio`, `i2c`, `uart`, `spi_flash`, `nvs_flash`, `esp_wifi`, `bt`, FreeRTOS, lwIP
- Arduino-ESP32 2.0.10 cores (`esp32-hal-uart.c`, etc.)
- App-level: dual **nRF24** over **HSPI + VSPI**, **SSD1306** over **I2C**

---

## 3. Ghidra project setup

### Create project

1. New project → non-shared → name e.g. `ESP32-BlueJammer-Combo`.
2. Import `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`.

### Language / processor

| Setting | Value |
| --- | --- |
| Architecture | **Xtensa** |
| Processor | **Xtensa** (ESP32 = LX6 dual-core) |
| Variant | Prefer **ESP32** / little-endian if offered |
| Base / load | Do **not** load as one blob at `0x0` |

### Recommended load strategy

ESP32 images are multi-segment. Prefer one of:

**A. Use `esp32_image` / esptool helpers** (if available in your Ghidra scripts ecosystem), or  

**B. Manual multi-segment import** (reliable):

1. Extract each segment with a short script, **or** in Ghidra use *Add To Program* / memory blocks:
   - DROM block: file `0x20`, length `0x1CFB0` → VA **`0x3F400020`**
   - IROM block: file `0x20020`, length `0x99060` → VA **`0x400D0020`**
   - IRAM block: file `0xBC008`, length `0x1A278` → VA **`0x40080000`**
   - DRAM blocks similarly at `0x3FFBDB60` and `0x3FFC0BA0`
2. Set entry point / analysis start: **`0x40082F0C`**.
3. Run **Auto Analysis** (default analyzers + decompiler).

### Address map cheat sheet

```text
0x3F400000  Flash cached .rodata (DROM)   ← strings, bitmaps
0x3FFB0000  Internal DRAM
0x40080000  IRAM (vectors / entry)
0x400D0000  Flash cached .text (IROM)    ← most code
```

---

## 4. Finding important functions (string → xref method)

In Ghidra: **Search → For Strings**, then **References → Show References to Address**.

### Priority string → expected function role

| Anchor string (VA) | Expected function rename | Notes |
| --- | --- | --- |
| HSPI success/fail (`0x3F4002C4` / `0x3F400482`) | `initHSPI_nRF24()` | SPI bus + `radio.begin()` style |
| VSPI success/fail (`0x3F400608` / `0x3F4007CB`) | `initVSPI_nRF24()` | Second nRF24 |
| `SSD1306 allocation failed` (`0x3F4016FA`) | `initDisplay()` / `initializeOLED()` | Early in `setup()` |
| `bitmapboot` (`0x3F40082D`) | `drawSplashScreen()` | Boot logo |
| `State N: …` strings | `setState()` / `printState()` / `updateUI()` | Mode switch |
| `Firmware : Combo-…` | `drawAbout()` / splash text | Banner |
| `RadioTask` (`0x3F401658`) | `radioTask()` | `xTaskCreate*` argument |
| `loopTask` | Arduino core | Calls user `loop()` |

### Pointer table already located (IROM literals)

Cross-refs from code often go through nearby pointer slots (literal pools):

| String | Pointer stored at (IROM VA) |
| --- | --- |
| `RadioTask` | `0x400D00EC` |
| `State 1: Bluetooth` | `0x400D010C` |
| `State 2: BLE` | `0x400D0114` |
| `State 3: WiFi` | `0x400D011C` |
| `State 4: RC` | `0x400D0124` |
| `State 0: Idle` | `0x400D013C` |
| `SSD1306 allocation failed` | `0x400D0190` |
| `bitmapboot` | `0x400D00A0`, `0x400D0198` |
| `by @emensta` | `0x400D01A0` |

In Ghidra, open `0x400D010C` and **Show References to Address** — callers are almost certainly the mode-switch / status-print path.

### Typical Arduino shape (what to recover)

```text
app_main / main_task
  └── setup()                    ← init once
        ├── initDisplay()        ← SSD1306 / Wire / I2C
        ├── drawSplashScreen()   ← bitmapboot + banner strings
        ├── initHSPI_nRF24()
        ├── initVSPI_nRF24()
        ├── pinMode(BOOT, INPUT) / LED GPIO27
        └── xTaskCreate(radioTask, "RadioTask", ...)
  └── loop()                     ← loopTask
        ├── handleButtons()      ← BOOT pin edge
        ├── updateStateMachine()
        ├── drawMenu() / drawStatus()
        └── statusLedBlink(state)
```

---

## 5. Call graph (recovered / hypothesized)

```text
setup()
 ├── initDisplay()
 │    ├── Wire.begin(SDA=4, SCL=5)      # from project pinout
 │    ├── SSD1306 constructor / begin()
 │    └── on fail → print "SSD1306 allocation failed"
 ├── drawSplashScreen()
 │    ├── drawBitmap(bitmapboot)
 │    ├── print "Firmware : Combo-Channel-Select..."
 │    ├── print github URL
 │    └── print "by @emensta"
 ├── initHSPI_nRF24()
 │    ├── SPI HSPI begin (SCK=14, MOSI=13, MISO=12, CSN=15)
 │    ├── CE=16
 │    └── success/fail serial banner
 ├── initVSPI_nRF24()
 │    ├── SPI VSPI begin (SCK=18, MOSI=23, MISO=19, CSN=21)
 │    ├── CE=22
 │    └── success/fail serial banner
 ├── configureStatusLed(GPIO27)
 └── create RadioTask

loop() / UI task
 ├── readBootButton()                 # ESP32 BOOT button
 ├── if pressed → nextState()
 │    └── state = (state % 4) + 1    # 1..4 (or include 0 Idle)
 ├── applyChannelPlan(state)
 │    ├── State1 → BT channel set (79 ch / 2.402–2.480)
 │    ├── State2 → BLE plan (40 ch)
 │    ├── State3 → WiFi plan (14 ch)
 │    └── State4 → RC plan (1–125)
 ├── updateOLED(state, bitmapN)
 ├── blinkLed(state)                  # 1..4 blinks
 └── serial print "State N: ..."

RadioTask (continuous)
 ├── for each active nRF24:
 │    ├── setChannel(ch)
 │    ├── startConstCarrier / write noise / flood packets
 │    └── hop channel within plan
 └── delay / yield
```

Build the real graph in Ghidra via **Window → Function Graph** / **Call Tree** after renaming.

---

## 6. Peripherals identification

### Application hardware (from strings + public pinout)

| Peripheral | Interface | App usage |
| --- | --- | --- |
| **nRF24L01 #1** | **HSPI** | Primary 2.4 GHz TX |
| **nRF24L01 #2** | **VSPI** | Secondary 2.4 GHz TX |
| **SSD1306 0.96" OLED** | **I2C** (SDA GPIO4, SCL GPIO5) | Menu / state icons |
| **Status LED** | **GPIO 27** | Blink count = mode |
| **BOOT button** | strapping / GPIO0 | Mode select |
| **UART0** | USB-Serial | Init banners + state logs |
| **Wi‑Fi / BT MAC (ESP32)** | on-chip | Present in IDF; combo firmware primarily uses nRF24 for RF work |
| **NVS / flash** | SPI flash | IDF plumbing (calibration, etc.) |

### HSPI nRF24 pinout (project documentation)

| nRF24 | ESP32 |
| --- | --- |
| CE | GPIO 16 |
| CSN | GPIO 15 |
| SCK | GPIO 14 |
| MOSI | GPIO 13 |
| MISO | GPIO 12 |

### VSPI nRF24 pinout

| nRF24 | ESP32 |
| --- | --- |
| CE | GPIO 22 |
| CSN | GPIO 21 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |

### Separating library vs application code

| Region / trait | Classification |
| --- | --- |
| Asserts with `/IDF/components/...` | ESP-IDF library |
| `Arduino15\packages\esp32\...` paths | Arduino-ESP32 core |
| Custom banners with `####` and `nRF24 module` | **Application** |
| `State N:`, `bitmapN`, `RadioTask`, `by @emensta` | **Application** |
| `wifi_init`, `esp_bt`, lwIP | SDK (may be linked even if unused by main path) |

Focus RE effort on functions that xref the application strings only.

---

## 7. Rename plan (Ghidra bookmarks)

Start with `FUN_*` that reference the anchors below:

| Temporary name | Rename to | How to find |
| --- | --- | --- |
| `FUN_…` xref HSPI strings | `initHSPI_nRF24` | String xref |
| `FUN_…` xref VSPI strings | `initVSPI_nRF24` | String xref |
| `FUN_…` xref SSD1306 fail | `initOLED` | String xref |
| `FUN_…` xref bitmapboot | `drawSplashScreen` | String xref |
| `FUN_…` xref State strings | `logState` / `setOperatingMode` | Pointer table `0x400D010C+` |
| Task entry using `"RadioTask"` | `radioTask` | `xTaskCreate` arg |
| Caller of inits from Arduino setup path | `setup` | Often only init-once caller |
| Periodic UI/button logic | `loop` | Called from `loopTask` |

Also rename globals:

| Pattern | Suggested name |
| --- | --- |
| Byte/int cycled 0–4 | `g_currentState` |
| Two radio object-like structs | `g_radioHSPI`, `g_radioVSPI` |
| Display object | `g_display` |
| Bitmap pointer table | `g_stateBitmaps[]` |

---

## 8. Data structures to recover

### A. State machine

```text
enum OperatingState {
  STATE_IDLE = 0,   // "Idle & Status"
  STATE_BT   = 1,   // Bluetooth  ~79 ch
  STATE_BLE  = 2,   // BLE        ~40 ch
  STATE_WIFI = 3,   // WiFi       ~14 ch
  STATE_RC   = 4,   // RC/drone   1–125 ch
};
```

Look for:

- `switch (state)` or jump table after button handler  
- Arrays of channel min/max or hop lists per state  
- LED blink counters matching state index  

### B. Bitmap / UI assets

DROM contains labels:

- `bitmapboot` — splash  
- `bitmap1` … `bitmap4` — per-mode icons  

In Ghidra, select large const byte arrays near these labels (or pointers from `drawBitmap` xrefs). Dimensions are often 128×64 (full) or smaller icons (e.g. 32×32 / 64×48). Export as raw and view as monochrome bitmap.

### C. String / mode tables

Pointer cluster in IROM around `0x400D010C`–`0x400D013C` is a strong lead for:

```c
const char *kStateNames[] = {
  /* possibly reordered */ "State 1: Bluetooth", ...
};
```

Also recover parallel tables for bitmaps and channel configs (same index as state).

### D. nRF24 configuration tables

Near radio init / hop loop, look for:

- channel arrays (`uint8_t channels_bt[]`, etc.)  
- constants 79, 40, 14, 125  
- PA level, data rate, payload length constants  
- registers written via SPI (library style: `write_register`, `setChannel`)

### E. Channel plans (from project docs, verify in binary)

| Mode | Channels | Frequency (approx) |
| --- | --- | --- |
| Bluetooth | 79 | 2.402–2.480 GHz |
| BLE | 40 | 2.400–2.4835 GHz |
| WiFi | 14 | 2.400–2.4835 GHz |
| RC | 1–125 | 2.400–2.525 GHz |

Search IROM for immediate values `79`, `40`, `14`, `125` near `setChannel`-like code.

---

## Suggested Ghidra session order (checklist)

1. [ ] Multi-segment load (DROM/IROM/IRAM/DRAM)  
2. [ ] Auto-analysis  
3. [ ] Define strings in DROM; bookmark app strings  
4. [ ] Xref HSPI/VSPI init strings → rename radio init  
5. [ ] Xref SSD1306 / bitmapboot → rename display path  
6. [ ] Xref State strings / pointer table → rename mode switch  
7. [ ] Find `xTaskCreate` with `"RadioTask"` → rename `radioTask`  
8. [ ] Trace Arduino `setup`/`loop` (from `loopTask` / init-once callers)  
9. [ ] Recover `g_currentState` and channel tables  
10. [ ] Export bitmaps; document state machine in comments  

---

## Workspace artifacts generated

| File | Purpose |
| --- | --- |
| `analyze_fw.py` | Header parse + string categorization |
| `map_strings.py` | VA map + pointer xref locations |
| `firmware_strings.txt` | Full ASCII strings dump |
| `firmware_strings_interesting.txt` | Filtered interesting strings |
| `RE_ANALYSIS.md` | This report |

### Quick re-run

```powershell
esptool image-info .\Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
python .\analyze_fw.py
python .\map_strings.py
```

---

## Summary

| Question | Answer |
| --- | --- |
| Valid ESP32 image? | **Yes** — magic `0xE9`, checksum + SHA valid |
| SDK | **ESP-IDF 4.4.5** via **Arduino-ESP32 2.0.10** |
| Entry | **`0x40082F0C`** |
| App | Closed-source **Combo-Channel-Select** jammer UI + dual nRF24 |
| Display | **SSD1306** + named bitmaps |
| State machine | **Idle + BT + BLE + WiFi + RC** |
| Best RE entry points | String xrefs (not reset vector) |
| Code vs data | App logic in **IROM `0x400Dxxxx`**; strings/bitmaps in **DROM `0x3F40xxxx`** |

Next step in Ghidra: import with correct load addresses, then follow **string → xref → rename → call graph** starting from the HSPI init banner and `State 1: Bluetooth`.
