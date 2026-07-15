# Firmware From Start to End — Complete Inventory

This document is the **master map of the entire original binary**.  
Nothing in the file layout is left unlisted. Application logic is fully recovered; remaining bulk is SDK/library code (catalogued by address, not line-by-line decompiled).

**Primary data tree:** [`artifacts/complete_inventory/`](../artifacts/complete_inventory/)

---

## Executive summary

| Item | Value |
| --- | --- |
| File | `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` |
| Size | 877,232 bytes |
| SHA256 | `2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c` |
| Entropy | 7.04 bits/byte |
| Format | ESP32 app image magic `0xE9` |
| Segments | 5 (DROM, DRAM, IROM, DRAM, IRAM) |
| Functions (Ghidra) | **4244** |
| C-strings extracted | **14053** |
| App logic recovery | **Complete** (pins, FSM, RF, UI, tasks) |
| Full SDK line-by-line decomp | Not useful — addresses catalogued in CSV |

---

## File layout (byte-accurate)

```
0x000000  ESP image header (24 bytes) + extended header
0x000018  Segment 0 header
0x000020  Segment 0 DROM  118704 B  → VA 0x3F400020
0x01CFD0  Segment 1 header
0x01CFD8  Segment 1 DRAM1  12352 B  → VA 0x3FFBDB60
0x020018  Segment 2 header
0x020020  Segment 2 IROM  626784 B  → VA 0x400D0020
0x0B9080  Segment 3 header
0x0B9088  Segment 3 DRAM2  12152 B  → VA 0x3FFC0BA0
0x0BC000  Segment 4 header
0x0BC008  Segment 4 IRAM  107128 B  → VA 0x40080000
0x0D6280  Padding zeros
0x0D628F  Checksum 0x13
0x0D6290  Image SHA256 (32 bytes) ends file
```

Full table: `artifacts/complete_inventory/COMPLETE_INVENTORY.md`

---

## Segment contents (what lives where)

### DROM `0x3F400020` (const data) — fully mapped

| VA range | Content |
| --- | --- |
| 0x3F400020 | `esp_app_desc_t` (project, IDF 4.4.5, date Jun 12 2023) |
| 0x3F400120–0x3F40082C | RF serial banners + UTF-8 box art |
| 0x3F40082D–0x3F40171F | bitmapboot label, # art, BY EMENSTA, firmware banner, states |
| 0x3F401720–0x3F40207F | bitmap4, bitmap3, bitmap2 (800 B each) |
| 0x3F402080–0x3F40239F | bitmap1 (800 B) |
| 0x3F4023A0–0x3F4027A0 | bitmapboot pixels (1024 B) |
| 0x3F402915–0x3F402E15 | **Adafruit GLCD 5×7 font** (1280 B) |
| rest | ESP-IDF / Arduino rodata strings |

Raw: `artifacts/complete_inventory/DROM_FULL.bin`  
Assets: `asset_bitmap*.bin`, `asset_glcdfont.bin`

### DRAM1 `0x3FFBDB60` — .data (initialized)

| VA | Init | Name |
| ---: | ---: | --- |
| +0x08 | 1 | g_ledBlinkTarget |
| +0x0C | 1 | g_ledLevel |
| +0x10 | **45** | carrier_ch VSPI |
| +0x14 | **45** | carrier_ch HSPI |
| +0x18 | 1 | g_savedState |
| +0x1C | **1** | **g_state = BT** |

Full words: `DRAM1_WORDS.json`, `DRAM1_FULL.bin`

### DRAM2 `0x3FFC0BA0` — more .data

SDK strings and init (e.g. hex format helpers). Full: `DRAM2_FULL.bin`

### IROM `0x400D0020` — code

- **App cluster:** ~0x400D2300–0x400D4000 (setup/loop/radio/UI/RF24)  
- **Literal pool:** 0x400D0020–0x400D0800 (strings, RAM ptrs, immediates)  
- **Libraries:** Adafruit, Wire, SPI, WiFi/BT stack glue, etc.  

