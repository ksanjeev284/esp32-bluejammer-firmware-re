#!/usr/bin/env python3
"""Second-pass deep extraction: channel tables, fonts, bitmaps, app pointer graph."""
from __future__ import annotations

import json
import re
import struct
from pathlib import Path
from collections import defaultdict

ROOT = Path(__file__).resolve().parent
BIN = ROOT / "Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin"
OUT = ROOT / "extracted"
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


def find_all(blob, needle):
    out, i = [], 0
    while True:
        j = blob.find(needle, i)
        if j < 0:
            return out
        out.append(j)
        i = j + 1


# ---- App string block: dump raw DROM region around known app strings ----
# From earlier: HSPI strings ~0x2C4, firmware banner ~0xE40, states ~0x1658, bitmapboot ~0x82D
regions_of_interest = [
    ("drom_app_rf_banners", 0x20, 0x900),  # includes HSPI/VSPI messages + start bitmapboot label area
    ("drom_banner_and_url", 0xE00, 0x400),
    ("drom_states_bitmaps_labels", 0x1600, 0x200),
    ("drom_app_desc", 0x20, 0x120),
]

hex_dir = OUT / "hex_regions"
hex_dir.mkdir(exist_ok=True)
for name, start, length in regions_of_interest:
    chunk = data[start : start + length]
    lines = [f"; {name} file=0x{start:X} len=0x{length:X} va={file_to_va(start)[0]:#010x}"]
    for i in range(0, len(chunk), 16):
        row = chunk[i : i + 16]
        hexs = " ".join(f"{b:02X}" for b in row)
        asc = "".join(chr(b) if 32 <= b < 127 else "." for b in row)
        lines.append(f"{start+i:06X}  {hexs:<48}  {asc}")
    (hex_dir / f"{name}.txt").write_text("\n".join(lines), encoding="utf-8")

# ---- Extract exact full application banner strings (they may have spaces) ----
# Search for long runs with Firmware / HSPI
app_messages = []
for m in re.finditer(rb"[\x20-\x7e]{10,}", data):
    s = m.group().decode("ascii")
    if any(
        k in s
        for k in (
            "nRF24",
            "HSPI",
            "VSPI",
            "Firmware",
            "emensta",
            "BlueJammer",
            "State ",
            "bitmap",
            "SSD1306",
            "RadioTask",
            "Connected",
            "Combo-Channel",
            "Serial Peripheral",
        )
    ):
        va, reg = file_to_va(m.start())
        app_messages.append(
            {
                "string": s,
                "file_off": f"0x{m.start():X}",
                "va": f"0x{va:08X}" if va else None,
                "region": reg,
                "len": len(s),
            }
        )

(OUT / "app_messages_full.json").write_text(json.dumps(app_messages, indent=2), encoding="utf-8")
(OUT / "app_messages_full.txt").write_text(
    "\n\n".join(f"[{a['va']}] {a['string']}" for a in app_messages), encoding="utf-8"
)

# ---- Follow pointers near state labels for bitmap data addresses ----
# After labels like bitmap1 there may be no data; data referenced from code.
# Collect all IROM pointers into DROM that land in low app area (first 8KB of DROM)
ptr_graph = []
irom_off, irom_sz, irom_va = 0x20020, 0x99060, 0x400D0020
irom = data[irom_off : irom_off + irom_sz]
drom_lo, drom_hi = 0x3F400020, 0x3F400020 + 0x1CFB0

