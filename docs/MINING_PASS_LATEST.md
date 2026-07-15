# Mining Pass — Latest Deep Extract

Continuous reverse-engineering dump from the original firmware image.

## Headline discoveries (cumulative + this pass)

| Finding | Detail |
| --- | --- |
| Boot state | **`g_state = 1` (Bluetooth)** in `.data` |
| Initial carrier CH | **45** both radios (`0x3FFBDB70/74`) |
| begin() default CH | **76** then overwritten |
| Idle labels | **`R1=` `R2=` `USB` `Connected` `OK`/`FAIL`** |
| SPI clock | **16 MHz** (floor to 10 MHz if ≤35000) |
| I2C clocks | **400 kHz** during / **100 kHz** after |
| Dual hop RNG | Independent `random()%N` per radio |
| N moduli | 79 / 39 / 14 / 125 |
| OLED | 128×64 splash, 128×50 modes, addr 0x3C, no RST pin |
| Serial art | **33 exact UTF-8 lines** recovered |

## This pass deliverables

### `artifacts/mine_pass/`

| File | Description |
| --- | --- |
| `drom_all_c_strings.json` | ~3000 DROM C-strings with VAs |
| `drom_early_strings.txt` | App-region early strings |
| `irom_literal_pool_0x400d0020.txt` | Full literal pool decode |
| `serial_art_exact.json` | 33 exact banner lines |
| `OrigSerialArt.h` | Arduino PROGMEM UTF-8 headers + print helpers |
| `rf24_sequences.json` | begin() + app RF register program |
| `function_cheat_sheet.json` | Named VA map |
| `dram1_data_named.txt` | `.data` init values |

### `artifacts/ghidra/`

| File | Description |
| --- | --- |
| `MINE_DEEPER.md` | Rename map + call graphs + short decomp |
| `decomp_mine/*.c` | **89** additional decompiled functions |
| `MORE_FINDINGS.md` | Prior helper decomp |
| `decomp_more/*.c` | Helper library |

### Reconstruction updates

- `reconstruction/ComboChannelSelect/OrigSerialArt.h` — exact serial banners  
- Sketch still uses English banners; can `#include "OrigSerialArt.h"` for full UTF-8 art  

## RF24 method rename map (from Ghidra)

| VA | Name |
| ---: | --- |
| 0x400D3034 | nrf_writeRegister |
| 0x400D2FCC | nrf_readRegister |
| 0x400D2F90 | nrf_writeCmd |
| 0x400D2FF8 | nrf_writeBytes |
| 0x400D2F60 / 2F7C | csn low/high |
| 0x400D2F4C / 2F38 | ce / csn gpio |
| 0x400D3060 / 3078 | flushRx / flushTx |
| 0x400D30F0 | setPayloadSize |
| 0x400D3248 | setAddressWidth |
| 0x400D30D8 | setChannel |
| 0x400D32F4 | setPALevel |
| 0x400D3328 | setDataRate |
| 0x400D3460 | setCRCLength |
| 0x400D34B0 | setRetries |
| 0x400D32C4 | stopListening |
| 0x400D34D8 | startConstCarrier |
| 0x400D3590 | stopConstCarrier |
| 0x400D31D8 | powerDown |
| 0x400D31FC | powerUp |
| 0x400D3448 | begin |
| 0x400D337C | begin_chipInit |
| 0x400D3120 | isChipConnected |
| 0x400D5E80 | randomChannel |
| 0x400D670C | millis |
| 0x400D6724 | delay |
| 0x400D6730 | delayMicroseconds |
| 0x400D6224 | digitalRead |
| 0x400D6214 | digitalWrite |
| 0x400D6198 | pinMode |

## begin_chipInit sequence (JSON also in mine_pass)

1. delay 5 ms  
2. SETUP_RETR = 0x5F  
3. dataRate probe 1 Mbps  
4. FEATURE probe / clear  
5. DYNPD = 0  
6. EN_AA = 0x3F  
7. EN_RXADDR = 3  
8. payload = 32  
9. address width = 5  
10. channel = **76**  
11. STATUS clear 0x70  
12. flush RX/TX  
13. CONFIG = 0x0C → expect readback **0x0E**  
14. powerUp  

App configure after success:

1. stopListening  
2. powerUp  
3. setRetries(0,0)  
4. setPALevel(MAX, LNA)  
5. setDataRate(2 Mbps)  
6. setCRCLength(disabled)  
7. startConstCarrier(MAX, **45**)  

## Exact UTF-8 HSPI SUCCESS art (decoded)

```
╦ ╦╔═╗╔═╗╦       ╔═╗╦ ╦╔═╗╔═╗╔═╗╔═╗╔═╗
╠═╣╚═╗╠═╝║  ───  ╚═╗║ ║║  ║  ║╣ ╚═╗╚═╗
╩ ╩╚═╝╩  ╩       ╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝
Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY! ####...
```

(Similar blocks for FAIL / VSPI — see `serial_art_exact.json`.)

## How to keep mining

```bash
python mine_pass.py
python fix_art.py
# Ghidra headless: MineDeeper.java on existing project
```

Then copy `extracted/mine_pass` + `extracted/ghidra/decomp_mine` into the repo and push.
