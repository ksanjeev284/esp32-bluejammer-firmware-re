# 06 — Better system design (hardware + firmware integration)

## 1. Target system name (concept)

**BLE Spectrum Lab vNext** — a dual-track educational platform:

| Track | Hardware | Firmware role |
| --- | --- | --- |
| **A. ISM stimulus / spectrum** | Dual nRF24 PA+LNA | Map-faithful tones, dual diversity, duty, logs |
| **B. Native BLE** | ESP32/nRF52 BLE | Real ADV/SCAN/CONNECT, true AFH |
| **C. Metrology** | INA219, Vcc sense, SDR optional | Science-grade KPIs |

---

## 2. Block diagram

```text
                    ┌─────────────────────────────┐
   USB host/logs ───┤  ESP32-S3 app MCU           │
                    │  FreeRTOS dual-core         │
                    │  JSON telemetry + NVS       │
                    └──────┬───────────┬──────────┘
                           │           │
              HSPI nRF24 PA│           │VSPI nRF24 PA
                           │           │
                      [ant H]     [ant V]
                           │
              native BLE radio (on-chip or nRF52 link)
                           │
                      [BLE ant / shared carefully]
                           │
              I2C: OLED, INA219, sensors
```

---

## 3. Logical layers

```text
┌──────────────────────────────────────────┐
│ Application: lab scripts, OLED UI, NVS   │
├──────────────────────────────────────────┤
│ Experiment engine: modes, schedules, CSA │
├──────────────────────────────────────────┤
│ Radio drivers: RF24 | NimBLE/Bluedroid   │
├──────────────────────────────────────────┤
│ HAL: SPI, I2C, ADC, GPIO, timers         │
└──────────────────────────────────────────┘
```

---

## 4. Experiment catalog (authorized lab)

| Exp ID | Question | Method |
| --- | --- | --- |
| E1 | Where are BLE adv centers on SDR? | BLE_ADV_MAP + SDR |
| E2 | How does Wi‑Fi 6/11 mask change hop set? | SOFT_AFH + mask |
| E3 | Dual separation vs desense | vary Δf and antenna spacing |
| E4 | Duty vs temperature / current | INA219 + thermistor |
| E5 | Native ADV RSSI vs distance | phone/nRF52 scanner |
| E6 | Compare original `%39` vs research map | A/B firmware flags |
| E7 | Airtime vs coexistence (sim) | scripted schedules |

---

## 5. Configuration policy

```text
config.h
  LAB_TRACK_A_NRF24 = 1
  LAB_TRACK_B_NATIVE_BLE = 1
  DEFAULT_DUTY_MAX = 0.7
  REQUIRE_ARM_CONFIRM = 1
  JSON_TELEMETRY = 1
  CSA_IMPL = 2
```

---

## 6. Success metrics (definition of “better”)

| Metric | Original combo | vNext target |
| --- | --- | --- |
| Adv channel coverage | Incomplete | 2/26/80 explicit |
| AFH concept | Absent | Soft map + native AFH |
| Measurability | Serial banners | JSON + current + RSSI |
| Power integrity | Often ignored | 2 A rail + sense |
| Reproducibility | Opaque | Seed, logs, exp IDs |
| Safety | Continuous | Duty + SAFE + arming |
| Scientific alignment | Low | Maps to papers/SIG |

---

## 7. Development phases (local; not pushed)

1. **Docs freeze** (this folder)  
2. **Firmware branch** `research/ble-vnext` on your machine  
3. **Hardware rev 1** PCB or wiring harness  
4. **Calibration** of \(P_t\) with SA + attenuator  
5. **Paper-style lab report** using ANSI-inspired tiers  

---

## 8. Relation to existing Complete kit packages

| Existing package | Role relative to this research |
| --- | --- |
| REBuild / OurFirmware | Faithful baseline |
| Optimized Pro EDU | First map-aware step |
| Range Pro | PA/power/range track |
| IEEE NextLab | Multi-standard coexist |
| **This research pack** | Deep BLE science → next architecture |

When ready to publish, copy selected docs into `community/findings/` via PR (separate decision).
