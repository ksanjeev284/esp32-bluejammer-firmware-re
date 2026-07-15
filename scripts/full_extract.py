#!/usr/bin/env python3
"""
Exhaustive extraction from ESP32 Combo-Channel-Select firmware.
Produces structured dumps under ./extracted/
"""
from __future__ import annotations

import hashlib
import json
import os
import re
import struct
import collections
from pathlib import Path

ROOT = Path(__file__).resolve().parent
BIN_PATH = ROOT / "Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin"
OUT = ROOT / "extracted"
OUT.mkdir(exist_ok=True)

data = BIN_PATH.read_bytes()

# --- Segment map from esptool image-info ---
SEGS = [
    {"idx": 0, "name": "DROM", "file_off": 0x20, "size": 0x1CFB0, "load": 0x3F400020},
    {"idx": 1, "name": "DRAM1", "file_off": 0x1CFD8, "size": 0x3040, "load": 0x3FFBDB60},
    {"idx": 2, "name": "IROM", "file_off": 0x20020, "size": 0x99060, "load": 0x400D0020},
    {"idx": 3, "name": "DRAM2", "file_off": 0xB9088, "size": 0x2F78, "load": 0x3FFC0BA0},
    {"idx": 4, "name": "IRAM", "file_off": 0xBC008, "size": 0x1A278, "load": 0x40080000},
]


def file_to_va(foff: int):
    for s in SEGS:
        if s["file_off"] <= foff < s["file_off"] + s["size"]:
            return s["load"] + (foff - s["file_off"]), s["name"]
    return None, None


def va_to_file(va: int):
    for s in SEGS:
        if s["load"] <= va < s["load"] + s["size"]:
            return s["file_off"] + (va - s["load"]), s["name"]
    return None, None


def find_all(blob: bytes, needle: bytes):
    out = []
    i = 0
    while True:
        j = blob.find(needle, i)
        if j < 0:
            break
        out.append(j)
        i = j + 1
    return out


report = []
meta = {}

# ========== 1. FILE HASHES / HEADER ==========
meta["filename"] = BIN_PATH.name
meta["size_bytes"] = len(data)
meta["md5"] = hashlib.md5(data).hexdigest()
meta["sha1"] = hashlib.sha1(data).hexdigest()
meta["sha256"] = hashlib.sha256(data).hexdigest()
meta["first_64_hex"] = data[:64].hex()
meta["last_64_hex"] = data[-64:].hex()

magic = data[0]
nseg = data[1]
spi_mode = data[2]
spi_sf = data[3]
entry = struct.unpack_from("<I", data, 4)[0]
meta["image"] = {
    "magic": f"0x{magic:02X}",
    "valid_esp": magic == 0xE9,
    "segments": nseg,
    "spi_mode": spi_mode,
    "spi_mode_name": {0: "QIO", 1: "QOUT", 2: "DIO", 3: "DOUT"}.get(spi_mode, "?"),
    "flash_size_code": (spi_sf >> 4) & 0xF,
    "flash_freq_code": spi_sf & 0xF,
    "flash_size": {0: "1MB", 1: "2MB", 2: "4MB", 3: "8MB", 4: "16MB"}.get((spi_sf >> 4) & 0xF, "?"),
    "flash_freq": {0: "40MHz", 1: "26MHz", 2: "20MHz", 0xF: "80MHz"}.get(spi_sf & 0xF, "?"),
    "entry_point": f"0x{entry:08X}",
    "wp_pin": data[8],
    "chip_id": data[12],
    "min_chip_rev": data[13],
    "hash_appended": data[23],
    "extended_header_hex": data[8:24].hex(),
}

# App info block often near end of image after checksum
# ESP-IDF app desc is typically in DROM early
# Search for known project name
for marker in [b"arduino-lib-builder", b"esp-idf:", b"ESP-IDF:"]:
    idx = data.find(marker)
    if idx >= 0:
        meta.setdefault("markers", {})[marker.decode()] = f"file=0x{idx:X}"

