# Flash LabUltimate TX to first CP210x / CH340 / ESP COM port
param(
  [string]$Port = "",
  [string]$Bin = ""
)
$ErrorActionPreference = "Stop"
$root = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
if (-not $root) { $root = "E:\esp32\combochannel" }
$fw = Join-Path $PSScriptRoot "..\firmware\LabUltimateTX_FULL_FLASH.bin"
if ($Bin) { $fw = $Bin }
$fw = (Resolve-Path $fw).Path

if (-not $Port) {
  $p = Get-CimInstance Win32_SerialPort | Where-Object {
    $_.Name -match 'CP210|CH340|USB.?Serial|UART'
  } | Select-Object -First 1
  if (-not $p) { throw "No USB serial ESP port found. Pass -Port COMx" }
  $Port = $p.DeviceID
}

Write-Host "Flashing LabUltimate TX -> $Port"
Write-Host "Image: $fw"
python -m esptool --chip esp32 -p $Port write_flash 0x0 $fw
Write-Host "Done. Serial 115200. Triple BOOT to arm."
