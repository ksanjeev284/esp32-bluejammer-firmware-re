# Hardware upgrades for more range (lab education)

This guide lists **components you can add** to a dual-nRF24 + ESP32 BlueJammer-class board to improve **RF range, reliability, and measurability** — for **authorized lab learning** only.

> **Legal / safety:** PA modules and high-gain antennas raise EIRP and interference risk.  
> Do **not** operate continuous-carrier demos toward public networks. Use a shielded room, RF cage, or faraday tent where required by local law.

Firmware that matches these profiles: **`ComboChannelSelectRangePro`** (`HW_PROFILE` in `config.h`).

---

## 1. Quick tier list

| Tier | What you build | Typical lab reach vs stock* | `HW_PROFILE` |
| --- | --- | --- | ---: |
| **0 Stock** | Cheap nRF24 + PCB antenna | Baseline | `0` |
| **1 PA+LNA** | nRF24L01+ **PA+LNA** + SMA whip | Much farther LOS | `1` (default firmware) |
| **2 PA+LNA + HG** | Same + high-gain / directional antenna + strong PSU | Best controlled-lab reach | `2` |

\*Distance is **not guaranteed**. It depends on height, LOS, noise floor, orientation, and legality of test setup. Use for **relative** A/B learning.

---

## 2. Core RF modules (biggest single upgrade)

### 2.1 nRF24L01+ with PA + LNA + SMA

| Item | Notes for students |
| --- | --- |
| Module | “nRF24L01+ PA LNA” with **SMA** connector |
| PA | Boosts **transmit** power (often marketed ~20 dBm class — **verify with datasheet / meter**) |
| LNA | Improves **receive** sensitivity (useful if you ever do two-way labs) |
| Why range↑ | Higher EIRP + better front-end; stock PCB antenna is tiny and lossy |

**Wiring:** same CE/CSN/SPI pins as the original RE pinout (HSPI + VSPI).  
**Critical:** PA modules draw **much more current** on TX than stock nRF24.

### 2.2 Stock nRF24L01+ (baseline control)

Keep one board as **control group** for A/B: same firmware, different module tier.

---

## 3. Antennas (second biggest upgrade)

| Component | Approx. gain | When to use |
| --- | --- | --- |
| 2.4 GHz **2 dBi** whip (SMA) | ~2 dBi | Default with PA+LNA; omnidirectional lab |
| **5–8 dBi** omni stick | Higher | Longer corridor / outdoor **authorized** LOS demos |
| **Panel / patch** directional | Moderate–high | Point-to-point lab, reduces energy in other directions |
| **Yagi / grid** 2.4 GHz | High | Max directed lab link; careful aiming |
| RP-SMA vs SMA adapter | 0 dBi | Match connector gender — wrong adapter = no RF |

**Learning rules:**

1. **Height and clear LOS** often beat raw gain.  
2. **Polarization** match (both vertical or both horizontal).  
3. Keep **antenna ≥ λ/2** from large metal when possible (~6 cm at 2.4 GHz).  
4. Separate the **two module antennas** (see §6) so they don’t desense each other.

---

## 4. Power supply (most common “range fails here”)

PA modules brown out when VCC sags → random `begin FAIL`, hop freezes, short range.

| Component | Recommendation |
| --- | --- |
| **Dedicated 3.3 V regulator** | ≥ **1 A** continuous (better **2 A** for dual PA) — not a weak AMS1117 on thin USB |
| **Bulk caps at each module** | **100 µF** electrolytic + **100 nF** ceramic on VCC–GND |
| **Short thick power wires** | Star-feed 3.3 V from regulator to both modules |
| **USB power quality** | Powered hub / bench PSU; avoid long thin USB cables |
| **Optional ADC sense** | 10k/10k divider from 3.3 V rail → free GPIO (see firmware `VCC_SENSE_PIN`) |

Firmware prints Vcc when sense is wired — teaches **rail sag under TX**.

---

## 5. Passive and EMI (reliability = effective range)

| Component / practice | Why |
| --- | --- |
| Shorter SPI Dupont lines | Fewer glitches at 8–10 MHz SPI |
| **Common ground** plane / solid GND wire | Return path integrity |
| **Ferrite bead** on VCC to each module | Softens PA current spikes |
| Shielded jumper kits or PCB redesign | Production-quality demos |
| Keep nRF **away from ESP32 PCB antenna** | Reduces self-interference |
| Metal case with antenna SMA bulkheads | Controlled radiation pattern (lab) |

Range firmware defaults **SPI 8 MHz** + longer **power settle** on PA profiles for this reason.

---

## 6. Dual-module layout (desense & diversity)

Two PA modules close together can:

