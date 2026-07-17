# IEEE & industry research notes (SpectrumLab Next)

**Package:** `ESP32-ComboChannelSelect-IEEE-NextLab`  
**Purpose:** Map recent IEEE / industry RF standards knowledge into an **educational** dual-nRF24 lab platform that is technically ahead of the original closed combo binary and prior rebuild packages.

> This is **not** an IEEE-compliant transmitter PHY.  
> nRF24 constant-carrier is a **teaching stimulus** used to exercise **channel maps**, **coexistence concepts**, and **lab instrumentation** — only in authorized environments.

---

## 1. Standards surveyed (latest relevant material)

| Area | Document / amendment | Takeaways used in this package |
| --- | --- | --- |
| WLAN | **IEEE 802.11ax** (Wi-Fi 6/6E) | 2.4 GHz channelization **unchanged**; denser BSS; **OFDMA**; coexistence still relies on **CCA** / CSMA-CA family rules in 2.4 GHz |
| WLAN | **IEEE 802.11be-2024** (Wi-Fi 7), published **2025** | Extremely High Throughput; still **2.4 / 5 / 6 GHz** with backward compatibility; 2.4 GHz remains crowded multi-technology band |
| WLAN mentor docs | 802.11ax / 802.11be **coexistence assessment** docs | Explicit: CSMA/CA / CCA remain the coexistence tools in 2.4 GHz; non-802.11 systems share the ISM band |
| WPAN | **IEEE 802.15.4-2020** | 2.4 GHz O-QPSK channels **11–26**, 5 MHz spacing, \(f=2405+5(ch-11)\) MHz |
| Bluetooth | **Bluetooth Core Spec** (industry + IEEE historical 802.15.1 lineage) | Adv channels **37/38/39** @ **2402 / 2426 / 2480** MHz; classic 79×1 MHz AFH story |
| Coexistence literature | 802.11 ↔ 802.15.4 overlap studies | Wi-Fi 20 MHz energy swamps narrow WPAN; channel planning (Wi-Fi 1/6/11 vs Zigbee 15/20/25/26) is a real engineering skill |

### Key 2024–2025 WLAN note

**802.11be (Wi-Fi 7)** optimizes multi-link / wider channels especially in **6 GHz**, but **2.4 GHz does not go away**. It remains the long-range, wall-penetrating, IoT-heavy band where **Bluetooth, 802.15.4 (Zigbee/Thread/Matter lower layers), and 802.11** still collide. That is why a **2.4 GHz multi-standard educational map** is still the right lab focus for this hardware class.

---

## 2. Channel math used in firmware (`ieee_maps.h`)

### 2.1 IEEE 802.11 (2.4 GHz)

| Wi-Fi ch | Center MHz | nRF24 ch (\(f-2400\)) |
| ---: | ---: | ---: |
| 1 | 2412 | **12** |
| 6 | 2437 | **37** |
| 11 | 2462 | **62** |
| 13 | 2472 | **72** |

**Firmware improvement vs original binary:** original Wi-Fi mode used `random%14` → only ~2400–2413 MHz.  
**NextLab** uses real centers and **weights non-overlapping 1/6/11** (`WIFI_NOLAP_WEIGHT_PCT`) — matching how operators actually plan BSS.

### 2.2 BLE (Core Spec advertising)

| BLE adv | MHz | nRF |
| --- | ---: | ---: |
| 37 | 2402 | **2** |
| 38 | 2426 | **26** |
| 39 | 2480 | **80** |

Original BLE mode `%39` **missed 2480 MHz**. NextLab prioritizes adv + data samples.

### 2.3 IEEE 802.15.4 (new mode vs all prior packages)

| 802.15.4 ch | MHz | nRF |
| ---: | ---: | ---: |
| 11 | 2405 | **5** |
| 15 | 2425 | **25** |
| 20 | 2450 | **50** |
| 25 | 2475 | **75** |
| 26 | 2480 | **80** |

New **ST_154** mode + preferred set that often avoids Wi-Fi 1/6 energy in textbooks.

