# Functional Specification — Rebuild Target

This is the **behavioral contract** recovered from the original binary.  
A from-scratch firmware that implements this spec will match the original **device behavior**.  
A **byte-identical** `.bin` is **not** a realistic goal (see § Limits).

---

## 1. Platform

| Item | Required value |
| --- | --- |
| MCU | ESP32 (Xtensa LX6 dual-core) |
| Arduino core | **esp32 by Espressif 2.0.10** (IDF 4.4.5 era) |
| Board | ESP32 Dev Module |
| Flash size | 4 MB |
| Flash mode | DIO |
| Flash freq | 80 MHz |
| PSRAM | off (not used by app) |
| USB CDC | classic UART0 Serial @ **115200** |

### Libraries (versions used in original era)

| Library | Role |
| --- | --- |
| **RF24** (TMRh20) | nRF24L01 driver, `startConstCarrier` |
| **Adafruit SSD1306** | OLED |
| **Adafruit GFX** | drawBitmap / text |
| Wire, SPI | bus drivers (core) |

Exact library git SHAs from the original build machine are **unknown**. Closest: RF24 with constant-carrier API; Adafruit SSD1306 supporting 128×64.

---

## 2. Hardware interface (mandatory)

### nRF24 #1 — HSPI

| Signal | GPIO |
| --- | ---: |
| CE | 16 |
| CSN | 15 |
| SCK | 14 |
| MOSI | 13 |
| MISO | 12 |

SPI host: **HSPI** (bus id 2 in ESP-IDF terms).  
SPI clock argument to RF24 ctor: **16_000_000** Hz (pool `0x400D012C`).

### nRF24 #2 — VSPI

| Signal | GPIO |
| --- | ---: |
| CE | 22 |
| CSN | 21 |
| SCK | 18 |
| MOSI | 23 |
| MISO | 19 |

SPI host: **VSPI** (bus id 3).

### UI

| Function | GPIO / bus |
| --- | --- |
| Status LED | GPIO **27** (active HIGH) |
| Mode button | GPIO **0** BOOT, **INPUT_PULLUP**, active LOW |
| OLED | I2C SDA **4**, SCL **5**, address **0x3C**, 128×64, SSD1306 |

---

## 3. Tasks & concurrency

| Task | Stack | Priority | Behavior |
| --- | ---: | ---: | --- |
| Arduino `loopTask` | core default | — | UI + button |
| **`RadioTask`** | **8192** | **1** | SPI/radio init + hop loop forever |

`setup()` creates `RadioTask` then returns; RF work never blocks `loop()`.

---

## 4. Operating states

| ID | Name | Serial string | OLED bitmap | LED blinks |
| ---: | --- | --- | --- | ---: |
| 0 | Idle & Status | `State 0: Idle & Status` | `R1=`/`R2=` OK\|FAIL, `USB`, `Connected…` | none |
| 1 | Bluetooth (**boot default**) | `State 1: Bluetooth` | bitmap1 128×50 | 1 |
| 2 | BLE | `State 2: Bluetooth Low Energy` | bitmap2 | 2 |
| 3 | WiFi | `State 3: WiFi` | bitmap3 | 3 |
| 4 | RC | `State 4: RC` | bitmap4 | 4 |

### Transitions

1. **Short press BOOT** (active low, held &lt; 500 ms):  
   `state = state + 1; if (state > 4) state = 1;`  
   (cycles **1→2→3→4→1**, idle not in short cycle)

2. **Long press BOOT** (≥ 500 ms while RF running):  
   - Save previous state  
   - `state = 0` (Idle)  
   - `pauseRf = true` → RadioTask stops carriers  

3. **Short release while paused**:  
   - Restore saved state  
   - `pauseRf = false` → carriers restart  

4. On every state entry (when UI state changes):  
   - `Serial.println(stateName)`  
   - Redraw OLED  
   - Reset LED blink FSM  

---

## 5. Boot sequence (`setup`)

Exact order from decompilation `0x400D2714`:

1. Core/BT coexistence init stubs (IDF)  
2. `Serial.begin(115200, …)` with config word `0x0800001C`, timeout-related **20000**  
3. Display helper init (timeout 0x32 / 50)  
4. `pinMode(27, OUTPUT)`  
5. OLED init: `Wire.begin(4,5)`, `SSD1306.begin(SWITCHCAP, 0x3C)`  
   - On failure: print `SSD1306 allocation failed` and **infinite loop**  
6. `pinMode(0, INPUT_PULLUP)`  
7. Draw **bitmapboot** full screen 128×64  
8. `delay(2000)`  
9. Print serial splash (hash lines, firmware banner, educational disclaimer, GitHub URL)  
10. `xTaskCreate(radioTask, "RadioTask", 8192, NULL, 1, …)`  