- Couple into each other  
- Raise the local noise floor  
- Cancel the benefit of dual TX  

| Practice | Detail |
| --- | --- |
| Physical spacing | ≥ **5–10 cm** between antennas if possible |
| Frequency separation | Firmware `DUAL_MIN_SEPARATION` (default **8** channels on PA profiles) |
| Antenna orientation | Slight angle diversity; avoid parallel touching |
| Optional RF shield can / copper tape wall | Between modules for advanced lab |

---

## 7. Thermal / duty (PA longevity)

| Component | Use |
| --- | --- |
| Small **heatsink** on PA IC | Continuous carrier labs |
| Airflow | Open enclosure |
| Firmware **duty cycle** | `HW_PROFILE=2` defaults ON 800 ms / OFF 200 ms (educational thermal safety) |

Continuous PA_MAX carrier is harsh; duty teaching shows **average power vs peak**.

---

## 8. Optional lab instruments (measure, don’t guess)

| Instrument | Learning outcome |
| --- | --- |
| **Spectrum analyzer / SDR** (RTL-SDR, HackRF, etc.) | See hop centers, dual tones, duty gaps |
| RF **power meter** + attenuator | Approximate conducted power (with care) |
| Multimeter / scope on 3.3 V | Capture sag when carrier starts |
| Fixed **attenuator** chain | Safe high-power module tests without frying SA input |
| GPS / laser tape | Document distance for lab reports |

---

## 9. Optional “next components” (advanced education)

These are **not required** for Range Pro firmware, but good course projects:

| Component | Idea | Firmware note |
| --- | --- | --- |
| **ESP32-S3** / better MCU board | Faster dual-core, more RAM for logging | Port pins carefully |
| **External watchdog** | Recover hard SPI hangs | GPIO kick |
| **INA219 / INA226 current sensor** | Plot mA vs mode | I2C; extend HUD |
| **BME280** | Correlate humidity/temp with fade | Optional sensor lab |
| **NeoPixel status** | Visual duty / mode | Replace or parallel LED27 |
| **SD card log** | Long hop CSV for class | SPI bus conflict — use VSPI carefully |
| **Second ESP32 “observer”** | RSSI/sniffer lab (no jam) | Separate project |
| **RF switch / antenna switch** | Antenna diversity experiment | Extra GPIO CE-like control |
| **Attenuator bank** | Controlled “range” without walking far | Manual lab tool |

---

## 10. Same pinout as original RE (do not change unless you rewire)

| Function | GPIO |
| --- | ---: |
| nRF #1 CE / CSN / SCK / MOSI / MISO | 16 / 15 / 14 / 13 / 12 |
| nRF #2 CE / CSN / SCK / MOSI / MISO | 22 / 21 / 18 / 23 / 19 |
| OLED SDA / SCL | 4 / 5 |
| LED | 27 |
| BOOT button | 0 |

---

## 11. Suggested shopping list (lab kit)

**Minimum range upgrade**

- [ ] 2× nRF24L01+ **PA+LNA SMA**  
- [ ] 2× 2.4 GHz SMA antennas (2 dBi)  
- [ ] 3.3 V / 2 A regulator module  
- [ ] 2× 100 µF + 2× 100 nF caps  
- [ ] Quality DuPont or rewired PCB  

**Better range lab**

- [ ] 2× 5–8 dBi omni or 1× directional pair  
- [ ] Heatsinks  
- [ ] Bench PSU  
- [ ] SDR for visualization  
- [ ] SMA attenuators for instrument protection  

**Measure power rail**

- [ ] 2× 10 kΩ for divider  
- [ ] Wire mid-point to free ADC GPIO; set `VCC_SENSE_PIN` in `config.h`  

---

## 12. How firmware maps to hardware

| Hardware you installed | Set in `config.h` |
| --- | --- |
| Stock nRF PCB antenna | `HW_PROFILE 0` |
| PA+LNA SMA dual modules | `HW_PROFILE 1` (default) |
| PA+LNA + high-gain + want thermal duty | `HW_PROFILE 2` |
| Want original-like 2 Mbps | `RF_DATA_RATE_SEL 1` |
| Max sensitivity lab rate | `RF_DATA_RATE_SEL 2` (250 kbps) |
| Continuous carrier (no duty) | `RANGE_DUTY_ON_MS 0` |

Rebuild after changing `config.h`.

---

## 13. Safety checklist before power-on

1. Antennas **connected** before TX (open SMA can stress PA)  
2. 3.3 V capable of dual PA peaks  
3. Correct CE/CSN — swapped buses cause one FAIL forever  
4. Lab location authorized / shielded as required  
5. Serial 115200 open to confirm both modules `begin OK`  