### 2.4 Coexistence scheduler (new)

**ST_COEXIST** time-slices: BT → BLE → 802.11 → 802.15.4.

IEEE materials emphasize **CCA / CSMA**. nRF24 const-carrier **cannot implement true CCA**. NextLab therefore:

- Teaches **spectral family rotation** (who occupies what, when)  
- Prints slice family on serial  
- Documents that **real coexistence research** needs SDR + packet-level stacks  

---

## 3. Why prior packages were not “IEEE-complete”

| Package | Strength | Gap NextLab closes |
| --- | --- | --- |
| Original closed bin | Works on hardware | Opaque; weak Wi-Fi/BLE math |
| Faithful rebuild | Pin/behavior parity | Same weak maps |
| Pro EDU | Protocol maps + stats | No 802.15.4, no coexist scheduler, no JSON |
| Range Pro | PA profiles / link budget | Hardware-centric; not multi-standard IEEE lesson |
| **IEEE NextLab** | **Standards-aligned maps + coexist + research telemetry + component roadmap** | — |

---

## 4. Modern components that make a “best tech” lab (2024–2026)

### 4.1 Keep dual-nRF24 path (this firmware)

Still the best **drop-in** for existing BlueJammer-class boards.

### 4.2 Recommended upgrades (see `hardware/NEXT_COMPONENTS.md`)

| Tier | Components | Why “better tech” |
| --- | --- | --- |
| RF front-end | nRF24 **PA+LNA SMA**, quality antennas | Range + stability |
| Power | 3.3 V **≥2 A**, bulk caps, sense divider | PA integrity |
| MCU future | **ESP32-S3** / **ESP32-C6** | USB-HS, more RAM, Wi-Fi 6 (C6) for *observer* apps |
| Observe path | **RTL-SDR / HackRF**, attenuators | Measure IEEE channel hits |
| Multi-band edu | **CC1101** / **SX127x** (Sub-GHz) | Separate course module — not ISM 2.4 only |
| Sensing | INA219, BME280 | Power / environment labs |
| Containment | RF cage | Classroom safety |

### 4.3 What we deliberately did **not** put in firmware

- Claims of “IEEE certified jammer”  
- Wi-Fi 6 OFDMA waveform generation (needs wideband SDR)  
- Real 802.11 CCA engine on nRF24  
- Covert attack tooling  

NextLab optimizes **pedagogy + measurable spectral relevance + platform reliability**.

---

## 5. Firmware architecture advantages

1. **Six educational modes** including 802.15.4 + coexist  
2. **Weighted IEEE maps** (not uniform random%N)  
3. **Dual complementary channels** with min separation  
4. **PA hardware profiles** (from Range Pro lineage)  
5. **JSON telemetry** for automated lab notebooks  
6. **Larger RadioTask stack**, dual-core pin, health re-init  
7. **SAFE sim mode** for lecture halls without TX  

---

## 6. References (public / mentor / encyclopedic)

Students should pull primary text from IEEE Xplore / GET program where available:

1. IEEE Std **802.11be-2024** (Wi-Fi 7 amendment; published 2025) — coexistence with legacy 2.4/5/6 GHz  
2. IEEE Std **802.11ax** — High Efficiency WLAN; 2.4 GHz channelization notes  
3. IEEE 802.11 mentor coexistence assurance / assessment documents (ax, be)  
4. IEEE Std **802.15.4-2020** — 2.4 GHz channel tables  
5. Bluetooth SIG Core Specification — LE advertising channels  
6. NXP / vendor app notes on **802.11 ↔ 802.15.4 coexistence**  
7. Wikipedia / Wi-Fi Alliance channel lists (quick lab cross-check only)

---

## 7. Research conclusion (one paragraph)

A “best” educational platform on this hardware class is not “maximum random SPI thrash.” It is **standards-accurate frequency selection**, **multi-protocol coexistence teaching**, **instrumentable telemetry**, and **hardware that can actually sustain PA-class TX** without brownout — all while remaining **legally and ethically framed**. SpectrumLab Next is built to that definition.
