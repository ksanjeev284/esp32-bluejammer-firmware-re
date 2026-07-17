# Flash RangeObserver to a COM port (use second ESP32)
param(
  [Parameter(Mandatory = $true)][string]$Port,
  [string]$Bin = ""
)
$ErrorActionPreference = "Stop"
$fw = Join-Path $PSScriptRoot "..\firmware\RangeObserver_FULL_FLASH.bin"
if ($Bin) { $fw = $Bin }
$fw = (Resolve-Path $fw).Path
Write-Host "Flashing RangeObserver -> $Port"
python -m esptool --chip esp32 -p $Port write_flash 0x0 $fw
Write-Host "Done. Match OBS_CHANNEL to TX FIXED_CH_H (default 45)."
