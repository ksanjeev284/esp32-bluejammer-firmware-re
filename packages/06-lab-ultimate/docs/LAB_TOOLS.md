# Lab tools (Python)

## Capture serial

```bash
pip install pyserial
python scripts/serial_capture.py COM5 -o walk1.txt --seconds 180
```

## Parse CSV / markers

```bash
python scripts/lab_parse.py walk1.txt
python scripts/lab_parse.py walk1.txt --markers
python scripts/lab_parse.py walk1.txt --csv-out clean.csv
python scripts/lab_parse.py walk1.txt --plot   # needs matplotlib
```

## Pull LittleFS log via serial

On device:

```text
logdump
```

Paste into a file, then run `lab_parse.py`.

## CSA unit tests (host)

```bash
python scripts/csa_test.py
```

Validates educational CSA#1 period-37 and CSA#2 remap math (mirrors `soft_csa.h`).
