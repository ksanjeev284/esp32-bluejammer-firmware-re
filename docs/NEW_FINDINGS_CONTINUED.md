# Continued Analysis — New Recovered Details

Further static analysis of the original `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin`.

---

## 1. Idle-screen labels (previously incomplete)

DROM short strings at `0x3F4016E4+`:

| String | VA | Use on Idle UI |
| --- | --- | --- |
| `R1=` | `0x3F4016E4` | Label before HSPI OK/FAIL |
| `R2=` | `0x3F4016E8` | Label before VSPI OK/FAIL |
| `USB` | `0x3F4016EC` | Third status token (USB/serial presence glyph area) |
| `Connected` | `0x3F4016F0` | Animated status line |
| `OK` | `0x3F406B12` | Chip connected |
| `FAIL` | `0x3F40EB56` | Chip not connected |

Idle drawing (`enterState_Idle` / `0x400D2A24`) prints:

```text
R1=OK|FAIL   R2=OK|FAIL
[iconography / USB mark]
Connected...
```

Not generic “HSPI/VSPI” text — original uses **R1/R2**.

---

## 2. Initial constant-carrier channel = **45**

`.data` (DRAM1) initialized values:

| VA | Value | Role |
| ---: | ---: | --- |
| `0x3FFBDB70` | **45** (`0x2D`) | VSPI startConstCarrier channel (`*PTR @ 0x400D0068`) |
| `0x3FFBDB74` | **45** (`0x2D`) | HSPI startConstCarrier channel (`*PTR @ 0x400D0040`) |

In `radioTask`, after successful begin:

```c
startConstCarrier(radio, PA_MAX, *channel_ptr);  // channel_ptr → 45
```

Separately, **inside `nrf_begin` / chip init** (`0x400D337C`):

```c
setChannel(radio, 0x4C);  // 76 — default RF24 bring-up
```

So bring-up uses ch **76**, then app carrier start forces ch **45** until hop loop overwrites.

---

## 3. RF24 constructor SPI-speed clamp (`0x400D3090`)

```c
void RF24_postInit(obj) {
  obj->spi = &SPI_default;           // DAT_400d0020
  if (obj->spi_speed <= 35000)       // DAT_400d01d0 = 0x88B8
    obj->spi_speed = 10000000;       // DAT_400d01d4 = 10 MHz
}
```

App passes **16_000_000** (`0x400D012C` = `0xF42400`) → **not** clamped (16e6 > 35e3).  
So runtime SPI rate intent: **16 MHz**.

---

## 4. Full `begin()` register sequence (`0x400D337C`)

Decoded against nRF24 register map:

| Step | Reg | Value | Meaning |
| --- | ---: | ---: | --- |
| delay | — | 5 ms | settle |
| write | 4 SETUP_RETR | `0x5F` | ARD/ARC defaults |
| setDataRate | 6 | 1 Mbps temp | probe |
| FEATURE probe | 0x1D | read/toggle | detect silicon variant |
| write | 0x1D FEATURE | 0 | clear |
| write | 0x1C DYNPD | 0 | |
| write | 1 EN_AA | `0x3F` | all pipes AA |
| write | 2 EN_RXADDR | 3 | pipes 0–1 |
| payload | — | 32 (`0x20`) | |
| addr width | 3 SETUP_AW | 5 bytes | |
| channel | 5 RF_CH | **76** (`0x4C`) | |
| status | 7 | `0x70` | clear IRQ |
| flush | — | TX/RX | |
| CONFIG | 0 | `0x0C` | PWR_UP\|EN_CRC… then expect `0x0E` |

Success if CONFIG readback == **`0x0E`**.

---

## 5. stopConstCarrier / power helpers

| Addr | Recovered name | Behavior |
| ---: | --- | --- |
| `0x400D3590` | `stopConstCarrier` | Clear RF_SETUP cont-wave bits (`& 0x6F`), CE=0, flush |
| `0x400D31D8` | `powerDown` | CE=0, clear PWR_UP in CONFIG (`& ~2`) |
| `0x400D31FC` | `powerUp` | Set PWR_UP, delay **5000 µs** (`DAT_400d01dc`) |
| `0x400D3220` | `txPulse helper` | CE dance + `W_TX_PAYLOAD` `0xE3` REUSE_TX_PL |

Pause path in `radioTask`:

```
stopConstCarrier both
powerDown both
while (pause) delay 10ms
powerUp both
startConstCarrier both (ch from ptr / hop)
```

---

