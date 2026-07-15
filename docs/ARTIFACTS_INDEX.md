# Artifacts Index

Complete inventory of files published for study.

## firmware/

| File | Description |
| --- | --- |
| `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` | Original ESP32 app image (877,232 bytes) |

## artifacts/segments/

Raw loadable segments for Ghidra / IDA / Binary Ninja.

| File | Virtual address |
| --- | --- |
| `seg0_DROM_0x3F400020.bin` | `0x3F400020` |
| `seg1_DRAM1_0x3FFBDB60.bin` | `0x3FFBDB60` |
| `seg2_IROM_0x400D0020.bin` | `0x400D0020` (code) |
| `seg3_DRAM2_0x3FFC0BA0.bin` | `0x3FFC0BA0` |
| `seg4_IRAM_0x40080000.bin` | `0x40080000` |

## artifacts/strings/

| File | Description |
| --- | --- |
| `all_strings.txt` | Every ASCII string (len≥4) |
| `all_strings_with_addresses.tsv` | file off + VA + region |
| `app_level_strings.tsv` | Filtered app-ish strings |
| `app_messages_full.txt` | Author UI/RF messages |
| `serial_splash_art.txt` | UTF-8 boot banners |
| `drom_readable_strings.txt` | DROM readable dump |
| `metadata.json` | Hashes, header, segments, IDF components |
| `key_string_xrefs.json` | Pointer xrefs for anchors |
| `app_string_pointer_tables.json` | State/bitmap pointer tables |
| `irom_to_drom_string_pointers.json` | Bulk code→string ptrs |
| `constants_and_tables.json` | Immediate / table heuristics |
| `firmware_strings*.txt` | Earlier dumps |
| `urls.txt`, `task_names.txt`, … | Misc extracts |

## artifacts/strings_by_category/

Categorized string lists: app identity, RF, display, wireless stack, errors, SDK paths, etc.

## artifacts/confirmed_assets/

| Pattern | Description |
| --- | --- |
| `bitmap1..4_*.bin` | Mode icons (800 bytes = 128×50) |
| `bitmapboot_or_extra_*.bin` | Splash-related blob |

## artifacts/hex_regions/

Hex + ASCII dumps of important DROM windows (app desc, RF banners, state labels).

## artifacts/ghidra/

| File | Description |
| --- | --- |
| `FINAL_COMPLETE_FINDINGS.md` | CE pins + last-pass results |
| `GHIDRA_ANALYSIS_REPORT.md` | Main Ghidra narrative |
| `GHIDRA_FINDINGS.md` / `GHIDRA_MORE.md` | Export scripts output |
| `REMAINING_FINDINGS.md` | Exhaustive gap-fill dump |
| `BINARY_REMAINING_SCAN.md` | Binary pin scan |
| `PIN_IMMEDIATES.txt` | Instruction-level pin immediates |
| `functions.txt` | All 4244 function entries |
| `decomp/*.c` | Core decompiled functions |
| `decomp_extra/*.c` | Full app-cluster + helpers |

### Notable decompiled files

| File | Function |
| --- | --- |
| `400d236c_radioTask.c` | RF worker |
| `400d2714_*.c` | setup |
| `400d2bfc_*.c` | loop |
| `400d29f8_*.c` | CE/CSN radio init |
| `400d30a8_*.c` | RF24 constructor |
| `400d2d68_*.c` | OLED init |
| `400d28d8`…`29b0_*.c` | enterState_* |
| `400d34d8_*startConstCarrier*.c` | Carrier TX |
| `400d30d8_nrf_setChannel.c` | Channel write |
| `400d5e80_randomChannel.c` | Hop RNG |

## scripts/

Python tools used to produce artifacts (`full_extract.py`, `analyze_fw.py`, `map_strings.py`, `deep_extract.py`, `scan_remaining.py`, `decode_splash.py`).

## ghidra_scripts/

Java headless scripts: load segments, export findings, deep decompile.

## docs/

| File | Description |
| --- | --- |
| `FULL_TECHNICAL_REPORT.md` | Master report |
| `ARCHITECTURE.md` | Diagrams / state machine |
| `GHIDRA_GUIDE.md` | Reproduce in Ghidra |
| `ARTIFACTS_INDEX.md` | This file |
| `RE_ANALYSIS.md` | Early methodology notes |
| `MASTER_EXTRACTION_REPORT.md` | Early extraction summary |
