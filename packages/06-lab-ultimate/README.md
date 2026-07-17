# Lab Ultimate (package 06)

> **Active lab platform** · path: `packages/06-lab-ultimate/` · recommended daily driver

# ESP32-ComboChannelSelect-LabUltimate

**Lab Ultimate** — active high-ROI feature branch (currently **v0.5.0**).

Built on SpectrumLab Next + Range Pro, then keeps shipping the highest-value lab features first.

> **Educational / authorized lab only.** Radio jamming is illegal in most places.  
> Default: **RF disarmed** until you triple-press BOOT.

---

## ROI features (v0.1 → v0.5)

| # | Feature | Why |
| ---: | --- | --- |
| 1 | **FIXED + SLOW modes** | Measurable range / SDR |
| 2 | **RangeObserver** RPD + CSV | Distance data |
| 3 | **RF arming gate** | Safer accidental TX |
| 4 | **CSV + JSON telemetry** | Lab notebooks |
| 5 | **PA+LNA + 250 kbps** | Your SMA modules |
| 6 | **IEEE maps + COEXIST** | Better hop math |
| 7 | **Soft CSA#1 / CSA#2 AFH** | Teach BLE channel selection |
| 8 | **ESP-NOW markers** | TX↔OBS aligned range walks |
| 9 | **Native BLE scan mode** | Real advertisers vs maps |
| 10 | **Serial console** | `m`, `csa1`, `fixed`, `arm`… |
| 11 | **Flash/build scripts** | `scripts/*.ps1` |
| 12 | **SoftAP web UI** | Phone control @ 192.168.4.1 |
| 13 | **INA219 current** | Power vs mode labs |
| 14 | **LittleFS CSV log** | On-device notebook |
| 15 | **SAFE classroom bin** | No RF TX |
| 16 | **Web OTA** | Update firmware from browser `/ota` |
| 17 | **Captive portal** | Phones open control page automatically |
| 18 | **Current-limit protect** | Auto-disarm if INA219 over limit |
| 19 | **NVS settings** | Fixed ch + duty survive reboot |
| 20 | **Python lab tools** | `scripts/lab_parse.py`, `serial_capture.py` |
| 21 | **Experiment sequencer** | Timed multi-mode playlist (`exp0` / `exp1`) |
| 22 | **Profiles** | `profile 0|1|2` (original / edu / range) |
| 23 | **Bidirectional ESP-NOW** | OBS can `fixed` / `marker` / `arm` TX |
| 24 | **Watchdog + boot log** | Crash/brownout visibility |
| 25 | **CSA host tests** | `python scripts/csa_test.py` |

Next (v0.6): S3 port, external SD — see `docs/ROI_ROADMAP.md`.

### SoftAP + OTA (v0.3/0.4)

1. Connect phone/PC to Wi‑Fi **`LabUltimate`** / password **`labult123`**  
2. Open **http://192.168.4.1/** (captive portal may auto-open)  
3. Arm / mode / marker / fixed presets from the browser  
4. Firmware update: **http://192.168.4.1/ota** (upload app `.bin`)  

Change SSID/pass in `config.h` (`SOFTAP_SSID` / `SOFTAP_PASS`).

---

## Folder layout

```text
ESP32-ComboChannelSelect-LabUltimate/
├── README.md
├── DISCLAIMER.md
├── docs/
│   ├── ROI_ROADMAP.md
│   └── RANGE_WALK.md
├── hardware/
│   └── POWER_AND_VCC.md
├── firmware/                 ← filled after compile
└── src/
    ├── LabUltimateTX/        ← main dual-nRF TX board
    └── RangeObserver/        ← second ESP32 + 1 nRF (RPD log)
```

---

## Flash TX (after build)

```bash
# Needs min_spiffs (1.9MB app) — default 1.2MB is too small for BLE+WiFi+RF24
arduino-cli compile --fqbn esp32:esp32:esp32:PartitionScheme=min_spiffs ^
  --output-dir build src/LabUltimateTX
esptool.py --chip esp32 -p COMx write_flash 0x0 build/LabUltimateTX.ino.merged.bin
```

Or: `scripts\build_all.ps1` then `scripts\flash_tx.ps1`

Serial **115200**.

### Controls (TX)

| Action | Effect |
| --- | --- |
| **3× short BOOT** (within 4 s) while disarmed | **Arm RF** |
| Short BOOT (armed) | Next mode |
| Long BOOT ≥500 ms | Pause RF / idle |
| Short while paused | Resume |

### Modes (cycle)

`BT → BLE → 802.11 → RC → 802.15.4 → COEXIST → FIXED → SLOW → **CSA1** → **CSA2** → **BLESCAN** → …`

| Mode | Use |
| --- | --- |
| **FIXED** | Carriers on ch 45/55 — range walks + observer |
| **SLOW** | Slow channel walk — SDR waterfall |
| **CSA1 / CSA2** | Educational BLE AFH hop (see `soft_csa.h`) |
| **BLESCAN** | Native BLE advertisers (nRF TX held) |

**Markers:** double short BOOT, or serial `m` / `marker`. Observer logs `CSV_MARK` with RPD%.

### CSV (TX)

```text
CSV_HEADER,t_ms,mode,chH,chV,hop_rate,unique,vcc,heap,armed
CSV,12345,7,45,55,20.0,2,0.00,210000,1
```

---

## Flash RangeObserver (2nd board)

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 --output-dir build src/RangeObserver
esptool.py --chip esp32 -p COMy write_flash 0x0 build/RangeObserver.ino.merged.bin
```

Wire **one** nRF24 on HSPI pins (same as TX radio #1): CE16 CSN15 SCK14 MOSI13 MISO12.

Set `OBS_CHANNEL` in `RangeObserver/config.h` = TX `FIXED_CH_H` (default **45**).

Match data rate (default **250 kbps** both sides).

### CSV (observer)

```text
CSV_HEADER,t_ms,ch,rpd_hits,rpd_samples,rpd_pct,connected
CSV,5000,45,180,200,90.0,1
```

Walk away; when `rpd_pct` collapses, you’ve found qualitative edge of link for that setup.

---

## Config knobs (`LabUltimateTX/config.h`)

| Define | Default | Meaning |
| --- | --- | --- |
| `HW_PROFILE` | 1 | 0 stock / 1 PA+LNA / 2 HG+duty |
| `HOP_STRATEGY` | 1 | 0 original · 1 EDU · 2 slow · 3 fixed global |
| `FIXED_CH_H/V` | 45/55 | FIXED mode channels |
| `SLOW_DWELL_MS` | 200 | Slow sweep step |
| `REQUIRE_RF_ARM` | 1 | Triple-press arm |
| `VCC_SENSE_PIN` | 255 | Set e.g. 34 with divider |
| `CSV_TELEMETRY` | 1 | Notebook rows |
| `REBUILD_SAFE` | 0 | 1 = no RF TX |

---

## Libraries

- **RF24**
- **Adafruit SSD1306**
- **Adafruit GFX**

Board: ESP32 Dev Module, Flash **4 MB**, Partition **Minimal SPIFFS (1.9MB APP)** / `min_spiffs`, DIO, 80 MHz.

---

## Relation to other packages

| Package | Role vs LabUltimate |
| --- | --- |
| Original `.bin` | Closed baseline |
| OurFirmware / REBuild | Faithful open clone |
| Optimized / Range / NextLab | Earlier improvement steps |
| **LabUltimate** | **Active high-ROI feature tree** (use this for new work) |

---

## Legal

See [DISCLAIMER.md](DISCLAIMER.md). Prefer shielded / authorized environments. Observer is RX-only; TX still emits RF when armed.
