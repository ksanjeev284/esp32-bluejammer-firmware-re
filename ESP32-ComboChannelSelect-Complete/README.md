# ESP32-ComboChannelSelect-Complete

**One complete educational kit** for independent reverse engineering of a public ESP32 dual-nRF24 “Combo Channel Select” firmware image:

reverse engineering → faithful rebuild → optimized Pro EDU → range hardware → IEEE multi-standard SpectrumLab Next.

**Not affiliated with any original product brand** — educational RE and lab tooling only.

> **Educational / authorized lab only.**  
> **Radio jamming is illegal in most places.** Do not interfere with networks you do not own.  
> Prefer `REBUILD_SAFE=1` builds for classroom UI work without RF TX.

---

## What’s inside (all packages)

| # | Subfolder | What it is | When to use |
| ---: | --- | --- | --- |
| 1 | [`ESP32-ComboChannelSelect-REBuild/`](ESP32-ComboChannelSelect-REBuild/) | Full RE kit: source, docs, hardware JSON, original + rebuild bins | Study analysis end-to-end |
| 2 | [`ESP32-ComboChannelSelect-OurFirmware/`](ESP32-ComboChannelSelect-OurFirmware/) | Faithful rebuild **binaries only** | Flash behavior-close to original |
| 3 | [`ESP32-ComboChannelSelect-Optimized/`](ESP32-ComboChannelSelect-Optimized/) | **Pro EDU** — protocol-aware hops + lab telemetry | Better hop maps & dual-core stability |
| 4 | [`ESP32-ComboChannelSelect-RangePro/`](ESP32-ComboChannelSelect-RangePro/) | **Range Pro** — PA/LNA profiles + hardware upgrade docs | Longer-range lab hardware + PHY |
| 5 | [`ESP32-ComboChannelSelect-IEEE-NextLab/`](ESP32-ComboChannelSelect-IEEE-NextLab/) | **SpectrumLab Next** — IEEE multi-standard research package | 802.11 / BLE / 802.15.4 + coexist scheduler |

```text
ESP32-ComboChannelSelect-Complete/
├── README.md                          ← you are here
├── ESP32-ComboChannelSelect-REBuild/
├── ESP32-ComboChannelSelect-OurFirmware/
├── ESP32-ComboChannelSelect-Optimized/
├── ESP32-ComboChannelSelect-RangePro/
└── ESP32-ComboChannelSelect-IEEE-NextLab/
```

---

## Recommended path

1. **Learn** — open `…-REBuild/docs/` and hardware pinout  
2. **Flash baseline** — `…-OurFirmware/ComboChannelSelect_FULL_FLASH.bin` @ `0x0`  
3. **Better education hops** — `…-Optimized/firmware/ComboChannelSelectPro_FULL_FLASH.bin`  
4. **PA modules / range** — `…-RangePro/` + `hardware/HARDWARE_RANGE.md`  
5. **IEEE multi-standard lab** — `…-IEEE-NextLab/firmware/SpectrumLabNext_FULL_FLASH.bin`  

---

## Quick flash (esptool)

### Faithful rebuild

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-OurFirmware/ComboChannelSelect_FULL_FLASH.bin
```

### Pro EDU (optimized)

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-Optimized/firmware/ComboChannelSelectPro_FULL_FLASH.bin
```

### Range Pro

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-RangePro/firmware/ComboChannelSelectRangePro_FULL_FLASH.bin
```

### IEEE SpectrumLab Next

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  ESP32-ComboChannelSelect-IEEE-NextLab/firmware/SpectrumLabNext_FULL_FLASH.bin
```

Serial monitor: **115200** baud. Wiring: dual nRF24 + SSD1306 combo pinout (see REBuild hardware docs).

---

## Shared hardware pinout (all firmwares)

| Function | GPIO |
| --- | ---: |
| nRF #1 CE / CSN / SCK / MOSI / MISO | 16 / 15 / 14 / 13 / 12 |
| nRF #2 CE / CSN / SCK / MOSI / MISO | 22 / 21 / 18 / 23 / 19 |
| OLED SDA / SCL | 4 / 5 |
| Status LED | 27 |
| BOOT button | 0 |

---

## Key docs by package

| Topic | Path |
| --- | --- |
| RE deep dive | `ESP32-ComboChannelSelect-REBuild/docs/` |
| Pro hop effectiveness | `ESP32-ComboChannelSelect-Optimized/EFFECTIVENESS.md` |
| Range components | `ESP32-ComboChannelSelect-RangePro/hardware/HARDWARE_RANGE.md` |
| Range learning | `ESP32-ComboChannelSelect-RangePro/docs/RANGE_LEARNING.md` |
| IEEE research | `ESP32-ComboChannelSelect-IEEE-NextLab/research/IEEE_RESEARCH.md` |
| NextLab labs | `ESP32-ComboChannelSelect-IEEE-NextLab/docs/NEXTLAB_LEARNING.md` |
| Next components | `ESP32-ComboChannelSelect-IEEE-NextLab/hardware/NEXT_COMPONENTS.md` |

---

## Contribute more findings

Researchers and lab builders can add results to the **parent repository**:

- Guidelines: [CONTRIBUTING.md](../CONTRIBUTING.md)  
- Community findings folder: [community/findings/](../community/findings/)  
- Open a **Pull Request** with a new `community/findings/YYYY-MM-DD_topic/` write-up  

Firmware/package improvements for this Complete kit also go through PRs (edit the matching subfolder + explain in the PR).

---

## Repo

https://github.com/ksanjeev284/esp32-combo-channel-select-re  

**Note:** Rebuild SHA256 will not match the original closed-source binary. These packages reconstruct **behavior** and improve **education / lab tooling**.