# Parse esp_app_desc-like structure if present near start of DROM
# After image header + first segment header, often app_desc at 0x3f400020 area
# Standard layout: magic 0xABCD5432 at start of app_desc
app_desc_magic = struct.pack("<I", 0xABCD5432)
ad = data.find(app_desc_magic)
if ad >= 0:
    # esp_app_desc_t fields (IDF 4.x)
    # magic, secure_version, reserv1[2], version[32], project_name[32], time[16], date[16], idf_ver[32], app_elf_sha256[32]
    try:
        version = data[ad + 16 : ad + 48].split(b"\x00")[0].decode("ascii", "replace")
        project = data[ad + 48 : ad + 80].split(b"\x00")[0].decode("ascii", "replace")
        time_s = data[ad + 80 : ad + 96].split(b"\x00")[0].decode("ascii", "replace")
        date_s = data[ad + 96 : ad + 112].split(b"\x00")[0].decode("ascii", "replace")
        idf_ver = data[ad + 112 : ad + 144].split(b"\x00")[0].decode("ascii", "replace")
        elf_sha = data[ad + 144 : ad + 176].hex()
        meta["app_desc"] = {
            "file_offset": f"0x{ad:X}",
            "va": f"0x{file_to_va(ad)[0]:08X}" if file_to_va(ad)[0] else None,
            "version": version,
            "project_name": project,
            "compile_time": time_s,
            "compile_date": date_s,
            "idf_ver": idf_ver,
            "elf_sha256": elf_sha,
        }
    except Exception as e:
        meta["app_desc_error"] = str(e)

# ========== 2. EXTRACT SEGMENTS ==========
seg_dir = OUT / "segments"
seg_dir.mkdir(exist_ok=True)
for s in SEGS:
    blob = data[s["file_off"] : s["file_off"] + s["size"]]
    name = f"seg{s['idx']}_{s['name']}_0x{s['load']:08X}.bin"
    (seg_dir / name).write_bytes(blob)
    s["sha256"] = hashlib.sha256(blob).hexdigest()
    s["entropy"] = round(
        -sum(
            (c / len(blob)) * __import__("math").log2(c / len(blob))
            for c in collections.Counter(blob).values()
            if c
        ),
        4,
    )
meta["segments"] = SEGS

# ========== 3. STRINGS ==========
raw_strings = re.findall(rb"[\x20-\x7e]{4,}", data)
decoded = [s.decode("ascii", errors="replace") for s in raw_strings]
# with offsets
strings_with_off = []
for m in re.finditer(rb"[\x20-\x7e]{4,}", data):
    s = m.group().decode("ascii", "replace")
    va, reg = file_to_va(m.start())
    strings_with_off.append(
        {
            "string": s,
            "file_off": m.start(),
            "file_off_hex": f"0x{m.start():X}",
            "va": f"0x{va:08X}" if va else None,
            "region": reg,
            "length": len(s),
        }
    )

(OUT / "all_strings.txt").write_text("\n".join(decoded), encoding="utf-8")
with (OUT / "all_strings_with_addresses.json").open("w", encoding="utf-8") as f:
    json.dump(strings_with_off, f, indent=1)

# CSV-like for easy search
with (OUT / "all_strings_with_addresses.tsv").open("w", encoding="utf-8") as f:
    f.write("file_off\tva\tregion\tlength\tstring\n")
    for e in strings_with_off:
        esc = e["string"].replace("\t", "\\t").replace("\n", "\\n")
        f.write(f"{e['file_off_hex']}\t{e['va']}\t{e['region']}\t{e['length']}\t{esc}\n")

meta["string_count"] = len(decoded)
meta["string_count_len_ge_8"] = sum(1 for s in decoded if len(s) >= 8)

# Categorize
categories = collections.defaultdict(list)


def cat(name, s, info=None):
    entry = s if info is None else {"string": s, **info}
    if entry not in categories[name]:
        categories[name].append(entry)


