# Repository structure

```text
esp32-combo-channel-select-re/
│
├── README.md                 ← start here
├── DISCLAIMER.md             ← legal / ethics (required reading)
├── CONTRIBUTING.md           ← how to add findings
├── LICENSE
├── STRUCTURE.md              ← this file
│
├── packages/                 ← flashable firmware kits (numbered)
│   ├── README.md
│   ├── 01-rebuild/           RE kit + original binary study
│   ├── 02-faithful/          open behavioral clone (bins)
│   ├── 03-pro-edu/           smarter hop maps
│   ├── 04-range-pro/         PA+LNA / range lab
│   ├── 05-spectrum-next/     IEEE multi-standard
│   └── 06-lab-ultimate/      ★ active development (v0.5+)
│
├── firmware/                 ← original closed sample + early rebuild
│   ├── Combo-Channel-Select_BT-BLE-WiFi-RC.ino.bin
│   └── reconstructed/
│
├── docs/                     ← reverse-engineering write-ups
├── research/
│   └── ble-advanced/         BLE PHY / CSA / literature notes
│
├── artifacts/                ← extracted strings, Ghidra exports, segments
├── reconstruction/           ← early Arduino reconstruction notes
├── ghidra_scripts/           ← headless / analysis helpers
├── scripts/                  ← Python extractors
│
└── community/
    └── findings/             ← contributor drop zone (dated folders)
```

## Naming conventions

| Pattern | Meaning |
| --- | --- |
| `packages/0N-short-name/` | User-facing firmware kits |
| `docs/*.md` | Long-form RE reports |
| `community/findings/YYYY-MM-DD_topic/` | New public findings |
| `*_FULL_FLASH.bin` | Flash at address `0x0` |
| `*_SAFE_*` | No RF transmit path |

## What to open first

1. [DISCLAIMER.md](DISCLAIMER.md)  
2. [packages/06-lab-ultimate/README.md](packages/06-lab-ultimate/README.md) — run on hardware  
3. [packages/01-rebuild/docs/](packages/01-rebuild/docs/) — how the original binary was recovered  
4. [research/ble-advanced/](research/ble-advanced/) — channel math deep dive  
