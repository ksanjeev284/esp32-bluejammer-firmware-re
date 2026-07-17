# Legal & Ethical Disclaimer — Range Pro

## Educational purpose only

This package documents **hardware upgrades and firmware profiles** for studying:

- 2.4 GHz link budget and antennas  
- nRF24 PA/LNA module behavior  
- Power integrity under TX  
- Dual-radio desense and channel separation  
- Embedded FreeRTOS dual-core control  

## Higher power = higher risk

**PA modules and high-gain antennas increase radiated energy.**  
Intentionally interfering with radio communications is **illegal** in most countries and may be a criminal offense.

Do **not** use this package to:

- Build or operate jammers against public or third-party networks  
- Conduct outdoor “range tests” that disturb others  
- Bypass laws, licenses, or institutional RF safety rules  

Use only in **authorized, preferably shielded** lab environments. Prefer `REBUILD_SAFE=1` for classroom UI work without RF TX.

## No warranty

Hardware advice and firmware are provided as-is. Module vendor “dBm” claims vary. Authors accept no liability for misuse, injury, equipment damage, or legal consequences.

## Attribution

Analysis lineage includes reverse engineering of a published ESP32 combo firmware image for educational reconstruction. Original ecosystem discussed for context: https://github.com/EmenstaNougat/ESP32-BlueJammer  
