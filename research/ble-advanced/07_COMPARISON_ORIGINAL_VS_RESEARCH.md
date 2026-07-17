# 07 — Original creator design vs research-aligned platform

## Snapshot

| Dimension | Original combo design | Research-aligned better design |
| --- | --- | --- |
| BLE channel model | `random()%39` | Adv 37/38/39 + data 0..36 + maps |
| Hits 2480 MHz adv? | **No** (max nRF 38) | **Yes** (nRF 80) |
| AFH | None | Soft AFH + native BLE AFH |
| PHY realism | None (const carrier only) | Carrier lab **and** native 1M/2M/Coded study path |
| Hop timing | Ultra-aggressive SPI storm | CI-like dwell profiles |
| Dual radio | Independent random (often same ch) | Min separation + diversity intent |
| Power design | Board-dependent | Spec’d multi-amp rail + sense |
| Observability | Minimal | JSON, current, RSSI observer |
| Energy philosophy | Max TX | Duty, measure J/mode |
| Openness | Closed binary | Open experiments & logs |
| Primary goal (inferred) | Product combo UX | **Education + reproducible RF science** |

## Math difference (same PA board)

- Geometric range: **~+10%** (firmware/setup)  
- BLE-relevant utility: **~×2–3** (maps + dual sep)  
- With better antenna: geometric **~+40–60%** outdoors (\(n=2.5\))

## Hardware difference (if upgraded)

- Stock → PA+LNA: geometric outdoor **~×8–15** (path-loss model)  
- Add native BLE observer: qualitative leap (real packets)

## Philosophical difference

Original: **one device, opaque RF thrash, mode labels.**  
Research platform: **stimulus + observer + metrology + standards maps.**
