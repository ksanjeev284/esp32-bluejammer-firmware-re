# Deep Analysis Update — Rebuild-Level Reconstruction

**Date:** 2026-07-15  
**Goal:** Recover enough detail that an engineer can implement **behaviorally equivalent** firmware from scratch.

---

## What was added this pass

### 1. Corrected RF hop model

Earlier notes said both radios share one random channel.  
Decompilation of `radioTask` shows **two independent** `randomChannel()` calls:

```c
setChannel(radioH, random() % mod);
setChannel(radioV, random() % mod);  // second independent RNG
```

### 2. Full control-flow reconstruction

| Address | Role | Reconstruction symbol |
| ---: | --- | --- |
| `0x400D2714` | setup | `setup()` |
| `0x400D2BFC` | loop + button | `loop()` / `handleBootButton()` |
| `0x400D236C` | RadioTask | `radioTask()` |
| `0x400D2844` | cycle 1..4 | `cycleNextAttackState()` |
| `0x400D28D8`…`29B0` | mode entry | `enterState_*` |
| `0x400D2A24` | idle UI | `drawIdleStatus()` |
| `0x400D2DAC` | splash/mode draw | `drawSplash` / `drawModeScreen` |
| `0x400D2868` | LED FSM | `statusLedBlink()` |
| `0x400D29F8` | CE/CSN ctor | global RF24 construction |
| `0x400D2D68` | OLED init | Wire+SSD1306 begin |

### 3. Constants table (literal pool)

| Pool VA | Value | Meaning |
| ---: | ---: | --- |
| `0x400D0094` | 115200 | UART baud |
| `0x400D0098` | 20000 | Serial timeout-related |
| `0x400D0090` | `0x0800001C` | Serial config word |
| `0x400D00E8` | 8192 | RadioTask stack |
| `0x400D012C` | **16000000** | RF24 SPI Hz |
| `0x400D01D4` | 10000000 | other SPI speed constant |
| LED | 150 / 1000 ms | pulse / inter-group gap |
| Long press | 500 ms | pause threshold |
| Splash | 2000 ms | boot delay |

### 4. Button FSM refined

- Short press → `g_state = (g_state % 4) + 1` style cycle **1–4 only** (`FUN_400d2844` wraps `>4` → `1`)  
- Long press → save state, force **0**, `pauseRf=1`  
- Short release while paused → restore, clear pause  

### 5. Extracted assets as PROGMEM

`reconstruction/ComboChannelSelect/bitmap{boot,1,2,3,4}.h`  
copied from original DROM for pixel-level UI parity.

### 6. Reconstructable sketch

`reconstruction/ComboChannelSelect/ComboChannelSelect.ino`  
with `REBUILD_SAFE=1` default (no TX).

### 7. Spec + build recipe

- `reconstruction/SPEC_FOR_REBUILD.md` — full contract  
- `reconstruction/BUILD.md` — Arduino 2.0.10 steps  

---

## Honest rebuild fidelity

| Layer | Fidelity |
| --- | --- |
| Pins / buses | Exact |
| State machine & timings | Exact (ms-level) |
| Hop moduli 79/39/14/125 | Exact |
| Independent dual RNG hop | Exact |
| RF24 register intent | Exact (via public API mapping) |
| OLED bitmaps | Exact bytes from original |
| Serial English strings | Exact / near-exact |
| UTF-8 multi-line box art | Approximate in sketch (full art in artifacts) |
| Idle screen micro-glyphs | Simplified (OK/FAIL text) |
| IDF coexistence init | Abstracted by Arduino core |
| **SHA256 of bin** | Will not match |

---

## Still not bit-identical (and why)

Original binary embeds:

- `esp_app_desc_t` with **Jun 12 2023 16:41:45** and ELF SHA  
- `arduino-lib-builder` project name  
- Exact precompiled IDF objects from that Arduino package build  

Recreating that requires the author’s full build environment, not just app logic.

**Definition of done for this project:**  
A student can implement from `SPEC_FOR_REBUILD.md` + assets and obtain matching **runtime behavior**.

---

## Files to read next

1. `reconstruction/SPEC_FOR_REBUILD.md`  
2. `reconstruction/ComboChannelSelect/ComboChannelSelect.ino`  
3. `reconstruction/BUILD.md`  
4. `artifacts/ghidra/decomp/400d236c_radioTask.c`  
