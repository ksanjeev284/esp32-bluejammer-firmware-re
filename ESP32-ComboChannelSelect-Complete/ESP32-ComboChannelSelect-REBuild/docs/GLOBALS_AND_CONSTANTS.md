# Globals & Constants Master Table

All values recovered from original firmware image analysis.

## Image / build

| Item | Value |
| --- | --- |
| File | Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin |
| Size | 877232 |
| SHA256 | 2e26452fbbd72ee3c97ec94b5a4c0b4ac20800dfdae7ff7ff7029beed0a95a3c |
| ESP-IDF | v4.4.5 |
| Arduino-ESP32 | 2.0.10 |
| Compile | Jun 12 2023 16:41:45 |
| Entry | 0x40082F0C |
| Flash | 4MB DIO 80MHz |

## Pins

| Function | GPIO |
| --- | ---: |
| nRF24#1 CE | 16 |
| nRF24#1 CSN | 15 |
| nRF24#1 SCK | 14 |
| nRF24#1 MOSI | 13 |
| nRF24#1 MISO | 12 |
| nRF24#2 CE | 22 |
| nRF24#2 CSN | 21 |
| nRF24#2 SCK | 18 |
| nRF24#2 MOSI | 23 |
| nRF24#2 MISO | 19 |
| LED | 27 |
| BOOT | 0 |
| OLED SDA | 4 |
| OLED SCL | 5 |
| OLED I2C addr | 0x3C |

## Timing

| Name | Value |
| --- | --- |
| Serial baud | 115200 |
| Serial config word | 0x0800001C |
| Serial timeout-related | 20000 |
| Splash delay | 2000 ms |
| Long-press | 500 ms |
| LED pulse | 150 ms |
| LED group gap | 1000 ms |
| Hop batch | 100 |
| Hop delay | 1 ms |
| Pause poll | 10 ms |
| SPI settle | 5 ms |
| powerUp settle | 5000 µs |
| RF24 SPI Hz | 16000000 |
| RF24 SPI min floor | 10000000 (if ctor speed ≤ 35000) |
| I2C during | 400000 Hz |
| I2C after | 100000 Hz |

## RF

| Name | Value |
| --- | --- |
| begin() default channel | 76 (0x4C) |
| startConstCarrier initial ch | **45** (0x2D) both radios |
| PA | RF24_PA_MAX + LNA |
| Data rate (app) | 2 Mbps |
| CRC (app) | disabled |
| Retries | 0,0 |
| AutoAck | off (app path) |
| Payload len | 32 |
| Addr width | 5 |
| BT hop mod | 79 → ch 0..78 |
| BLE hop mod | 39 → ch 0..38 |
| WiFi hop mod | 14 → ch 0..13 |
| RC hop mod | 125 → ch 0..124 |
| Dual RNG | independent per radio |

## Code addresses

| Symbol | VA |
| --- | --- |
| setup | 0x400D2714 |
| loop | 0x400D2BFC |
| radioTask | 0x400D236C |
| cycleMode | 0x400D2844 |
| enterState_BT | 0x400D28D8 |
| enterState_BLE | 0x400D2920 |
| enterState_WiFi | 0x400D2968 |
| enterState_RC | 0x400D29B0 |
| enterState_Idle | 0x400D2A24 |
| initRadios ctor | 0x400D29F8 |
| RF24_ctor | 0x400D30A8 |
| initOLED | 0x400D2D68 |
| drawModeBitmap | 0x400D2DAC |
| statusLedBlink | 0x400D2868 |
| nrf_begin | 0x400D3448 |
| nrf_begin_chip | 0x400D337C |
| setChannel | 0x400D30D8 |
| startConstCarrier | 0x400D34D8 |
| stopConstCarrier | 0x400D3590 |
| powerDown | 0x400D31D8 |
| powerUp | 0x400D31FC |
| randomChannel | 0x400D5E80 |
| setPALevel | 0x400D32F4 |
| setDataRate | 0x400D3328 |
| setCRCLength | 0x400D3460 |
| setRetries | 0x400D34B0 |
| stopListening | 0x400D32C4 |

## Boot defaults (.data)

| Global | Init |
| --- | --- |
| g_state | **1** (Bluetooth) |
| g_ledBlinkTarget | 1 |
| g_savedState | 1 |
| carrier_ch HSPI/VSPI | 45 |

## Bitmaps

| Name | VA | Bytes | Geom |
| --- | --- | ---: | --- |
| bitmapboot | 0x3F4023A0 | 1024 | 128×64 |
| bitmap1 | 0x3F402080 | 800 | 128×50 |
| bitmap2 | 0x3F401D60 | 800 | 128×50 |
| bitmap3 | 0x3F401A40 | 800 | 128×50 |
| bitmap4 | 0x3F401720 | 800 | 128×50 |
