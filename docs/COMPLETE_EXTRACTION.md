# Complete Firmware Extraction Report

**File:** `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`  
**Size:** 877232 bytes (856.67 KB)  
**MD5:** `7dd270bbf3b947d0b68191ef5a2719ea`  
**SHA1:** `fc1b7b5a7ea6bfd8ef866938600acb539034ef21`  
**SHA256:** `2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c`  

## Image header
```json
{
  "magic": "0xE9",
  "valid_esp": true,
  "segments": 5,
  "spi_mode": 2,
  "spi_mode_name": "DIO",
  "flash_size_code": 2,
  "flash_freq_code": 15,
  "flash_size": "4MB",
  "flash_freq": "80MHz",
  "entry_point": "0x40082F0C",
  "wp_pin": 238,
  "chip_id": 0,
  "min_chip_rev": 0,
  "hash_appended": 1,
  "extended_header_hex": "ee0000000000000000ffff0000000001"
}
```
## esp_app_desc_t
```json
{
  "file_offset": "0x20",
  "va": "0x3F400020",
  "version": "esp-idf: v4.4.5 ac5d805d0e",
  "project_name": "arduino-lib-builder",
  "compile_time": "16:41:45",
  "compile_date": "Jun 12 2023",
  "idf_ver": "v4.4.5",
  "elf_sha256": "81292e8df6005ce011d594030ec5f8fd5c170b485f80594f315be1ef05ed7e3d"
}
```
## Segments (extracted to `extracted/segments/`)
| # | Name | Load VA | Size | File off | Entropy | SHA256 |
|---|------|---------|------|----------|---------|--------|
| 0 | DROM | `0x3F400020` | 118704 | `0x20` | 5.8007 | `f781a0e8442ec92a…` |
| 1 | DRAM1 | `0x3FFBDB60` | 12352 | `0x1CFD8` | 3.3141 | `058f5e2b50687a73…` |
| 2 | IROM | `0x400D0020` | 626784 | `0x20020` | 7.1318 | `01da7ab99f2498ea…` |
| 3 | DRAM2 | `0x3FFC0BA0` | 12152 | `0xB9088` | 4.0755 | `f4542260b78fafbf…` |
| 4 | IRAM | `0x40080000` | 107128 | `0xBC008` | 6.9561 | `2303bd3c437b7b4f…` |

## Strings: 8698 total (len≥4)

### Application / UI strings
| VA | File | String |
|----|------|--------|
| `0x3F4002C4` | `0x2C4` | `Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY! #######…` |
| `0x3F40044A` | `0x44A` | `!!! Hardware Serial Peripheral Interface start failure! HSPI nRF24 module could NOT be initialized! …` |
| `0x3F400608` | `0x608` | `Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY! #######…` |
| `0x3F400793` | `0x793` | `!!! Variable Serial Peripheral Interface start failure! VSPI nRF24 module could NOT be initialized! …` |
| `0x3F40082D` | `0x82D` | `bitmapboot` |
| `0x3F400E16` | `0xE16` | `                                          Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)          …` |
| `0x3F40154E` | `0x154E` | `                                         https://github.com/EmenstaNougat/ESP32-BlueJammer          …` |
| `0x3F401658` | `0x1658` | `RadioTask` |
| `0x3F401662` | `0x1662` | `State 1: Bluetooth` |
| `0x3F401675` | `0x1675` | `bitmap1` |
| `0x3F40167D` | `0x167D` | `State 2: Bluetooth Low Energy` |
| `0x3F40169B` | `0x169B` | `bitmap2` |
| `0x3F4016A3` | `0x16A3` | `State 3: WiFi` |
| `0x3F4016B1` | `0x16B1` | `bitmap3` |
| `0x3F4016B9` | `0x16B9` | `State 4: RC` |
| `0x3F4016C5` | `0x16C5` | `bitmap4` |
| `0x3F4016CD` | `0x16CD` | `State 0: Idle & Status` |
| `0x3F4016F0` | `0x16F0` | `Connected` |
| `0x3F4016FA` | `0x16FA` | `SSD1306 allocation failed` |
| `0x3F401714` | `0x1714` | `by @emensta` |
| `0x3F40C151` | `0xC151` | `sl_map && "internal error - second level bitmap is null"` |

### Key string pointer xrefs (for Ghidra)
- **Firmware : Combo-Channel-Select** @ `0x3F400E40`
- **https://github.com/EmenstaNougat/ESP32-BlueJammer** @ `0x3F401577`
- **HSPI nRF24 module initialized SUCCESSFULLY** @ `0x3F4002F5`
- **VSPI nRF24 module initialized SUCCESSFULLY** @ `0x3F400639`
- **HSPI nRF24 module could NOT** @ `0x3F400482`
- **VSPI nRF24 module could NOT** @ `0x3F4007CB`
- **Hardware Serial Peripheral Interface started** @ `0x3F4002C4`
  - ptr @ `0x400D003C` (IROM)
