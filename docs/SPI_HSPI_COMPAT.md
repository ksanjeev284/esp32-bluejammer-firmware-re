# Dual nRF24 SPI speed compatibility (HSPI vs VSPI)

## Symptom

On ESP32 dual-nRF24 combo pinout:

| Bus | Typical pins | Boot serial |
| --- | --- | --- |
| **HSPI** nRF #1 | CE16 CSN15 SCK14 MOSI13 MISO12 | `could NOT be initialized` |
| **VSPI** nRF #2 | CE22 CSN21 SCK18 MOSI23 MISO19 | `initialized SUCCESSFULLY` |

Wiring can be **correct** and this still happens.

## Root cause (on-device)

A SPI speed sweep on a 30-pin ESP32-WROOM DevKit with two clone nRF24 modules:

| SPI rate | HSPI #1 | VSPI #2 |
| ---: | --- | --- |
| 1–10 MHz | OK | OK |
| **16 MHz** | **FAIL** | OK |

The **original closed binary** and early rebuild used **16 MHz** (`RF24` ctor / IROM `0x400D012C`). That matches the RE analysis, but is too aggressive for many jumper-wire / clone-module setups on the HSPI bus.

## Fix applied in this repo

| Package | Default `RF24_SPI_HZ` |
| --- | --- |
| Faithful rebuild / OurFirmware (`ComboChannelSelect`) | **10 MHz** |
| Pro EDU / Optimized | **10 MHz** |
| Range Pro / SpectrumLab Next / Lab Ultimate TX | **10 MHz** (or **8 MHz** on higher `HW_PROFILE`) |
| RangeObserver | **8 MHz** |

Historical RE docs still record **16 MHz** as the *original* firmware constant. Runtime flash images ship the safer default.

## How to verify

1. Serial **115200** after reset: need **both** HSPI and VSPI SUCCESS lines.  
2. Optional: flash `nrf_diag` (local tooling) and sweep 1 / 4 / 8 / 10 / 16 MHz.  
3. If only 1–4 MHz works, shorten jumpers, add VCC caps, or set `RF24_SPI_HZ` to `4000000UL` / `8000000UL`.

## Override

```cpp
// in config.h or build flags
#define RF24_SPI_HZ 8000000UL
// PCB with short traces + known-good modules may try:
// #define RF24_SPI_HZ 16000000UL
```
