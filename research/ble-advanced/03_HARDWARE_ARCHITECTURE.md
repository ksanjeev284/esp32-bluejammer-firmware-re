# 03 — Hardware architecture for a better BLE-centric lab platform

## 1. Design goals

| Goal | Hardware consequence |
| --- | --- |
| Protocol-faithful BLE experiments | Need **native BLE radio** (ESP32/nRF52), not only nRF24 |
| Controlled 2.4 GHz spectrum labs | Dual **nRF24 PA+LNA** still useful as **instrumented stimulus** |
| Measurable science | Current sense, optional SDR, logging storage |
| Reproducible range | Stable **3.3 V multi-amp** rail, known antennas |
| Safety | RF enclosure option, duty switch, antenna interlock culture |

---

## 2. Recommended tiered BOM

### Tier 0 — Minimum (study existing combo board)

| Part | Role |
| --- | --- |
| ESP32 + dual nRF24 + OLED | Baseline from original design class |
| USB serial | Logs |

### Tier 1 — Research fidelity (recommended)

| Part | Role | Notes |
| --- | --- | --- |
| **ESP32-S3** (or ESP32 classic) | App MCU, dual SPI | S3: more RAM for logs |
| 2× **nRF24L01+ PA+LNA SMA** | Dual independent ISM tones / packet labs | Space antennas ≥5–10 cm |
| 2× 2.4 GHz antennas (start 2 dBi) | Known \(G_t\) | Document gain |
| **3.3 V / ≥2 A** regulator | PA current peaks | Star distribute + bulk caps |
| 100 µF + 100 nF per radio | Decoupling | Against brownout |
| SSD1306 or larger display | UI | |
| **INA219 / INA226** | Current / power telemetry | Scientific energy plots |
| Optional ADC divider on 3.3 V | Rail sag | |

### Tier 2 — True BLE path (critical upgrade)

| Part | Role |
| --- | --- |
| **ESP32’s built-in BLE** *or* **nRF52840 dongle** | Real advertising / connection / PHY |
| Second board as **observer** | Sniff ADV, measure RSSI, PER |
| USB isolation / ferrite | Clean measurements |

### Tier 3 — Instrumentation grade

| Part | Role |
| --- | --- |
| RTL-SDR / SA + attenuators | Spectral truth |
| RF cage / tent | Classroom safety & repeatability |
| Directional antennas | Controlled path experiments |
| Temperature sensor near PA | Thermal derating labs |

---

## 3. Dual-radio geometry (physics)

Two PA modules close together couple energy → **desense**.

**Practice:**

\[
\Delta f_{\min} \ge 6\ldots12\ \text{MHz (nRF channels)}
\]

physical separation \(d_{\mathrm{ant}} \gtrsim 0.05\ldots0.10\ \mathrm{m}\)

**Logic:** treat radios as **diversity / dual-tone lab sources**, not “twice free range.”

---

## 4. Power integrity (often the real “range bug”)

PA modules can draw **hundreds of mA peaks**.

Simple budget:

| Load | Current order |
| --- | --- |
| ESP32 active | ~80–160 mA |
| 1× PA nRF TX | ~100–200+ mA (module dependent) |
| 2× PA TX | ~200–400+ mA |
| OLED | ~20 mA |
| **Peak sum** | **~0.5–0.8 A** → design **≥2 A** rail |

Voltage sag \(\Delta V = I \cdot R_{\mathrm{wire}} + L\,di/dt\) effects → brownout → “short range.”

**Hardware rule:** short thick VCC/GND, bulk caps at modules, measure with INA219.

---

## 5. Antenna & EIRP

\[
\mathrm{EIRP_{dBm}} = P_{t,\mathrm{dBm}} + G_{t,\mathrm{dBi}} - L_{\mathrm{cable,dB}}
\]

| Front-end | \(P_t\) ballpark | \(G_t\) | Notes |
| --- | ---: | ---: | --- |
| Stock nRF PCB | ~0 dBm | −2…0 dBi | Baseline |
| PA module | ~10…20 dBm claimed | +2 dBi whip | Verify; fakes exist |
| + HG antenna | same \(P_t\) | +5…8 dBi | Directional ethics |

**Always** connect antenna before TX (open SMA can stress PA).

---

## 6. Observer architecture (from research needs)

```text
[DUT board: dual nRF + ESP] ----RF----> [Observer: ESP32-BLE / nRF52]
         |                                  |
      INA219 logs                        RSSI / ADV parse
         |                                  |
         +-------- USB serial merge --------+
```

This matches literature focus on **measurable KPIs** (throughput, delay, PER), not only “TX on.”

---

## 7. Optional multi-band expansion (curriculum)

| Module | Use |
| --- | --- |
| CC1101 Sub-GHz | Compare ISM policies |
| 802.15.4 radio | Zigbee/Thread coexistence with BLE |
| Wi‑Fi 6 capable ESP32-C6 | Observer / traffic generator on 802.11 |

Keep BLE research track **2.4 GHz first**.

---

## 8. Safety hardware checklist

- [ ] Shielded room / cage for continuous RF demos  
- [ ] Physical pause switch cutting PA VCC  
- [ ] Clear labeling: EDUCATIONAL LAB DEVICE  
- [ ] Attenuators before any spectrum analyzer  
