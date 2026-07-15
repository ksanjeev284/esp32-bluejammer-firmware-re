# Ultra-deep mine pass 2
# Ultra-deep mining pass
- Extended literal pool entries: **504**
- String pointer tables: **29**
- GLCD font signature: **{'glcdfont_sig': '0x2915', 'va': '0x3F402915', 'size_guess': 1280, 'preview_hex': '00005f00000007000700147f147f14242a7f2a12231308646236495620500008070300001c2241000041221c002a1c7f1c2a08083e0808008070300008080808'}**

## Files generated
- `constants_encyclopedia.md` (1759 bytes)
- `font_detection.json` (228 bytes)
- `hardware_bom.json` (772 bytes)
- `iram_entry_0x40082f0c_hex.txt` (416 bytes)
- `iram_head_hex.txt` (791 bytes)
- `largest_app_functions.md` (1491 bytes)
- `literal_pool_extended.json` (57801 bytes)
- `literal_pool_extended.txt` (25881 bytes)
- `nrf_cmd_byte_frequency_in_app.json` (488 bytes)
- `ram_symbol_map.md` (4416 bytes)
- `segment_stats.json` (1063 bytes)
- `state_machine_complete.json` (1311 bytes)
- `string_pointer_tables.md` (12643 bytes)

## State machine
```json
{
  "boot_g_state": 1,
  "states": {
    "0": {
      "name": "Idle & Status",
      "serial": "State 0: Idle & Status",
      "oled": "R1=/R2=/USB/Connected",
      "led_blinks": 0,
      "hop_mod": 0,
      "rf_hop": false
    },
    "1": {
      "name": "Bluetooth",
      "serial": "State 1: Bluetooth",
      "bitmap": "bitmap1",
      "led_blinks": 1,
      "hop_mod": 79,
      "channels": "0..78"
    },
    "2": {
      "name": "BLE",
      "serial": "State 2: Bluetooth Low Energy",
      "bitmap": "bitmap2",
      "led_blinks": 2,
      "hop_mod": 39,
      "channels": "0..38"
    },
    "3": {
      "name": "WiFi",
      "serial": "State 3: WiFi",
      "bitmap": "bitmap3",
      "led_blinks": 3,
      "hop_mod": 14,
      "channels": "0..13"
    },
    "4": {
      "name": "RC",
      "serial": "State 4: RC",
      "bitmap": "bitmap4",
      "led_blinks": 4,
      "hop_mod": 125,
      "channels": "0..124"
    }
  },
  "short_press": "state = state+1; if state>4: state=1 (from non-idle) or idle->1",
  "long_press_ms": 500,
  "long_press": "save state; state=0; pauseRf=true",
  "short_while_paused": "restore; pauseRf=false",
  "hop": "100 iters then delay 1ms; independent RNG per radio",
  "initial_carrier_ch": 45,
  "begin_ch": 76
}
```

## Hardware BOM
```json
{
  "mcu": "ESP32",
  "radios": [
    {
      "bus": "HSPI",
      "module": "nRF24L01+",
      "ce": 16,
      "csn": 15,
      "sck": 14,
      "mosi": 13,
      "miso": 12
    },
    {
      "bus": "VSPI",
      "module": "nRF24L01+",
      "ce": 22,
      "csn": 21,
      "sck": 18,
      "mosi": 23,
      "miso": 19
    }
  ],
  "display": {
    "type": "SSD1306",
    "size": "128x64",
    "i2c_addr": "0x3C",
    "sda": 4,
    "scl": 5,
    "rst": null
  },
  "led": {
    "gpio": 27,
    "active": "HIGH"
  },
  "button": {
    "gpio": 0,
    "active": "LOW",
    "mode": "INPUT_PULLUP",
    "note": "BOOT"
  },
  "serial": {
    "uart": 0,
    "baud": 115200
  },
  "caps_recommended": "10-100uF on each nRF24 VCC"
}
```
