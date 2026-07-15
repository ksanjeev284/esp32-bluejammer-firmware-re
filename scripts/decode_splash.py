#!/usr/bin/env python3
from pathlib import Path

data = Path("Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin").read_bytes()
OUT = Path("extracted")

ptrs = [
    0x3F400120,
    0x3F4001A5,
    0x3F400206,
    0x3F400265,
    0x3F4002C4,
    0x3F40035E,
    0x3F4003AE,
    0x3F400400,
    0x3F40044A,
    0x3F4004E4,
    0x3F400546,
    0x3F4005A8,
    0x3F400608,
    0x3F4006A2,
    0x3F4006F3,
    0x3F400748,
    0x3F400793,
    0x3F40082D,
    0x3F400838,
    0x3F4008BD,
    0x3F4009E8,
    0x3F400AD5,
    0x3F400C06,
    0x3F400CEB,
    0x3F400E16,
    0x3F400E9B,
    0x3F400FA6,
    0x3F4010C1,
    0x3F4011CA,
    0x3F4012D1,
    0x3F4013D2,
    0x3F4014C9,
    0x3F40154E,
    0x3F4015D3,
]

lines = []
for va in ptrs:
    fo = 0x20 + (va - 0x3F400020)
    # limit scan to 200 bytes
    z = data.find(b"\x00", fo, fo + 200)
    if z < 0:
        raw = data[fo : fo + 160]
    else:
        raw = data[fo:z]
    try:
        s = raw.decode("utf-8")
    except Exception:
        s = raw.decode("latin-1", errors="replace")
    lines.append(f"[{va:08X}] {s}")
    print(f"[{va:08X}] {s[:140]}")

(OUT / "serial_splash_art.txt").write_text("\n".join(lines), encoding="utf-8")
print("wrote serial_splash_art.txt", len(lines), "lines")

print("bitmap spacing:")
for a, b in [
    (0x3F401720, 0x3F401A40),
    (0x3F401A40, 0x3F401D60),
    (0x3F401D60, 0x3F402080),
    (0x3F402080, 0x3F4023A0),
]:
    print(hex(b - a), b - a)
