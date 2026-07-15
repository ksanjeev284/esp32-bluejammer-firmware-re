#!/usr/bin/env python3
"""Map key firmware strings to file offsets and virtual addresses for Ghidra."""
import re
import struct

path = r"Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin"
data = open(path, "rb").read()

# From esptool image-info
segs = [
    (0x000018 + 8, 0x1CFB0, 0x3F400020),  # DROM  file offs from esptool: 0x18 header then data...
    # esptool said: Seg0 file offs 0x00000018 — that's start of segment header;
    # load data starts after 8-byte seg header at 0x20
    (0x20, 0x1CFB0, 0x3F400020),
    (0x1CFD0 + 8, 0x3040, 0x3FFBDB60),  # esptool: 0x0001cfd0
    (0x1CFD8, 0x3040, 0x3FFBDB60),
    (0x20018 + 8, 0x99060, 0x400D0020),
    (0x20020, 0x99060, 0x400D0020),
    (0xB9080 + 8, 0x2F78, 0x3FFC0BA0),
    (0xB9088, 0x2F78, 0x3FFC0BA0),
    (0xBC000 + 8, 0x1A278, 0x40080000),
    (0xBC008, 0x1A278, 0x40080000),
]

# Clean unique segments
segs = [
    (0x20, 0x1CFB0, 0x3F400020),
    (0x1CFD8, 0x3040, 0x3FFBDB60),
    (0x20020, 0x99060, 0x400D0020),
    (0xB9088, 0x2F78, 0x3FFC0BA0),
    (0xBC008, 0x1A278, 0x40080000),
]


def file_to_va(foff: int):
    for fstart, size, vaddr in segs:
        if fstart <= foff < fstart + size:
            return vaddr + (foff - fstart)
    return None


def find_all(needle: bytes):
    out = []
    i = 0
    while True:
        j = data.find(needle, i)
        if j < 0:
            break
        out.append(j)
        i = j + 1
    return out


targets = [
    b"Firmware : Combo-Channel-Select",
    b"https://github.com/EmenstaNougat/ESP32-BlueJammer",
    b"HSPI nRF24 module initialized SUCCESSFULLY",
    b"VSPI nRF24 module initialized SUCCESSFULLY",
    b"HSPI nRF24 module could NOT",
    b"VSPI nRF24 module could NOT",
    b"State 1: Bluetooth",
    b"State 2: Bluetooth Low Energy",
    b"State 3: WiFi",
    b"State 4: RC",
    b"State 0: Idle & Status",
    b"RadioTask",
    b"SSD1306 allocation failed",
    b"bitmapboot",
    b"bitmap1",
    b"bitmap2",
    b"bitmap3",
    b"bitmap4",
    b"Connected",
    b"by @emensta",
    b"loopTask",
    b"esp-idf: v4.4.5",
    b"Hardware Serial Peripheral Interface started",
    b"Variable Serial Peripheral Interface started",
]

print("String | File offset | VA")
print("-" * 80)
for t in targets:
    idx = data.find(t)
    if idx < 0:
        print(f"NOT FOUND: {t[:60]!r}")
        continue
    va = file_to_va(idx)
    va_s = f"0x{va:08X}" if va is not None else "N/A"
    label = t[:52].decode("ascii", "replace")
    print(f"{label:52s}  file=0x{idx:06X}  VA={va_s}")

print("\n=== Pointer xrefs to state strings ===")
for name in [
    b"State 1: Bluetooth",
    b"State 2: Bluetooth Low Energy",
    b"State 3: WiFi",
    b"State 4: RC",
    b"State 0: Idle & Status",
    b"RadioTask",
    b"bitmapboot",
    b"SSD1306 allocation failed",
    b"by @emensta",
]:
    f = data.find(name)
    if f < 0:
        continue
    va = file_to_va(f)
    if va is None:
        continue
    ptr = struct.pack("<I", va)
    locs = find_all(ptr)
    print(f"\n{name.decode()!r}")
    print(f"  string @ file 0x{f:X}  VA 0x{va:08X}")
    print(f"  pointer 0x{va:08X} found at file offsets: {[hex(x) for x in locs[:15]]}")
    for loc in locs[:5]:
        pva = file_to_va(loc)
        if pva:
            print(f"    -> table entry VA 0x{pva:08X}")

print("\n=== RF24 / nRF related strings ===")
for s in re.findall(rb"[\x20-\x7e]{6,}", data):
    sl = s.lower()
    if any(x in sl for x in (b"rf24", b"nrf24", b"setchannel", b"setpa", b"setdata", b"setauto")):
        print(" ", s.decode("ascii", "replace"))

print("\n=== Display-related (non-IDF) ===")
for s in re.findall(rb"[\x20-\x7e]{6,}", data):
    if any(x in s for x in (b"SSD1306", b"Adafruit", b"bitmap", b"OLED", b"emensta")):
        if b"IDF" not in s and b"components" not in s and b"Arduino15" not in s:
            print(" ", s.decode("ascii", "replace")[:120])
