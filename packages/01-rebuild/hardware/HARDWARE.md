# Hardware — exact pinout from original firmware

## nRF24 #1 (HSPI)

| nRF24 | ESP32 GPIO |
| --- | ---: |
| CE | **16** |
| CSN | **15** |
| SCK | **14** |
| MOSI | **13** |
| MISO | **12** |
| VCC | 3.3 V (+ 10–100 µF) |
| GND | GND |

## nRF24 #2 (VSPI)

| nRF24 | ESP32 GPIO |
| --- | ---: |
| CE | **22** |
| CSN | **21** |
| SCK | **18** |
| MOSI | **23** |
| MISO | **19** |
| VCC | 3.3 V (+ cap) |
| GND | GND |

## OLED SSD1306 0.96" I2C

| OLED | ESP32 |
| --- | ---: |
| SDA | **4** |
| SCL | **5** |
| ADDR | **0x3C** |
| VCC | 3.3 V |
| GND | GND |
| RST | not used |

## Controls

| Part | GPIO | Notes |
| --- | ---: | --- |
| Status LED | **27** | active HIGH, resistor ~1–4.7 kΩ |
| Mode button | **0** | BOOT, active LOW, INPUT_PULLUP |

## Electrical notes

- nRF24 modules need solid 3.3 V; brownouts → FAIL banners.  
- PA+LNA modules draw more current — good PSU / caps required.  
- SPI rate in firmware: **16 MHz**.  
- I2C: **400 kHz** during transfer, **100 kHz** after.  

Machine-readable: `hardware_bom.json`
