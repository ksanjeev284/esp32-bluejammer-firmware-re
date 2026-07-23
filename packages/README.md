# Firmware packages

Numbered folders — **higher number = newer / more capable** lab tooling.

| # | Folder | Role | Flash first? |
| ---: | --- | --- | --- |
| 01 | [`01-rebuild/`](01-rebuild/) | Full RE kit: analysis docs, pinout, original + faithful source | Study |
| 02 | [`02-faithful/`](02-faithful/) | Faithful rebuild **binaries only** | Baseline open clone |
| 03 | [`03-pro-edu/`](03-pro-edu/) | Protocol-aware hops + dual-core reliability | Better hop maps |
| 04 | [`04-range-pro/`](04-range-pro/) | PA+LNA profiles, link-budget docs | Dual PA modules |
| 05 | [`05-spectrum-next/`](05-spectrum-next/) | IEEE multi-standard maps + coexist + JSON | Teaching standards |
| **06** | **[`06-lab-ultimate/`](06-lab-ultimate/)** | **Active lab platform (v0.5)** — FIXED/SLOW, CSA, SoftAP, OTA, observer, experiments | **Recommended daily driver** |

## Quick flash (Lab Ultimate)

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  packages/06-lab-ultimate/firmware/LabUltimateTX_FULL_FLASH.bin
```

Classroom (no RF TX):

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 \
  packages/06-lab-ultimate/firmware/LabUltimateTX_SAFE_FULL_FLASH.bin
```

Second board (range observer):

```bash
esptool.py --chip esp32 -p COMy write_flash 0x0 \
  packages/06-lab-ultimate/firmware/RangeObserver_FULL_FLASH.bin
```

Serial **115200**. Lab Ultimate boots **disarmed** — triple short BOOT to arm.

## Shared pinout (all packages)

| Function | GPIO |
| --- | ---: |
| nRF #1 CE / CSN / SCK / MOSI / MISO | 16 / 15 / 14 / 13 / 12 |
| nRF #2 CE / CSN / SCK / MOSI / MISO | 22 / 21 / 18 / 23 / 19 |
| OLED SDA / SCL | 4 / 5 |
| LED / BOOT | 27 / 0 |

**SPI default:** ≤ **10 MHz** on all packages (original binary used 16 MHz; that often breaks HSPI on Dupont/clone hardware). See [docs/SPI_HSPI_COMPAT.md](../docs/SPI_HSPI_COMPAT.md).

## Legal

Educational / authorized lab only. See root [DISCLAIMER.md](../DISCLAIMER.md).
