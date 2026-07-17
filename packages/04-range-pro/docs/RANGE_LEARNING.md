# Learning guide: range, components, and firmware

**Audience:** students and hobbyists studying embedded RF, link budget, and dual-SPI systems.  
**Platform:** ESP32 + dual nRF24 + SSD1306 (BlueJammer-class pinout).  
**Firmware:** `ComboChannelSelectRangePro`

> Continuous-carrier demos can cause **unlawful interference**.  
> Use only in **authorized / shielded** environments. This document teaches **engineering trade-offs**, not how to attack networks.

---

## Learning goals

After this package you should be able to:

1. Explain **why stock nRF24 range is short** (antenna, PA class, supply, data rate).  
2. List **components** that improve range and **how each term enters a link budget**.  
3. Match **hardware tiers** to firmware `HW_PROFILE` settings.  
4. Measure qualitative range with **serial stats**, optional **Vcc sense**, and optional **SDR**.  
5. Contrast **coverage hopping** vs **range-oriented dwell / PHY**.  
6. Describe **dual-PA desense** and why channel separation matters.

---

## Part A — Link budget in plain language

A simplified received-power story:

\[
P_{rx} \approx P_{tx} + G_{tx} + G_{rx} - L_{path} - L_{misc}
\]

| Symbol | Meaning | What you change on this project |
| --- | --- | --- |
| \(P_{tx}\) | Transmit power | PA module + `RF_PA_LEVEL` / LNA enable |
| \(G_{tx}, G_{rx}\) | Antenna gains | Whip → HG omni → directional |
| \(L_{path}\) | Path loss (~20 log d + 20 log f) | Distance, walls, height |
| \(L_{misc}\) | Cable, connector, mismatch | Short SMA, good adapters |
| Sensitivity | Minimum usable \(P_{rx}\) | **250 kbps** rate helps RX labs |

**Const carrier labs** emphasize the **TX side** of the budget (energy on air).  
**Two-way packet labs** (separate project) would also stress **LNA + rate**.

### What “more range” meant for firmware

| Lever | Stock / original-style | Range Pro idea |
| --- | --- | --- |
| Module class | PCB antenna nRF | **PA+LNA SMA** profile defaults |
| Data rate | 2 Mbps | Default **250 kbps** on PA profiles |
| Hop dwell | Extremely fast random | Slightly **longer dwell**, higher priority on protocol centers |
| Dual radios | Often same channel | **Min separation** (desense + two tones) |
| Power-up | Short settle | **Longer settle + more retries** for PA rails |
| Thermal | Continuous always | Optional **duty cycle** on HG profile |
| Observability | Weak | **LAB STATS**, HUD, optional **Vcc** |

---

## Part B — Component catalog (what to add)

### B1 Must-consider for range

| # | Component | Improves | Firmware interaction |
| --- | --- | --- | --- |
| 1 | nRF24 **PA+LNA+SMA** modules | \(P_{tx}\), RX NF | `HW_PROFILE 1/2`, PA/LNA flags |
| 2 | External **2.4 GHz antennas** | \(G_{tx}/G_{rx}\) | None (passive) — document orientation |
| 3 | **Strong 3.3 V / ≥1–2 A** supply | Prevents PA brownout | Retries + health messages; optional ADC |
| 4 | **Decoupling 100 µF + 100 nF** | Rail stability under TX | Fewer lost chips mid-hop |
| 5 | Antenna **spacing / aiming** | Less mutual coupling | `DUAL_MIN_SEPARATION` |

### B2 Reliability components (range you can keep)

| # | Component | Improves |
| --- | --- | --- |
| 6 | Short SPI wiring / PCB | Bus integrity at 8 MHz |
| 7 | Ferrites / star ground | Noise, brownout spikes |
| 8 | Heatsink / airflow | PA lifetime under carrier |
| 9 | Quality SMA cables/adapters | Lower \(L_{misc}\) |

### B3 Measurement components (learn, don’t guess)

| # | Component | Improves learning |
| --- | --- | --- |
| 10 | SDR / spectrum analyzer | See dual tones, hop, duty gaps |
| 11 | Multimeter / scope on 3.3 V | See sag when carrier starts |
| 12 | Resistive divider → ADC | Firmware `VCC_SENSE_PIN` |
| 13 | RF attenuators | Protect instruments |

### B4 Optional expansion projects

| # | Component | Project idea |
| --- | --- | --- |
| 14 | INA219 current sensor | Graph mA vs mode / duty |
| 15 | SD logger | CSV hop logs for lab reports |
| 16 | Second ESP32 observer | Passive-side experiment (no TX) |
| 17 | Directional antenna pair | Pointing lab + polarization |
| 18 | RF enclosure / cage | Safe classroom demos |

Full shopping narrative: [`../hardware/HARDWARE_RANGE.md`](../hardware/HARDWARE_RANGE.md).

---

## Part C — Firmware architecture (Range Pro)

```text
Core 1 (Arduino loop)              Core 0 (RadioTask)
─────────────────────              ──────────────────
BOOT button FSM                    power settle → begin retries
OLED HUD / idle                    radioConfigure (PA, rate, LNA)
LAB STATS printer                  duty gate (optional)
NVS last mode                      EDU hop + min dual separation
                                   health re-init on disconnect
```

### Profiles (`HW_PROFILE`)

| Value | Name | Defaults (see `config.h`) |
| ---: | --- | --- |
| 0 | STOCK | 10 MHz SPI, 2 Mbps option path, short settle, sep=1 |
| 1 | PA+LNA | 8 MHz SPI, **250 kbps**, settle 25 ms, sep=8, batch 24 / 3 ms |
| 2 | PA+LNA HG | like 1 + **duty 800/200 ms**, settle 50 ms |

