# ESP32-ComboChannelSelect-Optimized

**ComboChannelSelect Pro EDU** — improved, optimized, and **effectiveness-tuned** firmware for the same dual-nRF24 + SSD1306 BlueJammer-style hardware.

Built from full reverse-engineering of  
`Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`, then redesigned for **stability, dual-core balance, protocol-aware hop maps, and lab-measurable coverage**.

---

## ⚠️ Legal

**Jamming is illegal in most places.**  
Use only where you are authorized. Prefer `REBUILD_SAFE=1` for UI-only experiments.  
See [DISCLAIMER.md](DISCLAIMER.md).

---

## What’s in this folder

```
ESP32-ComboChannelSelect-Optimized/
├── README.md                 ← this file
├── DISCLAIMER.md
├── IMPROVEMENTS.md           ← runtime reliability vs original rebuild
├── EFFECTIVENESS.md          ← how hop/spectrum effectiveness improved (education)
├── firmware/                 ← flashable binaries (use these)
│   ├── ComboChannelSelectPro_FULL_FLASH.bin   ★ easiest
│   ├── ComboChannelSelectPro.bin
│   ├── bootloader.bin
│   ├── partitions.bin
│   ├── boot_app0.bin
│   └── SHA256SUMS.txt
└── src/
    └── ComboChannelSelectPro/   ← Arduino source
        ├── ComboChannelSelectPro.ino
        ├── config.h
        └── …
```

---

## Flash (recommended — one file)

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 ComboChannelSelectPro_FULL_FLASH.bin
```

Windows example (COM3):

```bash
esptool.py --chip esp32 -p COM3 write_flash 0x0 ComboChannelSelectPro_FULL_FLASH.bin
```

Run the command from the `firmware/` directory (or give the full path to the bin).

### Split layout (same as Arduino)

```bash
esptool.py --chip esp32 -p COMx write_flash ^
  0x1000  bootloader.bin ^
  0x8000  partitions.bin ^
  0xe000  boot_app0.bin ^
  0x10000 ComboChannelSelectPro.bin
```

---

## Why Pro is better

### Runtime reliability ([IMPROVEMENTS.md](IMPROVEMENTS.md))

| Area | Faithful rebuild | **Pro** |
| --- | --- | --- |
| SPI clock | 16 MHz (original) | **10 MHz default** — more reliable on jumper wires |
| FreeRTOS | RadioTask prio 1 | **prio 2 on core 0**, UI on core 1 |
| Radio bring-up | single `begin` | **3 retries + periodic health re-init** |
| Pause RF | busy wait | **stop carrier + powerDown** |
| Button / OLED / NVS | basic | **debounced FSM**, frame limit, last mode |

### Educational effectiveness ([EFFECTIVENESS.md](EFFECTIVENESS.md))

| Area | Original hop math | **Pro EDU (default)** |
| --- | --- | --- |
| Wi‑Fi channels | `random%14` → only ~2400–2413 MHz | **Real ch1–13 centers** (nRF 12…72) |
| BLE | `random%39` → misses 2480 MHz adv | **Priority 2 / 26 / 80** + data samples |
| Dual radios | Often same channel | **Forced complementary** R1 ≠ R2 |
| Strategy | Fixed random | **EDU / ORIGINAL / SWEEP** selectable |
| Lab metrics | None | **Serial hop_rate + unique coverage + OLED HUD** |

Same pinout, bitmaps, serial art style, and mode names (BT / BLE / WiFi / RC).

---

## Hardware (unchanged pinout)

| Function | Pins |
| --- | --- |
| nRF24 #1 (HSPI) | CE **16**, CSN **15**, SCK **14**, MISO **12**, MOSI **13** |
| nRF24 #2 (VSPI) | CE **22**, CSN **21**, SCK **18**, MISO **19**, MOSI **23** |
| OLED SSD1306 | SDA **4**, SCL **5**, addr **0x3C** |
| LED | GPIO **27** |
| BOOT button | GPIO **0** (short = next mode, hold ≈0.5 s = pause RF) |

---

## Controls

| Action | Effect |
| --- | --- |
| Short press BOOT | Cycle BT → BLE → WiFi → RC |
| Long press BOOT (~0.5 s) | Pause RF, show Idle status |
| Short press while paused | Resume last mode |
| LED blinks | 1=BT, 2=BLE, 3=WiFi, 4=RC |

Serial monitor: **115200** baud.

---

## Build from source

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 ^
  --output-dir build ^
  src/ComboChannelSelectPro
```

Libraries: **RF24**, **Adafruit SSD1306**, **Adafruit GFX**.

### Config knobs (`src/ComboChannelSelectPro/config.h`)

| Define | Default | Meaning |
| --- | --- | --- |
| `REBUILD_SAFE` | `0` | `1` = UI only (sim hop stats, no RF TX) |
| `HOP_STRATEGY` | `1` | `0` original · `1` EDU maps · `2` sweep |
| `HOP_PRIORITY_PCT` | `60` | % of EDU hops from protocol priority table |
| `COMPLEMENTARY_DUAL` | `1` | Force dual radios onto different channels |
| `HOP_BATCH` / `HOP_DELAY_MS` | `48` / `1` | Hop density |
| `EDU_STATS_MS` | `2000` | Serial lab stats period (`0` = off) |
| `EDU_OLED_HUD` | `1` | Live H/V channel on OLED |
| `RF24_SPI_HZ` | `10000000` | SPI speed |
| `REMEMBER_LAST_MODE` | `1` | NVS persist mode |

---

## After flash — quick check

1. Open serial at **115200** — expect Pro boot banner + radio begin lines  
2. OLED splash, then mode screen (or last NVS mode)  
3. Short BOOT cycles modes; long BOOT pauses; short resumes  
4. Idle screen shows `R1=OK/FAIL` and `R2=OK/FAIL` for both nRF24 chips  

---

## Package family

| Folder | Purpose |
| --- | --- |
| `ESP32-ComboChannelSelect-REBuild` | Full RE kit + faithful source |
| `ESP32-ComboChannelSelect-OurFirmware` | Faithful rebuild binaries only |
| **`ESP32-ComboChannelSelect-Optimized`** | **Pro improved firmware (this)** |

Repo: https://github.com/ksanjeev284/esp32-bluejammer-firmware-re  

**Note:** SHA256 will not match the original closed-source binary. Pro is an intentional optimization over recovered behavior.
