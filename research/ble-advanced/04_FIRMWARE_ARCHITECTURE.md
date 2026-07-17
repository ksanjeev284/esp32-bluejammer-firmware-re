# 04 — Firmware architecture (research-aligned “better BLE lab”)

## 1. Principles from science → code

| Literature principle | Firmware feature |
| --- | --- |
| Structured BLE channels | Tables for adv 37/38/39 + data 0..36 |
| AFH channel map | 37-bit (or 40-bit) map + blacklist API |
| CSA #1 / #2 | Pluggable hop selector modules |
| Connection intervals | Timer-driven dwell, not SPI storm only |
| Coexistence | Wi‑Fi 1/6/11 overlap mask |
| Energy | Duty cycle + INA219 sampling task |
| Reproducibility | JSON telemetry, seedable PRNG, session ID |
| Safety | SAFE mode (no RF), max duty clamp |

---

## 2. Process model (ESP32 FreeRTOS)

```text
Core 0                          Core 1
─────────────────────           ─────────────────────
RadioTask / BLE stack           UI / button / OLED
  - nRF24 dual hop              - mode FSM
  - optional native BLE         - NVS settings
SenseTask (100 ms)              TelemetryTask (1–2 s)
  - Vcc / INA219                - JSON + human logs
  - optional Wi‑Fi scan RSSI
```

Stack sizes: Radio ≥ 8–10 KB; BLE NimBLE may need more.

---

## 3. Mode taxonomy (better than original 5 states)

| Mode ID | Name | RF behavior | Teaching goal |
| ---: | --- | --- | --- |
| 0 | IDLE | Off / powerDown | Baseline current |
| 1 | BLE_ADV_MAP | Prefer nRF **2/26/80** | Advertising geometry |
| 2 | BLE_DATA_MAP | Even grid data band | Connected-band occupancy |
| 3 | BLE_SOFT_AFH | Map + CSA-like hop | AFH education |
| 4 | BLE_NATIVE_ADV | ESP32 BLE advertise | Real packets / RSSI on phone |
| 5 | BLE_NATIVE_SCAN | ESP32 scan | Observer metrics |
| 6 | WIFI_OVERLAP_LAB | Mask vs Wi‑Fi 1/6/11 | Coexistence planning |
| 7 | DUAL_DIVERSITY | Two nRF, min Δf | Desense / dual tone |
| 8 | RANGE_PROFILE | 250k, PA, long dwell | Link budget labs |
| 9 | SAFE_SIM | No TX, simulated hops | Classroom |

Original BT/BLE/WiFi/RC can remain as **legacy compatibility modes**.

---

## 4. Soft-AFH logic (pseudocode)

```text
# channel index 0..36 for data
map[37] = all True initially
energy[37] = 0

every sense_period:
  for ch in 0..36:
    e = measure_proxy(ch)   # WiFi scan bucket / SDR / model
    energy[ch] = α*e + (1-α)*energy[ch]
    map[ch] = energy[ch] < E_th

# CSA #2 educational subset (simplified)
next = CSA2(eventCounter, map, accessAddress_salt)

# Map to nRF24 MHz
nrf_ch = ble_center_mhz(next) - 2400
setChannel(radio, nrf_ch)
```

**Important honesty:**  
Without a true energy detector on nRF24, `measure_proxy` may be:

- manual blacklist,  
- ESP32 Wi‑Fi scan RSSI buckets,  
- or offline scripted interference schedules for reproducibility.

Native BLE stacks implement real AFH internally — use **BLE_NATIVE_*** modes for fidelity.

---

## 5. Advertising-faithful nRF schedule

For educational stimulus aligned with BLE adv centers:

```text
weights: {2: 0.34, 26: 0.33, 80: 0.33}   # nRF channels
every T_adv_ms:   # e.g. 20–100 ms, not 1 ms thrash
  ch = weighted_pick(weights)
  radio.setChannel(ch)
  # optional: short carrier burst ON for D ms, OFF for remainder
```

Compare to original: thousands of random channels/second in 0..38.

---

## 6. Telemetry schema (machine-readable)

```json
{
  "session": "uuid",
  "t_ms": 120000,
  "mode": "BLE_SOFT_AFH",
  "chH": 26,
  "chV": 80,
  "map_ones": 31,
  "hop_rate": 12.5,
  "i_mA": 185.2,
  "v_rail": 3.28,
  "duty": 0.7,
  "notes": "wifi_mask=1,6,11"
}
```

Supports the academic culture of **KPIs** (throughput/delay/PER analogs).

---

## 7. Timing profiles

| Profile | Hop / dwell | Use |
| --- | --- | --- |
| FAITHFUL | dwell 7.5–50 ms | BLE-like CI education |
| LAB_SCAN | dwell 1–5 ms | SDR waterfall visibility |
| STRESS | batch writes | Legacy comparison only |

Default teaching profile should be **FAITHFUL**, with STRESS behind a config flag.

---

## 8. Safety state machine

```text
BOOT → SAFE_BOOT
        │
        ├─(REBUILD_SAFE)→ UI_ONLY
        │
        └─(armed via NVS flag + button confirm)→ RF_ENABLED
                │
                ├ duty gate
                ├ thermal / current limit → backoff
                └ long BOOT → PAUSE (powerDown)
```

---

## 9. Implementation roadmap (no code push required here)

| Phase | Deliverable |
| ---: | --- |
| 1 | Port maps 2/26/80 + data grid into existing Pro/Range tree |
| 2 | Add soft map + JSON |
| 3 | Add ESP32 native BLE adv/scan modes |
| 4 | INA219 driver + energy plots |
| 5 | CSA #1/#2 educational modules + unit tests on host |
| 6 | Observer protocol over UART/ESP-NOW |

---

## 10. What not to implement

- Features whose only purpose is maximizing illegal interference  
- Hidden continuous max-EIRP modes without duty clamp  
- Claims of “defeats all BLE AFH” as a product pitch  

Frame every RF mode as **lab stimulus / measurement / education**.
