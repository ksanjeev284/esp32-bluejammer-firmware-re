#!/usr/bin/env python3
"""ESP32 firmware analysis: image header + strings extraction."""
import re
import struct
from collections import Counter

path = r"Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin"
data = open(path, "rb").read()

print("=== FILE ===")
print(f"Path: {path}")
print(f"Size: {len(data)} bytes ({len(data)/1024:.1f} KB)")
print(f"First 32 bytes: {data[:32].hex()}")

magic, nseg, spi_mode, spi_sf = data[0], data[1], data[2], data[3]
entry = struct.unpack_from("<I", data, 4)[0]

print("\n=== ESP IMAGE HEADER ===")
print(f"Magic: 0x{magic:02x} ({'VALID ESP' if magic == 0xE9 else 'INVALID'})")
print(f"Segments: {nseg}")
spi_modes = {0: "QIO", 1: "QOUT", 2: "DIO", 3: "DOUT"}
print(f"SPI mode: {spi_mode} ({spi_modes.get(spi_mode, '?')})")
flash_size = (spi_sf >> 4) & 0xF
flash_freq = spi_sf & 0xF
size_map = {0: "1MB", 1: "2MB", 2: "4MB", 3: "8MB", 4: "16MB"}
freq_map = {0: "40MHz", 1: "26MHz", 2: "20MHz", 0xF: "80MHz"}
print(f"Flash size: {size_map.get(flash_size, f'code={flash_size}')}")
print(f"Flash freq: {freq_map.get(flash_freq, f'code={flash_freq}')}")
print(f"Entry point: 0x{entry:08x}")

# ESP32 extended header (bytes 8-23)
print(f"WP pin: {data[8]}")
print(f"SPI drive: {data[9:12].hex()}")
print(f"Chip ID: {data[12]}")
print(f"Min chip rev: {data[13]}")
print(f"Hash appended: {data[23]}")

print("\n=== SEGMENTS ===")
off = 24
segments = []
for i in range(nseg):
    if off + 8 > len(data):
        break
    load_addr, size = struct.unpack_from("<II", data, off)
    file_off = off + 8
    segments.append((load_addr, size, file_off))
    # Classify region
    if 0x3F400000 <= load_addr < 0x3F800000:
        region = "DROM (flash const data)"
    elif 0x3FF80000 <= load_addr < 0x40000000:
        region = "DRAM / RTC / peripherals"
    elif 0x40070000 <= load_addr < 0x40080000:
        region = "IRAM cache"
    elif 0x40080000 <= load_addr < 0x400A0000:
        region = "IRAM"
    elif 0x400C0000 <= load_addr < 0x400C2000:
        region = "RTC FAST"
    elif 0x400D0000 <= load_addr < 0x40400000:
        region = "IROM (flash code)"
    elif 0x50000000 <= load_addr < 0x50002000:
        region = "RTC SLOW"
    else:
        region = "other"
    print(f"  Seg {i}: load=0x{load_addr:08x} size={size:7d} (0x{size:06x}) file@0x{file_off:06x}  [{region}]")
    off += 8 + size

print(f"After segments: 0x{off:x}")
if off < len(data):
    print(f"Checksum: 0x{data[off]:02x}")

# Extract strings
print("\n=== STRING EXTRACTION ===")
raw_strings = re.findall(rb"[\x20-\x7e]{4,}", data)
decoded = [s.decode("ascii", errors="replace") for s in raw_strings]
print(f"Total strings (len>=4): {len(decoded)}")

# Categorize
categories = {
    "ESP-IDF / SDK": [],
    "Arduino / App identity": [],
    "Display (SSD1306/OLED)": [],
    "RF / Radio / Wireless": [],
    "WiFi / BT / BLE": [],
    "UI / Menu / State": [],
    "GPIO / SPI / I2C / Peripherals": [],
    "Errors / Debug": [],
    "Protocols / Channels": [],
    "Libraries": [],
}

def add_cat(cat, s):
    if s not in categories[cat]:
        categories[cat].append(s)

