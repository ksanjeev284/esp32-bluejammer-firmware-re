# 01 — BLE PHY and channel structure (engineer-accurate)

## 1. Band and channelization

BLE (Bluetooth Core Spec, LE) uses the **2.4 GHz ISM** band with:

- **40 channels**, index \(k = 0 \ldots 39\)
- **2 MHz** channel spacing
- Center frequencies:

\[
f_k = 2402 + 2\cdot k \quad \text{[MHz]},\quad k=0..39
\]

So:

| Role | Channel indices | Centers (MHz) |
| --- | --- | --- |
| **Data / general purpose** | 0 … 36 | 2402 … 2474 (even steps) |
| **Primary advertising** | **37, 38, 39** | **2402, 2426, 2480** |

**Why advertising is special (design intent):**  
Centers **2402 / 2426 / 2480** sit in **gaps relative to common Wi‑Fi 1 / 6 / 11** energy, reducing average collision probability for discovery — a recurring theme in coexistence literature and teaching materials.

### Mapping to nRF24L01 channel numbers

nRF24: \(f = 2400 + N\) MHz ⇒ \(N = f - 2400\).

| BLE | \(f\) (MHz) | nRF24 \(N\) |
| --- | ---: | ---: |
| Adv 37 | 2402 | **2** |
| Adv 38 | 2426 | **26** |
| Adv 39 | 2480 | **80** |
| Data ch 0 | 2402 | 2 |
| Data ch 18 | 2438 | 38 |
| Data ch 36 | 2474 | 74 |

**Implication for any nRF24 “BLE mode”:**  
Prioritize **2, 26, 80** for advertising-centric demos; use even nRF channels **2…74** for data-band sampling.  
Original combo firmware `random() % 39` → nRF **0…38 only** → **never reaches 2480 MHz (adv 39)** and poorly matches the 2 MHz BLE grid.

---

## 2. Modulation and PHY options (BLE 4 → 5)

| PHY | Symbol rate / idea | Approx. data rate | Robustness / range trend |
| --- | --- | --- | --- |
| **LE 1M** | 1 Msps GFSK | 1 Mbps | Baseline |
| **LE 2M** (BLE 5) | 2 Msps | 2 Mbps | Higher throughput, less range margin |
| **LE Coded S=2 / S=8** | Coding + longer symbols | 500 / 125 kbps class | **Better sensitivity / range**, longer airtime |

Empirical coexistence work (e.g. BLE 5 vs cellular LBT in 2.4 GHz) reports that **coded / long-range PHY** is **less susceptible** to interference under some conditions, while **low-rate PHYs occupy air longer** and can harm coexisting LBT systems’ throughput. Design lesson:

- For **lab robustness demos** → study coded PHY airtime vs reliability.  
- For **observer tools** → 1M is enough for advertising decode.  
- nRF24 const-carrier **cannot** implement coded BLE PHY; native BLE silicon is required for true PHY labs.

---

## 3. Connectionless vs connection-oriented

```text
[Advertiser] --ADV on 37/38/39--> [Scanner]
       |
       +-- connect request --> [Connection]
              hops on data channels 0..36 under AFH map
```

### Advertising

- Packets on **primary** adv channels (and optionally secondary for extended adv).  
- Used for discovery, beacons, connection establishment.  
- Research note: some works even study **nRF24 ↔ BLE** interaction via **advertisement frames only** (interop research), showing adv channels are the critical shared surface.

### Connection (AFH)

- Master maintains a **channel map** (used / unused among 37 data channels).  
- **Channel Selection Algorithm (CSA)** picks next hop.  
- Spec defines **CSA #1** and **CSA #2**; literature finds **CSA #2 more robust** under interference; further papers propose **probability-weighted** maps and **informed exploration (eAFH)**.

**Firmware implication:** A “better BLE lab mode” should at least:

1. Weight advertising centers heavily in discovery demos.  
2. For “connected hop” demos, use a **37-bit map** model + pseudo-CSA, not `%39`.  
3. Optionally **blacklist** channels overlapping active Wi‑Fi (measured or assumed 1/6/11).

---

## 4. Adaptive Frequency Hopping (AFH) — logic

Conceptual control loop (from standards + vendor notes + papers):

```text
measure energy / PER per channel
        │
        ▼
 update channel map (block bad channels)
        │
        ▼
 CSA picks hop sequence from remaining channels
        │
        ▼
 master distributes map to slave
```

Example industrial threshold (vendor docs, not universal): channels with RSSI above roughly **−71 dBm** class may be marked bad for a hold time. Academic work studies **prediction**, **multi-map probability**, and **exploration vs exploitation** of channels.

**Educational platform feature (recommended):**

| Feature | Purpose |
| --- | --- |
| Simulated channel map UI | Teach AFH without illegal field attacks |
| Manual blacklist (Wi‑Fi 1/6/11) | Coexistence planning lab |
| Logged hop sequence | Compare CSA #1 vs #2 implementations |
| Energy sense via SDR or ESP Wi‑Fi scan | Cheap “environment map” input |

---

## 5. Wi‑Fi overlap model (for calculations)

One 20 MHz Wi‑Fi channel overlaps **many** BLE 2 MHz channels (literature often cites order of **~8–10+ BLE channels** under a Wi‑Fi 20 MHz occupancy).

Rough center mapping:

| Wi‑Fi ch | Center MHz | Nearby BLE centers |
| ---: | ---: | --- |
| 1 | 2412 | BLE data around 2410–2414 region |
| 6 | 2437 | mid band |
| 11 | 2462 | upper data band |

Advertising **2426** sits near Wi‑Fi 6 skirts; **2402/2480** are relatively edge-placed.

---

## 6. Timing (order-of-magnitude)

| Parameter | Typical order |
| --- | --- |
| Adv interval | 20 ms … multi-second (app dependent) |
| Connection interval | 7.5 ms … 4 s (spec range class) |
| Event length | few packets per event |

Hop rate of a **connected** BLE link is **much slower** than the original combo firmware’s “100 SPI channel writes per ms” style.  
**Lesson:** original hop storm is **not** a faithful BLE traffic model; it is a **dense continuous stimulus**. A better educational firmware should offer:

- **BLE_FAITHFUL** — slow hop / dwell matching connection intervals  
- **BLE_STRESS_LAB** — dense dual-tone maps for spectrum analyzer teaching (clearly labeled)

---

## 7. Takeaways for “better than original”

| Original combo BLE mode | Research-aligned better mode |
| --- | --- |
| `random()%39` on nRF | Adv **2/26/80** + data even grid **2…74** |
| No channel map | Soft AFH map + blacklist |
| No PHY concept | Document 1M/2M/Coded; use native BLE chip for real PHY |
| Same hop rate all modes | Mode-specific timing profiles |
| Opaque binary | Open logs: hop sequence, map, duty, EIRP assumptions |