for e in strings_with_off:
    s = e["string"]
    sl = s.lower()
    info = {"va": e["va"], "file_off": e["file_off_hex"], "region": e["region"]}

    if any(k in s for k in ("ESP-IDF", "esp-idf", "v4.4", "arduino-lib", "Arduino15", "2.0.10")):
        cat("build_sdk_version", s, info)
    if any(k in sl for k in ("emensta", "bluejammer", "combo-channel", "firmware :", "github.com")):
        cat("app_identity", s, info)
    if any(k in s for k in ("State 0", "State 1", "State 2", "State 3", "State 4", "Idle", "Bluetooth", "WiFi", "BLE")):
        if "State" in s or s in ("Connected",):
            cat("state_machine_ui", s, info)
    if any(k in s for k in ("nRF24", "HSPI", "VSPI", "RadioTask", "radio")):
        cat("rf_nrf24", s, info)
    if any(k in s for k in ("SSD1306", "bitmap", "OLED", "display", "Display", "GFX", "Adafruit")):
        cat("display", s, info)
    if any(k in sl for k in ("gpio", "spi", "i2c", "uart", "mosi", "miso", "sclk", "sda", "scl")):
        if len(s) < 100:
            cat("peripherals_api", s, info)
    if any(k in sl for k in ("wifi", "bluetooth", "ble", "bt_", "nimble", "bluedroid", "coex")):
        if len(s) < 120:
            cat("wireless_stack", s, info)
    if any(k in sl for k in ("error", "fail", "assert", "panic", "abort", "exception", "guru")):
        if len(s) < 100:
            cat("errors_debug", s, info)
    if "Task" in s or "task" in s and len(s) < 40:
        cat("tasks", s, info)
    if "/IDF/" in s or "components/" in s or "Arduino15" in s:
        cat("source_paths", s, info)
    if any(k in sl for k in ("channel", "freq", "mhz", "ghz", "hop", "carrier", "packet", "payload", "protocol")):
        cat("rf_protocol_words", s, info)
    if re.search(r"GPIO\s*\d+|gpio\s*\d+|pin\s*\d+", s, re.I):
        cat("pin_mentions", s, info)
    if any(k in s for k in ("Copyright", "copyright", "License", "Apache", "MIT", "BSD")):
        cat("licenses", s, info)
    if re.search(r"v?\d+\.\d+\.\d+", s) and len(s) < 80:
        cat("version_numbers", s, info)

# Write categories
cat_dir = OUT / "strings_by_category"
cat_dir.mkdir(exist_ok=True)
for name, items in categories.items():
    lines = []
    for it in items:
        if isinstance(it, dict):
            lines.append(f"{it.get('va')}\t{it.get('file_off')}\t{it.get('region')}\t{it['string']}")
        else:
            lines.append(str(it))
    (cat_dir / f"{name}.txt").write_text("\n".join(lines), encoding="utf-8")

# App-only strings (heuristic: DROM, no IDF paths, printable useful)
app_strings = []
for e in strings_with_off:
    s = e["string"]
    if e["region"] != "DROM":
        continue
    if any(x in s for x in ("/IDF/", "components/", "Arduino15", "crosstool", "lwip", "mbedtls", "FreeRTOS")):
        continue
    if s.startswith("E (%") or s.startswith("I (%") or s.startswith("W (%"):
        continue
    if re.fullmatch(r"[\W\d_]+", s):
        continue
    if len(s) < 5:
        continue
    # filter font/glyph garbage: high ratio of rare chars or mostly symbols
    if sum(1 for c in s if c.isalnum() or c in " :./-_@#!") / len(s) < 0.7:
        continue
    app_strings.append(e)

with (OUT / "app_level_strings.tsv").open("w", encoding="utf-8") as f:
    f.write("file_off\tva\tstring\n")
    for e in app_strings:
        f.write(f"{e['file_off_hex']}\t{e['va']}\t{e['string']}\n")

# ========== 4. KEY STRING XREFS (pointer search) ==========
key_needles = [
    b"Firmware : Combo-Channel-Select",
    b"https://github.com/EmenstaNougat/ESP32-BlueJammer",
    b"HSPI nRF24 module initialized SUCCESSFULLY",
    b"VSPI nRF24 module initialized SUCCESSFULLY",
    b"HSPI nRF24 module could NOT",
    b"VSPI nRF24 module could NOT",
    b"Hardware Serial Peripheral Interface started",
    b"Variable Serial Peripheral Interface started",
    b"State 1: Bluetooth",
    b"State 2: Bluetooth Low Energy",
    b"State 3: WiFi",
    b"State 4: RC",
    b"State 0: Idle & Status",
    b"RadioTask",
    b"loopTask",
    b"SSD1306 allocation failed",
    b"bitmapboot",
    b"bitmap1",
    b"bitmap2",
    b"bitmap3",
    b"bitmap4",
    b"Connected",
    b"by @emensta",
    b"esp-idf: v4.4.5",
    b"arduino-lib-builder",
]

