# Classroom SAFE build — UI + telemetry, no RF TX (REBUILD_SAFE=1)
$ErrorActionPreference = "Stop"
$pkg = Resolve-Path (Join-Path $PSScriptRoot "..")
$tx = Join-Path $pkg "src\LabUltimateTX"
$fw = Join-Path $pkg "firmware"
$fqbn = "esp32:esp32:esp32:PartitionScheme=min_spiffs"
New-Item -ItemType Directory -Force -Path $fw | Out-Null

Write-Host "=== Build LabUltimate TX SAFE (no RF) ==="
arduino-cli compile --fqbn $fqbn `
  --build-property "compiler.cpp.extra_flags=-DREBUILD_SAFE=1" `
  --output-dir (Join-Path $tx "build_safe") $tx

Copy-Item (Join-Path $tx "build_safe\LabUltimateTX.ino.merged.bin") `
  (Join-Path $fw "LabUltimateTX_SAFE_FULL_FLASH.bin") -Force
Write-Host "Wrote firmware\LabUltimateTX_SAFE_FULL_FLASH.bin"
