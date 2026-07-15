# Complete firmware inventory

## 0. Whole-file identity

- Size: **877232** bytes
- MD5: `7dd270bbf3b947d0b68191ef5a2719ea`
- SHA1: `fc1b7b5a7ea6bfd8ef866938600acb539034ef21`
- SHA256: `2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c`
- Shannon entropy: **7.0401** bits/byte
- Zero bytes: 99146 (11.30%)
- 0xFF bytes: 16034 (1.83%)

## 1. ESP image header (byte-level)

| Off | Hex | Field |
| ---: | --- | --- |
| 0x00 | `e9` | magic |
| 0x01 | `05` | segment_count |
| 0x02 | `02` | spi_mode |
| 0x03 | `2f` | spi_size_freq |
| 0x04 | `0c2f0840` | entry_point LE |
| 0x08 | `ee` | wp_pin |
| 0x09 | `000000` | spi_drive |
| 0x0C | `00` | chip_id |
| 0x0D | `00` | min_chip_rev |
| 0x0E | `00` | min_chip_rev_full? |
| 0x0F | `0000ffff00000000` | reserved |
| 0x17 | `01` | hash_appended |

- Magic valid ESP: **True**
- Segments: **5**
- Entry: **`0x40082F0C`**
- SPI mode: 2 (2=DIO)
- Flash size code: 2 (2=4MB), freq code: 15 (0xF=80MHz)

## 2. Segment table (parsed)

| # | File off | Load VA | Size | End VA | SHA256 |
| ---: | ---: | ---: | ---: | ---: | --- |
| 0 | `0x000020` | `0x3F400020` | 118704 | `0x3F41CFD0` | `f781a0e8442ec92a…` |
| 1 | `0x01CFD8` | `0x3FFBDB60` | 12352 | `0x3FFC0BA0` | `058f5e2b50687a73…` |
| 2 | `0x020020` | `0x400D0020` | 626784 | `0x40169080` | `01da7ab99f2498ea…` |
| 3 | `0x0B9088` | `0x3FFC0BA0` | 12152 | `0x3FFC3B18` | `f4542260b78fafbf…` |
| 4 | `0x0BC008` | `0x40080000` | 107128 | `0x4009A278` | `2303bd3c437b7b4f…` |

- After last segment file offset: `0xD6280`
- Checksum byte: `0x00`
- Trailing bytes after segments: 48
- Trailing hex (first 64): `00000000000000000000000000000013c009263fae8f73ee29383ac56bfed62e2eef4fca80c377e1ed41e4d01f55a8b0`
- Trailing hex (last 64): `00000000000000000000000000000013c009263fae8f73ee29383ac56bfed62e2eef4fca80c377e1ed41e4d01f55a8b0`
- Possible validation hash (last 32): `c009263fae8f73ee29383ac56bfed62e2eef4fca80c377e1ed41e4d01f55a8b0`

## 3. esp_app_desc_t

- File offset: `0x20`
- Project: `arduino-lib-builder`
- Version: `esp-idf: v4.4.5 ac5d805d0e`
- Time: `16:41:45` Date: `Jun 12 2023`
- IDF: `v4.4.5`
- ELF SHA256: `81292e8df6005ce011d594030ec5f8fd5c170b485f80594f315be1ef05ed7e3d`

## 4. Complete string catalog

- Total C-strings (len≥4, null-terminated): **14053**
- Categories: {'other': 13635, 'app_rf': 4, 'app_ui': 12, 'idf_path': 97, 'errors': 305}

## 5. DROM full extract

- DROM written: 118704 bytes → `DROM_FULL.bin`

### DROM region map

| Start | End | Content |
| ---: | ---: | --- |
| `0x3F400020` | `0x3F400120` | app_desc + build strings |
| `0x3F400120` | `0x3F40082D` | serial RF banners + UTF-8 art |
| `0x3F40082D` | `0x3F401720` | splash # art + BY EMENSTA + firmware banner + states |
| `0x3F401720` | `0x3F4023A0` | mode bitmaps 4,3,2,1 (800 each) |
| `0x3F4023A0` | `0x3F4027A0` | bitmapboot 1024 + padding |
| `0x3F402915` | `0x3F402E15` | glcdfont 5x7 |
| `0x3F4027A0` | `0x3F41CFD0` | SDK strings / rodata remainder |

## 6. DRAM initialized data

- DRAM1: 12352 bytes, 1533 nonzero words → `DRAM1_FULL.bin`
- DRAM2: 12152 bytes, 1758 nonzero words → `DRAM2_FULL.bin`

### DRAM1 named head

