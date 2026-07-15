# Ultra-Deep Mining Pass

Continuous extraction from the original closed-source binary.  
Companion data: `artifacts/mine_pass2/`, `artifacts/ghidra/decomp_display_spi/`, `artifacts/ghidra/DISPLAY_SPI_MINE.md`.

---

## 1. SPI transaction format (bit-level)

Recovered from `nrf_writeRegister` / `nrf_readRegister` / `nrf_writeCmd`:

### Write register
```
CSN = 0
SPI.transfer( reg | 0x20 )   // W_REGISTER
  → status byte returned, stored on radio object
SPI.transfer( value )
CSN = 1
```

### Read register
```
CSN = 0
SPI.transfer( reg )          // R_REGISTER
SPI.transfer( 0xFF )         // NOP clock-out data
CSN = 1
return data
```

### Multi-byte (payload / cmd)
```
CSN = 0
status = SPI.transfer(cmd)
for each byte: *buf++ = SPI.transfer(0xFF)   // or write path
CSN = 1
```

### CSN sequencing
`nrf_csnLow` also calls SPI transaction begin (`FUN_400d3730`) before driving CSN GPIO low — matches Arduino `SPIClass` transaction + RF24 CSN pin.

Commands seen in code paths: `0xE1` FLUSH_TX, `0xE2` FLUSH_RX, `0xE3` REUSE_TX_PL, `0xA0` W_TX_PAYLOAD, `0x20|reg` W_REGISTER.

---

## 2. Adafruit GLCD 5×7 font located

| Item | Value |
| --- | --- |
| File offset | `0x2915` |
| DROM VA | **`0x3F402915`** |
| Signature | `00 00 5F 00 00` (glyph `!`) |
| Size extracted | 1280 bytes (5×256) |
| Artifact | `artifacts/mine_pass2/glcdfont_5x7.bin` + `glcdfont_orig.h` |

Confirms stock **Adafruit_GFX** default font is linked (not a custom font).

---

## 3. SSD1306 object construction (`0x400D5014`)

```c
Adafruit_SSD1306(w=128, h=64, wire, rst=-1, clkDuring, clkAfter)
// fields:
//  vtable PTR
//  +0x28 Wire*
//  +0x33.. pins 0xFF (unused)
//  +0x37 rst = 0xFF (-1)
//  +0x38 clkDuring (400000)
//  +0x44 clkAfter (100000)
//  textsize = 1
```

Matches public Adafruit_SSD1306 constructor layout.

---

## 4. xTaskCreate wrapper (`0x400949F4`)

```c
// from setup: FUN_400949f4(radioTask, "RadioTask", 8192, NULL, 1, &handle, core)
alloc stack (8192)
alloc TCB (0x158 bytes)
xTaskCreatePinned-style(fn, name, stack, param, prio, handle_out, tcb, core)
return 1 on success
```

Parameters recovered earlier still hold: **stack=8192, prio=1, name=`RadioTask`**.

---

## 5. Extended literal pool

312 → **~500+** entries decoded through `0x400D0800`:

- `artifacts/mine_pass2/literal_pool_extended.json`
- `artifacts/mine_pass2/literal_pool_extended.txt`

String pointer runs documented in `string_pointer_tables.md`.

---

## 6. Complete RAM symbol map

See `artifacts/mine_pass2/ram_symbol_map.md` — every RAM pointer in the app pool with names:

`radioHSPI`, `radioVSPI`, `Serial`, `g_state`, `g_pauseRf`, carrier channels, LED FSM, SSD1306, TwoWire, task handle, button state, etc.

---

## 7. State machine (complete JSON)

`artifacts/mine_pass2/state_machine_complete.json`

| State | Boot? | Hop mod | LED | Serial |
| ---: | --- | ---: | ---: | --- |
| 0 Idle | no | — | off | State 0: Idle & Status |
| **1 BT** | **YES** | 79 | 1 | State 1: Bluetooth |
| 2 BLE | | 39 | 2 | State 2: Bluetooth Low Energy |
| 3 WiFi | | 14 | 3 | State 3: WiFi |
| 4 RC | | 125 | 4 | State 4: RC |

Initial carrier channel **45**; begin() channel **76**.

---

## 8. Hardware BOM (machine-readable)

`artifacts/mine_pass2/hardware_bom.json` — full pinout for rebuild/flash testing.

---

## 9. Segment integrity stats

`artifacts/mine_pass2/segment_stats.json` — size, sha256, zero/FF ratios per segment.

---

## 10. Largest app-region functions

Top code blobs (library + app) for future focus:

| VA | Size | Notes |
| ---: | ---: | --- |
| 0x400DA2FC | 1900 | large lib (likely WiFi/BT stack glue) |
| 0x400D5220 | 619 | SSD1306::begin |
| 0x400D2A24 | 470 | enterState_Idle |
| 0x400D2BFC | 344 | loop |
| 0x400D2DAC | 331 | drawModeBitmap |
| 0x400D2714 | 304 | setup |

App logic remains concentrated in **0x400D23xx–0x400D2Fxx**.

---

## 11. Display SPI mine outputs

- `artifacts/ghidra/DISPLAY_SPI_MINE.md`
- `artifacts/ghidra/decomp_display_spi/*.c` — writeRegister, readRegister, csnLow, SPI begin, SSD1306 construct, xTaskCreate, Serial.begin, …

---

## Implications for hardware rebuild

Already reflected / to sync in sketch:

1. SPI bit protocol matches RF24 library (good)  
2. Font is stock Adafruit (no custom font needed)  
3. SSD1306 ctor params confirmed  
4. Boot BT + carrier 45 already in reconstruction  

---

## Reproduce this pass

```bash
python mine_deeper2.py
# Ghidra headless MineDisplaySPI.java
```
