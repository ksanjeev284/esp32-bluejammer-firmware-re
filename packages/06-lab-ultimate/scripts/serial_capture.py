#!/usr/bin/env python3
"""Capture Lab Ultimate serial CSV/JSON to a file.

  python serial_capture.py COM5 -o walk1.txt -b 115200
  python serial_capture.py COM5 -o walk1.txt --seconds 120
"""

from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("port")
    ap.add_argument("-o", "--out", type=Path, required=True)
    ap.add_argument("-b", "--baud", type=int, default=115200)
    ap.add_argument("--seconds", type=float, default=0, help="0 = until Ctrl+C")
    args = ap.parse_args()

    try:
        import serial
    except ImportError:
        print("pip install pyserial", file=sys.stderr)
        return 1

    ser = serial.Serial(args.port, args.baud, timeout=0.2)
    print(f"capturing {args.port} -> {args.out}  (Ctrl+C stop)")
    t0 = time.time()
    n = 0
    with args.out.open("a", encoding="utf-8") as f:
        try:
            while True:
                if args.seconds and (time.time() - t0) >= args.seconds:
                    break
                line = ser.readline()
                if not line:
                    continue
                try:
                    s = line.decode("utf-8", errors="replace").rstrip("\r\n")
                except Exception:
                    continue
                f.write(s + "\n")
                f.flush()
                n += 1
                if n % 20 == 0:
                    print(f"  lines={n} last={s[:80]}")
        except KeyboardInterrupt:
            print("\nstopped")
    ser.close()
    print(f"wrote {n} lines to {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