xrefs = []
for needle in key_needles:
    fo = data.find(needle)
    if fo < 0:
        xrefs.append({"needle": needle.decode(), "found": False})
        continue
    va, reg = file_to_va(fo)
    ptr_locs = []
    if va is not None:
        ptr = struct.pack("<I", va)
        for loc in find_all(data, ptr):
            pva, preg = file_to_va(loc)
            ptr_locs.append(
                {
                    "file_off": f"0x{loc:X}",
                    "va": f"0x{pva:08X}" if pva else None,
                    "region": preg,
                }
            )
    xrefs.append(
        {
            "needle": needle.decode("ascii", "replace")[:80],
            "found": True,
            "string_file_off": f"0x{fo:X}",
            "string_va": f"0x{va:08X}" if va else None,
            "region": reg,
            "pointer_xrefs": ptr_locs,
        }
    )

(OUT / "key_string_xrefs.json").write_text(json.dumps(xrefs, indent=2), encoding="utf-8")

# ========== 5. CONSTANT HUNT (channels etc.) ==========
# Search for byte sequences that look like channel lists
# e.g. 0..78 for BT, or common nRF channel tables
constants_found = {}

# Immediate-like patterns in whole file: count occurrences of key integers as LE u32 and u8 sequences
interesting_imm = {
    79: "BT classic channels",
    40: "BLE channels",
    14: "WiFi channels",
    125: "nRF max channel / RC",
    126: "nRF channel count 0-125",
    83: "sometimes BT",
    37: "BLE advertising primary",
    2400: "MHz base",
    2402: "BT start MHz",
    2480: "BT end MHz",
    2483: "ISM edge",
    2525: "RC upper",
}

imm_hits = {}
for val, desc in interesting_imm.items():
    # u32 LE
    pat32 = struct.pack("<I", val)
    locs32 = find_all(data, pat32)
    # u16 LE
    if val < 65536:
        pat16 = struct.pack("<H", val)
        locs16 = find_all(data, pat16)
    else:
        locs16 = []
    imm_hits[str(val)] = {
        "description": desc,
        "u32_count": len(locs32),
        "u32_sample_file": [f"0x{x:X}" for x in locs32[:20]],
        "u32_sample_va": [
            f"0x{file_to_va(x)[0]:08X}" for x in locs32[:20] if file_to_va(x)[0]
        ],
        "u16_count": len(locs16),
        "u16_sample_file": [f"0x{x:X}" for x in locs16[:15]],
    }

# Sequential channel tables: look for 0,1,2,3,4... runs of length >= 10 as uint8
def find_sequential_u8(blob, min_len=10, max_start=5):
    results = []
    i = 0
    while i < len(blob) - min_len:
        if blob[i] <= max_start:
            start = blob[i]
            j = 1
            while i + j < len(blob) and blob[i + j] == start + j:
                j += 1
            if j >= min_len:
                results.append((i, start, j))
                i += j
                continue
        i += 1
    return results


seq_tables = []
for s in SEGS:
    blob = data[s["file_off"] : s["file_off"] + s["size"]]
    for off, start, length in find_sequential_u8(blob, min_len=12):
        fo = s["file_off"] + off
        va = s["load"] + off
        seq_tables.append(
            {
                "file_off": f"0x{fo:X}",
                "va": f"0x{va:08X}",
                "region": s["name"],
                "start": start,
                "length": length,
                "preview": list(blob[off : off + min(32, length)]),
            }
        )

# Also look for common hop patterns: even channels only etc.
constants_found["interesting_immediates"] = imm_hits
constants_found["sequential_u8_tables"] = seq_tables[:50]

# GPIO pin numbers commonly used by this project
pin_set = [0, 4, 5, 12, 13, 14, 15, 16, 18, 19, 21, 22, 23, 27]
# Search for arrays of these pins
pin_hits = {str(p): {"u8_count": data.count(bytes([p]))} for p in pin_set}

# Look for SPI pin config patterns: sequences including known pins as bytes nearby
constants_found["gpio_pin_byte_counts"] = pin_hits

# nRF24 register addresses / commands
nrf_cmds = {
    0x00: "CONFIG",
    0x05: "RF_CH",
    0x06: "RF_SETUP",
    0x07: "STATUS",
    0x1C: "DYNPD",
    0x1D: "FEATURE",
    0x20: "W_REGISTER",
    0x60: "R_RX_PAYLOAD",
    0xA0: "W_TX_PAYLOAD",
    0xE1: "FLUSH_TX",
    0xE2: "FLUSH_RX",
    0x50: "ACTIVATE",
    0x73: "ACTIVATE payload R_RX",
}
# less useful alone; note presence of string "RF24" etc already

