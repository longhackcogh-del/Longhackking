param([switch]$KiemThu, [switch]$KiemThuThongKe, [string]$ThuMucBuild = 'build/tich-hop')
$ErrorActionPreference = 'Stop'
$gocDuAn = $PSScriptRoot
$thuMucBuild = Join-Path $gocDuAn $ThuMucBuild
New-Item -ItemType Directory -Path $thuMucBuild -Force | Out-Null
Get-Command g++ -ErrorAction Stop | Out-Null
$tenNguon = @(
    'Nguoi.cpp', 'DocGia.cpp', 'SinhVien.cpp', 'GiangVien.cpp',
    'NhanVienThuThu.cpp', 'ThuThuTruong.cpp', 'QuanLyDocGia.cpp',
    'QuanLyNhanVien.cpp', 'QuanLyThuThuTruong.cpp', 'NhapXuat.cpp',
    'TaiLieu.cpp', 'Sach.cpp', 'TapChi.cpp', 'Bao.cpp', 'QuanLyTaiLieu.cpp',
    'PhieuMuon.cpp', 'QuanLyPhieuMuon.cpp', 'NhatKyViPham.cpp',
    'QuanLyViPham.cpp', 'QuanLyThuVien.cpp', 'TepHeThong.cpp', 'ThongKe.cpp'
)
if($KiemThu -and $KiemThuThongKe){
    throw 'Chi chon mot bo kiem thu moi lan.'
}
if($KiemThuThongKe){
    $tenNguon += 'tests/kiemThuThongKe.cpp'
    $tepChay = Join-Path $thuMucBuild 'kiemThuThongKe.exe'
}
elseif($KiemThu){
    $tenNguon += 'tests/kiemThuTichHop.cpp'
    $tepChay = Join-Path $thuMucBuild 'kiemThuTichHop.exe'
}
else{
    $tenNguon += @('Menu.cpp', 'main.cpp')
    $tepChay = Join-Path $thuMucBuild 'thuVien.exe'
}
$tepNguon = @()
foreach($ten in $tenNguon){
    $tep = Join-Path $gocDuAn $ten
    if(!(Test-Path -LiteralPath $tep -PathType Leaf)){
        throw "Thieu ma nguon: $ten"
    }
    $tepNguon += $tep
}
$ErrorActionPreference = 'Continue'
& g++ -std=c++17 -Wall -Wextra -Wpedantic @tepNguon -o $tepChay 2> (Join-Path $thuMucBuild 'bien_dich.log')
$maBienDich = $LASTEXITCODE
$ErrorActionPreference = 'Stop'
Get-Content -LiteralPath (Join-Path $thuMucBuild 'bien_dich.log')
if($maBienDich -ne 0){
    exit $maBienDich
}
Write-Host "Da bien dich: $tepChay"
if($KiemThu -or $KiemThuThongKe){
    & $tepChay
    exit $LASTEXITCODE
}