---

## 6. RadioTask algorithm (`0x400D236C`)

### 6.1 Init

1. Construct SPI object HSPI size 0x20, `setBus(2)`, pins `(14,12,13,15)`, delay 5 ms  
2. Construct SPI VSPI, `setBus(3)`, pins `(18,19,23,21)`, delay 5 ms  
3. Global radios already constructed with CE/CSN via `initRadioObjects` (`0x400D29F8`):  
   - radioH: CE=16, CSN=15, spiSpeed=16000000  
   - radioV: CE=22, CSN=21, spiSpeed=16000000  
4. `begin(spi)` each radio  
5. Print multi-line SUCCESS/FAIL banners (UTF-8 art + English)  
6. If begin OK, configure:

```
stopListening()
powerUp()
setRetries(0, 0)
setPALevel(RF24_PA_MAX, /*LNA*/ true)
setDataRate(RF24_2MBPS)
setCRCLength(RF24_CRC_DISABLED)
startConstCarrier(RF24_PA_MAX, channel=45)  // .data 0x2D both radios
```

(`begin()` programs channel **76** first; app then starts carrier on **45**. Hop loop overwrites.)

`.data` boot: **`g_state = 1` (Bluetooth)** — hops immediately after radio init.

### 6.2 Main loop (forever)

```
repeat forever:
  for i in 1..100:
    if pauseRf:
      stopConstCarrier both
      while pauseRf: delay 10ms
      restartConstCarrier both
    mod = {1:79, 2:39, 3:14, 4:125}.get(state, 0)
    if mod:
      setChannel(radioH, random() % mod)   # independent RNG
      setChannel(radioV, random() % mod)   # independent RNG
  delay(1)
```

**Note:** HSPI and VSPI channels are **not synchronized** (two separate `randomChannel` calls).

### 6.3 setChannel

- Write nRF24 register `RF_CH` (5)  
- Clamp channel to ≤ 125  

---

## 7. LED blink algorithm

When in states 1–4:

- Toggle GPIO27  
- On-time / off-time **150 ms** between toggles  
- After completing `state` rising edges (blinks), use **1000 ms** gap before next group  
- Counter wraps when `count > target`  

---

## 8. Graphics assets

| Name | Size | Geometry | DROM VA (orig) |
| --- | ---: | --- | --- |
| bitmapboot | 1024 B | 128×64 | `0x3F4023A0` |
| bitmap1 | 800 B | 128×50 | `0x3F402080` |
| bitmap2 | 800 B | 128×50 | `0x3F401D60` |
| bitmap3 | 800 B | 128×50 | `0x3F401A40` |
| bitmap4 | 800 B | 128×50 | `0x3F401720` |

Files: `reconstruction/ComboChannelSelect/bitmap*.h` (PROGMEM arrays extracted from original).

Mode screens also print centered text **`by @emensta`** at y≈2, bitmap at y=12.

---

## 9. Serial strings (must match for fidelity)

See `artifacts/strings/app_messages_full.txt` and `serial_splash_art.txt` for full UTF-8 art.  
Minimum required English strings are listed in the reconstruction sketch.

---

## 10. Limits of “same bin” recreation

| Goal | Feasible? |
| --- | --- |
| Same pins, UI, hop math, RF settings | **Yes** |
| Same serial banners & bitmaps | **Yes** (assets extracted) |
| Same FreeRTOS task name/stack | **Yes** |
| **Byte-identical** `.bin` SHA256 | **No** (practically) |

Why bit-identical fails:

1. ESP-IDF / Arduino **lib-builder** embeds build timestamps & ELF hash  
2. Compiler version / flags / LTO differ  
3. Library source revisions differ  
4. Link order / section packing differ  
5. Original uses closed customizations we approximate with public RF24/Adafruit APIs  

**Success metric for rebuild:**  
On identical hardware, serial output, OLED screens, button/LED behavior, and nRF24 register settings (SPI sniff) match this spec.

---

## 11. Verification checklist (student lab)

- [ ] `esptool image-info` on rebuilt bin → ESP32, 4MB, DIO, 80M  
- [ ] Serial shows firmware banner + GitHub URL  
- [ ] BOOT short cycles State 1..4 strings  
- [ ] LED blink count matches state  
- [ ] Long BOOT → Idle + RF pause  
- [ ] Logic analyzer: CE16/CE22 activity; RF_CH hopping in ranges  
- [ ] SPI: HSPI pins 14/12/13/15, VSPI 18/19/23/21  

**Do not** verify by jamming third-party devices.
