# Master Extraction Report — Complete Dump

**Binary:** `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`  
**Extraction date:** 2026-07-15  
**Method:** static analysis only (esptool, custom Python, string/xref mapping)

> Educational reverse-engineering only. This firmware is designed for intentional RF interference; operating it as a jammer is illegal in most jurisdictions.

---

## 1. File identity & integrity

| Field | Value |
| --- | --- |
| Filename | `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` |
| Size | **877,232 bytes** (856.67 KiB) |
| MD5 | `7dd270bbf3b947d0b68191ef5a2719ea` |
| SHA1 | `fc1b7b5a7ea6bfd8ef866938600acb539034ef21` |
| SHA256 | `2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c` |
| Image checksum | valid (`0x13`) |
| Image SHA256 (footer) | `c009263fae8f73ee29383ac56bfed62e2eef4fca80c377e1ed41e4d01f55a8b0` (valid) |
| ELF SHA256 (app_desc) | `81292e8df6005ce011d594030ec5f8fd5c170b485f80594f315be1ef05ed7e3d` |

---

## 2. ESP32 image header

| Field | Value |
| --- | --- |
| Magic | `0xE9` — **valid ESP image** |
| Chip | **ESP32** (chip ID 0) |
| Image version | 1 |
| Segments | 5 |
| Entry point | **`0x40082F0C`** (IRAM) |
| Flash mode | **DIO** |
| Flash size | **4 MB** |
| Flash frequency | **80 MHz** |
| WP pin | `0xEE` (disabled) |
| Min chip rev | v0.0 |
| Max chip rev | v655.35 (unrestricted) |
| Hash appended | yes |
| Secure version | 0 |

### esp_app_desc_t (at DROM `0x3F400020` / file `0x20`)

| Field | Value |
| --- | --- |
| Magic | `0xABCD5432` |
| Project name | `arduino-lib-builder` |
| App version | `esp-idf: v4.4.5 ac5d805d0e` |
| ESP-IDF | **v4.4.5** |
| Compile time | **16:41:45** |
| Compile date | **Jun 12 2023** |
| Arduino-ESP32 core (from paths) | **2.0.10** |
| Builder host path | `C:\Users\emens\AppData\Local\Arduino15\packages\esp32\...` |

---

## 3. Memory segments (extracted)

| # | Name | Load VA | Size | File offset | Entropy | Output file |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| 0 | **DROM** (.rodata) | `0x3F400020` | 118,704 | `0x000020` | 5.80 | `segments/seg0_DROM_0x3F400020.bin` |
| 1 | **DRAM1** (.data) | `0x3FFBDB60` | 12,352 | `0x01CFD8` | 3.31 | `segments/seg1_DRAM1_0x3FFBDB60.bin` |
| 2 | **IROM** (.text) | `0x400D0020` | 626,784 | `0x020020` | 7.13 | `segments/seg2_IROM_0x400D0020.bin` |
| 3 | **DRAM2** (.data) | `0x3FFC0BA0` | 12,152 | `0x0B9088` | 4.08 | `segments/seg3_DRAM2_0x3FFC0BA0.bin` |
| 4 | **IRAM** | `0x40080000` | 107,128 | `0x0BC008` | 6.96 | `segments/seg4_IRAM_0x40080000.bin` |

**VA formula (DROM):** `VA = 0x3F400000 + file_offset`  
**VA formula (IROM):** `VA = 0x400D0000 + (file_offset - 0x20000)` approximately; exact: `0x400D0020 + (file_off - 0x20020)`.

---

## 4. Application identity (from embedded strings)

| Item | Content |
| --- | --- |
| Product | **Combo-Channel-Select (BT-BLE-WiFi-RC)** |
| Project | **ESP32-BlueJammer** |
| Author | **@emensta** / `by @emensta` |
| URL | `https://github.com/EmenstaNougat/ESP32-BlueJammer` |
| Disclaimer 1 | `!Educational purposes only!` |
| Disclaimer 2 | `I'm not responsible for your actions!` |

### Serial console splash (UTF-8 box-drawing + block letters)

Full dump: `extracted/serial_splash_art.txt`

