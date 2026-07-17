# Build & flash

## Flash prebuilt (recommended)

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 firmware_rebuild/ComboChannelSelect.ino.merged.bin
```

Or split layout (typical Arduino):

```bash
esptool.py --chip esp32 -p COMx write_flash \
  0x1000  firmware_rebuild/ComboChannelSelect.ino.bootloader.bin \
  0x8000  firmware_rebuild/ComboChannelSelect.ino.partitions.bin \
  0xe000  firmware_rebuild/boot_app0.bin \
  0x10000 firmware_rebuild/ComboChannelSelect.ino.bin
```

## Build from source

### Requirements

- Arduino IDE or `arduino-cli`  
- Board package **esp32** (prefer **2.0.10** for closest match to original)  
- Libraries: **RF24** (TMRh20), **Adafruit SSD1306**, **Adafruit GFX**

### Board options

| Setting | Value |
| --- | --- |
| Board | ESP32 Dev Module |
| Flash Size | 4 MB |
| Flash Mode | DIO |
| Flash Freq | 80 MHz |
| CPU Freq | 240 MHz |
| PSRAM | Disabled |

### config.h

```cpp
#define REBUILD_SAFE 0          // 1 = UI only, no RF TX
#define INITIAL_STATE 1         // 1 = BT (original boot)
#define INITIAL_CARRIER_CH 45   // original .data carrier channel
```

### arduino-cli

```bash
cd src
arduino-cli compile --fqbn esp32:esp32:esp32:FlashMode=dio,FlashFreq=80,FlashSize=4M ComboChannelSelect
arduino-cli upload -p COMx --fqbn esp32:esp32:esp32 ComboChannelSelect
```

## Serial monitor

- Baud: **115200**  
- UTF-8 terminal recommended (box-drawing banners)  
