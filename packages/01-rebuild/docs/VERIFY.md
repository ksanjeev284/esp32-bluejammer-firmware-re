# Verification checklist (hardware)

After flash, confirm:

## Boot

- [ ] OLED splash (~2 s) from extracted `bitmapboot`  
- [ ] Serial: firmware banner, educational disclaimer, GitHub URL  
- [ ] No hang on `SSD1306 allocation failed`  

## Radios

- [ ] HSPI SUCCESS or FAIL line (UTF-8 art + English)  
- [ ] VSPI SUCCESS or FAIL line  
- [ ] FAIL both → check wiring / 3.3 V / caps  

## Modes (BOOT short)

- [ ] State 1 Bluetooth · LED 1 blink · bitmap1  
- [ ] State 2 BLE · 2 blinks · bitmap2  
- [ ] State 3 WiFi · 3 blinks · bitmap3  
- [ ] State 4 RC · 4 blinks · bitmap4  
- [ ] Cycles back to BT  

## Pause (BOOT hold ≥ 500 ms)

- [ ] Idle: `R1=` / `R2=` OK|FAIL, `USB`, `Connected…`  
- [ ] RF paused  

## Resume

- [ ] Short BOOT while paused restores previous mode  

## RF (authorized lab only)

- [ ] Activity in 2.4 GHz when not paused  
- [ ] Hop ranges: 0–78 / 0–38 / 0–13 / 0–124  
- [ ] Two modules hop independently  

**Do not** test against live third-party networks.  
