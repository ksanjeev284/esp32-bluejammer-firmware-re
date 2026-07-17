# SoftAP web UI + power sensing (v0.3)

## SoftAP

| Setting | Default |
| --- | --- |
| SSID | `LabUltimate` |
| Password | `labult123` |
| URL | http://192.168.4.1/ |
| JSON | http://192.168.4.1/api/status |
| OTA | http://192.168.4.1/ota |
| Captive DNS | enabled (`ENABLE_CAPTIVE_PORTAL`) |

**Controls:** Arm, Disarm, Marker, Pause, Resume, mode buttons, fixed channel presets.

Serial: `web` / `ota` reprints connection info.

### OTA notes

- Upload the **app** `.bin` (`LabUltimateTX.bin`), not always the full 4 MB merged image.
- Prefer USB `esptool` for first bring-up; OTA is for field lab updates.
- After OTA the board reboots.

## INA219 (optional)

| Pin | Connection |
| --- | --- |
| SDA / SCL | same as OLED (GPIO 4 / 5) |
| Addr | `0x40` default |
| Shunt | 0.1 Ω typical breakout |

Wire INA219 **in series with 3.3 V supply to both PA modules** (high-side) for meaningful dual-PA current.

If missing, firmware prints `[INA219] not found` and continues.

Serial stats / CSV columns: `busV`, `currA`.

## LittleFS log

| Cmd | Effect |
| --- | --- |
| `logdump` | Print CSV tail on serial |
| `logclear` | Truncate `/labult.csv` |

Auto-appends a row every stats interval (`EDU_STATS_MS`).

## Runtime duty

```text
duty 800 200    # 800 ms on, 200 ms off
duty 0 0        # continuous
save            # persist duty + fixed channels to NVS
```

## Current-limit protect (v0.4)

| Define | Default |
| --- | --- |
| `CURRENT_LIMIT_ENABLE` | 1 |
| `CURRENT_LIMIT_A` | 2.5 A |
| `CURRENT_LIMIT_HITS` | 3 consecutive samples |

On trip: RF disarmed, serial `[PROTECT] overcurrent…`, ESP-NOW `I-TRIP`, web `trips` counter.

Tune limit for your PA modules (dual PA often peaks lower than 2.5 A depending on wiring).