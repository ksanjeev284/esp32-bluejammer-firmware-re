# ESP32-ComboChannelSelect-REBuild

**Behavioral reconstruction package** of the closed-source firmware:

`Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`  
(ESP32-BlueJammer / @emensta)

Recovered by static reverse engineering (esptool + Ghidra Xtensa).  
This folder is a **standalone kit**: original sample, rebuilt sources, assets, hardware map, and flashable binaries.

---

## ⚠️ Legal

**Radio jamming is illegal in most jurisdictions.**  
This package is for **education and security research only**.  
You are responsible for lawful use. See `DISCLAIMER.md`.

---

## Package layout

```text
ESP32-ComboChannelSelect-REBuild/
├── README.md                 ← you are here
├── DISCLAIMER.md
├── LICENSE                   ← docs/scripts (MIT); original .bin not re-licensed
├── PACKAGE_INFO.md           ← version, hashes, fidelity notes
│
├── firmware_original/        ← original closed binary under study
│   └── Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
│
├── firmware_rebuild/         ← prebuilt reconstructed images (flash these)
│   ├── ComboChannelSelect.ino.merged.bin   (easiest full flash)
│   ├── ComboChannelSelect.ino.bin
│   └── README.md
│
├── src/
│   └── ComboChannelSelect/   ← Arduino sketch (open this in IDE)
│       ├── ComboChannelSelect.ino
│       ├── config.h
│       ├── bitmaps.h / bitmap*.h
│       ├── OrigSerialArt.h
│       └── glcdfont_orig.h
│
├── assets/
│   ├── bitmaps/              ← OLED bitmaps extracted from original DROM
│   ├── font/                 ← Adafruit GLCD 5×7 from original
│   └── serial/               ← exact UTF-8 serial banners
│
├── hardware/
│   ├── HARDWARE.md           ← wiring + pinout
│   ├── hardware_bom.json
│   ├── state_machine_complete.json
│   └── rf24_sequences.json
│
├── docs/
│   ├── SPEC.md               ← full behavioral contract
│   ├── BUILD.md              ← compile instructions
│   ├── VERIFY.md             ← acceptance checklist
│   ├── FROM_START_TO_END.md  ← original binary map
│   ├── GLOBALS_AND_CONSTANTS.md
│   └── ULTRA_DEEP_MINING.md
│
└── reference/
    ├── APP_SYMBOLS.json      ← key VAs in original binary
    └── ram_symbol_map.md
```

---

## Quick start (flash rebuild)

1. Wire hardware per **`hardware/HARDWARE.md`** (must match original pinout).  
2. Flash:

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 firmware_rebuild/ComboChannelSelect.ino.merged.bin
```

3. Serial **115200** → banners + mode strings.  
4. **BOOT** short = cycle BT/BLE/WiFi/RC; long hold = pause RF.

Full steps: `docs/BUILD.md` · `docs/VERIFY.md`

---

## Quick start (build from source)

1. Arduino-ESP32 core (closest match: **2.0.10**; also builds on 3.x).  
2. Libraries: **RF24**, **Adafruit SSD1306**, **Adafruit GFX**.  
3. Open `src/ComboChannelSelect/ComboChannelSelect.ino`.  
4. Board: ESP32 Dev Module · Flash **4MB · DIO · 80 MHz**.  
5. `config.h`:

```cpp
#define REBUILD_SAFE 0   // full dual-nRF24 path
#define INITIAL_STATE 1  // boot in Bluetooth (matches original .data)
#define INITIAL_CARRIER_CH 45
```

Set `REBUILD_SAFE 1` for UI-only (no RF TX compile).

---

## What was recovered (truth table)

| Item | Recovered value |
| --- | --- |
| Chip / core | ESP32 · Arduino-ESP32 2.0.10 era · IDF 4.4.5 |
| Boot state | **1 = Bluetooth** |
| Initial carrier CH | **45** (begin uses 76 first) |
| nRF24 #1 | HSPI CE16 CSN15 SCK14 MOSI13 MISO12 |
| nRF24 #2 | VSPI CE22 CSN21 SCK18 MOSI23 MISO19 |
| OLED | SSD1306 128×64 I2C **SDA4 SCL5** addr **0x3C** |
| LED / BOOT | GPIO **27** / GPIO **0** |
| Hop moduli | BT **79** · BLE **39** · WiFi **14** · RC **125** |
| Hop style | Independent `random()%N` **per radio** |
| RF mode | `startConstCarrier` · PA_MAX+LNA · 2 Mbps · CRC off |
| SPI rate | **10 MHz** runtime (original RE: 16 MHz; 10 MHz for HSPI reliability on jumper/clone modules) |
| I2C | **400 kHz** during / **100 kHz** after |
| Task | `RadioTask` stack **8192** prio **1** |
| Idle UI | **`R1=` `R2=` `USB` `Connected`** |
| Serial art | Exact UTF-8 lines from original DROM |

---

## Fidelity

| Goal | Status |
| --- | --- |
| Works on original hardware pinout | **Yes** (design goal) |
| Same UI bitmaps / serial strings | **Yes** (extracted) |
| Same control flow / RF settings | **Yes** (from Ghidra) |
| Same SHA256 as closed original | **No** (different toolchain) |

---

## Original binary hashes

```
File:   Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
Size:   877232
MD5:    7dd270bbf3b947d0b68191ef5a2719ea
SHA256: 2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c
```

---

## Credits

- Original project context: [ESP32-BlueJammer](https://github.com/EmenstaNougat/ESP32-BlueJammer)  
- Analysis tooling: esptool, Ghidra (Xtensa)  
- This package: educational reconstruction from published binary artifacts  
