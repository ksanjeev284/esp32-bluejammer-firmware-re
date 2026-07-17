# ROI roadmap — Lab Ultimate

Features ordered by lab value per hour of work.

## Shipped in v0.1.0-roi1

| # | Item | Status |
| ---: | --- | --- |
| 1 | FIXED + SLOW TX modes | **Done** |
| 2 | RangeObserver RPD logger | **Done** |
| 3 | RF arming (triple BOOT) | **Done** |
| 4 | CSV + JSON telemetry | **Done** |
| 5 | PA profile + IEEE maps inheritance | **Done** |
| 6 | Vcc sense compile-time hook | **Done** (enable pin) |

## Shipped in v0.2.0-roi2

| # | Item | Status |
| ---: | --- | --- |
| 7 | Soft **CSA#1 / CSA#2** AFH modes | **Done** (`soft_csa.h`) |
| 8 | **ESP-NOW** beacon + marker TX↔OBS | **Done** |
| 9 | Double-BOOT / serial `m` markers | **Done** |
| 10 | **Native BLE scan** mode | **Done** |
| 11 | Serial console (`help`, `fixed`, `csa1`…) | **Done** |
| 12 | PowerShell `build_all` / `flash_tx` | **Done** |

## Shipped in v0.3.0-roi3

| # | Item | Status |
| ---: | --- | --- |
| 13 | **SoftAP web UI** (`LabUltimate` / `labult123` → 192.168.4.1) | **Done** |
| 14 | **INA219** optional current/power (I2C 0x40) | **Done** |
| 15 | **LittleFS CSV log** (`logdump` / `logclear`) | **Done** |
| 16 | **SAFE prebuilt** (`LabUltimateTX_SAFE_FULL_FLASH.bin`) | **Done** |
| 17 | Runtime **duty** (`duty ON OFF`) | **Done** |
| 18 | Web arm/disarm/mode/marker/fixed presets | **Done** |

## Shipped in v0.4.0-roi4

| # | Item | Status |
| ---: | --- | --- |
| 19 | **Web OTA** `/ota` | **Done** |
| 20 | **Captive portal** DNS | **Done** |
| 21 | **Current-limit auto-disarm** (INA219) | **Done** |
| 22 | **NVS** fixed channels + duty | **Done** |
| 23 | **CSA#2** Core-Spec-style remap | **Done** |
| 24 | Python `lab_parse.py` / `serial_capture.py` | **Done** |
| 25 | Observer serial `ch N` | **Done** |

## Shipped in v0.5.0-roi5

| # | Item | Status |
| ---: | --- | --- |
| 26 | **Experiment sequencer** (`exp` / `exp0` / `exp1`) | **Done** |
| 27 | **Profiles** `profile 0|1|2` | **Done** |
| 28 | **Watchdog** + boot reason + boot count | **Done** |
| 29 | **ESP-NOW bidirectional** (OBS cmds + ACK) | **Done** |
| 30 | **factory** reset NVS | **Done** |
| 31 | **stats MS** runtime interval | **Done** |
| 32 | Host **csa_test.py** | **Done** |

## Next (v0.6)

| # | Item | Notes |
| ---: | --- | --- |
| 33 | External SD | Optional |
| 34 | ESP32-S3 port | Next hardware |
| 35 | ESP32-C6 observer | Wi-Fi 6 listen |
| 36 | CSA vs Zephyr golden vectors | Stronger tests |

## Definition of done for “range”

1. TX FIXED armed, both PA modules OK  
2. Observer `rpd_pct` > 50% at 1 m  
3. Walk until `rpd_pct` < 5% — record meters  
4. Change one variable (power / antenna / rate) — repeat  

That is a better “range test” than marketing 800–1000 m claims.