# Group consecutive string pointers (tables)
tables = []
cur = []
for i in range(0, len(irom) - 3, 4):
    (val,) = struct.unpack_from("<I", irom, i)
    if drom_lo <= val < drom_hi:
        fo, _ = va_to_file(val)
        s = None
        if fo is not None:
            z = data.find(b"\x00", fo, fo + 180)
            if z > fo:
                raw = data[fo:z]
                if all(32 <= b < 127 for b in raw) and len(raw) >= 4:
                    s = raw.decode("ascii")
        entry = {
            "code_va": irom_va + i,
            "str_va": val,
            "string": s,
        }
        ptr_graph.append(entry)
        if s:
            if cur and (irom_va + i) - cur[-1]["code_va"] <= 16:
                cur.append(entry)
            else:
                if len(cur) >= 3:
                    tables.append(cur)
                cur = [entry]
        else:
            if len(cur) >= 3:
                tables.append(cur)
            cur = []
    else:
        if len(cur) >= 3:
            tables.append(cur)
        cur = []
if len(cur) >= 3:
    tables.append(cur)

# Save string pointer tables
table_out = []
for t in tables:
    table_out.append(
        {
            "start_code_va": f"0x{t[0]['code_va']:08X}",
            "count": len(t),
            "entries": [
                {"code_va": f"0x{e['code_va']:08X}", "str_va": f"0x{e['str_va']:08X}", "string": e["string"]}
                for e in t
            ],
        }
    )
(OUT / "string_pointer_tables.json").write_text(json.dumps(table_out, indent=2), encoding="utf-8")

# App-relevant pointer tables only
app_keys = (
    "State",
    "bitmap",
    "nRF",
    "HSPI",
    "VSPI",
    "Firmware",
    "emensta",
    "SSD1306",
    "Radio",
    "Connected",
    "BlueJammer",
    "Combo",
)
app_tables = [
    t
    for t in table_out
    if any(e["string"] and any(k in e["string"] for k in app_keys) for e in t["entries"])
]
(OUT / "app_string_pointer_tables.json").write_text(json.dumps(app_tables, indent=2), encoding="utf-8")

# ---- Search for non-string data pointers from early IROM (likely bitmap / config) ----
# Pointers into DROM that do NOT start a C string — likely binary assets
data_ptrs = []
for i in range(0, min(len(irom), 0x8000), 4):  # first 32KB of IROM (app code often early)
    (val,) = struct.unpack_from("<I", irom, i)
    if not (drom_lo <= val < drom_hi):
        continue
    fo, _ = va_to_file(val)
    if fo is None:
        continue
    # not a clean string?
    sample = data[fo : fo + 16]
    is_str = all(32 <= b < 127 for b in sample[:8])
    if is_str:
        continue
    # skip all zeros
    if sample == b"\x00" * 16:
        continue
    data_ptrs.append(
        {
            "code_va": f"0x{irom_va + i:08X}",
            "data_va": f"0x{val:08X}",
            "file_off": f"0x{fo:X}",
            "sample_hex": sample.hex(),
        }
    )

(OUT / "drom_data_pointers_from_irom_head.json").write_text(
    json.dumps(data_ptrs[:500], indent=2), encoding="utf-8"
)

# Extract chunks at unique data pointer targets (possible bitmaps)
bmp_dir = OUT / "bitmap_from_pointers"
bmp_dir.mkdir(exist_ok=True)
seen_targets = set()
extracted_assets = []
for p in data_ptrs:
    va = int(p["data_va"], 16)
    if va in seen_targets:
        continue
    seen_targets.add(va)
    fo = int(p["file_off"], 16)
    for size, tag in [(1024, "1024"), (512, "512"), (256, "256"), (128, "128"), (64, "64")]:
        if fo + size > len(data):
            continue
        chunk = data[fo : fo + size]
        zeros = chunk.count(0)
        if zeros > size * 0.9:
            continue
        ascii_r = sum(1 for b in chunk if 32 <= b < 127) / size
        if ascii_r > 0.6:
            continue
        uniq = len(set(chunk))
        if uniq < 6:
            continue
        fname = f"asset_0x{va:08X}_{tag}.bin"
        (bmp_dir / fname).write_bytes(chunk)
        extracted_assets.append({"va": p["data_va"], "size": size, "file": fname, "uniq": uniq})
        break  # one size per target for overview

(OUT / "assets_from_pointers.json").write_text(json.dumps(extracted_assets, indent=2), encoding="utf-8")

