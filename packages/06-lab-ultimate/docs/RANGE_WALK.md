# Range walk procedure (high ROI)

## Hardware

| Board | Firmware | Radios |
| --- | --- | --- |
| **A — TX** | LabUltimateTX | 2× nRF24 PA+LNA SMA |
| **B — OBS** | RangeObserver | 1× nRF24 (HSPI pins) |

## Setup

1. Strong power for dual PA (see `hardware/POWER_AND_VCC.md`).  
2. Antennas seated; TX antennas ≥5–10 cm apart.  
3. Flash both boards.  
4. Serial both at **115200**.  
5. TX: triple short **BOOT** to **arm**.  
6. TX: cycle to **FIXED** mode (or set `HOP_STRATEGY 3`).  
7. Confirm TX CSV shows `mode=7` (FIXED), `chH=45`, `chV=55` (defaults).  
8. OBS: `OBS_CHANNEL` = 45 (match `FIXED_CH_H`).  

## Walk (v0.2 markers)

1. Start at 1 m LOS, note OBS `rpd_pct`.  
2. At each distance mark, on **TX**: double short **BOOT** or serial `m`.  
3. OBS prints `CSV_MARK,t,tag,ch,rpd_pct,count` aligned via **ESP-NOW**.  
4. Step 2 m / 5 m / 10 m / … on your property only.  
5. Stop when rpd_pct stays near 0.  

## A/B ideas

| Change one | Expect |
| --- | --- |
| TX rate 250k vs 2M | 250k often better presence margin |
| USB vs 5 V adapters | Power sag kills “range” |
| Antennas stacked vs spaced | Dual PA desense |
| Original firmware vs LabUltimate FIXED | Fair PHY comparison |

## Legal

Your property / authorized lab only. Do not use public networks as the metric.
