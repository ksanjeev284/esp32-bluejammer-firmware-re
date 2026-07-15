# ESP32 Combo Channel Select — Educational Reverse Engineering

> **Independent educational / security research only.**  
> This repository documents static reverse engineering of a **publicly distributed** ESP32 dual-nRF24 firmware image  
> (`Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`) for learning embedded RE, Ghidra, and lab rebuilds.  
> **Not affiliated with, endorsed by, or a fork of any upstream “product” project.**  
> **Radio jamming is illegal in most jurisdictions.** Do **not** build, flash, or operate jamming devices.

---

## Contribute your research

Have you RE’d this binary further, measured hardware, fixed docs, or improved a package? **Publish it here.**

| Step | Link |
| --- | --- |
| Full guidelines | **[CONTRIBUTING.md](CONTRIBUTING.md)** |
| Drop new findings | **[community/findings/](community/findings/)** (use the template) |
| Quick path | Fork → add `community/findings/YYYY-MM-DD_topic/README.md` → Pull Request |

We welcome: extra Ghidra notes, pin/board variants, lab measurements, corrections, scripts, and educational improvements.  
We do **not** accept “how to jam the public” content — see [DISCLAIMER.md](DISCLAIMER.md).

---

## Complete kit (start here)

All firmwares and docs live in **one folder**:

### **[`ESP32-ComboChannelSelect-Complete/`](ESP32-ComboChannelSelect-Complete/)**

| Subpackage | Best for |
| --- | --- |
| [`…/ESP32-ComboChannelSelect-REBuild/`](ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-REBuild/) | Full RE kit: source, docs, hardware, original + rebuild bins |
| [`…/ESP32-ComboChannelSelect-OurFirmware/`](ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-OurFirmware/) | Faithful rebuild **binaries only** |
| [`…/ESP32-ComboChannelSelect-Optimized/`](ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-Optimized/) | **Pro EDU** protocol-aware hops + lab telemetry |
| [`…/ESP32-ComboChannelSelect-RangePro/`](ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-RangePro/) | **Range Pro** PA/LNA hardware + long-range profiles |
| [`…/ESP32-ComboChannelSelect-IEEE-NextLab/`](ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-IEEE-NextLab/) | **SpectrumLab Next** IEEE multi-standard research lab |

Master index: [`ESP32-ComboChannelSelect-Complete/README.md`](ESP32-ComboChannelSelect-Complete/README.md)

### Flash (from repo root)

```bash
# Faithful rebuild
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-OurFirmware/ComboChannelSelect_FULL_FLASH.bin

# Pro EDU
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-Optimized/firmware/ComboChannelSelectPro_FULL_FLASH.bin

# Range Pro
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-RangePro/firmware/ComboChannelSelectRangePro_FULL_FLASH.bin

# IEEE SpectrumLab Next
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-Complete/ESP32-ComboChannelSelect-IEEE-NextLab/firmware/SpectrumLabNext_FULL_FLASH.bin
```

### Important paths

| Contents | Path under `ESP32-ComboChannelSelect-Complete/` |
| --- | --- |
| Package index | `README.md` |
| RE docs / pinout | `ESP32-ComboChannelSelect-REBuild/` |
| Pro EDU source | `ESP32-ComboChannelSelect-Optimized/src/ComboChannelSelectPro/` |
| Range learning | `ESP32-ComboChannelSelect-RangePro/docs/` + `hardware/` |
| IEEE research | `ESP32-ComboChannelSelect-IEEE-NextLab/research/` |
| SpectrumLab source | `ESP32-ComboChannelSelect-IEEE-NextLab/src/SpectrumLabNext/` |

---

## What this is

A full technical reconstruction of the closed-source firmware:

**`Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`**

analyzed as a **published binary artifact** (filename: `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`) for **learning embedded reverse engineering**:

- ESP32 image format & segments  
- String / xref based analysis  
- Ghidra (Xtensa) multi-segment load  
- Recovered `setup` / `loop` / `radioTask` decompilation  
- Pin map, state machine, channel hop algorithm, RF24 configuration  

**Independence:** This repo is an **independent educational RE package**. It is **not** an official continuation, mirror, or rebrand of any third-party product repository.  
**We do not claim ownership of the original closed firmware.** Credit for that binary remains with its original author(s). We only document behavior recovered from a public file for research/education.

---

## Quick facts (recovered)

