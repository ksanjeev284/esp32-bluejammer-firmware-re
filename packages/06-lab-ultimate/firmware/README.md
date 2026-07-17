# Prebuilt images (Lab Ultimate v0.5.0-roi5)

Built with `PartitionScheme=min_spiffs` (1.9 MB app — required for BLE+WiFi+Web).

| File | Flash offset | Board |
| --- | --- | --- |
| `LabUltimateTX_FULL_FLASH.bin` | `0x0` | Dual nRF24 TX (full lab) |
| `LabUltimateTX_SAFE_FULL_FLASH.bin` | `0x0` | Classroom **no RF TX** |
| `RangeObserver_FULL_FLASH.bin` | `0x0` | Second board + 1 nRF |

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 LabUltimateTX_FULL_FLASH.bin
esptool.py --chip esp32 -p COMy write_flash 0x0 RangeObserver_FULL_FLASH.bin
```

Or: `..\scripts\flash_tx.ps1` · `..\scripts\build_safe.ps1`

Serial 115200. TX: triple BOOT to arm; double BOOT = marker.  
Phone: Wi‑Fi **LabUltimate** / **labult123** → http://192.168.4.1/