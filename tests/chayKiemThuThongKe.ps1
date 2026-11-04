$ErrorActionPreference = 'Stop'
$gocDuAn = Split-Path -Parent $PSScriptRoot
$thuMuc = 'build/thongke-kiemthu-' + [Guid]::NewGuid().ToString('N')
$duongDan = Join-Path $gocDuAn $thuMuc
New-Item -ItemType Directory -Path $duongDan | Out-Null
& powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $gocDuAn 'build.ps1') -KiemThuThongKe -ThuMucBuild $thuMuc |
    Tee-Object -FilePath (Join-Path $duongDan 'ket_qua.txt')
$maThoat = $LASTEXITCODE
Write-Host "Ket qua thong ke va thuat toan: $duongDan"
exit $maThoat