Raw: `IROM_FULL.bin`  
All functions: `artifacts/ghidra/ALL_FUNCTIONS.csv` (4244 rows)

### IRAM `0x40080000` — vectors / hot code

- Entry **`0x40082F0C`** at IRAM+0x2F0C  
- Raw: `IRAM_FULL.bin`, `IRAM_entry_128B.bin`

---

## Application logic (nothing left hidden)

### Boot flow
1. IDF/Arduino runtime → entry IRAM  
2. `setup` @ `0x400D2714`  
3. Serial 115200, LED27, OLED I2C 4/5 addr 0x3C  
4. Splash bitmapboot 2s + serial banners  
5. Create `RadioTask` stack 8192 prio 1  
6. **`g_state` starts at 1 (BT)** → hops after radio init  

### Runtime
- `loop` @ `0x400D2BFC`: BOOT short cycle 1–4, long pause, short resume  
- `radioTask` @ `0x400D236C`: dual SPI nRF24, constant carrier, independent hop  
- Channels: BT 0–78, BLE 0–38, WiFi 0–13, RC 0–124  
- Idle UI: `R1=` `R2=` `USB` `Connected`  

### Pins (complete)
See `docs/GLOBALS_AND_CONSTANTS.md` / `hardware_bom.json`.

### SPI bit protocol
```
W_REG: CSN↓  (reg|0x20)  value  CSN↑
R_REG: CSN↓  reg  0xFF  CSN↑
```

### RF24 begin + app configure
See `artifacts/mine_pass/rf24_sequences.json`.

---

## What “nothing hidden” means vs full source

| Layer | Status |
| --- | --- |
| Every **byte range** of the file assigned a role | **Done** |
| Every **segment** dumped raw + hashed | **Done** |
| Every **C-string** listed with VA | **Done** (14053) |
| Every **Ghidra function** listed (addr,name,size) | **Done** (4244 CSV) |
| **App** control flow decompiled & documented | **Done** |
| **RF24 / SSD1306 / GPIO / SPI** app wrappers decompiled | **Done** |
| Entire WiFi/BT/lwIP/mbedTLS line-by-line | **Catalogued only** (SDK, not app secrets) |
| Bit-identical rebuild of original SHA256 | **Impossible** without author’s toolchain |

There are **no hidden app features** left (no secret menus, no extra protocols, no crypto keys). Remaining code is standard Espressif/Arduino/Adafruit/RF24 libraries.

---

## Artifact index (`artifacts/complete_inventory/`)

| File | Purpose |
| --- | --- |
| `COMPLETE_INVENTORY.md` | This narrative (generated) |
| `INDEX.md` | File list |
| `ALL_STRINGS.json` / `.txt` | Full string catalog |
| `ALL_FUNCTIONS.csv` | 4244 functions (also under ghidra/) |
| `APP_SYMBOLS.json` | App VA map |
| `segments.json` | Segment table |
| `DROM_FULL.bin` / `IROM_FULL.bin` / `IRAM_FULL.bin` | Raw segments |
| `DRAM1_FULL.bin` / `DRAM2_FULL.bin` | Raw .data |
| `DRAM*_WORDS.json` | Word dumps |
| `asset_*.bin` | Bitmaps + font |
| `app_desc_raw.bin` | esp_app_desc_t |
| `IROM_literal_pool_2KB.json` | Pool |
| `functions_full.txt` | Ghidra function list copy |

Plus prior trees: `mine_pass/`, `mine_pass2/`, `ghidra/decomp*`  

---

## Reconstruction

Hardware-faithful source remains in `reconstruction/ComboChannelSelect/`  
with extracted bitmaps, exact serial art, boot state BT, carrier ch 45.

---

## Legal

Educational reverse engineering of a published binary.  
Do not use RF continuous-carrier features for illegal jamming.
