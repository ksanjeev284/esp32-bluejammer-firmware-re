# Ghidra Analysis Report — ESP32 BlueJammer Combo Firmware

**Ghidra:** 12.1.2 PUBLIC @ `C:\Users\ksanj\tools\ghidra_12.1.2_PUBLIC`  
**Language:** `Xtensa:LE:32:default`  
**Functions recovered:** **4244**  
**Project (kept open):** `C:\Users\ksanj\Downloads\combochannel\ghidra_project\ESP32_BlueJammer`

---

## Install summary

| Item | Path |
| --- | --- |
| Ghidra | `C:\Users\ksanj\tools\ghidra_12.1.2_PUBLIC` |
| Java | Corretto 17 (`C:\Users\ksanj\.jdks\corretto-17.0.13`) |
| Launch GUI | `C:\Users\ksanj\tools\ghidra_12.1.2_PUBLIC\ghidraRun.bat` |
| Headless scripts | `combochannel\ghidra_scripts\` |
| Exports | `combochannel\extracted\ghidra\` |

Open existing project: **File → Open Project** → `ghidra_project\ESP32_BlueJammer`.

---

## Memory map (loaded)

| Block | Range | Perms | Content |
| --- | --- | --- | --- |
| DROM | `0x3F400020`–`0x3F41CFCF` | R | strings, bitmaps, splash |
| DRAM1 | `0x3FFBDB60`–`0x3FFC0B9F` | RW | .data |
| DRAM2 | `0x3FFC0BA0`–`0x3FFC3B17` | RW | .data |
| IRAM | `0x40080000`–`0x4009A277` | RX | entry / critical |
| IROM | `0x400D0020`–`0x4016907F` | RX | main code |

---

## Recovered application call graph

```
setup()  [FUN_400d2714 @ 0x400D2714]
├── Serial.begin(115200, ...)
├── pinMode(27, OUTPUT)          // status LED
├── pinMode(0, INPUT_PULLUP)     // BOOT button
├── drawModeBitmap("bitmapboot", splash=1)
├── delay(2000)
├── print splash / disclaimer / GitHub / firmware banner
└── xTaskCreatePinned(radioTask, "RadioTask", stack=8192, ...)

loop()  [FUN_400d2bfc @ 0x400D2BFC]
├── read BOOT (GPIO0)
├── long-press ~500ms → pause RF (flag)
├── short press / release → restore previous mode
└── dispatch by g_state:
      0 → enterState_Idle   @ 0x400D2A24
      1 → enterState_BT     @ 0x400D28D8
      2 → enterState_BLE    @ 0x400D2920
      3 → enterState_WiFi   @ 0x400D2968
      4 → enterState_RC     @ 0x400D29B0

enterState_*(mode)
├── Serial.print("State N: ...")
├── g_state = N
├── drawModeBitmap(bitmapN)
├── reset LED blink counters
├── digitalWrite path for LED pin 27
└── statusLedBlink()

radioTask()  @ 0x400D236C  (infinite FreeRTOS task)
├── SPI HSPI bus=2  pins SCK=14 MISO=12 MOSI=13 CSN=15
├── SPI VSPI bus=3  pins SCK=18 MISO=19 MOSI=23 CSN=21
├── nrf_begin(radioHSPI) → SUCCESS/FAIL serial art
├── nrf_begin(radioVSPI) → SUCCESS/FAIL serial art
├── configure both: stopListening, powerUp, autoAck off,
│                   PA, dataRate, CRC off, startConstCarrier
└── loop forever:
      if pause_flag: stop carrier; wait; restart carrier
      ch = randomChannel(mode_max)
      nrf_setChannel(radioHSPI, ch)
      nrf_setChannel(radioVSPI, ch)
      (inner loop ×100 then delay 1ms)
