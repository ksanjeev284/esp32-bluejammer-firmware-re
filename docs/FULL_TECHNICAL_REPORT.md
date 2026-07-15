# Full Technical Report — ESP32 Combo-Channel-Select Firmware RE

**Target:** `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`  
**Purpose:** Educational reverse engineering documentation  
**Method:** Static analysis only (`esptool`, custom Python, Ghidra 12.1 Xtensa)

> **Disclaimer:** Radio jamming is illegal in most jurisdictions. This document describes how a published firmware image is structured and how RE tools recover its logic. Do not operate jamming hardware.

---

## 1. Executive summary

The binary is a valid **ESP32 application image** built with **Arduino-ESP32 2.0.10** (ESP-IDF **v4.4.5**) on **2023-06-12**. It implements a multi-mode 2.4 GHz RF noise generator using **two nRF24L01 modules** (HSPI + VSPI), an optional **SSD1306 OLED**, a **BOOT button** for mode selection, and a **status LED**.

Application logic was recovered despite stripped symbols by:

1. Parsing the ESP image header and flash segments  
2. Cataloguing strings and pointer tables  
3. Multi-segment Ghidra load (DROM/IROM/IRAM/DRAM)  
4. Decompiling functions reached from string xrefs  

Approximately **4244** functions exist in the linked binary (mostly SDK/libraries). Application-specific logic concentrates around **`0x400D2000`–`0x400D4000`**.

---

## 2. File identity

| Field | Value |
| --- | --- |
| Filename | `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` |
| Size | 877,232 bytes |
| MD5 | `7dd270bbf3b947d0b68191ef5a2719ea` |
| SHA1 | `fc1b7b5a7ea6bfd8ef866938600acb539034ef21` |
| SHA256 | `2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c` |
| Image checksum | valid |
| App hash footer | valid |

### ESP image header (`esptool image-info`)

| Field | Value |
| --- | --- |
| Magic | `0xE9` |
| Chip | ESP32 (ID 0) |
| Entry | `0x40082F0C` |
| Segments | 5 |
| Flash | 4 MB, DIO, 80 MHz |
| Project name | `arduino-lib-builder` |
| ESP-IDF | v4.4.5 (`ac5d805d0e`) |
| Compile | Jun 12 2023 16:41:45 |
| ELF SHA256 | `81292e8df6005ce011d594030ec5f8fd5c170b485f80594f315be1ef05ed7e3d` |

Path strings leak Arduino package path under user `emens` and core **2.0.10**.

---

## 3. Memory map / segments

| # | Name | Load VA | Size | File off | Role |
| --- | --- | ---: | ---: | ---: | --- |
| 0 | DROM | `0x3F400020` | 118,704 | `0x20` | .rodata (strings, bitmaps) |
| 1 | DRAM1 | `0x3FFBDB60` | 12,352 | `0x1CFD8` | .data |
| 2 | IROM | `0x400D0020` | 626,784 | `0x20020` | .text (main code) |
| 3 | DRAM2 | `0x3FFC0BA0` | 12,152 | `0xB9088` | .data |
| 4 | IRAM | `0x40080000` | 107,128 | `0xBC008` | vectors / hot code |

Segment binaries: `artifacts/segments/`.

---

## 4. Application identity strings

Embedded marketing / UI text (DROM):

- `Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)`  
- `https://github.com/EmenstaNougat/ESP32-BlueJammer`  
- `by @emensta`  
- `!Educational purposes only!`  
- `I'm not responsible for your actions!`  
- UTF-8 box-drawing “HSPI SUCCESS / FAILED”, “VSPI SUCCESS / FAILED”, “BY EMENSTA” banners  

RF init banners mention **HSPI/VSPI nRF24 module** success and failure.

State strings:

| State | String |
| --- | --- |
| 0 | State 0: Idle & Status |
| 1 | State 1: Bluetooth |
| 2 | State 2: Bluetooth Low Energy |
| 3 | State 3: WiFi |
| 4 | State 4: RC |

Tasks: `RadioTask`, `loopTask`.

Full dumps: `artifacts/strings/`.

---

## 5. Architecture

### 5.1 Call graph (recovered)

```text
Arduino runtime
 └─ setup @ 0x400D2714
     ├─ Serial.begin(115200, ...)
     ├─ pinMode(27, OUTPUT)          // LED
     ├─ pinMode(0, INPUT_PULLUP)     // BOOT
     ├─ initOLED @ 0x400D2D68        // Wire 4/5, SSD1306 0x3C
     ├─ draw splash bitmapboot 128×64
     ├─ delay(2000)
     ├─ print splash / disclaimers / URL
     └─ xTaskCreate(radioTask, "RadioTask", 8192, ...)

 └─ loop @ 0x400D2BFC
     ├─ digitalRead(0)  // BOOT
     ├─ long-press ~500ms → pause RF
     └─ dispatch g_state:
          0 → enterState_Idle
          1 → enterState_BT
          2 → enterState_BLE
          3 → enterState_WiFi
          4 → enterState_RC

 radioTask @ 0x400D236C  (FreeRTOS, forever)
     ├─ SPI HSPI bus2 pins 14,12,13,15
     ├─ SPI VSPI bus3 pins 18,19,23,21
     ├─ nrf_begin both radios; print SUCCESS/FAIL art
     ├─ configure: PA_MAX+LNA, 2Mbps, CRC off, startConstCarrier
     └─ loop:
          if pause: stop carrier; wait; restart
          ch = random() % mode_max
          setChannel(radioH, ch); setChannel(radioV, ch)
          (×100 then delay 1ms)
```

### 5.2 Global objects (logical)

