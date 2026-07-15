# Prebuilt reconstructed firmware

These binaries were **compiled from** `reconstruction/ComboChannelSelect/`  
(`REBUILD_SAFE=0`, full hardware path) using `arduino-cli` + esp32 core + RF24 + Adafruit SSD1306.

## Files

| File | Use |
| --- | --- |
| `ComboChannelSelect.ino.bin` | App image (Arduino export) |
| `ComboChannelSelect.ino.bootloader.bin` | Bootloader |
| `ComboChannelSelect.ino.partitions.bin` | Partition table |
| `ComboChannelSelect.ino.merged.bin` | Full 4MB flash image (easiest one-shot flash) |
| `boot_app0.bin` | OTA data initial |

## Flash (esptool) — merged image

```bash
esptool.py --chip esp32 --port COMx write_flash 0x0 ComboChannelSelect.ino.merged.bin
```

## Flash (esptool) — split (typical Arduino layout)

```bash
esptool.py --chip esp32 --port COMx write_flash \
  0x1000  ComboChannelSelect.ino.bootloader.bin \
  0x8000  ComboChannelSelect.ino.partitions.bin \
  0xe000  boot_app0.bin \
  0x10000 ComboChannelSelect.ino.bin
```

(Offsets can vary; prefer Arduino IDE upload or the merged image.)

## Expectation

- **Will run** on BlueJammer-class wiring documented in `reconstruction/HARDWARE_WORKING_BUILD.md`
- **Will not** match SHA256 of the original closed-source `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`
- Built against **esp32 core 3.x** on the maintainer machine; for closest match to original, rebuild with core **2.0.10** (see BUILD.md)

## Legal

Contains RF continuous-carrier control path. **Illegal to use as a jammer.** Lab / education only.
