# How Pro EDU improves effectiveness (education)

This document explains **what** changed for hop/spectrum effectiveness, **why** it matters for learning 2.4 GHz protocol layout, and **how** to measure it in a lab.

> **Legal:** Continuous-carrier RF can cause unlawful interference.  
> Use only in an **authorized / shielded** environment. This is **not** a guide to jam public networks.

---

## 1. The problem with the original hop math

Recovered from the closed binary `radioTask`:

| Mode | Original formula | What that actually hits on nRF24 |
| --- | --- | --- |
| Bluetooth | `random() % 79` | nRF channels **0–78** (reasonable for BT classic) |
| BLE | `random() % 39` | nRF **0–38** only — **misses BLE adv @ 2480 MHz (nRF 80)** |
| Wi‑Fi | `random() % 14` | nRF **0–13** ≈ **2400–2413 MHz** — barely Wi‑Fi ch1 edge |
| RC | `random() % 125` | nRF **0–124** (wide, unstructured) |

Also:

- Both radios pick **independently**, so they often land on the **same** channel (wasted second radio).
- Hop is pure random — no bias toward **protocol centers** (Wi‑Fi 1/6/11, BLE advertising).

So the original is aggressive in SPI write rate, but **weak in spectral relevance** for Wi‑Fi and BLE demos.

---

## 2. What Pro EDU changes

### A. Protocol-aware channel maps (`hop_maps.h`)

nRF24 channel \(N\) → frequency \(2400 + N\) MHz.

| Mode | EDU priority targets | Full fill band |
| --- | --- | --- |
| **BT** | Evenly spaced samples across 0–78 | 0–78 |
| **BLE** | Adv **2 / 26 / 80** (2402 / 2426 / 2480 MHz) + data samples | 0–80 |
| **Wi‑Fi** | Centers of ch **1–13**: **12, 17, 22, …, 72** | 0–82 |
| **RC** | 5 MHz grid across 0–125 | 0–125 |

Default mix: **`HOP_PRIORITY_PCT = 60`** → 60% priority map, 40% full-band random fill.

**Educational takeaway:** you can see on a spectrum analyzer / SDR that Wi‑Fi mode now lines up with real 20 MHz Wi‑Fi centers, not a 13 MHz stub at the bottom of the band.

### B. Complementary dual radio (`COMPLEMENTARY_DUAL = 1`)

Every hop:

1. Pick channel for radio H  
2. Pick channel for radio V **≠** H (offset / other priority entry)

**Effect:** two simultaneous tones → roughly **2× spectral presence** vs both modules stacking on one channel.

**Educational takeaway:** diversity vs redundancy — two transmitters only help if they cover **different** resources (here: channels).

### C. Hop strategies (`HOP_STRATEGY` in `config.h`)

| Value | Name | Behavior | Best for |
| --- | ---: | --- | --- |
| `0` | ORIGINAL | Pure `random%mod` like the closed binary | A/B compare with stock behavior |
| `1` | **EDU (default)** | Priority maps + fill + dual complement | Teaching + denser relevant coverage |
| `2` | SWEEP | Deterministic walk; V offset by half-band | SDR waterfall demos, repeatable labs |

### D. Density without the original SPI storm

| | Original | Pro EDU default |
| --- | --- | --- |
| Writes per loop | 100 × 2 radios | **48** × 2 |
| Loop delay | 1 ms | **1 ms** |
| Channel quality | random % small-N | **protocol centers** |

You still hop very fast, but each hop is **more likely to matter** for the selected protocol class.

### E. Lab observability (measure effectiveness)

| Feature | What you learn |
| --- | --- |
| Serial **LAB STATS** every 2 s | hop rate, chH/chV, unique≈ coverage |
| Mode enter **EDU mode map** text | which MHz / nRF numbers that mode targets |
| OLED HUD `Hxx Vyy` | live dual-channel confirmation |
| Idle screen hops + uniq | coverage progress while paused UI |

Example serial line:

```text
==== LAB STATS (education) ====
mode=State 3: WiFi  strategy=EDU (protocol maps + dual complement)
chH=37  chV=62  dual_diff=yes
hop_rate≈9600/s  total=192340  unique_in_mode≈41
```

- `chH=37, chV=62` → Wi‑Fi **ch6** and **ch11** centers (good dual placement).  
- `dual_diff=yes` → second radio is not wasted.  
- `unique_in_mode` → how much of the map you’ve visited since mode entry.

---

## 3. Why this is “more effective” (lab definition)

Effectiveness here means **better use of hardware time for educational spectrum coverage**, not “stronger illegal jammer.”

| Metric | Original | Pro EDU | Why better for education |
| --- | --- | --- | --- |
| Wi‑Fi energy near real centers | Rare (0–13 only) | Common (12…72 map) | Matches textbooks / Wireshark ch plan |
| BLE advertising frequencies | Often missed (no ch80) | Prioritized 2/26/80 | Matches BLE core spec adv channels |
| Dual-radio utilization | Same-ch collisions | Forced different ch | Teaches spatial/spectral diversity |
| Measurability | Opaque | Stats + HUD | Students can quantify hop_rate & coverage |
| Repeatability | RNG only | SWEEP mode | Same waterfall every run |

---

## 4. How to demonstrate in class / lab (authorized)

1. Flash Pro: `firmware/ComboChannelSelectPro_FULL_FLASH.bin`  
2. Open serial **115200** — read strategy banner and mode maps.  
3. Optional: SDR/spectrum analyzer near a **shielded** setup.  
4. Cycle modes with BOOT; watch LAB STATS and OLED `H/V`.  
5. A/B test: set `HOP_STRATEGY 0` vs `1` vs `2`, recompile, compare unique coverage and SDR traces for Wi‑Fi / BLE modes.  
6. SAFE UI-only: `REBUILD_SAFE 1` still runs **simulated** hop stats (no RF TX) for classroom without radios.

---

## 5. Config cheat sheet

| Define | Default | Effect |
| --- | --- | --- |
| `HOP_STRATEGY` | `1` (EDU) | 0=original, 1=edu maps, 2=sweep |
| `HOP_PRIORITY_PCT` | `60` | % of hops from protocol priority table |
| `COMPLEMENTARY_DUAL` | `1` | Force R1 ≠ R2 channel |
| `HOP_BATCH` / `HOP_DELAY_MS` | `48` / `1` | Hop density vs SPI load |
| `EDU_STATS_MS` | `2000` | Serial stats period (`0` = off) |
| `EDU_OLED_HUD` | `1` | Live ch on OLED |
| `REBUILD_SAFE` | `0` | `1` = no RF TX |

---

## 6. Files involved

| File | Role |
| --- | --- |
| `src/ComboChannelSelectPro/hop_maps.h` | Protocol channel tables + strategy names |
| `src/ComboChannelSelectPro/config.h` | Strategy / density / telemetry knobs |
| `src/ComboChannelSelectPro/ComboChannelSelectPro.ino` | Hop engine, dual complement, stats, HUD |
| `IMPROVEMENTS.md` | Runtime reliability vs original rebuild |
| **This file** | Effectiveness / education rationale |

---

## 7. Summary in one sentence

**Pro EDU spends hop time on frequencies that real BT/BLE/Wi‑Fi/RC systems actually use, keeps both nRF24 modules on different channels, and exposes hop metrics so students can measure coverage — instead of thrashing random low channel numbers like the original binary.**