Reconstructed themes printed on boot / RF init:

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
╦ ╦╔═╗╔═╗╦       ╔═╗╦ ╦╔═╗╔═╗╔═╗╔═╗╔═╗     ← "HSPI SUCCESS" art
╠═╣╚═╗╠═╝║  ───  ╚═╗║ ║║  ║  ║╣ ╚═╗╚═╗
╩ ╩╚═╝╩  ╩       ╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝
Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY! ####...

(or FAIL variants with "HSPI FAILED" art)

Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY! ####...

(or FAIL variants)

####################################################################
  large "BY EMENSTA" block-letter banner
####################################################################
Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)
  large "BY EMENSTA" second banner
!Educational purposes only!
https://github.com/EmenstaNougat/ESP32-BlueJammer
I'm not responsible for your actions!
```

---

## 5. Complete application UI / state model

### States (confirmed strings + pointer table)

| ID | Serial / UI string | Bitmap label | Bitmap data VA (confirmed) |
| --- | --- | --- | --- |
| 0 | `State 0: Idle & Status` | — | — |
| 1 | `State 1: Bluetooth` | `bitmap1` | **`0x3F402080`** (800 bytes) |
| 2 | `State 2: Bluetooth Low Energy` | `bitmap2` | **`0x3F401D60`** (800 bytes) |
| 3 | `State 3: WiFi` | `bitmap3` | **`0x3F401A40`** (800 bytes) |
| 4 | `State 4: RC` | `bitmap4` | **`0x3F401720`** (800 bytes) |

Additional UI strings:

| String | VA |
| --- | --- |
| `bitmapboot` | `0x3F40082D` |
| `Connected` | `0x3F4016F0` |
| `SSD1306 allocation failed` | `0x3F4016FA` |
| `by @emensta` | `0x3F401714` |
| `RadioTask` | `0x3F401658` |
| `loopTask` | `0x3F403649` |

### Mode semantics (from project docs + firmware name)

| State | Band purpose | Channel count (docs) | Freq (docs) |
| --- | --- | --- | --- |
| BT | Classic Bluetooth | 79 | 2.402–2.480 GHz |
| BLE | Bluetooth Low Energy | 40 | 2.400–2.4835 GHz |
| WiFi | 2.4 GHz Wi‑Fi | 14 | 2.400–2.4835 GHz |
| RC | RC / drones etc. | 1–125 | 2.400–2.525 GHz |

User control (docs): **ESP32 BOOT button** cycles modes; status LED blink count = mode (1–4).

---

## 6. Critical code / data addresses (Ghidra ready)

### Confirmed function / task pointers

| Symbol | Address | Evidence |
| --- | --- | --- |
| Image entry | `0x40082F0C` | ESP header |
| **`radioTask` function** | **`0x400D236C`** | Literal next to `"RadioTask"` at `0x400D00F0` |
| RadioTask name string | `0x3F401658` | DROM |
| RadioTask stack size | **8192** (`0x2000`) | Immediate at `0x400D00E8` |
| `loopTask` string | `0x3F403649` | ptr `0x400D04F0` |

### State / bitmap pointer table (`0x400D010C`)

```
0x400D010C -> "State 1: Bluetooth"
0x400D0110 -> "bitmap1"
0x400D0114 -> "State 2: Bluetooth Low Energy"
0x400D0118 -> "bitmap2"
0x400D011C -> "State 3: WiFi"
0x400D0120 -> "bitmap3"
0x400D0124 -> "State 4: RC"
0x400D0128 -> "bitmap4"
0x400D013C -> "State 0: Idle & Status"
```

### OLED bitmap data table (`0x400D01A4`)

```
0x400D01A4 -> "bitmap1" label
0x400D01A8 -> 0x3F402080   bitmap1 pixels
0x400D01AC -> "bitmap2" label
0x400D01B0 -> 0x3F401D60   bitmap2 pixels
0x400D01B4 -> "bitmap3" label
0x400D01B8 -> 0x3F401A40   bitmap3 pixels
0x400D01BC -> "bitmap4" label
0x400D01C0 -> 0x3F401720   bitmap4 pixels
```

Also:

```
0x400D0190 -> "SSD1306 allocation failed"
0x400D0198 -> "bitmapboot"
0x400D019C -> 0x3F4023A0   (likely boot/splash related asset)
0x400D01A0 -> "by @emensta"
0x400D0164 -> "Connected"
```

### HSPI / VSPI init string pointers

```
0x400D003C -> HSPI SUCCESS long message
0x400D0050 -> HSPI FAIL long message
0x400D0064 -> VSPI SUCCESS long message
0x400D0078 -> VSPI FAIL long message
```

Plus UTF-8 art line pointers `0x400D002C`–`0x400D0074`.

### Immediate constants near app pool

| Address | Value | Likely meaning |
| --- | ---: | --- |
| `0x400D0094` | **115200** | UART baud rate |
| `0x400D0098` | 20000 | delay / timeout (µs or ms scale) |
| `0x400D00E8` | **8192** | `RadioTask` stack size |
| `0x400D012C` | 16000000 | clock / timing related |
| `0x400D01C8` | 400000 | SPI / timing |
| `0x400D01CC` | 100000 | SPI / timing |
| `0x400D01D0` | 35000 | timing |
| `0x400D01D4` | 10000000 | timing |
| `0x400D01DC` | 5000 | delay |
| `0x400D01E0` | 1000000 | 1e6 (µs/sec or similar) |
| `0x400D014C` | 0x80000 | size / mask |
| `0x400D0154` | `0x001A0037` | packed field (investigate in Ghidra) |

---

## 7. Hardware / peripherals recovered

### Application hardware

| Device | Interface | Role |
| --- | --- | --- |
| **nRF24L01 #1** | **HSPI** | 2.4 GHz TX module 1 |
| **nRF24L01 #2** | **VSPI** | 2.4 GHz TX module 2 |
| **SSD1306 OLED** | **I2C** | Status / mode graphics |
| Status LED | GPIO (docs: **27**) | Blink = mode index |
| Mode button | BOOT (docs: **GPIO0**) | Cycle states |
| UART0 | USB-Serial **115200** | Splash + state logs |

### Documented pinout (project; matches dual-SPI design in firmware strings)

**HSPI nRF24**

| nRF24 | ESP32 |
| --- | --- |
| CE | GPIO 16 |
| CSN | GPIO 15 |
| SCK | GPIO 14 |
| MOSI | GPIO 13 |
| MISO | GPIO 12 |

**VSPI nRF24**

| nRF24 | ESP32 |
| --- | --- |
| CE | GPIO 22 |
| CSN | GPIO 21 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |

**OLED I2C:** SDA GPIO **4**, SCL GPIO **5**

### Drivers / stacks linked (from path & API strings)

**ESP-IDF components seen (28):**  
`app_update`, `bootloader_support`, `bt`, `driver`, `efuse`, `esp_event`, `esp_hw_support`, `esp_ipc`, `esp_netif`, `esp_phy`, `esp_ringbuf`, `esp_system`, `esp_timer`, `esp_wifi`, `espcoredump`, `freertos`, `hal`, `heap`, `log`, `lwip`, `mbedtls`, `newlib`, `nvs_flash`, `pthread`, `spi_flash`, `vfs`, `wifi_provisioning`, `wpa_supplicant`

**Peripheral APIs referenced:** GPIO, I2C, UART, SPI flash, RTCIO, Wi‑Fi, BTDM Bluetooth controller, PHY init, NVS, OTA stubs, FreeRTOS tasks.

**App-specific RF library:** nRF24 over HSPI/VSPI (no `RF24` C++ symbol strings; logic is compiled in). Display uses **SSD1306** allocation pattern (Adafruit-style).

---

## 8. FreeRTOS / tasks

| Task name | Role |
| --- | --- |
| `main_task` | IDF/Arduino startup |
| `loopTask` | Arduino `loop()` |
| **`RadioTask`** | Application RF worker (`0x400D236C`, stack 8192) |
| `uart_event_task` | UART driver |
| `ipc_task` | ESP IPC |
| `sc_ack_send_task` | smartconfig (linked) |
| `btController` / `ke_task` / `lc_task` / `lm_task` | BT controller internals |
| `elf_save_task` | coredump |
| `IDLE` | FreeRTOS idle |
| `wifi` task | Wi‑Fi stack (linked) |

---

## 9. Strings statistics

| Metric | Count |
| --- | --- |
| ASCII strings len ≥ 4 | **8,698** |
| Strings len ≥ 8 | 2,677 |
| IROM → DROM string pointers | **1,290** |
| App-level filtered strings | ~1,875 |
| DROM “readable” strings | 1,631 |
| Categories dumped | 13 |

### Full application messages (author-written)

```
Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY! ####...
!!! Hardware Serial Peripheral Interface start failure! HSPI nRF24 module could NOT be initialized! ####...
Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY! ####...
!!! Variable Serial Peripheral Interface start failure! VSPI nRF24 module could NOT be initialized! ####...
Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)
https://github.com/EmenstaNougat/ESP32-BlueJammer
!Educational purposes only!
I'm not responsible for your actions!
State 1: Bluetooth
State 2: Bluetooth Low Energy
State 3: WiFi
State 4: RC
State 0: Idle & Status
RadioTask
bitmapboot / bitmap1 / bitmap2 / bitmap3 / bitmap4
Connected
SSD1306 allocation failed
by @emensta
```

---

## 10. Bitmaps & assets

### Confirmed OLED bitmaps (800 bytes each = spaced `0x320`)

| Name | Data VA | Extracted path |
| --- | --- | --- |
| bitmap4 (RC) | `0x3F401720` | `confirmed_assets/bitmap4_0x3F401720.bin` |
| bitmap3 (WiFi) | `0x3F401A40` | `confirmed_assets/bitmap3_0x3F401A40.bin` |
| bitmap2 (BLE) | `0x3F401D60` | `confirmed_assets/bitmap2_0x3F401D60.bin` |
| bitmap1 (BT) | `0x3F402080` | `confirmed_assets/bitmap1_0x3F402080.bin` |
| boot/extra | `0x3F4023A0` | `confirmed_assets/bitmapboot_or_extra_0x3F4023A0.bin` |

PBM previews generated for widths 100/80/50 (geometry not 100% confirmed; open in image viewer and try SSD1306 page format).  
Also bulk candidates: `bitmaps_candidates/` (40) and `bitmap_from_pointers/` (85).

**800 bytes** ⇒ possible geometries: **100×64** (page mode), **80×80**, or custom icon with padding.

---

## 11. Channel tables

Static scan for clean u8 arrays of length 14/40/79/125 produced many false positives (strings/structs).  
**No definitive labeled channel table** was isolated without decompilation.

**How to finish in Ghidra:**

1. Go to `radioTask` at **`0x400D236C`**.
2. Find calls that write nRF24 **RF_CH** (register 0x05) or SPI transfers with channel byte.
3. Xref immediates **14, 40, 79, 125** near that function.
4. Expect either:
   - hop loops `for (ch = min; ch <= max; ch++)`, or
   - arrays of channel numbers per state.

Docs imply continuous hopping across the mode’s channel plan on both nRF24 modules.

---

## 12. Recovered program architecture

```
Reset / IRAM entry 0x40082F0C
  └── ESP-IDF + Arduino init
        ├── setup()  [inferred]
        │     ├── Serial @ 115200
        │     ├── print UTF-8 splash / disclaimers
        │     ├── init SSD1306 (I2C) — fail string if OOM
        │     ├── draw bitmapboot + "by @emensta"
        │     ├── init HSPI nRF24 — SUCCESS/FAIL art + text
        │     ├── init VSPI nRF24 — SUCCESS/FAIL art + text
        │     ├── configure LED + BOOT button
        │     └── xTaskCreate(radioTask @ 0x400D236C, "RadioTask", stack=8192, ...)
        ├── loopTask → loop()
        │     ├── read BOOT button → next state 0..4
        │     ├── update OLED bitmapN + state text
        │     ├── blink LED N times
        │     └── Serial.print state string
        └── RadioTask
              └── continuous TX / hop on both nRF24 per current state plan