## 6. OLED / Wire constructor constants (`0x400D2F0C`)

```c
SSD1306_construct(display, width=0x80, height=0x40, wire,
                  rst=-1, clkDuring=400000, clkAfter=100000);
```

| Param | Value |
| --- | ---: |
| Width | **128** |
| Height | **64** |
| Reset pin | **none (-1)** |
| I2C clock during xfer | **400 kHz** |
| I2C clock after | **100 kHz** |

Matches Adafruit_SSD1306 `(w,h,twi,rst,clkDuring,clkAfter)`.

---

## 7. Complete BSS / DAT map (application)

| Pool slot | Points to | Logical name |
| --- | --- | --- |
| `0x400D0020` | SPI mgr / default SPI | `spi_default` |
| `0x400D0024` | `0x3FFC3B88` | `radioHSPI` object |
| `0x400D0028` | `0x3FFC3DC0` | `Serial` |
| `0x400D0054` | `0x3FFC3B60` | `radioVSPI` object |
| `0x400D007C` | `0x3FFC3B38` | `g_pauseRf` |
| `0x400D0080` | `0x3FFBDB7C` | `g_state` (init **1** in .data!) |
| `0x400D009C` | `0x3FFC3B3C` | display helper / GFX ctx |
| `0x400D00E4` | `0x3FFC3B28` | RadioTask handle storage |
| `0x400D00F8` | `0x3FFBDB6C` | `g_ledLevel` (init 1) |
| `0x400D00FC` | `0x3FFC3B24` | `g_ledTimestamp` |
| `0x400D0100` | `0x3FFC3B20` | `g_ledBlinkCount` |
| `0x400D0104` | `0x3FFBDB68` | `g_ledBlinkTarget` (init 1) |
| `0x400D0108` | `0x3FFC3B2C` | `g_uiLastState` |
| `0x400D0140` | `0x3FFC3B18` | idle animation counter |
| `0x400D0144` | `0x3FFC3BB0` | `Adafruit_SSD1306` object |
| `0x400D0178` | `0x3FFC3B34` | boot press start millis |
| `0x400D017C` | `0x3FFC3B30` | long-press latch |
| `0x400D0180` | `0x3FFBDB78` | saved state (init 1) |
| `0x400D0184` | `0x3FFC3B1C` | skip-cycle flag |
| `0x400D018C` | `0x3FFC3CD4` | `TwoWire` / Wire object |

### Critical: `g_state` initial value is **1**, not 0

DRAM1 `@ 0x3FFBDB7C = 1` → device **boots in Bluetooth mode** and starts hopping immediately after radio init (matches upstream README “jams right away” for combo firmware after power-on, with BOOT cycling modes).

`g_ledBlinkTarget` init **1**, `g_savedState` init **1** — consistent with BT-first boot.

---

## 8. UTF-8 serial art structure (SUCCESS vs FAIL)

Pointer groups for HSPI success art:

1. `~~~~...` separator  
2–4. Box-drawing “HSPI SUCCESS” 3-line glyph  
5. Long English SUCCESS line  

HSPI fail: different 3-line glyph + FAIL English line.  
VSPI: parallel structure with “VSPI SUCCESS/FAILED” glyphs.

Full lines: `artifacts/strings/serial_splash_art.txt` and pool `0x400D002C`–`0x400D0078`.

BY EMENSTA block letters: pool `0x400D00A8`–`0x400D00B8` (5 lines) + second banner `0x400D00C0`–`0x400D00D4` (6 lines).

---

## 9. setAddressWidth (`0x400D3248`)

```c
// param 5 → 5-byte addresses (nRF24 SETUP_AW)
write reg 3 with (5-2)=3 encoding; store width field = 5
```

---

## 10. Implications for rebuild

Update reconstruction to:

1. **Boot `g_state = 1` (BT)** not Idle  
2. **Initial carrier channel 45** after configure  
3. Idle labels **`R1=` / `R2=` / `USB`**  
4. SSD1306 ctor clocks **400 kHz / 100 kHz**  
5. SPI 16 MHz with RF24 floor rule documented  

---

## 11. Artifact outputs this pass

| File | Content |
| --- | --- |
| `artifacts/ghidra/MORE_FINDINGS.md` | Decomp dump of helpers |
| `artifacts/ghidra/decomp_more/*.c` | Additional C |
| `docs/NEW_FINDINGS_CONTINUED.md` | This note |
| `docs/GLOBALS_AND_CONSTANTS.md` | Master tables (generated companion) |
