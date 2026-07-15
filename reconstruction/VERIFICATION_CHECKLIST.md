# Hardware verification checklist

Use this after flashing the reconstructed firmware to the BlueJammer-class board.

## Pre-flight

- [ ] Wiring matches `HARDWARE_WORKING_BUILD.md` (dual nRF24 + OLED + LED27)
- [ ] `config.h` has `REBUILD_SAFE 0` for full RF path
- [ ] Serial monitor **115200** baud
- [ ] 3.3 V supplies solid; 10–100 µF caps on nRF24 VCC

## Boot

- [ ] OLED shows splash bitmap (~2 seconds)
- [ ] Serial shows firmware banner + educational disclaimer + GitHub URL
- [ ] No hang on `SSD1306 allocation failed` (if hang → I2C wiring)

## Radios

- [ ] Serial HSPI SUCCESS line (or FAIL if module missing/wrong pins)
- [ ] Serial VSPI SUCCESS line
- [ ] FAIL on both → fix SPI/CE/CSN/power before RF testing

## Modes (BOOT short press)

- [ ] `State 1: Bluetooth` + LED 1 blink pattern + OLED mode art
- [ ] `State 2: Bluetooth Low Energy` + 2 blinks
- [ ] `State 3: WiFi` + 3 blinks
- [ ] `State 4: RC` + 4 blinks
- [ ] Cycles back to BT

## Pause (BOOT long press ≥ 500 ms)

- [ ] Enters Idle status screen
- [ ] Serial may show `State 0: Idle & Status`
- [ ] OLED shows HSPI/VSPI OK/FAIL and Connected…
- [ ] RF carriers stop (pause)

## Resume

- [ ] Short BOOT while paused restores previous mode
- [ ] RF hop resumes

## RF behavior (lab only, lawful environment)

- [ ] Spectrum / SDR shows 2.4 GHz activity when not paused
- [ ] Channel energy moves across ranges:
  - BT: ch 0–78  
  - BLE: 0–38  
  - WiFi: 0–13  
  - RC: 0–124  
- [ ] Two modules hop independently (not locked to identical channel every hop)

## Legal

- [ ] I understand continuous-carrier TX on 2.4 GHz can be unlawful interference
- [ ] I only test in authorized / shielded conditions

## Build artifact note

| Item | Original closed bin | This reconstruction |
| --- | --- | --- |
| Works on hardware | Yes | Yes (goal) |
| Same SHA256 | — | No |
| Same UI bitmaps | — | Yes (extracted) |
| Same pins / FSM | — | Yes (from RE) |