| Symbol / DAT | Meaning |
| --- | --- |
| `DAT_400d0024` → BSS `0x3FFC3B88` | RF24 radio HSPI |
| `DAT_400d0054` → BSS `0x3FFC3B60` | RF24 radio VSPI |
| `PTR_DAT_400d0080` | `g_state` 0..4 |
| `DAT_400d007c` | pause flag |
| `DAT_400d0144` | SSD1306 display object |
| `DAT_400d0028` | HardwareSerial |

### 5.3 Radio object layout (`RF24_ctor` @ `0x400D30A8`)

| Offset | Field |
| ---: | --- |
| +4 | CE pin (uint8) |
| +5 | CSN pin (uint8) |
| +8 | SPI speed / related |
| +0x0D | payload len (0x20) |
| +0x1C | 0x105 (addr config) |
| +0x24 | csDelay (5) |

Init (`0x400D29F8`):

```c
RF24_ctor(radioH, CE=16, CSN=15, speed);
RF24_ctor(radioV, CE=22, CSN=21, speed);
```

---

## 6. RF behavior detail

### 6.1 Channel selection

| Mode | N | Effective channels |
| --- | ---: | --- |
| BT | 79 | 0–78 |
| BLE | 39 | 0–38 |
| WiFi | 14 | 0–13 |
| RC | 125 | 0–124 |

`setChannel` writes nRF24 register **5 (RF_CH)** and clamps to ≤ **125**.

### 6.2 Modulation / TX style

Uses RF24 **`startConstCarrier`** (register RF_SETUP continuous wave bits `0x90` ORed), not merely packet flood. After begin:

- stopListening  
- setRetries(0,0)  
- setPALevel(MAX, LNA enable)  
- setDataRate(**2 Mbps**)  
- setCRCLength(**disabled**)  
- startConstCarrier  

### 6.3 Pause behavior

BOOT held ≥ ~500 ms sets pause flag; `radioTask` stops carrier on both modules until cleared.

---

## 7. UI / OLED

| Asset | Geometry | Notes |
| --- | --- | --- |
| bitmapboot | 128×64 | splash |
| bitmap1..4 | 128×50 (800 bytes) | mode icons at y=12 |
| Text | — | `by @emensta`, state names, OK/FAIL |

Idle screen shows HSPI/VSPI connected status via `isChipConnected`.

LED: blink count = mode (1–4), ~150 ms pulses, 1000 ms gap after count.

---

## 8. Libraries linked (from asserts/paths)

ESP-IDF components observed include: `driver` (GPIO/I2C/UART), `spi_flash`, `nvs_flash`, `esp_wifi`, `bt`, FreeRTOS, lwIP, mbedTLS, `esp_event`, `esp_netif`, phy, heap, etc.

**Application RF path is nRF24-centric.** Wi‑Fi/BT stacks appear linked but are not the jam path in decompiled app logic.

---

## 9. Ghidra findings summary

| Metric | Value |
| --- | --- |
| Language | `Xtensa:LE:32:default` |
| Functions | 4244 |
| App cluster fns decompiled | 71+ |
| Key decomp files | `artifacts/ghidra/decomp/*.c` |

See also:

- `artifacts/ghidra/GHIDRA_ANALYSIS_REPORT.md`  
- `artifacts/ghidra/FINAL_COMPLETE_FINDINGS.md`  
- `artifacts/ghidra/functions.txt`  

---

## 10. Artifact catalog

### firmware/

| File | Description |
| --- | --- |
| `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` | Original image under study |

### artifacts/segments/

| File | Load at |
| --- | --- |
| `seg0_DROM_0x3F400020.bin` | `0x3F400020` |
| `seg1_DRAM1_0x3FFBDB60.bin` | `0x3FFBDB60` |
| `seg2_IROM_0x400D0020.bin` | `0x400D0020` |
| `seg3_DRAM2_0x3FFC0BA0.bin` | `0x3FFC0BA0` |
| `seg4_IRAM_0x40080000.bin` | `0x40080000` |

### artifacts/strings/

String dumps, TSV with VAs, JSON xrefs, metadata, splash art UTF-8.

### artifacts/ghidra/

Reports, full function list, decompiled C for app and helpers.

### scripts/

Python extractors used during analysis (`full_extract.py`, `map_strings.py`, etc.).

### ghidra_scripts/

- `LoadEsp32Firmware.java` — multi-segment load + labels  
- `ExportEsp32Findings.java` — export xrefs/decomp  
- `DecompileMore.java` / `DecompileGaps.java` / `FindEverything.java`  

---

## 11. What cannot be recovered statically

- Original C++ source names (stripped)  
- Author comments / uncommitted code  
- BSS initial values (zero until runtime constructors)  
- Real-world RF range / legality outcomes  
- Analog front-end behavior of PA+LNA modules  

---

## 12. Educational takeaways

1. **ESP images are multi-segment** — loading at `0x0` loses all xrefs.  
2. **Strings + literal pools beat reset-vector reading** for app logic.  
3. **FreeRTOS task names** (`RadioTask`) are gold anchors.  
4. **Known libraries (RF24, Adafruit SSD1306)** make decompiled stubs recognizable.  
5. **Pin immediates** in `movi` instructions confirm hardware without schematics.  

---

## 13. References

- [ESP32-BlueJammer upstream project](https://github.com/EmenstaNougat/ESP32-BlueJammer)  
- [esptool](https://github.com/espressif/esptool)  
- [Ghidra](https://github.com/NationalSecurityAgency/ghidra)  
- nRF24L01 product specification (Nordic)  
- ESP-IDF / Arduino-ESP32 documentation  

---

*End of full technical report.*