- **Variable Serial Peripheral Interface started** @ `0x3F400608`
  - ptr @ `0x400D0064` (IROM)
- **State 1: Bluetooth** @ `0x3F401662`
  - ptr @ `0x400D010C` (IROM)
- **State 2: Bluetooth Low Energy** @ `0x3F40167D`
  - ptr @ `0x400D0114` (IROM)
- **State 3: WiFi** @ `0x3F4016A3`
  - ptr @ `0x400D011C` (IROM)
- **State 4: RC** @ `0x3F4016B9`
  - ptr @ `0x400D0124` (IROM)
- **State 0: Idle & Status** @ `0x3F4016CD`
  - ptr @ `0x400D013C` (IROM)
- **RadioTask** @ `0x3F401658`
  - ptr @ `0x400D00EC` (IROM)
- **loopTask** @ `0x3F403649`
  - ptr @ `0x400D04F0` (IROM)
- **SSD1306 allocation failed** @ `0x3F4016FA`
  - ptr @ `0x400D0190` (IROM)
- **bitmapboot** @ `0x3F40082D`
  - ptr @ `0x400D00A0` (IROM)
  - ptr @ `0x400D0198` (IROM)
- **bitmap1** @ `0x3F401675`
  - ptr @ `0x400D0110` (IROM)
  - ptr @ `0x400D01A4` (IROM)
- **bitmap2** @ `0x3F40169B`
  - ptr @ `0x400D0118` (IROM)
  - ptr @ `0x400D01AC` (IROM)
- **bitmap3** @ `0x3F4016B1`
  - ptr @ `0x400D0120` (IROM)
  - ptr @ `0x400D01B4` (IROM)
- **bitmap4** @ `0x3F4016C5`
  - ptr @ `0x400D0128` (IROM)
  - ptr @ `0x400D01BC` (IROM)
- **Connected** @ `0x3F4016F0`
  - ptr @ `0x400D0164` (IROM)
- **by @emensta** @ `0x3F401714`
  - ptr @ `0x400D01A0` (IROM)
- **esp-idf: v4.4.5** @ `0x3F400030`
- **arduino-lib-builder** @ `0x3F400050`

### IDF components referenced in asserts/paths
`app_update`, `bootloader_support`, `bt`, `driver`, `efuse`, `esp_event`, `esp_hw_support`, `esp_ipc`, `esp_netif`, `esp_phy`, `esp_ringbuf`, `esp_system`, `esp_timer`, `esp_wifi`, `espcoredump`, `freertos`, `hal`, `heap`, `log`, `lwip`, `mbedtls`, `newlib`, `nvs_flash`, `pthread`, `spi_flash`, `vfs`, `wifi_provisioning`, `wpa_supplicant`

### URLs
- https://github.com/EmenstaNougat/ESP32-BlueJammer

### Sequential uint8 tables (possible channel lists)
- `0x3FFBFD10` (DRAM1): start=1 len=14 preview=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]

### Interesting immediate values
- **79** (BT classic channels): u32×2, u16×32
- **40** (BLE channels): u32×17, u16×242
- **14** (WiFi channels): u32×26, u16×115
- **125** (nRF max channel / RC): u32×4, u16×18
- **126** (nRF channel count 0-125): u32×2, u16×13
- **83** (sometimes BT): u32×2, u16×101
- **37** (BLE advertising primary): u32×9, u16×197
- **2400** (MHz base): u32×3, u16×7
- **2402** (BT start MHz): u32×0, u16×16
- **2480** (BT end MHz): u32×0, u16×2
- **2483** (ISM edge): u32×1, u16×3
- **2525** (RC upper): u32×0, u16×12

### Bitmap labels
- `bitmapboot` @ file `0x82D` VA `0x3F40082D`
- `bitmap1` @ file `0x1675` VA `0x3F401675`
- `bitmap2` @ file `0x169B` VA `0x3F40169B`
- `bitmap3` @ file `0x16B1` VA `0x3F4016B1`
- `bitmap4` @ file `0x16C5` VA `0x3F4016C5`

Bitmap candidates: 40 files in `extracted/bitmaps_candidates/`