(OUT / "constants_and_tables.json").write_text(
    json.dumps(constants_found, indent=2), encoding="utf-8"
)

# ========== 6. BITMAP EXTRACTION HEURISTICS ==========
# SSD1306 128x64 = 1024 bytes; 128x32 = 512; icons often 32x32=128 bytes (vertical byte pages)
bitmap_dir = OUT / "bitmaps_candidates"
bitmap_dir.mkdir(exist_ok=True)

# Find label positions for bitmaps
bitmap_labels = {}
for lab in [b"bitmapboot", b"bitmap1", b"bitmap2", b"bitmap3", b"bitmap4"]:
    fo = data.find(lab)
    if fo >= 0:
        va, reg = file_to_va(fo)
        bitmap_labels[lab.decode()] = {"file_off": fo, "va": f"0x{va:08X}" if va else None}

# Near labels, pointer xrefs may point to actual bitmap data
# Search for large non-zero, high-bit-variation regions in DROM after app_desc
drom = data[0x20 : 0x20 + 0x1CFB0]
drom_load = 0x3F400020

# Score windows of 1024/512/128 bytes for "bitmap-likeness" (not pure ASCII, not zeros)
candidates = []
for size, label in [(1024, "128x64"), (512, "128x32"), (256, "64x32"), (128, "32x32")]:
    for off in range(0, len(drom) - size, 16):
        chunk = drom[off : off + size]
        zeros = chunk.count(0)
        ff = chunk.count(0xFF)
        # skip mostly empty or mostly text
        if zeros > size * 0.85 or ff > size * 0.85:
            continue
        # ASCII ratio
        ascii_c = sum(1 for b in chunk if 0x20 <= b <= 0x7E)
        if ascii_c > size * 0.5:
            continue
        # entropy-ish: unique bytes
        uniq = len(set(chunk))
        if uniq < 8:
            continue
        # density of set bits
        bits = sum(bin(b).count("1") for b in chunk)
        density = bits / (size * 8)
        if 0.05 < density < 0.85 and uniq >= 12:
            candidates.append(
                {
                    "size": size,
                    "geom": label,
                    "file_off": 0x20 + off,
                    "va": drom_load + off,
                    "uniq": uniq,
                    "density": round(density, 3),
                    "zeros": zeros,
                }
            )

