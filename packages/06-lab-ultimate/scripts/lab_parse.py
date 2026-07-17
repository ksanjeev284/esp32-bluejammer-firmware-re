#!/usr/bin/env python3
"""Parse Lab Ultimate serial / LittleFS CSV exports and marker lines.

Usage:
  python lab_parse.py capture.txt
  python lab_parse.py capture.txt --markers
  python lab_parse.py capture.txt --plot   # if matplotlib available
"""

from __future__ import annotations

import argparse
import csv
import json
import re
import sys
from pathlib import Path


CSV_RE = re.compile(
    r"^CSV,(\d+),(-?\d+),(\d+),(\d+),([0-9.]+),(\d+),([0-9.]+),(\d+),(-?\d+),(\d+)(?:,([0-9.]+),([0-9.]+))?"
)
MARK_RE = re.compile(
    r"^CSV_MARK,(\d+),([^,]+),(\d+),([0-9.]+),(\d+)"
)
MARKER_TX_RE = re.compile(r"^MARKER,(\d+),([^,]+),(\d+),(\d+),(\d+)")
JSON_RE = re.compile(r"^\{.*\"lab\"\s*:\s*\"lab-ultimate\".*\}$")


def parse_file(path: Path):
    rows = []
    marks = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        m = CSV_RE.match(line)
        if m:
            g = m.groups()
            rows.append(
                {
                    "t_ms": int(g[0]),
                    "mode": int(g[1]),
                    "chH": int(g[2]),
                    "chV": int(g[3]),
                    "hop_rate": float(g[4]),
                    "unique": int(g[5]),
                    "vcc": float(g[6]),
                    "heap": int(g[7]),
                    "armed": int(g[8]),
                    "markers": int(g[9]),
                    "busV": float(g[10]) if g[10] else None,
                    "currA": float(g[11]) if g[11] else None,
                }
            )
            continue
        m = MARK_RE.match(line)
        if m:
            marks.append(
                {
                    "t_ms": int(m.group(1)),
                    "tag": m.group(2),
                    "ch": int(m.group(3)),
                    "rpd_pct": float(m.group(4)),
                    "count": int(m.group(5)),
                    "src": "obs",
                }
            )
            continue
        m = MARKER_TX_RE.match(line)
        if m:
            marks.append(
                {
                    "t_ms": int(m.group(1)),
                    "tag": m.group(2),
                    "chH": int(m.group(3)),
                    "chV": int(m.group(4)),
                    "mode": int(m.group(5)),
                    "src": "tx",
                }
            )
            continue
        if JSON_RE.match(line):
            try:
                rows.append({"json": json.loads(line)})
            except json.JSONDecodeError:
                pass
    return rows, marks


def main() -> int:
    ap = argparse.ArgumentParser(description="Lab Ultimate log parser")
    ap.add_argument("file", type=Path)
    ap.add_argument("--markers", action="store_true", help="print markers only")
    ap.add_argument("--csv-out", type=Path, help="write cleaned CSV rows")
    ap.add_argument("--plot", action="store_true", help="plot hop_rate / current if possible")
    args = ap.parse_args()

    if not args.file.exists():
        print(f"missing {args.file}", file=sys.stderr)
        return 1

    rows, marks = parse_file(args.file)
    data_rows = [r for r in rows if "t_ms" in r]

    print(f"file: {args.file}")
    print(f"CSV rows: {len(data_rows)}  markers: {len(marks)}")

    if args.markers or marks:
        print("\n--- markers ---")
        for m in marks:
            print(m)

    if data_rows:
        rates = [r["hop_rate"] for r in data_rows]
        curr = [r["currA"] for r in data_rows if r.get("currA") is not None]
        print("\n--- summary ---")
        print(f"hop_rate min/avg/max: {min(rates):.0f} / {sum(rates)/len(rates):.0f} / {max(rates):.0f}")
        if curr:
            print(f"currA min/avg/max: {min(curr):.3f} / {sum(curr)/len(curr):.3f} / {max(curr):.3f}")
        modes = {}
        for r in data_rows:
            modes[r["mode"]] = modes.get(r["mode"], 0) + 1
        print(f"mode histogram: {modes}")

    if args.csv_out and data_rows:
        with args.csv_out.open("w", newline="", encoding="utf-8") as f:
            w = csv.DictWriter(f, fieldnames=list(data_rows[0].keys()))
            w.writeheader()
            w.writerows(data_rows)
        print(f"wrote {args.csv_out}")

    if args.plot and data_rows:
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            print("matplotlib not installed", file=sys.stderr)
            return 0
        t0 = data_rows[0]["t_ms"]
        t = [(r["t_ms"] - t0) / 1000.0 for r in data_rows]
        fig, ax = plt.subplots(2, 1, sharex=True, figsize=(9, 5))
        ax[0].plot(t, [r["hop_rate"] for r in data_rows], label="hop/s")
        ax[0].set_ylabel("hop/s")
        ax[0].grid(True, alpha=0.3)
        if any(r.get("currA") is not None for r in data_rows):
            ax[1].plot(
                t,
                [r["currA"] if r.get("currA") is not None else float("nan") for r in data_rows],
                color="C1",
                label="A",
            )
            ax[1].set_ylabel("currA")
        ax[1].set_xlabel("time s")
        ax[1].grid(True, alpha=0.3)
        fig.suptitle(str(args.file))
        fig.tight_layout()
        plt.show()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