### Output file index
- `extracted\all_strings.txt` (119641 bytes)
- `extracted\all_strings_with_addresses.json` (1302349 bytes)
- `extracted\all_strings_with_addresses.tsv` (346573 bytes)
- `extracted\app_level_strings.tsv` (87749 bytes)
- `extracted\bitmap_candidates.json` (7445 bytes)
- `extracted\bitmaps_candidates\cand_00_128x64_0x3F412F00.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_00_128x64_0x3F412F00.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_01_128x64_0x3F413390.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_01_128x64_0x3F413390.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_02_128x64_0x3F413100.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_02_128x64_0x3F413100.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_03_128x64_0x3F413590.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_03_128x64_0x3F413590.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_04_128x64_0x3F413BF0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_04_128x64_0x3F413BF0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_05_128x64_0x3F4137D0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_05_128x64_0x3F4137D0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_06_128x64_0x3F412D00.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_06_128x64_0x3F412D00.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_07_128x64_0x3F4139F0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_07_128x64_0x3F4139F0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_08_128x32_0x3F413CF0.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_08_128x32_0x3F413CF0.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_09_128x32_0x3F413200.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_09_128x32_0x3F413200.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_10_128x32_0x3F413000.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_10_128x32_0x3F413000.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_11_128x32_0x3F4136D0.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_11_128x32_0x3F4136D0.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_12_128x32_0x3F413490.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_12_128x32_0x3F413490.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_13_128x32_0x3F412E00.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_13_128x32_0x3F412E00.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_14_128x32_0x3F413AF0.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_14_128x32_0x3F413AF0.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_15_128x64_0x3F415E40.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_15_128x64_0x3F415E40.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_16_64x32_0x3F413D70.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_17_128x64_0x3F415BD0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_17_128x64_0x3F415BD0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_18_64x32_0x3F413C70.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_19_64x32_0x3F4132A0.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_20_128x64_0x3F40EFA0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_20_128x64_0x3F40EFA0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_21_64x32_0x3F413DF0.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_22_64x32_0x3F413080.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_23_64x32_0x3F412F80.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_24_128x64_0x3F402AD0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_24_128x64_0x3F402AD0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_25_64x32_0x3F412E80.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_26_128x64_0x3F414D70.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_26_128x64_0x3F414D70.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_27_128x64_0x3F40ED70.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_27_128x64_0x3F40ED70.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_28_64x32_0x3F413180.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_29_128x64_0x3F4025C0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_29_128x64_0x3F4025C0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_30_64x32_0x3F413750.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_31_128x64_0x3F402850.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_31_128x64_0x3F402850.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_32_64x32_0x3F413410.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_33_128x32_0x3F4110B0.bin` (512 bytes)
- `extracted\bitmaps_candidates\cand_33_128x32_0x3F4110B0.pbm` (8236 bytes)
- `extracted\bitmaps_candidates\cand_34_128x64_0x3F417860.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_34_128x64_0x3F417860.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_35_64x32_0x3F413870.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_36_128x64_0x3F402FA0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_36_128x64_0x3F402FA0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_37_64x32_0x3F413510.bin` (256 bytes)
- `extracted\bitmaps_candidates\cand_38_128x64_0x3F402CD0.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_38_128x64_0x3F402CD0.pbm` (16460 bytes)
- `extracted\bitmaps_candidates\cand_39_128x64_0x3F414650.bin` (1024 bytes)
- `extracted\bitmaps_candidates\cand_39_128x64_0x3F414650.pbm` (16460 bytes)
- `extracted\constants_and_tables.json` (9020 bytes)
- `extracted\DRAM1_hexpreview.txt` (1564 bytes)
- `extracted\DRAM2_hexpreview.txt` (1564 bytes)
- `extracted\emails.txt` (0 bytes)
- `extracted\functions_mentioned_in_strings.txt` (1587 bytes)
- `extracted\irom_to_drom_string_pointers.json` (136777 bytes)
- `extracted\key_string_xrefs.json` (7041 bytes)
- `extracted\metadata.json` (3282 bytes)
- `extracted\segments\seg0_DROM_0x3F400020.bin` (118704 bytes)
- `extracted\segments\seg1_DRAM1_0x3FFBDB60.bin` (12352 bytes)
- `extracted\segments\seg2_IROM_0x400D0020.bin` (626784 bytes)
- `extracted\segments\seg3_DRAM2_0x3FFC0BA0.bin` (12152 bytes)
- `extracted\segments\seg4_IRAM_0x40080000.bin` (107128 bytes)
- `extracted\strings_by_category\app_identity.txt` (347 bytes)
- `extracted\strings_by_category\build_sdk_version.txt` (404 bytes)
- `extracted\strings_by_category\display.txt` (291 bytes)
- `extracted\strings_by_category\errors_debug.txt` (20052 bytes)
- `extracted\strings_by_category\licenses.txt` (40 bytes)
- `extracted\strings_by_category\peripherals_api.txt` (9083 bytes)
- `extracted\strings_by_category\rf_nrf24.txt` (740 bytes)
- `extracted\strings_by_category\rf_protocol_words.txt` (1711 bytes)
- `extracted\strings_by_category\source_paths.txt` (6904 bytes)
- `extracted\strings_by_category\state_machine_ui.txt` (216 bytes)
- `extracted\strings_by_category\tasks.txt` (4574 bytes)
- `extracted\strings_by_category\version_numbers.txt` (76 bytes)
- `extracted\strings_by_category\wireless_stack.txt` (8729 bytes)
- `extracted\symbol_like_identifiers.txt` (26247 bytes)
- `extracted\urls.txt` (49 bytes)