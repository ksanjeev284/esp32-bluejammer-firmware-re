# ESP32-ComboChannelSelect-IEEE-NextLab

**SpectrumLab Next** — research-informed, multi-standard **educational** firmware and documentation package.

Built after reviewing recent **IEEE 802.11ax / 802.11be**, **802.15.4**, Bluetooth Core channel facts, coexistence literature, and modern lab components — then encoding that into a dual-nRF24 platform that is **clearly ahead** of the original closed combo binary for **teaching and measurement**.

---

## ⚠️ Legal

**Jamming is illegal in most places.**  
Authorized / shielded lab only. See [DISCLAIMER.md](DISCLAIMER.md). Prefer `REBUILD_SAFE=1` for classrooms.

---

## Why this is better (for education)

| Capability | Original / faithful | Pro EDU / Range | **IEEE NextLab** |
| --- | --- | --- | --- |
| Wi-Fi map | `random%14` (wrong band region) | Real centers | Real centers + **1/6/11 weighting** |
| BLE map | `%39` misses 2480 | Adv priority | Adv + data + labels |
| 802.15.4 | None | None | **Full ch11–26 mode** |
| Coexistence lesson | None | None | **Time-sliced multi-standard scheduler** |
| Telemetry | Minimal | Stats | **Stats + JSON** |
| IEEE docs | None | Partial | **Research + component roadmap** |
| Hardware profiles | No | Range Pro | Inherited PA profiles |

Deep dive: [`research/IEEE_RESEARCH.md`](research/IEEE_RESEARCH.md)

---

## Folder layout

```text
ESP32-ComboChannelSelect-IEEE-NextLab/
├── README.md
├── DISCLAIMER.md
├── firmware/          ★ flash SpectrumLabNext_FULL_FLASH.bin @ 0x0
├── src/SpectrumLabNext/
├── research/IEEE_RESEARCH.md
├── docs/NEXTLAB_LEARNING.md
└── hardware/NEXT_COMPONENTS.md
```

---

## Flash

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 SpectrumLabNext_FULL_FLASH.bin
```

Serial **115200** → `SpectrumLab Next / IEEE NextLab`

### Modes (short BOOT)

`BT → BLE → 802.11 → RC → 802.15.4 → COEXIST → …`

Long BOOT = pause.

---

## Build

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 ^
  --output-dir build ^
  src/SpectrumLabNext
```

Libraries: RF24, Adafruit SSD1306, Adafruit GFX.

Default `config.h`: `LAB_ENGINE=1`, `HW_PROFILE=1` (PA+LNA), `RF_DATA_RATE_SEL=2` (250 kbps).

---

## Components to go further

See [`hardware/NEXT_COMPONENTS.md`](hardware/NEXT_COMPONENTS.md):

- PA+LNA + strong 3.3 V (required for serious range)  
- SDR measurement stack  
- Future ESP32-S3 / C6 observer platforms  
- Optional Sub-GHz modules for multi-band courses  

---

## Package family

| Folder | Role |
| --- | --- |
| REBuild | Full RE archive |
| OurFirmware | Faithful bins |
| Optimized | Pro EDU hop effectiveness |
| RangePro | Range hardware + PHY |
| **IEEE-NextLab** | **IEEE multi-standard research lab firmware + docs** |

Repo: https://github.com/ksanjeev284/esp32-bluejammer-firmware-re  