| Item | Value |
| --- | --- |
| Chip | ESP32 |
| Framework | Arduino-ESP32 **2.0.10** + ESP-IDF **v4.4.5** |
| Built | 2023-06-12 16:41:45 |
| Image | Valid `0xE9` ESP app, 4MB flash DIO 80MHz |
| Entry | `0x40082F0C` |
| App | Combo channel select: Idle / BT / BLE / WiFi / RC |
| RF | Dual **nRF24L01** on HSPI + VSPI |
| Display | SSD1306 0.96" I2C (SDA4/SCL5, addr `0x3C`) |
| TX method | RF24 **constant carrier** + random channel hop |
| UI | BOOT button cycles modes; LED blinks = mode index |

### Pin map (from decompilation)

| Function | GPIO |
| --- | ---: |
| nRF24 #1 CE / CSN / SCK / MOSI / MISO | 16 / 15 / 14 / 13 / 12 |
| nRF24 #2 CE / CSN / SCK / MOSI / MISO | 22 / 21 / 18 / 23 / 19 |
| Status LED | 27 |
| Mode button (BOOT) | 0 |
| OLED SDA / SCL | 4 / 5 |

### Channel hop (from `radioTask`)

| Mode | Formula | Channels |
| --- | --- | --- |
| Bluetooth | `random() % 79` | 0–78 |
| BLE | `random() % 39` | 0–38 |
| WiFi | `random() % 14` | 0–13 |
| RC | `random() % 125` | 0–124 |

Both radios hop **together** on the same channel.

### Key code addresses

| Symbol | VA |
| --- | --- |
| `setup` | `0x400D2714` |
| `loop` | `0x400D2BFC` |
| `radioTask` | `0x400D236C` |
| `initRadioObjects` (CE/CSN) | `0x400D29F8` |
| `initOLED` | `0x400D2D68` |
| `enterState_BT/BLE/WiFi/RC` | `0x400D28D8` … `0x400D29B0` |

---

## Repository layout

```text
firmware/                 Original .bin under study
reconstruction/           From-scratch Arduino rebuild + SPEC
docs/                     Human-readable reports
scripts/                  Python extractors (no hardware needed)
ghidra_scripts/           Headless Ghidra Java scripts
artifacts/
  segments/               DROM/IROM/IRAM/DRAM extracts for Ghidra
  strings/                String dumps, xrefs, metadata JSON
  strings_by_category/    Categorized strings
  confirmed_assets/       OLED bitmap binaries (128×50 / boot)
  hex_regions/            Hex dumps of app DROM zones
  ghidra/
    *.md                  Analysis reports
    functions.txt         4244 recovered functions
    decomp/               Core decompiled C
    decomp_extra/         Full app-cluster decompilation
```

---

## Complete inventory (start → end of binary)

**Nothing in the file layout is unlisted.** Master map:

- **[`docs/FROM_START_TO_END.md`](docs/FROM_START_TO_END.md)** — full narrative map of every byte range  
- **[`artifacts/complete_inventory/`](artifacts/complete_inventory/)** — raw segments, all strings, all assets, DRAM words, hashes  
- **[`artifacts/ghidra/ALL_FUNCTIONS.csv`](artifacts/complete_inventory/ALL_FUNCTIONS.csv)** — 4244 functions  

### Prior mining layers

- [`docs/ULTRA_DEEP_MINING.md`](docs/ULTRA_DEEP_MINING.md) — SPI bit protocol, GLCD font, RAM map  
- [`docs/MINING_PASS_LATEST.md`](docs/MINING_PASS_LATEST.md) — UTF-8 banners, RF24 rename map  
- [`docs/GLOBALS_AND_CONSTANTS.md`](docs/GLOBALS_AND_CONSTANTS.md) — master pin/timing/VA tables  
- [`docs/NEW_FINDINGS_CONTINUED.md`](docs/NEW_FINDINGS_CONTINUED.md) — boot state, ch 45, R1/R2  
- [`artifacts/mine_pass2/`](artifacts/mine_pass2/) · [`artifacts/mine_pass/`](artifacts/mine_pass/)  
- [`artifacts/ghidra/decomp_*`](artifacts/ghidra/) — all decompiled C dumps

---

## Flash a working rebuild (hardware parity)

The reconstruction is written so that **flashing the new bin on the real board works**
(same pins, UI, button/LED, dual nRF24 hop) — not so that SHA256 matches the closed original.

| Path | Purpose |
| --- | --- |
| **[firmware/reconstructed/](firmware/reconstructed/)** | **Prebuilt** `.bin` / merged flash image (compiled, ready to esptool) |
| **[reconstruction/HARDWARE_WORKING_BUILD.md](reconstruction/HARDWARE_WORKING_BUILD.md)** | Wiring + flash + acceptance test |
| **[reconstruction/ComboChannelSelect/](reconstruction/ComboChannelSelect/)** | Source (`REBUILD_SAFE 0` = full RF path in `config.h`) |
| **[reconstruction/SPEC_FOR_REBUILD.md](reconstruction/SPEC_FOR_REBUILD.md)** | Full functional contract |
| **[reconstruction/VERIFICATION_CHECKLIST.md](reconstruction/VERIFICATION_CHECKLIST.md)** | Pass/fail hardware checks |
| **[reconstruction/BUILD.md](reconstruction/BUILD.md)** | Compile instructions |

