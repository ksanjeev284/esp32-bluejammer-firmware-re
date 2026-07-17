# 05 — Link budget & realistic calculations

## 1. Core formulas

### Free-space path loss

\[
\mathrm{FSPL(dB)} = 20\log_{10}(d_{\mathrm{m}}) + 20\log_{10}(f_{\mathrm{MHz}}) - 27.55
\]

At \(f=2440\ \mathrm{MHz}\):

\[
\mathrm{FSPL} \approx 20\log_{10}(d) + 40.2
\]

### Received power

\[
P_r = P_t + G_t + G_r - L - \mathrm{FSPL}
\quad \text{(dB units)}
\]

### EIRP

\[
\mathrm{EIRP} = P_t + G_t - L_{\mathrm{tx}}
\]

### Distance scaling

\[
\frac{d_2}{d_1} = 10^{\Delta P/(10n)},\quad
n=\begin{cases}2 & \text{free space}\\ 2.5 & \text{open outdoor}\\ 3.5 & \text{indoor}\end{cases}
\]

### Airtime (BLE-like packet)

\[
T_{\mathrm{air}} \approx \frac{N_{\mathrm{bits}}}{R} + T_{\mathrm{preamble/overhead}}
\]

Longer \(T_{\mathrm{air}}\) ⇒ more collision probability with coexisting systems (LBT/Wi‑Fi literature theme).

### Dual independent tones (not coherent)

If two transmitters on **different** frequencies, free-space range to detect *each* tone ≈ single-tone range.  
**Coverage utility** may increase roughly:

\[
U \propto \eta_{\mathrm{spectral}}\cdot\eta_{\mathrm{dual}}\cdot P_r
\]

---

## 2. Parameter sets

| ID | Description | \(P_t\) | \(G_t\) | \(L\) | EIRP-like \(P_t+G_t-L\) |
| --- | --- | ---: | ---: | ---: | ---: |
| S0 | Original stock nRF | 0 | −2 | 6 | **−8 dBm** |
| P0 | Original-style PA+LNA | 18 | 2 | 4 | **+16 dBm** |
| R0 | Research firmware + PA (better PSU) | 18 | 2 | 3 | **+17 dBm** |
| R1 | Research + 5 dBi | 18 | 5 | 3 | **+20 dBm** |
| B0 | Native BLE phone-class (illustrative) | 4 | −2 | 2 | **0 dBm** |
| B1 | Native BLE + front-end (lab) | 10 | 2 | 2 | **+10 dBm** |

*(PA “18 dBm” is a working assumption; measure your modules.)*

---

## 3. Free-space max distance for \(P_{r,\min}=-80\) dBm

\[
\mathrm{FSPL}_{\max} = (P_t+G_t-L) - P_{r,\min}
\]

| ID | FSPL_max | \(d_{\mathrm{FS}}\) |
| --- | ---: | ---: |
| S0 | 72 dB | \(10^{(72-40.2)/20}\approx\mathbf{39\ m}\) |
| P0 | 96 dB | \(\approx\mathbf{617\ m}\) |
| R0 | 97 dB | \(\approx\mathbf{692\ m}\) |
| R1 | 100 dB | \(\approx\mathbf{977\ m}\) |
| B0 | 80 dB | \(\approx\mathbf{98\ m}\) |
| B1 | 90 dB | \(\approx\mathbf{309\ m}\) |

Free space is a **ceiling**, not a field guarantee.

---

## 4. Realistic outdoor (\(n=2.5\)), anchor P0 = 120 m

Scale:

\[
d = 120 \times 10^{(E-16)/(10\cdot 2.5)} = 120 \times 10^{(E-16)/25}
\]

where \(E = P_t+G_t-L\).

| ID | \(E\) | Δ vs P0 | Ratio | **d_real** |
| --- | ---: | ---: | ---: | ---: |
| S0 | −8 | −24 dB | \(10^{-0.96}\approx0.110\) | **~13 m** |
| P0 | 16 | 0 | 1 | **120 m** |
| R0 | 17 | +1 | 1.096 | **~132 m** |
| R1 | 20 | +4 | 1.445 | **~173 m** |
| B0 | 0 | −16 | 0.229 | **~27 m** |
| B1 | 10 | −6 | 0.575 | **~69 m** |

### Indoor \(n=3.5\), anchor P0 = 35 m

| ID | Ratio | d_in |
| --- | ---: | ---: |
| S0 | \(10^{-24/35}\approx0.21\) | **~7 m** |
| P0 | 1 | **35 m** |
| R0 | 1.07 | **~37 m** |
| R1 | 1.30 | **~46 m** |

