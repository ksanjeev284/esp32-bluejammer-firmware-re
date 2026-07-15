# Ghidra Guide — Reproduce This Analysis

## Prerequisites

- Ghidra 11+ or 12.x (tested: **12.1.2**)  
- JDK **17**  
- This repository’s `artifacts/segments/` and `ghidra_scripts/`

## GUI load (recommended for learning)

1. **File → New Project** (non-shared).  
2. **Import** `artifacts/segments/seg2_IROM_0x400D0020.bin`  
   - Format: Raw Binary  
   - Language: **Xtensa:LE:32:default**  
   - Base address: **`0x400D0020`**  
3. Open the program.  
4. **Window → Script Manager** → add `ghidra_scripts` to the path.  
5. Run **`LoadEsp32Firmware.java`**  
   - Expects env `ESP32_SEG_DIR` pointing at `artifacts/segments`  
   - Or edit the default path inside the script.  
6. **Analysis → Auto Analyze** (defaults OK).  
7. Go to addresses:

| Go to | Name |
| --- | --- |
| `0x400D2714` | setup |
| `0x400D2BFC` | loop |
| `0x400D236C` | radioTask |
| `0x400D29F8` | initRadioObjects (CE/CSN) |
| `0x400D2D68` | initOLED |
| `0x3F401662` | string "State 1: Bluetooth" → xrefs |

8. In decompiler, rename functions as you understand them.

## Headless example (Windows)

```bat
set JAVA_HOME=C:\path\to\jdk-17
set ESP32_SEG_DIR=%CD%\artifacts\segments
set ESP32_OUT_DIR=%CD%\artifacts\ghidra_out
mkdir %ESP32_OUT_DIR%

analyzeHeadless.bat C:\tmp\ghidra_proj BlueJammerRE ^
  -import artifacts\segments\seg2_IROM_0x400D0020.bin ^
  -processor Xtensa:LE:32:default ^
  -loader BinaryLoader -loader-baseAddr 0x400d0020 ^
  -scriptPath ghidra_scripts ^
  -preScript LoadEsp32Firmware.java ^
  -postScript ExportEsp32Findings.java
```

## Why multi-segment matters

If you load the whole `.bin` at address 0:

- String addresses will not match code pointers  
- Xrefs break  
- Decompilation of app logic becomes noise  

Always map segments to **ESP32 load addresses**.

## Suggested exercise for students

1. Find xrefs to `SSD1306 allocation failed`.  
2. Prove SDA/SCL are 4 and 5 without reading this doc.  
3. Find the four `randomChannel` immediates (79/39/14/125).  
4. Identify `startConstCarrier` by RF_SETUP bit manipulations.  
5. Locate CE=16/22 in the radio constructor arguments.
