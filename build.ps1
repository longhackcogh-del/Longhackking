param([switch]$KiemThu)
$ErrorActionPreference = 'Stop'
$thuMucGoc = $PSScriptRoot
$thuMucBuild = Join-Path $thuMucGoc 'build'
New-Item -ItemType Directory -Path $thuMucBuild -Force | Out-Null
$tenNguon = @('NhapXuat','TaiLieu','Sach','TapChi','Bao','QuanLyTaiLieu')
$tepNguon = @($tenNguon | ForEach-Object { Join-Path $thuMucGoc ($_ + '.cpp') })
$tepDoiTuong = @($tenNguon | ForEach-Object { $_ + '.o' })
$tuyChon = @('-std=c++17','-Wall','-Wextra','-Wpedantic','-O2','-I',$thuMucGoc)
Push-Location $thuMucBuild
try {
    & g++ @tuyChon -c @tepNguon
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich module that bai' }
    & ar rcs libtaiLieu.a @tepDoiTuong
    if ($LASTEXITCODE -ne 0) { throw 'Tao thu vien that bai' }
    & g++ @tuyChon (Join-Path $thuMucGoc 'demoTaiLieu.cpp') libtaiLieu.a -o demoTaiLieu.exe
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich demo that bai' }
    & g++ @tuyChon (Join-Path $thuMucGoc 'tests/kiemThuTaiLieu.cpp') libtaiLieu.a -o kiemThuTaiLieu.exe
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich kiem thu that bai' }
}
finally { Pop-Location }
if ($KiemThu) {
    Push-Location $thuMucGoc
    try {
        & (Join-Path $thuMucBuild 'kiemThuTaiLieu.exe')
        if ($LASTEXITCODE -ne 0) { throw 'Kiem thu module that bai' }
        & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $thuMucGoc 'tests/kiemThuMenuTaiLieu.ps1') -TepChay (Join-Path $thuMucBuild 'demoTaiLieu.exe')
        if ($LASTEXITCODE -ne 0) { throw 'Kiem thu menu that bai' }
    }
    finally { Pop-Location }
}
Write-Output "Bien dich thanh cong: $thuMucBuild/demoTaiLieu.exe"