```

---

## 13. Build fingerprint

| Item | Value |
| --- | --- |
| Framework | Arduino-ESP32 **2.0.10** on ESP-IDF **4.4.5** |
| Project name in binary | `arduino-lib-builder` (Arduino core builder stub) |
| Compile | **2023-06-12 16:41:45** |
| Developer machine user | `emens` (path leak) |
| Source closed | Author states closed-source; binary-only distribution |

---

## 14. What is *not* recoverable without decompilation

| Item | Status |
| --- | --- |
| Full C/C++ source | Stripped; not present |
| Exact pin numbers in code | Not in strings; use docs + GPIO API xrefs |
| Exact channel hop algorithm | Needs Ghidra on `0x400D236C` |
| nRF24 PA level / data rate / payload | Needs SPI write analysis |
| Encryption / auth | None apparent (open RF flood design) |
| Wi‑Fi/BT stack used for jamming | Linked but app RF path is **nRF24**-centric |
| Original variable names | Stripped (except task/assert strings) |

---

## 15. Output file index (`extracted/`)

### Core reports
- `MASTER_EXTRACTION_REPORT.md` — this file
- `COMPLETE_EXTRACTION.md` — first-pass report
- `DEEP_SUMMARY.md` — second-pass summary
- `metadata.json` — hashes, header, segments, components
- `serial_splash_art.txt` — full decoded serial banners

### Strings
- `all_strings.txt` — 8698 strings
- `all_strings_with_addresses.tsv` / `.json` — with VA + file offset
- `app_level_strings.tsv`, `app_messages_full.txt`
- `drom_readable_strings.txt`
- `strings_by_category/*.txt` (13 categories)
- `urls.txt` → github BlueJammer link
- `task_names.txt`, `symbol_like_identifiers.txt`, `functions_mentioned_in_strings.txt`

### Cross-refs / tables
- `key_string_xrefs.json`
- `app_string_pointer_tables.json`
- `string_pointer_tables.json`
- `irom_to_drom_string_pointers.json` (1290 entries)
- `constants_and_tables.json`
- `possible_channel_arrays.json` (heuristic; noisy)
- `library_api_strings.json`

### Binaries / assets
- `segments/seg0..seg4_*.bin` — raw loadable segments for Ghidra
- `confirmed_assets/bitmap{1-4}_*.bin` + PBM previews
- `bitmaps_candidates/` — 40 heuristic candidates
- `bitmap_from_pointers/` — pointer-derived chunks + PBM
- `hex_regions/*.txt` — hex dumps of app DROM zones

### Scripts (workspace root)
- `full_extract.py`, `deep_extract.py`, `analyze_fw.py`, `map_strings.py`, `decode_splash.py`

---

## 16. Recommended next actions in Ghidra

1. Load the 5 segment bins at their VAs (or full image with correct block mapping).
2. Navigate to **`0x400D236C`** → rename `radioTask`.
3. Xref **`0x400D010C`** table → rename `setState` / `drawState`.
4. Xref HSPI/VSPI strings → rename `initHSPI_nRF24` / `initVSPI_nRF24`.
5. Xref `SSD1306 allocation failed` → rename `initOLED`.
6. Find Arduino `setup`/`loop` via `loopTask` and one-time init callers.
7. Recover channel hop logic and rename globals `g_state`, `g_radioHSPI`, `g_radioVSPI`.

---

## 17. One-page cheat sheet

```
FILE     Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
CHIP     ESP32  |  IDF 4.4.5  |  Arduino-ESP32 2.0.10  |  built 2023-06-12
ENTRY    0x40082F0C
APP      ESP32-BlueJammer Combo Channel Select by @emensta
RF       2x nRF24 (HSPI + VSPI)
UI       SSD1306 + 5 states (Idle/BT/BLE/WiFi/RC) + BOOT button
TASK     radioTask @ 0x400D236C  stack 8192
SERIAL   115200, big UTF-8 splash, state logs
DROM     0x3F400020   IROM 0x400D0020   IRAM 0x40080000
GITHUB   https://github.com/EmenstaNougat/ESP32-BlueJammer
```

**Everything extractable by automated static analysis has been written under `extracted/`.**  
Dynamic/decompiler work (Ghidra) is the remaining path for channel algorithms and exact GPIO immediates inside code.
