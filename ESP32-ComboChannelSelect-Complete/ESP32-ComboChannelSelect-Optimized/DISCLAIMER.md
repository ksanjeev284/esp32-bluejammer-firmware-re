# Legal & Ethical Disclaimer

## Educational / authorized lab use only

This package is an **optimized reconstruction** of behavior recovered from reverse-engineering an ESP32 dual-nRF24 combo firmware. It exists to document embedded systems design and safe rebuild practices.

## Do not jam

**Intentionally interfering with radio communications is illegal** in most countries and may be a criminal offense. It can disrupt emergency, aviation, medical, Wi-Fi, Bluetooth, and other systems.

Do **not** use this firmware to:

- Build or operate jammers  
- Attack networks or devices you do not own  
- Cause harmful interference  

Default full-RF build (`REBUILD_SAFE=0`) exercises continuous-carrier APIs that can create interference. Use only in a lawful, shielded environment with proper authorization. Prefer `REBUILD_SAFE=1` for UI experiments.

## No warranty

Firmware and documentation are provided as-is. Behavior may differ from the original closed binary. Authors and contributors accept no liability for misuse or damage.

## Attribution

Upstream project discussed for context:

https://github.com/EmenstaNougat/ESP32-BlueJammer

This Pro package is an independent educational optimization of a reconstruction effort, not an official product of that project.