```bash
# One-shot full flash example (merged 4MB image):
esptool.py --chip esp32 -p COMx write_flash 0x0 firmware/reconstructed/ComboChannelSelect.ino.merged.bin
```

**Legal:** Full build includes continuous-carrier RF control. Do not use as a jammer.

> Original closed bin SHA256 will **never** match. Hardware behavior is the success metric.

### Channel hop

Independent random hops on each radio:  
`N ∈ {79, 39, 14, 125}` for BT / BLE / WiFi / RC.

---

## Start reading (recommended order)

1. **[docs/FULL_TECHNICAL_REPORT.md](docs/FULL_TECHNICAL_REPORT.md)** — single master narrative  
2. **[reconstruction/SPEC_FOR_REBUILD.md](reconstruction/SPEC_FOR_REBUILD.md)** — rebuild contract  
3. **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)** — call graph, state machine, peripherals  
4. **[docs/GHIDRA_GUIDE.md](docs/GHIDRA_GUIDE.md)** — reproduce analysis in Ghidra  
5. **[artifacts/ghidra/FINAL_COMPLETE_FINDINGS.md](artifacts/ghidra/FINAL_COMPLETE_FINDINGS.md)** — pin/ctor proof  
6. **[artifacts/ghidra/decomp/400d236c_radioTask.c](artifacts/ghidra/decomp/400d236c_radioTask.c)** — recovered RF task  

---

## Reproduce the analysis

### Requirements

- Python 3.10+  
- `pip install esptool`  
- Optional: [Ghidra 12+](https://github.com/NationalSecurityAgency/ghidra) + JDK 17  

### Strings & image info (no Ghidra)

```bash
cd scripts
python full_extract.py          # run from repo root after adjusting paths
esptool image-info ../firmware/Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
```

Or open precomputed dumps under `artifacts/`.

### Ghidra (headless example)

```text
1. Import artifacts/segments/seg2_IROM_0x400D0020.bin
   Language: Xtensa:LE:32:default
   Base: 0x400D0020
2. Run ghidra_scripts/LoadEsp32Firmware.java (loads other segments + labels)
3. Auto-analyze
4. Jump to 0x400D236C (radioTask), 0x400D2714 (setup), 0x400D2BFC (loop)
```

See [docs/GHIDRA_GUIDE.md](docs/GHIDRA_GUIDE.md).

---

## Methodology (high level)

1. Identify ESP image with `esptool image-info`  
2. Extract segments & strings  
3. Map string VAs → IROM pointer pools → functions  
4. Load multi-segment program in Ghidra (Xtensa)  
5. Decompile anchors: init banners, state strings, task names  
6. Rename by behavior; recover data structures & pin immediates  

This is the standard embedded firmware RE workflow — useful beyond this sample.

---

## Legal & ethics

- **Jamming wireless communications is illegal** in most countries and can endanger safety systems.  
- This repo is for **understanding binaries, ESP32 layout, and RE tooling**.  
- Do not use recovered knowledge to cause interference.  
- Firmware copyright remains with original authors; analysis is fair-use style documentation of published binaries for research/education.  
- Authors of this RE write-up are **not affiliated** with the original binary’s author or any related product brand unless stated otherwise.  
- Rebuilds here are **behavior reconstructions for education**, not drop-in commercial clones or “official” firmware.

---

## Hashes (original firmware sample under study)

```text
File:   Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
Size:   877232 bytes
MD5:    7dd270bbf3b947d0b68191ef5a2719ea
SHA1:   fc1b7b5a7ea6bfd8ef866938600acb539034ef21
SHA256: 2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c
```

---

## Credits

- **Original closed firmware** remains copyright of its author(s). Public discussion of that ecosystem often points to community projects such as [ESP32-BlueJammer](https://github.com/EmenstaNougat/ESP32-BlueJammer) (`@emensta`) — cited only as **historical context**, not affiliation.  
- Analysis tooling: [esptool](https://github.com/espressif/esptool), [Ghidra](https://github.com/NationalSecurityAgency/ghidra)  
- This independent RE documentation & educational rebuild kit: repo maintainer  

---

## License for *this documentation & scripts*

Analysis notes, scripts, and write-ups in this repository are provided under **MIT** (see [LICENSE](LICENSE)).

The firmware binary is **not** re-licensed; it remains subject to its original author’s rights. Included only for study of the matching published artifact.
