# 02 — Literature & research survey (BLE-focused)

This survey summarizes **themes** from scientific and standards literature useful for designing a better lab platform. Prefer reading full PDFs via IEEE Xplore, ACM, MDPI, PubMed Central, university repos.

---

## 1. Core themes in the literature

| Theme | Why it matters for our platform |
| --- | --- |
| **AFH / channel maps** | BLE survives interference by **avoiding** bad channels — original firmware never models this |
| **CSA #1 vs #2** | Hop algorithm quality affects packet loss under Wi‑Fi |
| **Wi‑Fi coexistence** | Dominant interferer in 2.4 GHz; ~10 BLE channels under one Wi‑Fi 20 MHz |
| **PHY choice (1M/2M/Coded)** | Reliability vs airtime vs throughput trade-offs |
| **Energy efficiency** | BLE is designed for joules/byte; continuous carrier is the opposite extreme |
| **Medical / safety coexistence (ANSI C63.27)** | Formal test methods for shared-band devices |
| **Cross-radio research (nRF24 ↔ BLE adv)** | Shows adv channels as interoperability surface |

---

## 2. Selected works & takeaways

### 2.1 AFH improvements

| Work (short) | Venue / type | Takeaway for design |
| --- | --- | --- |
| **eAFH: Informed Exploration for AFH in BLE** (Poirot & Landsiedel, DCOSS 2022) | Conference | AFH can use **informed exploration** of channels rather than naive use of maps — firmware can log exploration policies for labs |
| **Enhancing AFH for BLE** (Mast et al., LCN 2021 area) | Conference | Quality improves by **deactivating channels** under external interference — implement **blacklist UI** |
| **Revisiting AFH map prediction** (Lee et al., Energies / MDPI-related line) | Journal-style | Sniffer/AFH map **prediction** is a research problem — observer path is scientifically valuable |
| **Probability-based channel selection** (Pang et al.) | Academic | Replace hard 0/1 maps with **probabilities** under dynamic Wi‑Fi failure rates — advanced firmware mode |

**Design translation:**

```text
channel_score[i] = EMA(success) - λ * measured_energy[i]
map_bit[i] = (channel_score[i] > threshold)
next_ch = CSA(map_bit, event_counter)
```

### 2.2 Interference awareness & sensors journal line

| Work | Takeaway |
| --- | --- |
| **BLE Interference Awareness Scheme…** (Pang et al., Sensors 2021, PMC) | BLE AFH purpose is congestion avoidance in multi-protocol ISM; connection timeline = **connection intervals** + events; CSA core of hop |

**Design translation:**  
Firmware should expose **CI (connection interval) simulation**, not only max hop rate.

### 2.3 Coexistence with new unlicensed cellular (LBT / NR-U)

| Work | Takeaway |
| --- | --- |
| **Wireless Coexistence of Cellular LBT Systems and BLE 5** (Muhammad et al., PMC 2021+) | Empirical BLE 5 vs LBT; ANSI C63.27 tiers; **throughput drops** as intended-to-unintended ratio falls; **Coded/LR PHY** less susceptible in some cases; low-rate PHY **longer airtime** hurts LBT |

**Design translation:**

- Lab mode matrix: PHY × interferer class × I/U ratio  
- Teach **airtime** = packet_bits / rate as first-class metric  
- Medical/hospital coexistence is a **documented research driver** — keep ethics framing serious  

### 2.4 Classic energy & protocol comparison

| Work | Takeaway |
| --- | --- |
| **How Low Energy is Bluetooth Low Energy?** (Siekkinen et al., well-cited) | BLE efficient in **bytes per Joule** vs ZigBee-class radios under tested scenarios |

**Design translation:**  
A “better platform” should measure **current (mA)** per mode (INA219), not only RF hop rate — continuous carrier is an energy anti-pattern vs real BLE.

### 2.5 nRF24 and BLE advertisement research

| Work | Takeaway |
| --- | --- |
| Disney Research / related **two-way protocol using BLE advertisement frames** with **nRF24L01+** | nRF24 can participate in **adv-channel experiments**; interop without full BLE stack is a research topic |

**Design translation:**  
Document dual use of nRF24:

1. **Stimulus / spectrum lab** (const carrier — educational, authorized only)  
2. **Packet experiments on adv centers** (more aligned with published interop research)

### 2.6 Industry / standards companions (not journals, but essential)

| Source | Takeaway |
| --- | --- |
| Bluetooth SIG Core Specification | Normative channel tables, CSA, PHYs |
| Bluetooth SIG blogs on AFH | Clear channel map / used-unused teaching diagrams |
| Silicon Labs / Nordic AFH app notes | Practical thresholds, sweep costs (~ms, µJ class overheads) |
| IEEE 802.11 coexistence mentor docs | 2.4 GHz still crowded under Wi‑Fi 6/7 era |
| MathWorks BLE–WLAN coexistence examples | Simulation structure for teaching |

---

## 3. Research gaps useful for *our* project

| Gap | Opportunity |
| --- | --- |
| Few open **teaching kits** that implement soft-CSA + logging | Open firmware with CSA #1/#2 educational ports |
| Combo closed firmwares use crude `%N` hop | Publish **map-aware** open alternatives |
| Range claims without link budget | Force **worksheet + measurement** culture |
| Dual-PA desense understudied in hobby kits | Hardware spacing + min channel separation research note |
| Observer missing | Add cheap BLE sniffer path (ESP32/nRF52) |

---

## 4. What “better” means in a research sense

From literature, a superior system maximizes:

1. **Protocol fidelity** (channels, maps, timing)  
2. **Measurability** (PER, RSSI, current, hop logs)  
3. **Coexistence awareness** (Wi‑Fi map, LBT airtime ideas)  
4. **Reproducibility** (ANSI-like tier thinking, fixed geometries)  
5. **Safety / duty control** (especially for continuous RF stimuli)

Not merely: “higher PA and faster SPI thrash.”

---

## 5. Suggested reading order for contributors

1. Bluetooth Core Spec LE physical channel chapter (or solid secondary summary)  
2. Sensors 2021 BLE interference awareness (Pang et al.)  
3. One AFH enhancement paper (eAFH or LCN AFH)  
4. BLE 5 ↔ LBT coexistence empirical paper (PMC)  
5. Siekkinen energy paper  
6. Optional: nRF24–BLE advertisement interop paper  

## 6. Deep dive added in v2 — channel access prediction

**Karoliny et al., arXiv:2301.08109 (2023)** — *Predicting the Channel Access of Bluetooth Low Energy*

| Contribution | Relevance to our platform |
| --- | --- |
| Formal CSA#1 / CSA#2 reconstruction | Exact educational hop engine |
| Passive single-channel sniff | Observer design (Ubertooth / nRF52 / SDR) |
| \(c_{\mathrm{int}}\) estimation via GCD of inter-arrival times | Telemetry / sniffer firmware feature |
| CSA#1 period **37 events** | Easy SDR demo of periodicity |
| CSA#2 long period / CI from Access Address | Need unit tests + longer captures |
| Explicit: ADV prediction out of scope (randomness) | Don’t overclaim ADV forecasting |

**Lab experiment idea E8:** Capture one data channel; estimate \(c_{\mathrm{int}}\); distinguish CSA#1 vs #2 from inter-arrival structure.

See full equations in [09_CSA_AFH_VERIFIED.md](09_CSA_AFH_VERIFIED.md).