# Keep top by uniqueness * moderate density, de-dupe nearby
candidates.sort(key=lambda c: (-c["uniq"], -abs(c["density"] - 0.35)))
picked = []
for c in candidates:
    if any(abs(c["file_off"] - p["file_off"]) < c["size"] // 2 for p in picked):
        continue
    picked.append(c)
    if len(picked) >= 40:
        break

for i, c in enumerate(picked):
    chunk = data[c["file_off"] : c["file_off"] + c["size"]]
    fname = f"cand_{i:02d}_{c['geom']}_0x{c['va']:08X}.bin"
    (bitmap_dir / fname).write_bytes(chunk)
    # also write PBM for easy viewing (assume horizontal or page mode - try page mode SSD1306)
    # SSD1306 page format: for each page (8 rows), 128 columns
    def try_pbm_page(chunk, width=128):
        pages = len(chunk) // width
        if pages * width != len(chunk) or pages == 0:
            return None
        height = pages * 8
        rows = []
        for y in range(height):
            page = y // 8
            bit = y % 8
            row_bits = []
            for x in range(width):
                b = chunk[page * width + x]
                row_bits.append("1" if (b >> bit) & 1 else "0")
            rows.append(" ".join(row_bits))
        return f"P1\n{width} {height}\n" + "\n".join(rows) + "\n"

    if c["size"] in (1024, 512):
        w = 128
        pbm = try_pbm_page(chunk, w)
        if pbm:
            (bitmap_dir / fname.replace(".bin", ".pbm")).write_text(pbm, encoding="ascii")

(OUT / "bitmap_candidates.json").write_text(
    json.dumps({"labels": bitmap_labels, "candidates": picked}, indent=2, default=str),
    encoding="utf-8",
)

# ========== 7. FUNCTION / SYMBOL-LIKE NAMES FROM STRINGS ==========
# Extract C identifiers from strings that look like function names
idents = sorted(
    set(
        re.findall(
            r"\b[a-zA-Z_][a-zA-Z0-9_]{3,}\b",
            "\n".join(decoded),
        )
    )
)
# Filter likely symbols
symbolish = [
    i
    for i in idents
    if (
        i[0].islower()
        or i.startswith("esp_")
        or i.startswith("gpio_")
        or i.startswith("i2c_")
        or i.startswith("uart_")
        or i.startswith("spi_")
        or i.startswith("xTask")
        or i.startswith("vTask")
        or i.startswith("nrf")
        or i.startswith("RF24")
    )
    and not i.startswith("0x")
]
(OUT / "symbol_like_identifiers.txt").write_text("\n".join(symbolish), encoding="utf-8")

# Functions mentioned in assert path strings: "function_name" patterns
func_from_asserts = sorted(
    set(
        re.findall(
            r"\b([a-zA-Z_][a-zA-Z0-9_]{2,})\s*\(",
            "\n".join(s for s in decoded if "(" in s and len(s) < 120),
        )
    )
)
(OUT / "functions_mentioned_in_strings.txt").write_text(
    "\n".join(func_from_asserts), encoding="utf-8"
)

# ========== 8. URLS / EMAILS / HOSTS ==========
urls = sorted(set(re.findall(r"https?://[^\s\"'<>]+", "\n".join(decoded))))
emails = sorted(set(re.findall(r"[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}", "\n".join(decoded))))
(OUT / "urls.txt").write_text("\n".join(urls), encoding="utf-8")
(OUT / "emails.txt").write_text("\n".join(emails), encoding="utf-8")

# ========== 9. MEMORY MAP SUMMARY ==========
# List all string pointers into DROM from IROM (common for code)
drom_start, drom_end = 0x3F400020, 0x3F400020 + 0x1CFB0
irom = data[0x20020 : 0x20020 + 0x99060]
irom_base = 0x400D0020
ptr_map = []
for i in range(0, len(irom) - 3, 4):
    (val,) = struct.unpack_from("<I", irom, i)
    if drom_start <= val < drom_end:
        # check if points to printable string
        fo, _ = va_to_file(val)
        if fo is None:
            continue
        # read string
        end = data.find(b"\x00", fo)
        if end < 0 or end - fo > 200 or end - fo < 4:
            continue
        s = data[fo:end]
        if all(0x20 <= b <= 0x7E for b in s):
            ptr_map.append(
                {
                    "code_va": f"0x{irom_base + i:08X}",
                    "str_va": f"0x{val:08X}",
                    "string": s.decode("ascii"),
                }
            )

(OUT / "irom_to_drom_string_pointers.json").write_text(
    json.dumps(ptr_map[:2000], indent=1), encoding="utf-8"
)
meta["irom_drom_string_ptr_count"] = len(ptr_map)

# ========== 10. DRAM initialized data dump as hex preview ==========
for s in SEGS:
    if s["name"].startswith("DRAM"):
        blob = data[s["file_off"] : s["file_off"] + s["size"]]
        (OUT / f"{s['name']}_hexpreview.txt").write_text(
            f"load=0x{s['load']:08X} size=0x{s['size']:X}\n" + blob[:512].hex(" "),
            encoding="utf-8",
        )

# ========== 11. Build human report ==========
# Collect unique app identity full strings
app_full = []
for e in strings_with_off:
    s = e["string"]
    if any(
        k in s
        for k in (
            "Firmware",
            "emensta",
            "BlueJammer",
            "nRF24",
            "State ",
            "bitmap",
            "SSD1306",
            "RadioTask",
            "HSPI",
            "VSPI",
            "Combo",
            "Connected",
        )
    ):
        if "/IDF/" not in s and "components/" not in s and "Arduino15" not in s:
            app_full.append(e)

# Dedup by string
seen = set()
app_unique = []
for e in app_full:
    if e["string"] not in seen:
        seen.add(e["string"])
        app_unique.append(e)

# IDF component list from paths
components = sorted(
    set(
        re.findall(r"(?:/IDF/|IDF/)components/([a-zA-Z0-9_]+)", "\n".join(decoded))
    )
)
meta["idf_components_seen"] = components

# Arduino path
arduino_paths = sorted(set(s for s in decoded if "Arduino15" in s or "arduino" in s.lower() and "packages" in s))

# Write master JSON meta
(OUT / "metadata.json").write_text(json.dumps(meta, indent=2), encoding="utf-8")
(OUT / "key_string_xrefs.json").write_text(json.dumps(xrefs, indent=2), encoding="utf-8")

# Markdown mega report
lines = []
lines.append("# Complete Firmware Extraction Report")
lines.append("")
lines.append(f"**File:** `{BIN_PATH.name}`  ")
lines.append(f"**Size:** {len(data)} bytes ({len(data)/1024:.2f} KB)  ")
lines.append(f"**MD5:** `{meta['md5']}`  ")
lines.append(f"**SHA1:** `{meta['sha1']}`  ")
lines.append(f"**SHA256:** `{meta['sha256']}`  ")
lines.append("")
lines.append("## Image header")
lines.append("```json")
lines.append(json.dumps(meta["image"], indent=2))
lines.append("```")
if "app_desc" in meta:
    lines.append("## esp_app_desc_t")
    lines.append("```json")
    lines.append(json.dumps(meta["app_desc"], indent=2))
    lines.append("```")
lines.append("## Segments (extracted to `extracted/segments/`)")
lines.append("| # | Name | Load VA | Size | File off | Entropy | SHA256 |")
lines.append("|---|------|---------|------|----------|---------|--------|")
for s in SEGS:
    lines.append(
        f"| {s['idx']} | {s['name']} | `0x{s['load']:08X}` | {s['size']} | `0x{s['file_off']:X}` | {s['entropy']} | `{s['sha256'][:16]}…` |"
    )
lines.append("")
lines.append(f"## Strings: {meta['string_count']} total (len≥4)")
lines.append("")
lines.append("### Application / UI strings")
lines.append("| VA | File | String |")
lines.append("|----|------|--------|")
for e in app_unique:
    st = e["string"].replace("|", "\\|")
    if len(st) > 100:
        st = st[:100] + "…"
    lines.append(f"| `{e['va']}` | `{e['file_off_hex']}` | `{st}` |")
lines.append("")
lines.append("### Key string pointer xrefs (for Ghidra)")
for x in xrefs:
    if not x.get("found"):
        continue
    lines.append(f"- **{x['needle'][:60]}** @ `{x['string_va']}`")
    for p in x.get("pointer_xrefs", [])[:5]:
        lines.append(f"  - ptr @ `{p['va']}` ({p['region']})")
lines.append("")
lines.append("### IDF components referenced in asserts/paths")
lines.append(", ".join(f"`{c}`" for c in components))
lines.append("")
lines.append("### URLs")
for u in urls:
    lines.append(f"- {u}")
lines.append("")
lines.append("### Sequential uint8 tables (possible channel lists)")
for t in seq_tables[:30]:
    lines.append(
        f"- `{t['va']}` ({t['region']}): start={t['start']} len={t['length']} preview={t['preview'][:16]}"
    )
lines.append("")
lines.append("### Interesting immediate values")
for val, info in imm_hits.items():
    lines.append(
        f"- **{val}** ({info['description']}): u32×{info['u32_count']}, u16×{info['u16_count']}"
    )
lines.append("")
lines.append("### Bitmap labels")
for k, v in bitmap_labels.items():
    lines.append(f"- `{k}` @ file `0x{v['file_off']:X}` VA `{v['va']}`")
lines.append(f"\nBitmap candidates: {len(picked)} files in `extracted/bitmaps_candidates/`")
lines.append("")
lines.append("### Output file index")
for p in sorted(OUT.rglob("*")):
    if p.is_file():
        lines.append(f"- `{p.relative_to(ROOT)}` ({p.stat().st_size} bytes)")

(OUT / "COMPLETE_EXTRACTION.md").write_text("\n".join(lines), encoding="utf-8")

print("=== EXTRACTION COMPLETE ===")
print(f"Output dir: {OUT}")
print(f"Size: {len(data)}")
print(f"SHA256: {meta['sha256']}")
print(f"Strings: {meta['string_count']}")
print(f"App-level strings: {len(app_strings)}")
print(f"IROM->DROM string ptrs: {len(ptr_map)}")
print(f"Seq tables: {len(seq_tables)}")
print(f"Bitmap candidates: {len(picked)}")
print(f"IDF components: {len(components)}")
if "app_desc" in meta:
    print("app_desc:", meta["app_desc"])
print("Categories:", list(categories.keys()))
