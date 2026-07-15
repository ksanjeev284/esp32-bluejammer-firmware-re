#!/usr/bin/env python3
"""Binary-level remaining recovery: CE pins, ctors, globals, SPI freq."""
from __future__ import annotations
import struct
import re
from pathlib import Path
from collections import defaultdict

ROOT = Path(__file__).resolve().parent
BIN = ROOT / "Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin"
OUT = ROOT / "extracted" / "ghidra"
data = BIN.read_bytes()

SEGS = [
    (0x20, 0x1CFB0, 0x3F400020, "DROM"),
    (0x1CFD8, 0x3040, 0x3FFBDB60, "DRAM1"),
    (0x20020, 0x99060, 0x400D0020, "IROM"),
    (0xB9088, 0x2F78, 0x3FFC0BA0, "DRAM2"),
    (0xBC008, 0x1A278, 0x40080000, "IRAM"),
]

def file_to_va(foff):
    for fs, sz, va, name in SEGS:
        if fs <= foff < fs + sz:
            return va + (foff - fs), name
    return None, None

def va_to_file(va):
    for fs, sz, base, name in SEGS:
        if base <= va < base + sz:
            return fs + (va - base), name
    return None, None

lines = []
def log(s=""):
    lines.append(s)
    print(s)

log("# Binary remaining scan")
log()

# ---- 1. Xtensa MOVI encodings for pins ----
# Xtensa density: MOVI at, imm12  encoding varies
# Also look for L32R literal loads of small constants

# Search IROM for sequences: store of 16 and 15 near each other (CE,CSN)
# Common RF24 ctor: radio(ce, csn) stores to this->ce, this->csn
# Look for byte pairs in code as 8-bit immediates in known Xtensa formats

irom_f, irom_sz, irom_va = 0x20020, 0x99060, 0x400D0020
irom = data[irom_f : irom_f + irom_sz]

# Find all occurrences of pin values as isolated single bytes in app region of IROM
# App code roughly file offset for VA 0x400D2000-0x400D4000
app_start = 0x400D2000 - irom_va  # offset in irom
app_end = 0x400D4000 - irom_va
app = irom[app_start:app_end]
log(f"## App IROM slice VA 0x400D2000-0x400D4000 size={len(app)}")

# Xtensa instruction forms that embed 8-bit imm:
# Looking for pattern of two close stores of different pins
# Brute: for each occurrence of byte 0x10 (16) in app code, show context hex
for pin, name in [(0x10, "CE_HSPI?16"), (0x16, "CE_VSPI?22"), (0x0F, "CSN15"), (0x15, "CSN21"),
                  (0x0E, "SCK14"), (0x0C, "MISO12"), (0x0D, "MOSI13"),
                  (0x12, "SCK18"), (0x13, "MISO19"), (0x17, "MOSI23"),
                  (0x1B, "LED27"), (0x04, "SDA4"), (0x05, "SCL5"),
                  (0x3C, "I2C_ADDR"), (0x4F, "CH79"), (0x27, "CH39"),
                  (0x0E, "CH14_or_SCK"), (0x7D, "CH125")]:
    positions = [i for i, b in enumerate(app) if b == pin]
    log(f"- byte 0x{pin:02X} ({name}): {len(positions)} occurrences in app slice")
    for pos in positions[:8]:
        va = 0x400D2000 + pos
        ctx = app[max(0, pos - 8) : pos + 9]
        log(f"    VA 0x{va:08X}: {ctx.hex()}  (pin at +{min(8,pos)})")

# ---- 2. RF24 constructor signature search ----
# Arduino RF24 radio(CE, CSN) - compiler may emit:
# movi a10, CE; movi a11, CSN; callx constructor
# Or store into global object in .init

# Search entire IROM for L32R/const pools containing both 16 and 15 as words
log("\n## Word immediates 16 and 22 in IROM (as u32 LE)")
for val, name in [(16, "16"), (22, "22"), (15, "15"), (21, "21"), (27, "27"),
                  (4, "4"), (5, "5"), (0x3C, "0x3C"), (10000000, "10MHz"),
                  (1000000, "1MHz"), (4000000, "4MHz"), (8000000, "8MHz"),
                  (20000000, "20MHz"), (40000000, "40MHz"), (80000000, "80MHz"),
                  (115200, "115200"), (0x4C, "ch76_default"), (0x5F, "SETUP_RETR_5F")]:
    pat = struct.pack("<I", val)
    locs = []
    start = 0
    while True:
        j = irom.find(pat, start)
        if j < 0:
            break
        va = irom_va + j
        locs.append(va)
        start = j + 1
    log(f"- u32 {name}={val}: count={len(locs)} sample={[hex(x) for x in locs[:12]]}")

# ---- 3. Global pointer table from earlier literal pool ----
log("\n## Resolve DRAM BSS radio objects (not in image - list expected fields)")
# From decomp: radio at 3ffc3b88 and 3ffc3b60 - BSS
# CE at +4, secondary pin at +5 from FUN_400d3144
log("Radio BSS objects (runtime-only):")
log("  DAT_400d0024 -> 0x3FFC3B88  radioHSPI")
log("  DAT_400d0054 -> 0x3FFC3B60  radioVSPI")
log("  Fields: +0 SPI*, +4 CE pin byte, +5 CSN-related pin byte (from nrf begin path)")

