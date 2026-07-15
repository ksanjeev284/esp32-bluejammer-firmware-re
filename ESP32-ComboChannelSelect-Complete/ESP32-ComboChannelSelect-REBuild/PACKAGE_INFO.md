# Package info

| Field | Value |
| --- | --- |
| **Package name** | `ESP32-ComboChannelSelect-REBuild` |
| **Type** | Educational reconstruction kit |
| **Source firmware** | `Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin` |
| **Target hardware** | ESP32 + dual nRF24L01 + SSD1306 0.96" + LED + BOOT |
| **Analysis method** | Static RE (esptool, strings, Ghidra Xtensa) |
| **Rebuild fidelity** | Behavioral (not bit-identical) |

## Version snapshot

This package consolidates **all latest RE findings** into one folder:

- Start-to-end binary inventory  
- Full pin / timing / RF24 / OLED / task recovery  
- Extracted bitmaps + GLCD font + UTF-8 serial art  
- Arduino source + prebuilt flash images  
- Specs and verification checklist  

## Important addresses (original binary)

| Symbol | VA |
| --- | ---: |
| Image entry | `0x40082F0C` |
| setup | `0x400D2714` |
| loop | `0x400D2BFC` |
| radioTask | `0x400D236C` |
| initRadioObjects | `0x400D29F8` |
| initOLED | `0x400D2D68` |

See `reference/APP_SYMBOLS.json` for the full app map.