for s in decoded:
    sl = s.lower()
    if any(x in s for x in ("ESP-IDF", "esp-idf", "IDF", "FreeRTOS", "freertos", "v4.", "v5.")):
        if any(k in sl for k in ("idf", "freertos", "esp-idf", "sdk")):
            add_cat("ESP-IDF / SDK", s)
    if any(k in sl for k in ("arduino", "combo", "channel-select", "sketch")):
        add_cat("Arduino / App identity", s)
    if any(k in sl for k in ("ssd1306", "oled", "display", "adafruit", "u8g2", "gfx", "splash")):
        add_cat("Display (SSD1306/OLED)", s)
    if any(k in sl for k in ("nrf", "cc1101", "rf24", "radio", "rf ", "rf_", "module", "transmitter", "receiver", "jammer", "spectrum")):
        add_cat("RF / Radio / Wireless", s)
    if any(k in sl for k in ("wifi", "ble", "bluetooth", "bt_", "nimble", "bluedroid", "gap_", "gatt")):
        add_cat("WiFi / BT / BLE", s)
    if any(k in sl for k in ("menu", "state", "button", "select", "cursor", "screen", "page", "mode")):
        add_cat("UI / Menu / State", s)
    if any(k in sl for k in ("gpio", "spi", "i2c", "uart", "pin", "mosi", "miso", "sclk", "cs ", "sda", "scl")):
        add_cat("GPIO / SPI / I2C / Peripherals", s)
    if any(k in sl for k in ("error", "fail", "warn", "assert", "panic", "abort", "debug", "exception")):
        add_cat("Errors / Debug", s)
    if any(k in sl for x in () for k in ("protocol", "channel", "freq", "mhz", "ghz", "packet", "payload")):
        add_cat("Protocols / Channels", s)
    if any(k in sl for k in ("lib", ".cpp", ".c", ".h", "src/", "include/")):
        add_cat("Libraries", s)

# Broader interesting dump
interesting_keywords = [
    "ESP-IDF", "esp-idf", "Arduino", "SSD1306", "OLED", "WiFi", "BLE", "Bluetooth",
    "nRF", "NRF", "CC1101", "RF24", "SPI", "I2C", "GPIO", "menu", "Menu",
    "Channel", "channel", "state", "State", "init", "Init", "setup", "loop",
    "display", "Display", "button", "Button", "radio", "Radio", "error", "Error",
    "fail", "Fail", "version", "Version", "FreeRTOS", "heap", "flash",
    "config", "Config", "splash", "Battery", "battery", "frequency", "Protocol",
    "protocol", "RC", "combo", "Combo", "select", "Select", "Adafruit", "U8g2",
    "GFX", "Wire", "HSPI", "VSPI", "mosi", "miso", "jam", "Jam", "scan", "Scan",
    "attack", "Attack", "deauth", "Deauth", "beacon", "Beacon", "spam", "Spam",
    "evil", "Evil", "portal", "sniff", "Sniff", "mouse", "Mouse", "keyboard",
    "Keyboard", "HID", "flipper", "Flipper", "bruce", "Bruce", "marauder",
    "Marauder", "nrf24", "NRF24", "cc1101", "subghz", "SubGHz", "2.4",
]

seen = set()
interesting = []
for s in decoded:
    if len(s) < 5:
        continue
    for k in interesting_keywords:
        if k in s and s not in seen:
            seen.add(s)
            interesting.append(s)
            break

print(f"Interesting strings: {len(interesting)}")
print("\n--- All interesting strings ---")
for s in interesting:
    print(s)

print("\n=== BY CATEGORY (sample) ===")
for cat, items in categories.items():
    if not items:
        continue
    print(f"\n[{cat}] ({len(items)})")
    for s in items[:40]:
        print(f"  {s}")
    if len(items) > 40:
        print(f"  ... +{len(items)-40} more")

# Look for version strings specifically
print("\n=== VERSION / BUILD STRINGS ===")
for s in decoded:
    if re.search(r"(IDF|idf|version|Version|v\d+\.\d+|Arduino|esp32|ESP32)", s):
        if len(s) < 120:
            print(f"  {s}")

# Write full strings dump
out_path = "firmware_strings.txt"
with open(out_path, "w", encoding="utf-8") as f:
    for s in decoded:
        f.write(s + "\n")
print(f"\nFull strings written to {out_path}")

# Write interesting only
out2 = "firmware_strings_interesting.txt"
with open(out2, "w", encoding="utf-8") as f:
    for s in interesting:
        f.write(s + "\n")
print(f"Interesting strings written to {out2}")