### Key educational knobs

| Define | Role |
| --- | --- |
| `RF_DATA_RATE_SEL` | 0=1M 1=2M **2=250k** |
| `RF_PA_LEVEL` / `RF_PA_LNA_ENABLE` | TX class + LNA pin behavior in RF24 lib |
| `DUAL_MIN_SEPARATION` | Min \|chH−chV\| to reduce dual-PA desense |
| `HOP_PRIORITY_PCT` | Time on protocol centers vs fill |
| `RANGE_DUTY_ON_MS` / `OFF` | Average-power / thermal teaching |
| `VCC_SENSE_PIN` | Optional rail telemetry |
| `HOP_STRATEGY` | 0 original · 1 EDU · 2 sweep |
| `REBUILD_SAFE` | UI + sim hops, **no RF TX** |

---

## Part D — Lab exercises (authorized only)

### Lab 1 — Baseline vs PA module

1. Flash Range Pro with `HW_PROFILE 0`, stock modules.  
2. Note serial: begin success, hop_rate, Vcc if wired.  
3. Swap to PA+LNA, set `HW_PROFILE 1`, reflash.  
4. Compare brownout / begin retries and qualitative far-field with SDR.  
5. Write ½ page: which term in the link budget changed?

### Lab 2 — Data rate

1. Fix hardware at PA+LNA.  
2. Build A: `RF_DATA_RATE_SEL 1` (2 Mbps).  
3. Build B: `RF_DATA_RATE_SEL 2` (250 kbps).  
4. Discuss: sensitivity vs airtime (const-carrier still continuous; rate still configures radio modem settings).

### Lab 3 — Dual separation

1. Place antennas almost touching; watch stability.  
2. Increase `DUAL_MIN_SEPARATION` (8 → 15).  
3. On SDR, confirm two tones stay apart.  
4. Discuss desense and “two radios ≠ free 2× if co-channel.”

### Lab 4 — Duty cycle

1. `HW_PROFILE 2` or set ON/OFF ms manually.  
2. SDR waterfall shows periodic gaps.  
3. Feel PA temperature vs continuous.  
4. Compute duty = ON/(ON+OFF); relate to average power.

### Lab 5 — Protocol maps (carry-over from Pro EDU)

1. Wi‑Fi mode: confirm energy near nRF 12…72, not only 0–13.  
2. BLE mode: look for activity near 2 / 26 / 80.  
3. Explain why original `random%14` was a weak Wi‑Fi demo.

### Lab 6 — Power rail

1. Wire 10k/10k divider; set `VCC_SENSE_PIN`.  
2. Watch Vcc print when unpausing RF.  
3. Intentionally use a weak USB cable; observe FAIL / sag.  
4. Fix with bench 3.3 V; document.

---

## Part E — How this differs from other packages

| Package | Focus |
| --- | --- |
| `ESP32-ComboChannelSelect-REBuild` | Faithful RE reconstruction |
| `ESP32-ComboChannelSelect-OurFirmware` | Faithful bins only |
| `ESP32-ComboChannelSelect-Optimized` | Pro EDU hop effectiveness + reliability |
| **`ESP32-ComboChannelSelect-RangePro`** | **Hardware range upgrades + PHY/profile firmware + learning docs** |

Range Pro **includes** EDU hop maps, then adds **hardware profiles, 250 kbps, dual separation, duty, power settle, Vcc sense**.

---

## Part F — Common failure modes (troubleshooting class)

| Symptom | Likely cause | Fix |
| --- | --- | --- |
| `begin FAIL` | 3.3 V sag / wiring | Stronger PSU, caps, check CE/CSN |
| Works then dies | Thermal / brownout | Heatsink, duty cycle, thicker power |
| One radio always FAIL | Wrong SPI pins / module DOA | Swap module; verify bus |
| Short range with PA | Antenna disconnected / wrong connector | SMA fully seated; open-load risk |
| Weird hop / crash | SPI too fast on long wires | `RF24_SPI_HZ` 4–8 MHz |
| Dual seems useless | Antennas parallel & co-channel | Space antennas; raise `DUAL_MIN_SEPARATION` |

---

## Part G — Ethics & law (required reading)

1. **Jamming public RF is illegal** in most jurisdictions.  
2. Higher power + antennas increase **harm radius** — treat as hazardous lab energy.  
3. Prefer **SDR observation of your own shielded TX** over any outdoor “test.”  
4. Classroom default: `REBUILD_SAFE 1` for UI / stats simulation without carrier.  
5. You are responsible for local spectrum rules and institutional approval.

---

## Part H — Suggested report template

```text
Title: Dual nRF24 range upgrade lab
1. Hardware tier used (photos)
2. config.h settings (profile, rate, sep, duty)
3. Power rail measurement (if any)
4. Serial LAB STATS screenshots
5. SDR waterfall (if any)
6. Which link-budget term dominated?
7. What would you add next (component + reason)?
```

---

## File map

| Path | Purpose |
| --- | --- |
| `src/ComboChannelSelectRangePro/` | Firmware source |
| `src/.../config.h` | Profiles & knobs |
| `src/.../hop_maps.h` | Protocol channel tables |
| `hardware/HARDWARE_RANGE.md` | Component upgrade guide |
| `hardware/bom_range.json` | Machine-readable BOM |
| `docs/RANGE_LEARNING.md` | This learning document |
| `firmware/` | Prebuilt flash images |
| `README.md` | Flash & overview |

---

## One-sentence summary

**Range Pro teaches that “more range” is a system problem — PA modules, antennas, power integrity, dual-radio spacing, PHY rate, and dwell — and the firmware exposes those levers as named profiles and lab telemetry instead of a single opaque binary.**
