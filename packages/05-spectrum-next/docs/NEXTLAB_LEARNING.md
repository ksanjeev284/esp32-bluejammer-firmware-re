# SpectrumLab Next — learning guide

Educational firmware that is **standards-informed** and **instrumentable**, designed to be clearly better for teaching than opaque combo binaries.

---

## What you will learn

1. How **IEEE 802.11** 2.4 GHz centers map onto nRF24 channels  
2. Why operators use **non-overlapping 1/6/11**  
3. Where **BLE advertising** energy lives (2 / 26 / 80)  
4. How **IEEE 802.15.4** channels 11–26 sit between Wi-Fi energy  
5. Why **coexistence** is a scheduling + spectrum planning problem  
6. How **PA hardware + power integrity** dominate real performance  
7. How to log lab data with **JSON telemetry**

---

## Modes (BOOT short cycles)

| Mode | Label | Teaching point |
| --- | --- | --- |
| BT | BT classic edu grid | 79×1 MHz AFH-style sampling |
| BLE | BLE Core Spec | Adv 37/38/39 + data samples |
| 802.11 | IEEE 802.11 2.4 | Real centers; weight 1/6/11 |
| RC | ISM wide | Full 0..125 grid |
| **802.15.4** | Zigbee/Thread map | **New** vs older packages |
| **COEXIST** | Multi-sched | **New** time-sliced families |

Long BOOT = pause RF. Short while paused = resume.

---

## Lab sequence (authorized / shielded)

### Lab 1 — Wi-Fi non-overlap

1. Mode **802.11**, serial + SDR.  
2. Confirm energy clusters near nRF **12 / 37 / 62**.  
3. Change `WIFI_NOLAP_WEIGHT_PCT` from 55 → 10; rebuild; compare.

### Lab 2 — BLE advertising

1. Mode **BLE**.  
2. Look for **2, 26, 80**.  
3. Explain why original `%39` missed 2480 MHz.

### Lab 3 — 802.15.4 vs Wi-Fi

1. Alternate **802.15.4** and **802.11**.  
2. Map overlaps (e.g. Zigbee 11–14 near Wi-Fi 1).  
3. Discuss preferred Zigbee channels 15/20/25/26 in textbooks.

### Lab 4 — Coexist scheduler

1. Mode **COEXIST**.  
2. Watch serial `coexist_slice_family=...` rotate.  
3. SDR: see family-dependent spectral patterns over time.  
4. Essay: how real 802.11 CCA differs from this demo.

### Lab 5 — Hardware tier

1. Stock vs PA+LNA with same firmware profile change.  
2. Log hop_rate, begin retries, Vcc if wired.

### Lab 6 — JSON notebook

1. Capture lines starting with `{`.  
2. Parse in Python pandas; plot hop_rate vs mode.

---

## Config knobs (`config.h`)

| Knob | Meaning |
| --- | --- |
| `LAB_ENGINE` | 0 classic 4-mode · 1 IEEE next · 2 research max |
| `HW_PROFILE` | 0 stock · 1 PA+LNA · 2 HG+duty |
| `WIFI_NOLAP_WEIGHT_PCT` | Bias to Wi-Fi 1/6/11 |
| `COEXIST_SLICE_MS` | Family rotation period |
| `DUAL_MIN_SEPARATION` | Dual PA channel delta |
| `JSON_TELEMETRY` | Machine-readable stats |
| `REBUILD_SAFE` | No RF TX |

---

## Ethics

Higher standards fidelity ≠ permission to interfere.  
Authorized labs only. Prefer SAFE builds for lecture halls.

---

## Further reading

- `research/IEEE_RESEARCH.md`  
- `hardware/NEXT_COMPONENTS.md`  
- Prior packages: Optimized (EDU maps), RangePro (link budget)
