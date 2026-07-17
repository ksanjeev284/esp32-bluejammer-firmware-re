# Experiment sequencer & profiles (v0.5)

## Serial commands

| Cmd | Effect |
| --- | --- |
| `exp` / `exp0` | Default multi-mode tour (BT→BLE→WiFi→FIXED→CSA1→CSA2→SLOW→COEX) |
| `exp1` | Range fixed playlist (45/55, BLE adv, Wi‑Fi centers) |
| `profile 0` | Original-like stats pacing |
| `profile 1` | EDU default |
| `profile 2` | RANGE → jump to FIXED 45/55, faster stats |
| `stats 1000` | Stats / CSV interval ms (`0` = silence) |
| `factory` | Clear NVS settings |

BOOT cycle also reaches mode **EXP** after BLESCAN.

## Default playlist (`exp0`)

| Step | Duration | Notes |
| --- | ---: | --- |
| BT | 8 s | Classic map |
| BLE | 8 s | Adv-weighted |
| WiFi | 8 s | 1/6/11 weight |
| FIXED 45/55 | 10 s | Range / observer |
| CSA1 | 10 s | Soft AFH #1 |
| CSA2 | 10 s | Soft AFH #2 |
| SLOW | 12 s | SDR walk |
| COEX | 10 s | Family rotate |

Loops until you change mode or pause.

## Observer remote control (ESP-NOW)

On RangeObserver serial:

| Cmd | Sends to TX |
| --- | --- |
| `ch 45` | SET_CH + local RX ch |
| `fixed 45 55` | REQ_FIXED on TX |
| `marker` | Remote marker |
| `arm` / `disarm` | Remote arm |

Marker path: TX MARKER → OBS measures RPD → ACK with `rpd_pct`.

## Host CSA tests

```bash
python scripts/csa_test.py
```
