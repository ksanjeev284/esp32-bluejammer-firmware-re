# Build LabUltimate TX + RangeObserver and copy merged bins to firmware/
$ErrorActionPreference = "Stop"
$pkg = Resolve-Path (Join-Path $PSScriptRoot "..")
$tx = Join-Path $pkg "src\LabUltimateTX"
$obs = Join-Path $pkg "src\RangeObserver"
$fw = Join-Path $pkg "firmware"
New-Item -ItemType Directory -Force -Path $fw | Out-Null

# BLE+WiFi needs larger app partition than default 1.2MB
$fqbn = "esp32:esp32:esp32:PartitionScheme=min_spiffs"
Write-Host "=== Build TX ($fqbn) ==="
arduino-cli compile --fqbn $fqbn --output-dir (Join-Path $tx "build") $tx
Write-Host "=== Build Observer ==="
arduino-cli compile --fqbn $fqbn --output-dir (Join-Path $obs "build") $obs

Copy-Item (Join-Path $tx "build\LabUltimateTX.ino.merged.bin") (Join-Path $fw "LabUltimateTX_FULL_FLASH.bin") -Force
Copy-Item (Join-Path $tx "build\LabUltimateTX.ino.bin") (Join-Path $fw "LabUltimateTX.bin") -Force
Copy-Item (Join-Path $obs "build\RangeObserver.ino.merged.bin") (Join-Path $fw "RangeObserver_FULL_FLASH.bin") -Force
Copy-Item (Join-Path $obs "build\RangeObserver.ino.bin") (Join-Path $fw "RangeObserver.bin") -Force
Write-Host "Firmware updated in $fw"
Get-ChildItem $fw | Format-Table Name, Length
