# ComboChannelSelect Pro — what improved

This document compares **Pro** (this package) to:

1. The original closed-source `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`  
2. Our first faithful rebuild (`ESP32-ComboChannelSelect-REBuild` / `OurFirmware`)

Goal: **same hardware, better runtime** — more reliable SPI, cleaner pause, dual-core split, less bus thrash.

---

## Architecture

| Topic | Original / faithful rebuild | Pro |
| --- | --- | --- |
| Radio work | FreeRTOS `RadioTask` stack 8192, prio 1 | Same stack size; **prio 2**, pinned **core 0** |
| UI / button / OLED | Main Arduino loop (often same core contention) | **Core 1** loop; radio isolated |
| Critical sections | Limited | **mux around stop/start carrier** on pause |
| Mode persistence | Always boot state 1 (BT) | **NVS `ccspro/mode`** optional |

---

## RF path

| Topic | Original / faithful | Pro |
| --- | --- | --- |
| SPI Hz | **16 MHz** | **10 MHz** default (override in `config.h`) |
| `begin()` | Once | **Up to 3 retries**, 50 ms apart |
| Health | None | Every **5 s**: `isChipConnected()` → re-begin + reconfigure |
| Pause | Hop loop idles / poll only | **`stopConstCarrier` + `powerDown`**, restart carriers on resume |
| Hop pattern | 100× independent random%mod, delay 1 ms | **EDU maps** + **48× batch / 1 ms** + dual complement (see EFFECTIVENESS.md) |
| RF knobs | PA_MAX+LNA, 2 Mbps, CRC off, const carrier | **Same RF PHY knobs**; smarter **channel selection** |
| Start channel | 45 | **45** |

### Hop batch / effectiveness

Original does a SPI write storm (100 channel writes per radio ≈ every 1 ms) with **weak channel math** (especially Wi‑Fi `%14` and BLE `%39`).

Pro EDU keeps high hop rate (**48 / 1 ms**) but:

- Lands on **protocol-relevant** nRF channels  
- Keeps **R1 ≠ R2** for dual coverage  
- Exposes **lab stats** so coverage is measurable  

Full educational write-up: **[EFFECTIVENESS.md](EFFECTIVENESS.md)**.

### Why SPI 10 MHz

RE recovered **16 MHz** in the original binary. On clean PCB traces that is fine. On jumper-wire dual-module boards, **10 MHz** is the more stable default. Set `RF24_SPI_HZ` to `16000000UL` if your hardware is solid.

---

## UI / input

| Topic | Faithful rebuild | Pro |
| --- | --- | --- |
| Button | Edge + long threshold | **Debounce 30 ms** + short/long FSM |
| OLED idle | Continuous redraw possible | **Frame floor 33 ms** (~30 FPS) |
| Idle labels | R1/R2/USB/Connected | Same + **“Pro”** tag + pause hint line |
| LED | Pulse timing | Dedicated **non-blocking** service |

Controls remain compatible:

- Short BOOT → next mode (BT/BLE/WiFi/RC)  
- Long BOOT → pause RF / idle  
- Short while paused → resume  

---

## Reliability features (Pro-only)

1. **Radio begin retries** — bad first power-up less often “stuck FAIL”  
2. **Periodic health re-init** — recovers brown-out or SPI glitches  
3. **Clean RF pause** — modules power down, less heat / current while paused  
4. **Hardware RNG** — better channel spread than software LCG  
5. **Remember last mode** — reboot returns to last active band mode  

---

## What stayed the same (on purpose)

- Pin map (dual HSPI/VSPI nRF24, OLED 4/5, LED 27, BOOT 0)  
- Mode set: Idle / BT / BLE / WiFi / RC  
- Hop moduli: 79 / 39 / 14 / 125  
- Const carrier + PA_MAX + 2 Mbps + CRC disabled  
- Extracted bitmaps + original-style serial banners  
- Splash ~2 s, serial 115200  

---

## Size (this build)

| Metric | Approx. |
| --- | --- |
| App binary | ~349 KB (~26% of default app partition) |
| Full 4 MB flash image | 4 194 304 bytes |

---

## When to use which package

| Use case | Package |
| --- | --- |
| Study RE / match original behavior as closely as possible | `REBuild` / `OurFirmware` |
| Daily lab board, jumper wires, want fewer dropouts | **`Optimized` (Pro)** |
| UI-only demo without RF TX | Pro with `REBUILD_SAFE 1` |

---

## Tuning tips

- Modules drop often → lower `RF24_SPI_HZ` to 8e6, keep retries  
- Want more aggressive hop → raise `HOP_BATCH` or lower `HOP_DELAY_MS`  
- OLED flicker / lag → increase `OLED_MIN_FRAME_MS`  
- Always boot BT ignoring NVS → `REMEMBER_LAST_MODE 0`  
