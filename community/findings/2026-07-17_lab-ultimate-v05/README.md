# Finding: Lab Ultimate v0.1–v0.5 educational platform

| Field | Value |
| --- | --- |
| Date | 2026-07-17 |
| Author | repo maintainers / lab workstream |
| Status | Published in `packages/06-lab-ultimate/` |
| Hardware | ESP32 + dual nRF24L01+ PA+LNA SMA (BlueJammer pinout) |

## Summary

After reverse-engineering the public `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` image and shipping faithful / Pro / Range / IEEE packages, we built **Lab Ultimate** as the high-ROI active lab tree:

1. Measurable TX (**FIXED / SLOW**) + second-board **RangeObserver** (RPD %)  
2. Soft **CSA#1 / CSA#2** hop engines for BLE AFH education  
3. SoftAP control panel, captive portal, **Web OTA**  
4. Optional **INA219** current + over-current auto-disarm  
5. ESP-NOW beacons/markers + **bidirectional** OBS→TX commands  
6. Experiment sequencer, NVS settings, watchdog, Python tools  

## Why it is better than the original closed binary (lab definition)

| Area | Original | Lab Ultimate |
| --- | --- | --- |
| Wi‑Fi hop math | `random%14` (wrong band region) | Real centers + 1/6/11 weight |
| BLE hop math | `%39` misses 2480 MHz | Adv 2/26/80 + CSA modes |
| Observability | Serial banners | CSV/JSON, web, LittleFS log |
| Range hardware | Generic 2 Mbps | 250 kbps PA profile, dual sep |
| Safety | Always TX when powered | Arm gate, SAFE build, current trip |
| Source | Closed | Full Arduino + docs |

## Evidence / artifacts

- Source: `packages/06-lab-ultimate/src/`  
- Prebuilt: `packages/06-lab-ultimate/firmware/*_FULL_FLASH.bin`  
- Host CSA tests: `packages/06-lab-ultimate/scripts/csa_test.py` (all pass)  
- Design notes: `packages/06-lab-ultimate/docs/`  
- BLE theory pack: `research/ble-advanced/`  

## Legal framing

Const-carrier demos can cause unlawful interference. Lab Ultimate defaults to **disarmed** RF and provides SAFE builds. Authorized environments only.

## Follow-ups

- ESP32-S3 port  
- External SD logging  
- Stronger CSA golden vectors vs open BLE stacks  