```

---

## Named functions (from decompilation)

| Address | Renamed | Role |
| ---: | --- | --- |
| `0x400D2714` | **`setup`** | boot, splash, create RadioTask |
| `0x400D2BFC` | **`loop`** | button + state machine |
| `0x400D236C` | **`radioTask`** | dual nRF24 TX / hop |
| `0x400D28D8` | **`enterState_BT`** | state 1 |
| `0x400D2920` | **`enterState_BLE`** | state 2 |
| `0x400D2968` | **`enterState_WiFi`** | state 3 |
| `0x400D29B0` | **`enterState_RC`** | state 4 |
| `0x400D2A24` | **`enterState_Idle`** | state 0 status screen |
| `0x400D2DAC` | **`drawModeBitmap`** | OLED drawBitmap + “by @emensta” |
| `0x400D2868` | **`statusLedBlink`** | blink count = mode |
| `0x400D3448` | **`nrf_begin`** | RF24 begin on SPI |
| `0x400D30D8` | **`nrf_setChannel`** | write reg 5 (RF_CH), clamp ≤125 |
| `0x400D34D8` | **`nrf_startConstCarrier`** | RF24 startConstCarrier |
| `0x400D5E80` | **`randomChannel`** | `random() % max` |
| `0x400D35D0` | **`spi_setBus`** | SPI bus number |
| `0x400D35FC` | **`spi_setPins`** | SCK/MISO/MOSI/CSN |
| `0x400D3120` | **`nrf_isChipConnected`** | idle screen OK/FAIL |
| `0x400D5D30` | **`Serial_print`** | UART print |
| `0x400D6724` | **`delay_ms`** | delay |
| `0x400D6214` | **`gpio_write`** | digitalWrite wrapper |

Full decompiled C: `extracted/ghidra/decomp/*.c`

---

## Hardware pins (confirmed in code)

### From `radioTask` SPI setup

```c
spi_setBus(spiHSPI, 2);
spi_setPins(spiHSPI, 0x0E, 0x0C, 0x0D, 0x0F);  // 14, 12, 13, 15
spi_setBus(spiVSPI, 3);
spi_setPins(spiVSPI, 0x12, 0x13, 0x17, 0x15);  // 18, 19, 23, 21
```

| Module | Bus | SCK | MISO | MOSI | CSN | CE (docs) |
| --- | --- | --- | --- | --- | --- | --- |
| nRF24 #1 | HSPI (2) | **14** | **12** | **13** | **15** | 16 |
| nRF24 #2 | VSPI (3) | **18** | **19** | **23** | **21** | 22 |

### From `setup`

```c
pinMode(0x1B, 3);  // GPIO 27 OUTPUT  — status LED
pinMode(0x00, 5);  // GPIO 0  INPUT_PULLUP — BOOT
Serial.begin(..., baud=115200, ...);
```

| Function | GPIO |
| --- | --- |
| Status LED | **27** |
| Mode button (BOOT) | **0** |
| OLED (not in these fns; I2C API present) | SDA 4 / SCL 5 (docs) |

---

## Channel hop logic (confirmed)

Inside `radioTask` main loop, based on global state at `PTR_DAT_400d0080`:

| State | Code | `randomChannel(N)` | Effective channels |
| --- | --- | --- | --- |
| 1 BT | `N = 0x4F` (79) | `rand % 79` | **0–78** (79 channels) |
| 2 BLE | `N = 0x27` (39) | `rand % 39` | **0–38** (39 channels) |
| 3 WiFi | `N = 0x0E` (14) | `rand % 14` | **0–13** (14 channels) |
| 4 RC | `N = 0x7D` (125) | `rand % 125` | **0–124** (125 channels) |

```c
// nrf_setChannel
if (ch > 0x7c) ch = 0x7d;   // clamp to 125
write_register(radio, 5, ch); // RF_CH
```

Both radios get the **same random channel** each hop.  
Inner batch: **100** channel updates, then `delay(1)`.

### RF configuration after successful begin

```c
stopListening / power path
setAutoAck-like(0)
setPALevel-like(3, 1)
setDataRate-like(1)
setCRC-like(0)
startConstCarrier(level=3, channel=*)
```

`nrf_startConstCarrier` matches **RF24 `startConstCarrier`**:
- reads RF_SETUP (reg 6), ORs `0x90` (CONT_WAVE | PLL_LOCK style bits)
- optional dummy TX payload `0xFF…`
- sets PA, channel, CE high

---

## OLED bitmaps (confirmed geometry)

From `drawModeBitmap`:

```c
// splash
drawBitmap(display, 0, 0, boot_data, 0x80, 0x40, 1);  // 128×64

// mode icons
drawBitmap(display, 0, 0x0C, mode_data, 0x80, 0x32, 1);  // 128×50 @ y=12
// + centered text "by @emensta"
```

| Asset | VA | Size | Geometry |
| --- | --- | --- | --- |
| bitmapboot pixels | `0x3F4023A0` | — | 128×64 |
| bitmap1–4 | `0x3F402080` … `0x3F401720` | **800 B each** | **128×50** (128×50/8=800) |

Idle screen also draws small status icons and HSPI/VSPI **OK/FAIL** text via `nrf_isChipConnected`.

---

## Button behavior (`loop`)

- **`digitalRead(0)`** (BOOT)
- Press held **> 500 ms** while RF running → set **pause flag**, save state, force state 0 path (stops carrier in radioTask)
- Release / short interaction → restore previous mode, clear pause
- Normal path always re-enters current `enterState_*` (keeps UI/LED updated)

LED blink (`statusLedBlink`):
- toggle GPIO 27
- on-time ~150 ms (`0x96`), gap 150 ms between blinks
- after `mode` blinks, long pause **1000 ms**
- blink count stored vs `g_state` (1–4)

---

## `setup` serial splash sequence (order)

1. `#` / block art lines (BY EMENSTA)
2. `Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)`
3. large BY EMENSTA art
4. `!Educational purposes only!`
5. GitHub URL
6. `I'm not responsible for your actions!`
7. Create **RadioTask** (stack **8192**)

---

## Decompiled `radioTask` (annotated excerpt)

```c
void radioTask(void) {
  // construct SPI objects size 0x20
  spiH = new_SPI(0x20);  spi_setBus(spiH, 2);
  spi_setPins(spiH, 14, 12, 13, 15);
  spiV = new_SPI(0x20);  spi_setBus(spiV, 3);
  spi_setPins(spiV, 18, 19, 23, 21);

  if (!nrf_begin(radioH, spiH)) print HSPI_FAIL art;
  else { print HSPI_SUCCESS; configure; startConstCarrier; }

  if (!nrf_begin(radioV, spiV)) print VSPI_FAIL art;
  else { print VSPI_SUCCESS; configure; startConstCarrier; }

  for (;;) {
    for (i = 100; i; --i) {
      if (pause_flag) { stop both; while(pause); restart carrier; }
      switch (g_state) {
        case 1: ch = randomChannel(79);  break; // BT
        case 2: ch = randomChannel(39);  break; // BLE
        case 3: ch = randomChannel(14);  break; // WiFi
        case 4: ch = randomChannel(125); break; // RC
      }
      nrf_setChannel(radioH, ch);
      nrf_setChannel(radioV, ch);
    }
    delay(1);
  }
}
```

---

## Files produced by Ghidra run

| Path | Description |
| --- | --- |
| `extracted/ghidra/GHIDRA_FINDINGS.md` | xrefs + first decomp pass |
| `extracted/ghidra/GHIDRA_MORE.md` | helpers + callers |
| `extracted/ghidra/GHIDRA_ANALYSIS_REPORT.md` | this summary |
| `extracted/ghidra/functions.txt` | all 4244 functions |
| `extracted/ghidra/decomp/*.c` | decompiled C sources |
| `extracted/ghidra/headless_log*.txt` | analysis logs |
| `ghidra_project/ESP32_BlueJammer` | openable Ghidra project |

---

## How to re-open / re-run

**GUI:**
```bat
set JAVA_HOME=C:\Users\ksanj\.jdks\corretto-17.0.13
C:\Users\ksanj\tools\ghidra_12.1.2_PUBLIC\ghidraRun.bat
```
Open project `Downloads\combochannel\ghidra_project\ESP32_BlueJammer`.

**Headless re-analyze:**
```bat
set JAVA_HOME=C:\Users\ksanj\.jdks\corretto-17.0.13
set ESP32_SEG_DIR=C:\Users\ksanj\Downloads\combochannel\extracted\segments
set ESP32_OUT_DIR=C:\Users\ksanj\Downloads\combochannel\extracted\ghidra
analyzeHeadless.bat ghidra_project ESP32_BlueJammer -process seg2_IROM_0x400D0020.bin -scriptPath ghidra_scripts -postScript DecompileMore.java
```

---

## What Ghidra newly proved (vs strings-only)

1. **Exact pin numbers** for both SPI buses in code  
2. **`setup` / `loop` / `radioTask` addresses** and call graph  
3. **Channel ranges are random hops**, not fixed tables: 79 / 39 / 14 / 125  
4. **TX method = constant carrier** (RF24 `startConstCarrier`), not only packet flood  
5. **OLED mode icons are 128×50**; splash **128×64**  
6. **BOOT long-press pauses** RF; LED blink count = mode  
7. **Both nRF24 modules always hop together** on the same channel  

This is the core application logic of the closed-source firmware, recovered via Ghidra decompilation.