# PBM for 1024-byte assets
for a in extracted_assets:
    if a["size"] != 1024:
        continue
    chunk = (bmp_dir / a["file"]).read_bytes()
    width = 128
    pages = 8
    rows = []
    for y in range(64):
        page = y // 8
        bit = y % 8
        row = []
        for x in range(width):
            b = chunk[page * width + x]
            row.append("1" if (b >> bit) & 1 else "0")
        rows.append(" ".join(row))
    pbm = f"P1\n{width} 64\n" + "\n".join(rows) + "\n"
    (bmp_dir / a["file"].replace(".bin", "_ssd1306.pbm")).write_text(pbm, encoding="ascii")


# ---- Channel table heuristics ----
# 1) uint8 list of unique channels length 14/40/79/125
# 2) pairs of start/end
# 3) RF_CH write patterns: SPI buffer constructions hard in static analysis

def analyze_u8_array(blob, base_file, base_va, region):
    findings = []
    # sliding windows looking for arrays with values all <= 125 and high uniqueness
    for length in (14, 40, 79, 80, 83, 125, 126):
        for off in range(0, len(blob) - length):
            arr = list(blob[off : off + length])
            if any(x > 125 for x in arr):
                continue
            if max(arr) < 5:  # boring small numbers
                continue
            uniq = len(set(arr))
            # require decent coverage
            if uniq < max(8, length // 4):
                continue
            # skip pure sequential already noted
            if arr == list(range(arr[0], arr[0] + length)):
                # still record once
                pass
            # score: prefer values spanning RF range
            if max(arr) - min(arr) < 10 and uniq < length * 0.5:
                continue
            findings.append(
                {
                    "region": region,
                    "va": f"0x{base_va + off:08X}",
                    "file_off": f"0x{base_file + off:X}",
                    "length": length,
                    "uniq": uniq,
                    "min": min(arr),
                    "max": max(arr),
                    "first_32": arr[:32],
                }
            )
    return findings


ch_findings = []
for fs, sz, va, name in SEGS:
    if name not in ("DROM", "IROM", "DRAM1", "DRAM2"):
        continue
    blob = data[fs : fs + sz]
    # limit search density
    step_blob = blob
    ch_findings.extend(analyze_u8_array(step_blob, fs, va, name))

# Dedup / rank
ch_findings.sort(key=lambda x: (-x["uniq"], -x["length"]))
# Keep top interesting
top_ch = []
seen_va = set()
for f in ch_findings:
    if f["va"] in seen_va:
        continue
    # prefer lengths matching modes
    if f["length"] not in (14, 40, 79, 80, 125, 126):
        continue
    if f["max"] < 20 and f["length"] > 20:
        continue
    seen_va.add(f["va"])
    top_ch.append(f)
    if len(top_ch) >= 80:
        break

(OUT / "possible_channel_arrays.json").write_text(json.dumps(top_ch, indent=2), encoding="utf-8")

# ---- Look for C++ RF24 method-related strings / Arduino SPI ----
lib_strings = []
for m in re.finditer(rb"[\x20-\x7e]{5,}", data):
    s = m.group().decode("ascii", "replace")
    if any(
        k in s
        for k in (
            "RF24",
            "rf24",
            "nRF24",
            "setChannel",
            "startConstCarrier",
            "stopConstCarrier",
            "setPALevel",
            "setDataRate",
            "openWritingPipe",
            "enableDynamicPayloads",
            "SPIClass",
            "HSPI",
            "VSPI",
            "Adafruit_SSD1306",
            "Adafruit_GFX",
            "drawBitmap",
            "setCursor",
            "digitalWrite",
            "pinMode",
            "digitalRead",
            "delayMicroseconds",
            "xTaskCreate",
            "vTaskDelay",
        )
    ):
        va, reg = file_to_va(m.start())
        lib_strings.append({"s": s, "va": f"0x{va:08X}" if va else None, "reg": reg})

(OUT / "library_api_strings.json").write_text(json.dumps(lib_strings, indent=2), encoding="utf-8")

# ---- Extract ALL unique printable strings from DROM only that look like English/UI ----
drom = data[0x20 : 0x20 + 0x1CFB0]
ui = []
for m in re.finditer(rb"[\x20-\x7e]{4,}", drom):
    s = m.group().decode("ascii")
    if sum(c.isalpha() for c in s) < 3:
        continue
    if any(x in s for x in ("/IDF/", "components/", "Arduino15", "crosstool", "pxRing", "pxQueue", "pxTask")):
        continue
    if s.startswith("E (%") or s.startswith("W (%") or s.startswith("I (%"):
        continue
    # skip assert fragments
    if " != " in s or " == " in s or "&&" in s:
        continue
    fo = 0x20 + m.start()
    va = 0x3F400020 + m.start()
    ui.append((f"0x{va:08X}", s))

# unique preserve order
seen = set()
ui_u = []
for va, s in ui:
    if s not in seen:
        seen.add(s)
        ui_u.append((va, s))

(OUT / "drom_readable_strings.txt").write_text(
    "\n".join(f"{va}\t{s}" for va, s in ui_u), encoding="utf-8"
)

# ---- Task names ----
task_names = sorted(
    set(
        re.findall(
            r"\b([A-Za-z][A-Za-z0-9_]{2,30}Task)\b",
            "\n".join(a["string"] for a in app_messages)
            + "\n"
            + "\n".join(s for _, s in ui_u),
        )
    )
)
# also search all strings
all_tasks = sorted(
    set(re.findall(r"\b([A-Za-z][A-Za-z0-9_]{2,40}Task)\b", data.decode("latin-1", "replace")))
)
(OUT / "task_names.txt").write_text("\n".join(all_tasks), encoding="utf-8")

# ---- Build expanded human summary ----
summary = []
summary.append("# Deep Extraction Summary")
summary.append("")
summary.append("## Full application messages")
for a in app_messages:
    summary.append(f"- `{a['va']}` ({a['len']} chars): {a['string'][:200]}")
summary.append("")
summary.append("## App string pointer tables")
for t in app_tables:
    summary.append(f"### Table @ `{t['start_code_va']}` ({t['count']} entries)")
    for e in t["entries"]:
        summary.append(f"- `{e['code_va']}` -> `{e['str_va']}`: {e['string']}")
summary.append("")
summary.append(f"## Non-string DROM data pointers (first 32KB IROM): {len(data_ptrs)}")
summary.append(f"## Assets extracted: {len(extracted_assets)}")
summary.append(f"## Possible channel arrays: {len(top_ch)}")
if top_ch:
    summary.append("### Top candidates")
    for c in top_ch[:25]:
        summary.append(
            f"- `{c['va']}` len={c['length']} uniq={c['uniq']} range={c['min']}-{c['max']} first={c['first_32'][:16]}"
        )
summary.append("")
summary.append("## Library/API-related strings found")
for x in lib_strings:
    summary.append(f"- `{x['va']}` {x['s'][:120]}")
summary.append("")
summary.append("## FreeRTOS / task names")
for t in all_tasks:
    summary.append(f"- {t}")
summary.append("")
summary.append(f"## DROM readable strings: {len(ui_u)} (see drom_readable_strings.txt)")

(OUT / "DEEP_SUMMARY.md").write_text("\n".join(summary), encoding="utf-8")

print("Deep extraction done")
print("app_messages", len(app_messages))
print("app_tables", len(app_tables))
print("data_ptrs", len(data_ptrs))
print("assets", len(extracted_assets))
print("channel_candidates", len(top_ch))
print("lib_strings", len(lib_strings))
print("tasks", all_tasks)
print("drom_readable", len(ui_u))
# print app tables compact
for t in app_tables:
    print("TABLE", t["start_code_va"], [(e["string"] or "")[:40] for e in t["entries"]])
