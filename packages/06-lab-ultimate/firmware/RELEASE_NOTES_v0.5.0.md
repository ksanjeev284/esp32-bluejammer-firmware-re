# Lab Ultimate v0.5.0

Educational dual-nRF24 lab platform for ESP32 (BlueJammer-class pinout).

**Authorized / shielded lab only. Radio jamming is illegal in most places.**

## Assets

| File | Flash | Use |
| --- | --- | --- |
| `LabUltimateTX_FULL_FLASH.bin` | `0x0` | Main TX board (recommended) |
| `LabUltimateTX_SAFE_FULL_FLASH.bin` | `0x0` | Classroom UI — **no RF TX** |
| `RangeObserver_FULL_FLASH.bin` | `0x0` | Second board RPD range logger |
| `LabUltimateTX.bin` | app slot / OTA | App-only image for Web OTA |

## Flash

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 LabUltimateTX_FULL_FLASH.bin
# optional second board:
esptool.py --chip esp32 -p COMy write_flash 0x0 RangeObserver_FULL_FLASH.bin
```

Serial **115200**. RF boots **disarmed** — triple short **BOOT** to arm.

SoftAP: **LabUltimate** / **labult123** → http://192.168.4.1/  
OTA page: http://192.168.4.1/ota (upload `LabUltimateTX.bin`)

## Highlights (v0.1 → v0.5)

- FIXED / SLOW modes for range & SDR labs  
- Soft CSA#1 / CSA#2 educational AFH  
- RangeObserver + ESP-NOW markers / remote control  
- SoftAP web UI, captive portal, Web OTA  
- INA219 current sense + over-current protect  
- Experiment sequencer (`exp0` / `exp1`), profiles, WDT  
- Python tools: `serial_capture.py`, `lab_parse.py`, `csa_test.py`  

## Docs

- Package: https://github.com/ksanjeev284/esp32-combo-channel-select-re/tree/main/packages/06-lab-ultimate  
- Repo structure: https://github.com/ksanjeev284/esp32-combo-channel-select-re/blob/main/STRUCTURE.md  

## Hardware pinout

| Function | GPIO |
| --- | ---: |
| nRF1 CE/CSN/SCK/MOSI/MISO | 16/15/14/13/12 |
| nRF2 CE/CSN/SCK/MOSI/MISO | 22/21/18/23/19 |
| OLED SDA/SCL | 4/5 |
| LED / BOOT | 27/0 |

Dual PA+LNA modules need solid **3.3 V ≥1–2 A**.
