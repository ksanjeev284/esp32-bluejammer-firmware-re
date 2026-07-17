# 10 — nRF24L01+ numbers (datasheet-verified) & PA module caveats

**Update pass:** Nordic nRF24L01+ Product Specification cross-check + module ecosystem notes.

---

## 1. Stock nRF24L01+ (chip) — verified specs

| Parameter | Value | Source class |
| --- | --- | --- |
| Band | 2.400–2.525 GHz | Nordic PS |
| Channels | 126 × 1 MHz steps | Nordic PS |
| Air rates | **250 kbps, 1 Mbps, 2 Mbps** | nRF24L01+ (plus only for 250k) |
| TX power steps | **0, −6, −12, −18 dBm** | Nordic PS |
| TX current @ 0 dBm | **~11.3 mA** | Nordic PS |
| RX sensitivity @ 2 Mbps | **−82 dBm** (0.1% BER) | Nordic PS |
| RX sensitivity @ 1 Mbps | **−85 dBm** | Nordic PS |
| RX sensitivity @ 250 kbps | **−94 dBm** | Nordic PS |
| RX current @ 2 Mbps | **~12.3–13.5 mA** class | Nordic PS |

### Sensitivity gain (packet links)

\[
\Delta S(250\text{k vs }2\text{M}) = -94 - (-82) = \mathbf{−12\ dB\ better\ sensitivity}
\]

Free-space range factor from sensitivity alone (\(n=2\)):

\[
10^{12/20} \approx \mathbf{4.0×}
\]

At \(n=2.5\): \(10^{12/25}\approx \mathbf{3.0×}\).

**This applies to cooperative packet links**, not automatically to “const carrier interference reach,” which is dominated by **TX EIRP** and victim SIR.

---

## 2. PA+LNA modules — marketing vs reality

| Claim common on listings | Engineering reality |
| --- | --- |
| “+20 dBm / 100 mW” | Often **RFX2401C-class** front-end; **measure** with SA + attenuator |
| “1 km range” | Occasional LOS hobby reports; many tests **≪ 1 km** |
| TX current | PA stage alone **~100–120 mA** class @ high power (amp datasheets / community) |
| Module total TX | Often **~100–200+ mA**; dual modules need **≥1–2 A 3.3 V design** |

**Stock chip max is 0 dBm** — any “20 dBm” is **external PA**, not Nordic register alone.

**Verification rule for research platform:**

1. Calibrate each module’s conducted power into 50 Ω + attenuator.  
2. Record true \(P_t\) in lab notebook.  
3. Replace assumed +18 dBm in link budgets with measured value.

---

## 3. Updated link-budget rows (stock chip truth table)

Using **datasheet** \(P_t=0\) dBm max for bare module:

| Rate | Sensitivity | For packet SNR margin vs 2M |
| --- | --- | --- |
| 2 Mbps | −82 dBm | baseline |
| 1 Mbps | −85 dBm | +3 dB |
| 250 kbps | −94 dBm | +12 dB |

Original combo firmware used **2 Mbps** (RE). Range Pro default **250 kbps** is justified for **packet** labs by **+12 dB** RX sensitivity on stock silicon.

---

## 4. Dual-nRF24 vs BLE channel raster (verified mismatch)

| | nRF24 | BLE |
| --- | --- | --- |
| Spacing | **1 MHz** | **2 MHz** |
| Count | up to 126 | 40 |
| Adv centers | N/A | 2402/2426/2480 |

Mapping BLE→nRF is exact in MHz, but nRF can also sit on **odd** MHz BLE does not use as centers.  
Research firmware should hop **even nRF channels** matching BLE centers when in BLE modes.

---

## 5. Const carrier note (lab honesty)

`startConstCarrier` is **not** a BLE PHY.  
It is a **CW tone** useful for:

- spectrum analyzer teaching  
- dual-tone desense experiments  
- coarse occupancy demos  

It is **not** a substitute for AFH/CSA packet traffic in scientific BLE studies. Native BLE stack required for packet KPIs (PER, interval, ADV decode).

---

## 6. References

1. Nordic Semiconductor, *nRF24L01+ Product Specification*.  
2. RFX2401C / module vendor datasheets (PA current).  
3. Community range tests (anecdotal; treat as lower-tier evidence).  
