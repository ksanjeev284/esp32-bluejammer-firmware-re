# 09 — CSA #1 / #2 & AFH (verified from research literature)

**Update pass:** literature cross-check (Karoliny et al. arXiv:2301.08109; Bluetooth Core Spec Vol 6 Part B §4.5.8 via secondary engineering sources; Pang et al. Sensors 2021 line).

> Educational reconstruction of hop algorithms for lab firmware design.  
> Not for attacking third-party connections.

---

## 1. Connection parameters (verified table)

| Parameter | Meaning | Notes |
| --- | --- | --- |
| \(c_{\mathrm{int}}\) | Connection interval | Multiple of **1.25 ms**, range **7.5 ms … 4 s** |
| \(k\) | Connection event counter | 16-bit, starts 0, wraps 65536→0 |
| \(\mathrm{cmap}\) | Channel map | Allowed subset of data channels **0…36** |
| \(n_{\mathrm{ch}}\) | Number of used channels | Count of 1-bits in map; min typically ≥2 in practice |
| \(h_{\mathrm{inc}}\) | Hop increment (CSA#1 only) | Used in linear recurrence |
| \(\mathrm{CI}\) | Channel Identifier (CSA#2) | From Access Address |
| \(\mathrm{AA}\) | Access Address | 32-bit; in every packet |

Advertising prediction is **harder / partially random** — Karoliny et al. explicitly leave ADV prediction out of scope for that reason.

---

## 2. CSA #1 (pre–BLE 5 / mixed legacy)

### Unmapped hop

\[
\mathrm{ch}_k = (\mathrm{ch}_{k-1} + h_{\mathrm{inc}}) \bmod 37
\]

### If channel not in map → remap

\[
r_k = k \bmod n_{\mathrm{ch}}
\]

\[
\mathrm{ch}'_k = \mathrm{cmap}[r_k]
\]

(Only remap when unmapped \(\mathrm{ch}_k \notin \mathrm{cmap}\); else \(\mathrm{ch}'_k=\mathrm{ch}_k\).)

### Critical property (verified)

- Pattern **repeats every 37 connection events** (with full map).  
- With excluded channels, remapping still produces **short periodic structure**.  
- **Unequal usage** risk when many channels blocked — motivation for CSA#2.

### Lab firmware implication

```text
# educational CSA#1
ch = (ch + h_inc) % 37
if not map[ch]:
    ch = used_list[event_counter % n_used]
nrf = ble_data_index_to_nrf(ch)   # 2402+2*ch → nRF
```

Use for **legacy comparison** demos; log period-37 spectrograms on SDR.

---

## 3. CSA #2 (BLE 5.0+)

### Channel Identifier

\[
\mathrm{CI} = \mathrm{AA}[31:16] \oplus \mathrm{AA}[15:0]
\]

### Pseudo-random unmapped channel

Uses composed PRNG (MAM multiply-add-mod, bit-permutation \(g_{\mathrm{perm}}\), XOR with CI) — Core Spec function composition:

\[
\mathrm{prn}_k = F_{\mathrm{CI}}(k)
\]

\[
\mathrm{ch}_k = \mathrm{prn}_k \bmod 37
\]

**Important:** \(\mathrm{ch}_k\) depends on **current \(k\) and CI only**, not on \(\mathrm{ch}_{k-1}\).

### Remap when blocked

\[
r_k = \left\lfloor \frac{n_{\mathrm{ch}}\cdot \mathrm{prn}_k}{2^{16}} \right\rfloor
\]

\[
\mathrm{ch}'_k = \mathrm{cmap}[r_k]
\]

### Critical properties (verified)

- Repetition period on the order of **65536** events (not 37).  
- Remapping **more uniform** across remaining channels.  
- Literature: **more robust under interference** than CSA#1.  
- Passive observers can **reconstruct hop pattern** from passive single-channel sniff + enough samples (Karoliny et al.).

### Lab firmware implication

Implement educational CSA#2 with:

1. Fixed test Access Address → known CI  
2. Software event counter \(k\)  
3. Published test vectors (unit-test on host PC)  
4. Compare hop histogram CSA#1 vs #2 under same `cmap` (Wi‑Fi 1/6/11 mask)

---

## 4. AFH closed loop (standards + papers)

```text
PER / RSSI / energy per channel
        │
        ▼
 update cmap (block bad channels)
        │
        ▼
 master sends Channel Map Update Ind
        │
        ▼
 CSA uses new cmap for future events
```

Research improvements beyond the spec:

| Approach | Idea |
| --- | --- |
| Probability maps (Pang et al.) | Soft scores instead of hard 0/1 |
| eAFH informed exploration | Actively explore uncertain channels |
| Multi-map fusion | Combine several environmental snapshots |

**Vendor practice (example, not universal law):** energy sweeps marking channels above ~**−71 dBm** class as bad for hold times (Silicon Labs-style AFH notes). Always verify against your stack’s documentation.

---

## 5. Wi‑Fi footprint on BLE (verified order of magnitude)

Multiple academic sources: one **20 MHz Wi‑Fi** channel affects on the order of **~10 BLE channels** (2 MHz each).

Design lab mask (approximate data-channel indices under Wi‑Fi 1/6/11 — refine with spectrum plot):

| Wi‑Fi | Center | BLE data channels roughly impacted |
| ---: | ---: | --- |
| 1 | 2412 | lower ~0–8 class |
| 6 | 2437 | mid band |
| 11 | 2462 | upper data |

Advertising **37/38/39** remain special; still can sit near Wi‑Fi skirts (esp. 38 @ 2426 near ch6).

---

## 6. Empirical coexistence notes (INL / chamber-style studies)

- BLE under Wi‑Fi: **PER can rise** (example lab figures report BLE PER fluctuating in low single digits to ~10% class under specific setups; **do not universalize**).  
- Wi‑Fi often remains comparatively robust (higher power / wider bandwidth).  
- BLE 5 **coded PHY**: more robust in some LBT coexistence tests, but **longer airtime**.  
- Always report: distance, TX powers, duty, channel plan, PHY — ANSI C63.27 culture.

---

## 7. Verification checklist for our docs

| Claim in earlier notes | Status after this pass |
| --- | --- |
| 40 channels, 2 MHz, adv 37–39 @ 2402/2426/2480 | **Confirmed** (Core Spec consensus) |
| Data 0–36 for connections | **Confirmed** |
| CSA#1 period 37 | **Confirmed** (Karoliny et al.) |
| CSA#2 uses CI from Access Address | **Confirmed** |
| CSA#2 more robust | **Supported by literature** |
| Wi‑Fi ~10 BLE channels | **Supported by literature** |
| Original `%39` is not BLE-faithful | **Confirmed** (wrong domain entirely) |

---

## 8. References for this file

1. J. Karoliny et al., *Predicting the Channel Access of Bluetooth Low Energy*, arXiv:2301.08109, 2023.  
2. Bluetooth Core Specification, Vol 6, Part B, Channel Selection (§4.5.8 class).  
3. B. Pang et al., Sensors 2021 (interference awareness / CSA improvements).  
4. TI / Nordic / Silicon Labs BLE stack user guides (CSA#2 engineering notes).  
