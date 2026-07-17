# Next-gen components roadmap (best lab tech)

Companion to SpectrumLab Next firmware. Prioritize in order.

---

## A. Drop-in (works with this firmware today)

| # | Component | Role |
| ---: | --- | --- |
| 1 | 2× **nRF24L01+ PA+LNA SMA** | Primary RF upgrade |
| 2 | 2× **2.4 GHz antennas** (start 2 dBi; optional 5–8 dBi) | Gain / pattern |
| 3 | **3.3 V / 2 A** regulator + 100 µF/100 nF per radio | Power integrity |
| 4 | ESP32 DevKit (classic) | Runs NextLab as-is |
| 5 | SSD1306 I2C OLED | UI |
| 6 | Short SPI wiring / PCB | Bus integrity @ 8 MHz |

Set `HW_PROFILE 1` (default binary) or `2` for high-gain + duty.

---

## B. Measurement stack (makes the lab “research grade”)

| # | Component | Why |
| ---: | --- | --- |
| 7 | **RTL-SDR** or better SDR | See IEEE channel hits / dual tones / coexist slices |
| 8 | **SMA attenuators** (20–30 dB) | Protect SA/SDR front-ends |
| 9 | Multimeter / scope | 3.3 V sag under carrier |
| 10 | 10k/10k divider → ADC | Enable `VCC_SENSE_PIN` in firmware |
| 11 | Optional **INA219** | Current vs mode plots (future I2C fork) |

---

## C. Platform upgrades (next hardware revision)

| # | Component | Benefit | Firmware note |
| ---: | --- | --- | --- |
| 12 | **ESP32-S3** | USB-Serial-JTAG, more SRAM, vector instr | Port pins; keep dual SPI |
| 13 | **ESP32-C6** | **Wi-Fi 6** 802.11ax radio onboard | Use as **observer / sniffer UI**, not nRF replacement |
| 14 | Second MCU as **packet observer** | True coexistence experiments | Separate repo |
| 15 | Custom PCB + shield cans | Lower EMI, repeatable BOM | Production teaching kit |

---

## D. Multi-band / multi-standard expansion (course modules)

| # | Component | Band | Course use |
| ---: | --- | --- | --- |
| 16 | **CC1101** / CC2500 | Sub-GHz / 2.4 GFSK variants | ISM beyond nRF maps |
| 17 | **SX1262 / SX1276** | LoRa Sub-GHz | LPWAN education |
| 18 | **nRF52840** dongle | BLE native | Compare BLE stack vs nRF24 map |
| 19 | **Thread / Matter** RCP | 802.15.4 | Live WPAN vs Wi-Fi planning |

These are **not** wired into SpectrumLab Next by default (pin/SPI conflicts). Documented for curriculum roadmap.

---

## E. Safety / classroom

| # | Component |
| ---: | --- |
| 20 | RF cage / faraday tent |
| 21 | Interlock switch on PA supply |
| 22 | Thermal pads / heatsinks on PA modules |

---

## F. Suggested “best tech” bill for a university kit

1. Custom dual-PA nRF24 + ESP32-S3 PCB  
2. SMA bulkhead antennas  
3. 3.3 V 3 A rail + current sense  
4. OLED + BOOT UI  
5. RTL-SDR in the kit bag  
6. Firmware: **SpectrumLab Next** + SAFE classroom build  
7. Lab manual: `docs/NEXTLAB_LEARNING.md` + `research/IEEE_RESEARCH.md`

---

## Pinout (unchanged for this firmware)

Same RE pinout: HSPI CE16/CSN15, VSPI CE22/CSN21, OLED 4/5, LED27, BOOT0.
