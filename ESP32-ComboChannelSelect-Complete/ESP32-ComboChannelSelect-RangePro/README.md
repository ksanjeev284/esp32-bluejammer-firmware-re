# ESP32-ComboChannelSelect-RangePro

**Range Pro** — educational firmware + hardware guide for **longer-range dual-nRF24 labs** on BlueJammer-class wiring.

Builds on Pro EDU hop maps, then adds:

- Hardware **profiles** (stock / PA+LNA / high-gain)  
- **250 kbps** + PA_MAX+LNA defaults for range-oriented PHY  
- **Dual channel separation** (reduce PA self-desense)  
- Power **settle / retries**, optional **TX duty cycle**, optional **Vcc sense**  
- Full learning docs: components to add, labs, link budget  

---

## ⚠️ Legal

**Jamming is illegal in most places.** PA + antennas increase harm potential.  
Authorized / shielded lab only. See [DISCLAIMER.md](DISCLAIMER.md).

---

## Folder layout

```text
ESP32-ComboChannelSelect-RangePro/
├── README.md
├── DISCLAIMER.md
├── firmware/                         ★ flash these
│   ├── ComboChannelSelectRangePro_FULL_FLASH.bin
│   ├── ComboChannelSelectRangePro.bin
│   ├── bootloader.bin / partitions.bin / boot_app0.bin
│   └── SHA256SUMS.txt
├── src/ComboChannelSelectRangePro/   Arduino source
├── hardware/
│   ├── HARDWARE_RANGE.md             components & upgrades
│   └── bom_range.json
└── docs/
    └── RANGE_LEARNING.md             full learning document
```

---

## Flash

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 ComboChannelSelectRangePro_FULL_FLASH.bin
```

(from `firmware/`)

Split layout:

```bash
esptool.py --chip esp32 -p COMx write_flash ^
  0x1000 bootloader.bin ^
  0x8000 partitions.bin ^
  0xe000 boot_app0.bin ^
  0x10000 ComboChannelSelectRangePro.bin
```

Serial: **115200**. Expect `ComboChannelSelect Range Pro` + profile line.

---

## What components add range? (summary)

| Priority | Add this | Why |
| ---: | --- | --- |
| 1 | **nRF24 PA+LNA SMA** modules (×2) | Higher TX power + LNA |
| 2 | Proper **2.4 GHz antennas** | Gain + efficiency vs PCB trace |
| 3 | **3.3 V ≥1–2 A** + bulk caps | PA current; stop brownouts |
| 4 | Antenna **spacing / aim** | Less dual desense |
| 5 | Optional **high-gain / directional** | Controlled directed lab reach |
| 6 | SDR + attenuators | Measure instead of guessing |

Deep dive: [`hardware/HARDWARE_RANGE.md`](hardware/HARDWARE_RANGE.md)  
Learning path + labs: [`docs/RANGE_LEARNING.md`](docs/RANGE_LEARNING.md)

---

## Firmware vs hardware profiles

Set in `src/ComboChannelSelectRangePro/config.h` then rebuild:

| `HW_PROFILE` | Hardware you should use | Firmware behavior |
| ---: | --- | --- |
| `0` | Stock nRF24 | Milder settle, 10 MHz SPI path |
| `1` **default** | PA+LNA + SMA whip | 8 MHz SPI, **250 kbps**, sep≥8, longer dwell |
| `2` | PA+LNA + high-gain | Like 1 + **duty 800/200 ms**, longer settle |

Other useful knobs: `RF_DATA_RATE_SEL`, `DUAL_MIN_SEPARATION`, `RANGE_DUTY_*`, `VCC_SENSE_PIN`, `HOP_STRATEGY`, `REBUILD_SAFE`.

---

## Controls (same UX family)

| Action | Effect |
| --- | --- |
| Short BOOT | Cycle BT → BLE → WiFi → RC |
| Long BOOT | Pause RF / idle status |
| Short while paused | Resume |
| OLED | Profile, rate, live H/V channels |
| Serial | Mode maps + **RANGE LAB STATS** every 2 s |

Pins unchanged from RE (dual HSPI/VSPI nRF24, OLED 4/5, LED 27, BOOT 0).

---

## Build

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 ^
  --output-dir build ^
  src/ComboChannelSelectRangePro
```

Libraries: **RF24**, **Adafruit SSD1306**, **Adafruit GFX**.

---

## Package family

| Folder | Focus |
| --- | --- |
| `…-REBuild` | Full reverse-engineering kit |
| `…-OurFirmware` | Faithful rebuild binaries |
| `…-Optimized` | Pro EDU effectiveness + reliability |
| **`…-RangePro`** | **Range hardware + PHY profiles + learning docs** |

Repo: https://github.com/ksanjeev284/esp32-bluejammer-firmware-re  