# Find init functions that write those BSS addresses - search for pointer 3ffc3b88 in IROM
for name, addr in [("radioHSPI", 0x3FFC3B88), ("radioVSPI", 0x3FFC3B60),
                   ("maybe_display", 0x3FFC3B28), ("state_ptr_area", 0x3FFC3B20)]:
    pat = struct.pack("<I", addr)
    locs = []
    start = 0
    while True:
        j = data.find(pat, start)
        if j < 0:
            break
        va, reg = file_to_va(j)
        locs.append((j, va, reg))
        start = j + 1
    log(f"\n### Pointers to {name} (0x{addr:08X}): {len(locs)}")
    for fo, va, reg in locs[:20]:
        log(f"  file=0x{fo:X} va={hex(va) if va else None} reg={reg}")
        # show surrounding as potential init table
        if va and reg == "IROM":
            # dump 16 bytes before as possible function context
            fo2 = va_to_file(va)[0]
            ctx = data[fo2 - 16 : fo2 + 8]
            log(f"    ctx: {ctx.hex()}")

# ---- 4. Search for RF24(ce,csn) pattern: consecutive pin bytes in data tables ----
log("\n## Sequential pin pair tables in DROM/IROM")
drom = data[0x20 : 0x20 + 0x1CFB0]
for blob, base_va, name in [(drom, 0x3F400020, "DROM"), (irom, irom_va, "IROM")]:
    for i in range(len(blob) - 4):
        a, b = blob[i], blob[i + 1]
        if (a, b) in ((16, 15), (15, 16), (22, 21), (21, 22), (4, 5), (5, 4)):
            # skip if both are ASCII letters etc - pins are fine
            # require surrounding not high ASCII text
            if i > 0 and 0x20 <= blob[i - 1] <= 0x7e and 0x20 <= blob[i + 2] <= 0x7e:
                continue
            va = base_va + i
            log(f"  {name} 0x{va:08X}: bytes {a},{b} ctx={blob[max(0,i-4):i+6].hex()}")

# ---- 5. SPI clock from known constants near spi begin ----
log("\n## SPI frequency candidates near app pool (already partially known)")
# From literal pool earlier:
pool_imms = {
    0x400D0094: 115200,
    0x400D0098: 20000,
    0x400D00E8: 8192,
    0x400D01C8: 400000,
    0x400D01CC: 100000,
    0x400D01D0: 35000,
    0x400D01D4: 10000000,
    0x400D01DC: 5000,
    0x400D01E0: 1000000,
}
for va, val in pool_imms.items():
    log(f"  0x{va:08X} = {val} (0x{val:X})")

# ---- 6. Parse app_desc and ELF notes already done ----
# ---- 7. Find all C-string pointer tables for remaining UI ----
log("\n## All unique app strings (DROM first 8KB) re-dump")
region = data[0x20:0x2000]
for m in re.finditer(rb"[\x20-\x7e\xc2-\xf4][\x20-\x7e\x80-\xbf]{3,}", region):
    raw = m.group()
    try:
        s = raw.decode("utf-8")
    except Exception:
        s = raw.decode("latin-1", "replace")
    if any(c.isalpha() for c in s) and not s.startswith("E (%"):
        if len(s) >= 5 and len(s) < 160:
            fo = 0x20 + m.start()
            va = 0x3F400000 + fo
            # filter junk
            if sum(c.isprintable() for c in s) / len(s) > 0.9:
                pass  # already have most

# ---- 8. Extract init_array style from DRAM ----
log("\n## DRAM1 initialized words (possible vtables/obj)")
dram1 = data[0x1CFD8 : 0x1CFD8 + 0x3040]
for i in range(0, min(len(dram1), 512), 4):
    w = struct.unpack_from("<I", dram1, i)[0]
    if w == 0:
        continue
    note = ""
    if 0x400D0000 <= w < 0x40170000:
        note = "IROM"
    elif 0x40080000 <= w < 0x400A0000:
        note = "IRAM"
    elif 0x3F400000 <= w < 0x3F420000:
        note = "DROM"
    log(f"  DRAM1+0x{i:03X} (VA 0x{0x3FFBDB60+i:08X}) = 0x{w:08X} {note}")

dram2 = data[0xB9088 : 0xB9088 + 0x2F78]
log("\n## DRAM2 initialized words (first 256 non-zero)")
shown = 0
for i in range(0, len(dram2), 4):
    w = struct.unpack_from("<I", dram2, i)[0]
    if w == 0:
        continue
    note = ""
    if 0x400D0000 <= w < 0x40170000:
        note = "IROM"
    elif 0x3F400000 <= w < 0x3F420000:
        note = "DROM"
    log(f"  DRAM2+0x{i:03X} (VA 0x{0x3FFC0BA0+i:08X}) = 0x{w:08X} {note}")
    shown += 1
    if shown >= 80:
        break

# ---- 9. Cross-check RF24 register writes from known decomp values ----
log("\n## RF24 register map (from decomp)")
regs = {
    0: "CONFIG",
    1: "EN_AA",
    2: "EN_RXADDR",
    4: "SETUP_RETR",
    5: "RF_CH",
    6: "RF_SETUP",
    7: "STATUS",
    0x1C: "DYNPD",
    0x1D: "FEATURE",
}
log("begin() writes: SETUP_RETR=0x5F, dataRate=1Mbps temp, FEATURE checks, EN_AA=0x3f?, EN_RXADDR=3,")
log("  payload 0x20, addr width 5, channel 0x4C (76), STATUS clear 0x70, CONFIG=0x0C then expect 0x0E")
log("runtime: setRetries(0,0)->SETUP_RETR, setPALevel(3,1)->RF_SETUP, setDataRate(2MBPS), CRC off, startConstCarrier")

# ---- 10. Function size ranking in app cluster for completeness ----
log("\n## Done binary scan")
(OUT / "BINARY_REMAINING_SCAN.md").write_text("\n".join(lines), encoding="utf-8")
print("Wrote", OUT / "BINARY_REMAINING_SCAN.md")