---

## 5. Protocol effectiveness factor (BLE modes)

Original BLE mode spectral efficiency \(\eta_o\) vs research adv-weighted \(\eta_r\):

Assume:

- \(\eta_o = 0.35\) (random 0..38 misses adv39, poor 2 MHz alignment)  
- \(\eta_r = 0.85\) (weights 2/26/80 + data grid)  
- \(\eta_{\mathrm{dual},o}=1.05\), \(\eta_{\mathrm{dual},r}=1.40\)

\[
\frac{U_r}{U_o} = \frac{0.85}{0.35}\times\frac{1.40}{1.05}\approx 2.43\times 1.33 \approx \mathbf{3.2}
\]

Equivalent distance for same utility (\(n=2.5\)):

\[
\frac{d_r}{d_o} \approx 3.2^{1/2.5} \approx 3.2^{0.4} \approx \mathbf{1.6}
\]

**Interpretation:** On the **same PA hardware**, research-aligned BLE maps may feel like **~1.6× “effective BLE-relevant reach”**, while pure geometric EIRP range only rose **~10%** (R0 vs P0).

---

## 6. BLE airtime example (connected lab)

Packet 200 bits payload + ~100 bits overhead ≈ 300 bits.

| PHY rate \(R\) | \(T_{\mathrm{air}}\) approx |
| --- | ---: |
| 1 Mbps | 0.30 ms |
| 2 Mbps | 0.15 ms |
| 125 kbps coded-class | 2.4 ms |

Collision exposure vs Wi‑Fi grows with airtime — matches empirical papers: low-rate PHYs can **hurt neighbors** while being more robust themselves.

---

## 7. Current / energy example

Assume dual PA TX ~350 mA @ 3.3 V ⇒ \(P\approx 1.16\ \mathrm{W}\).

| Duty | Average power | Energy / hour |
| ---: | ---: | ---: |
| 100% | 1.16 W | 1.16 Wh |
| 70% | 0.81 W | 0.81 Wh |
| 20% | 0.23 W | 0.23 Wh |

Real BLE advertising at low duty is **orders of magnitude** lower average energy — Siekkinen-style results motivate **energy telemetry** as a first-class lab metric.

---

## 8. SNR / interference margin (conceptual)

For a victim receiver with desired signal \(P_s\) and interferer \(P_i\):

\[
\mathrm{SIR} = P_s - P_i \quad \text{(dB)}
\]

If coding/modulation needs SIR > \(\gamma_{\min}\):

\[
P_i < P_s - \gamma_{\min}
\]

**Range of interference** is the distance where \(P_i(d)\) still exceeds that bound — depends as much on **victim link budget** as on your EIRP.  
This is why literature uses **intended-to-unintended ratios** in chamber tests (ANSI C63.27 style).

---

## 8b. Datasheet-backed sensitivity (Nordic nRF24L01+) — verification addendum

| Air rate | Sensitivity (0.1% BER) | Δ vs 2 Mbps |
| --- | ---: | ---: |
| 2 Mbps | **−82 dBm** | 0 |
| 1 Mbps | **−85 dBm** | +3 dB |
| 250 kbps | **−94 dBm** | **+12 dB** |

Stock TX max **0 dBm** (not 20 dBm — that requires external PA).

**Packet range multiplier from rate alone (RX sensitivity):**

| Path exponent \(n\) | Factor \(10^{12/(10n)}\) for 250k vs 2M |
| ---: | ---: |
| 2.0 | **×4.0** |
| 2.5 | **×3.0** |
| 3.5 | **×2.2** |

Use this when comparing original **2 Mbps** rebuilds to Range Pro **250 kbps** *for packet links*. Const-carrier interference reach still tracks **TX EIRP** primarily.

See [10_NRF24_DATASHEET_VERIFIED.md](10_NRF24_DATASHEET_VERIFIED.md).

---

## 9. Summary table (use in reports)

| Scenario | Geometric outdoor (model) | BLE-relevant effectiveness |
| --- | --- | --- |
| Original stock | ~10–20 m | Poor |
| Original PA + `%39` hop | ~100–150 m | Moderate / misaligned |
| Research PA + maps + dual sep | ~130–180 m | **High** |
| Native BLE lab (phone-class) | tens of m | Real packets, true AFH |

Fill `calc_worksheets/link_budget_template.csv` with **your measured** \(P_t\).