- `0x3FFBDB60` (+0x00) = 1074280936 — IRAM_ptr_0x400839E8
- `0x3FFBDB68` (+0x08) = 1 — g_ledBlinkTarget=1
- `0x3FFBDB6C` (+0x0C) = 1 — g_ledLevel=1
- `0x3FFBDB70` (+0x10) = 45 — carrier_ch_VSPI=45
- `0x3FFBDB74` (+0x14) = 45 — carrier_ch_HSPI=45
- `0x3FFBDB78` (+0x18) = 1 — g_savedState=1
- `0x3FFBDB7C` (+0x1C) = 1 — g_state=1_BT

## 7. IROM code segment

- IROM: 626784 bytes → `IROM_FULL.bin`

## 8. IRAM segment

- IRAM: 107128 bytes load `0x40080000` → `IRAM_FULL.bin`
- Entry `0x40082F0C` is within IRAM at +0x2F0C

## 9. File layout map (no gaps unlisted)

| Range | Content |
| --- | --- |
| 0x000000–0x000017 | Image header + extended header |
| 0x000000–0x000017 | ESP image header (24 bytes) |
| 0x000018–0x00001F | Seg 0 header (load/size) |
| 0x000020–0x01CFCF | Seg 0 data @ VA 0x3F400020 |
| 0x01CFD0–0x01CFD7 | Seg 1 header (load/size) |
| 0x01CFD8–0x020017 | Seg 1 data @ VA 0x3FFBDB60 |
| 0x020018–0x02001F | Seg 2 header (load/size) |
| 0x020020–0x0B907F | Seg 2 data @ VA 0x400D0020 |
| 0x0B9080–0x0B9087 | Seg 3 header (load/size) |
| 0x0B9088–0x0BBFFF | Seg 3 data @ VA 0x3FFC0BA0 |
| 0x0BC000–0x0BC007 | Seg 4 header (load/size) |
| 0x0BC008–0x0D627F | Seg 4 data @ VA 0x40080000 |
| 0x0D6280–0x0D62AF | Checksum / padding / image hash footer |

## 10. Application symbol truth table

| Symbol | VA |
| --- | ---: |
| `setup` | `0x400D2714` |
| `loop` | `0x400D2BFC` |
| `radioTask` | `0x400D236C` |
| `cycleMode` | `0x400D2844` |
| `enterState_BT` | `0x400D28D8` |
| `enterState_BLE` | `0x400D2920` |
| `enterState_WiFi` | `0x400D2968` |
| `enterState_RC` | `0x400D29B0` |
| `enterState_Idle` | `0x400D2A24` |
| `initRadioObjects` | `0x400D29F8` |
| `RF24_ctor` | `0x400D30A8` |
| `initOLED` | `0x400D2D68` |
| `drawModeBitmap` | `0x400D2DAC` |
| `statusLedBlink` | `0x400D2868` |
| `nrf_writeRegister` | `0x400D3034` |
| `nrf_readRegister` | `0x400D2FCC` |
| `nrf_begin` | `0x400D3448` |
| `nrf_begin_chipInit` | `0x400D337C` |
| `nrf_setChannel` | `0x400D30D8` |
| `nrf_startConstCarrier` | `0x400D34D8` |
| `nrf_stopConstCarrier` | `0x400D3590` |
| `nrf_powerDown` | `0x400D31D8` |
| `nrf_powerUp` | `0x400D31FC` |
| `randomChannel` | `0x400D5E80` |
| `image_entry` | `0x40082F0C` |

## 11. Graphics assets (byte-exact)

| Asset | VA | Size | SHA256 |
| --- | ---: | ---: | --- |
| bitmap4 | `0x3F401720` | 800 | `a7c160c6901cec34caea7fb3cf7b7513f4b47f1cd1e38b9a8b77ad6d37d0669e` |
| bitmap3 | `0x3F401A40` | 800 | `7e73b239bdd87f4af077dba94a14fbab5fafb43114cd9a65c476f0392077c95b` |
| bitmap2 | `0x3F401D60` | 800 | `225a9bba32147bc4d76a7d68a334a498b69d1c228ff9ef2307538e66880c5280` |
| bitmap1 | `0x3F402080` | 800 | `d2db555a794e17326e5f35a15d36585efad3d23ba3febbe4379046728e2e1b68` |
| bitmapboot | `0x3F4023A0` | 1024 | `7a605caa711911bba3b83d21485140ec9c34da7586ad62b63d61eeaa76472f72` |
| glcdfont | `0x3F402915` | 1280 | `6f8eceb67f99025f2f186df4208cea3e18a4fdc3336c6e408a0135397419c310` |
