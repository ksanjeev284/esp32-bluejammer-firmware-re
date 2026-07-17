# ESP32-ComboChannelSelect-OurFirmware

**Our own compiled firmware** rebuilt from reverse-engineering findings  
(original: `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` / ESP32-BlueJammer combo).

This folder contains **only the flashable binaries** — not the full RE archive.

---

## ⚠️ Legal

**Jamming is illegal in most places.**  
Flash and run only where you are allowed. For education / authorized lab use only.

---

## Files (flash these)

| File | What it is | Typical use |
| --- | --- | --- |
| **`ComboChannelSelect_FULL_FLASH.bin`** | Full 4 MB image (bootloader + partitions + app) | **Easiest — flash at 0x0** |
| `ComboChannelSelect.bin` | App only | Flash at `0x10000` with split layout |
| `bootloader.bin` | ESP32 bootloader | Flash at `0x1000` |
| `partitions.bin` | Partition table | Flash at `0x8000` |
| `boot_app0.bin` | OTA data init | Flash at `0xe000` |
| `SHA256SUMS.txt` | Checksums of these files | Verify download |

---

## Flash (recommended — one file)

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 ComboChannelSelect_FULL_FLASH.bin
```

Windows example (COM3):

```bash
esptool.py --chip esp32 -p COM3 write_flash 0x0 ComboChannelSelect_FULL_FLASH.bin
```

---

## Flash (split layout, same as Arduino)

```bash
esptool.py --chip esp32 -p COMx write_flash ^
  0x1000  bootloader.bin ^
  0x8000  partitions.bin ^
  0xe000  boot_app0.bin ^
  0x10000 ComboChannelSelect.bin
```

---

## What this build includes (from RE)

| Feature | Setting |
| --- | --- |
| Dual nRF24 | HSPI (CE16/CSN15/…) + VSPI (CE22/CSN21/…) |
| Boot mode | **Bluetooth (state 1)** |
| Initial carrier channel | **45** |
| Hop ranges | BT 79 · BLE 39 · WiFi 14 · RC 125 |
| OLED | SSD1306 I2C SDA4/SCL5 addr 0x3C + original bitmaps |
| LED | GPIO 27 blinks = mode |
| BOOT button | short = cycle modes · long = pause RF |
| Serial | 115200 · original-style UTF-8 banners |
| RF config | const carrier · PA_MAX · 2 Mbps · CRC off · SPI 16 MHz |

Wiring must match BlueJammer pinout (see main RE package hardware docs).

---

## After flash

1. Serial monitor **115200**  
2. Expect splash + banners  
3. Press **BOOT** to change mode  
4. Hold **BOOT** ~0.5 s to pause  

---

## Source / full RE kit

- Source used for this build:  
  `ESP32-ComboChannelSelect-REBuild/src/ComboChannelSelect/`  
- Full analysis + docs:  
  https://github.com/ksanjeev284/esp32-bluejammer-firmware-re  

**Note:** SHA256 will **not** match the original closed-source bin. This is our rebuild from recovered behavior.
