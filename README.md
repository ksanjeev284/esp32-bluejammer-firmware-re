# ESP32 Combo Channel Select — Educational RE & Lab Platform

[![Educational](https://img.shields.io/badge/purpose-education%20%2F%20lab-blue)](DISCLAIMER.md)
[![License](https://img.shields.io/badge/license-see%20LICENSE-lightgrey)](LICENSE)
[![Lab Ultimate](https://img.shields.io/badge/lab%20ultimate-v0.5-success)](packages/06-lab-ultimate/)
[![Release](https://img.shields.io/github/v/release/ksanjeev284/esp32-combo-channel-select-re?filter=lab-ultimate*)](https://github.com/ksanjeev284/esp32-combo-channel-select-re/releases/tag/lab-ultimate-v0.5.0)

> **Independent educational reverse engineering and dual-nRF24 lab tooling.**  
> Not affiliated with any commercial product brand.  
> **Radio jamming is illegal in most places.** Authorized / shielded lab use only.

---

## Start in 60 seconds

| Goal | Go here |
| --- | --- |
| **Flash the best lab firmware** | [`packages/06-lab-ultimate/`](packages/06-lab-ultimate/) |
| **Understand the original binary** | [`packages/01-rebuild/`](packages/01-rebuild/) |
| **Repo map** | [`STRUCTURE.md`](STRUCTURE.md) |
| **Legal** | [`DISCLAIMER.md`](DISCLAIMER.md) |
| **Contribute findings** | [`CONTRIBUTING.md`](CONTRIBUTING.md) · [`community/findings/`](community/findings/) |

### Flash Lab Ultimate (recommended)

**Download prebuilt bins:** [Release lab-ultimate-v0.5.0](https://github.com/ksanjeev284/esp32-combo-channel-select-re/releases/tag/lab-ultimate-v0.5.0)

```bash
# Full lab TX (PA+LNA friendly, SoftAP, experiments, OTA, …)
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  packages/06-lab-ultimate/firmware/LabUltimateTX_FULL_FLASH.bin

# Optional second board — range RPD logger
esptool.py --chip esp32 -p COMy write_flash 0x0 \
  packages/06-lab-ultimate/firmware/RangeObserver_FULL_FLASH.bin
```

Serial **115200** · boots **RF disarmed** · triple short **BOOT** to arm · Wi‑Fi SoftAP **`LabUltimate`** / **`labult123`** → http://192.168.4.1/

> Partition: builds use **min_spiffs** (1.9 MB app). Full 4 MB merged images flash at `0x0`.

---

## Package ladder

Each step builds on the last. **06 is the active lab platform.**

| # | Package | What you get |
| ---: | --- | --- |
| 01 | **Rebuild** | Ghidra-backed RE kit, pinout, original sample, faithful source |
| 02 | **Faithful** | Open binaries that behave like the closed original |
| 03 | **Pro EDU** | Real Wi‑Fi / BLE channel maps, dual complement, lab stats |
| 04 | **Range Pro** | PA+LNA profiles, 250 kbps, dual separation, link-budget docs |
| 05 | **Spectrum Next** | IEEE 802.11 / 802.15.4 maps, coexist scheduler, JSON |
| **06** | **Lab Ultimate ★** | FIXED/SLOW, soft CSA#1/#2, SoftAP+OTA, INA219, observer, experiments, WDT |

Index: **[`packages/README.md`](packages/README.md)**

---

## What’s new (Lab Ultimate v0.5)

- **FIXED / SLOW** modes for measurable range & SDR walks  
- **Soft CSA#1 / CSA#2** educational AFH hop (`soft_csa.h` + host tests)  
- **RangeObserver** second board (RPD % + CSV markers)  
- **ESP-NOW** TX↔OBS beacons, markers, remote `fixed` / `arm`  
- **SoftAP web UI** + captive portal + **Web OTA**  
- **INA219** current sense + over-current auto-disarm  
- **LittleFS** CSV log, NVS settings, experiment playlists  
- **Watchdog**, boot reason, factory reset, Python lab tools  

Details: [`packages/06-lab-ultimate/docs/`](packages/06-lab-ultimate/docs/)

---

## Dual nRF SPI note (important)

Original closed firmware used **16 MHz** SPI. On many DevKit + jumper + clone nRF setups, **HSPI fails** at 16 MHz while **VSPI still works**. All open packages now default to **≤10 MHz** so both modules initialize. Details: [`docs/SPI_HSPI_COMPAT.md`](docs/SPI_HSPI_COMPAT.md). Diagnostic sketch: [`scripts/nrf_diag/`](scripts/nrf_diag/).

---

## Hardware (BlueJammer-class)

| Function | GPIO |
| --- | ---: |
| nRF #1 (HSPI) CE / CSN / SCK / MOSI / MISO | **16 / 15 / 14 / 13 / 12** |
| nRF #2 (VSPI) CE / CSN / SCK / MOSI / MISO | **22 / 21 / 18 / 23 / 19** |
| OLED SSD1306 SDA / SCL | **4 / 5** |
| Status LED / BOOT | **27 / 0** |

Dual **nRF24L01+ PA+LNA SMA** modules need a solid **3.3 V (≥1–2 A)** supply.

---

## Repository layout

```text
packages/          numbered firmware kits (01…06)
firmware/          original closed .bin + early rebuild images
docs/              reverse-engineering reports
research/          BLE / standards deep dives
artifacts/         strings, Ghidra decomp, segment dumps
scripts/           extraction helpers
community/         external findings (PRs welcome)
ghidra_scripts/    analysis automation
```

Full map: [`STRUCTURE.md`](STRUCTURE.md)

---

## Research notes

| Topic | Path |
| --- | --- |
| BLE PHY, AFH, CSA | [`research/ble-advanced/`](research/ble-advanced/) |
| RE master reports | [`docs/`](docs/) |
| Ghidra exports | [`artifacts/ghidra/`](artifacts/ghidra/) |
| Lab Ultimate finding write-up | [`community/findings/2026-07-17_lab-ultimate-v05/`](community/findings/2026-07-17_lab-ultimate-v05/) |

---

## Contribute

1. Fork → branch `findings/your-topic`  
2. Add `community/findings/YYYY-MM-DD_topic/README.md` (see template)  
3. Open a Pull Request  

We welcome measurements, pin variants, doc fixes, and educational firmware improvements.  
We **reject** “how to jam public networks” content.

---

## Legal

**Educational / authorized lab only.**  
See **[DISCLAIMER.md](DISCLAIMER.md)**. You are responsible for local spectrum law.

Original closed binary remains the property of its authors; this repo documents **independent analysis** and **open educational alternatives**. Rebuild SHA256 will not match the closed image (different toolchain).

---

## Credits

- Static RE: esptool, Ghidra (Xtensa), RF24 / Arduino-ESP32 ecosystem  
- Lab platform: open dual-nRF24 educational firmwares in `packages/`  

**Repo:** https://github.com/ksanjeev284/esp32-combo-channel-select-re  
