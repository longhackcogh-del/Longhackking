param([switch]$KiemThu)

$ErrorActionPreference = 'Stop'
$thuMucGoc = $PSScriptRoot
$thuMucBuild = Join-Path $thuMucGoc 'build/verification'
New-Item -ItemType Directory -Path $thuMucBuild -Force | Out-Null

$tenNguon = @(
    'NhapXuat', 'TaiLieu', 'Sach', 'TapChi', 'Bao', 'QuanLyTaiLieu',
    'Nguoi', 'DocGia', 'SinhVien', 'GiangVien', 'NhanVienThuThu', 'ThuThuTruong',
    'PhieuMuon', 'NhatKyViPham', 'QuanLyDocGia', 'QuanLyNhanVien',
    'QuanLyThuThuTruong', 'QuanLyPhieuMuon', 'QuanLyViPham', 'QuanLyThuVien',
    'ThongKe', 'ThucNghiem'
)
$tepNguon = @($tenNguon | ForEach-Object { Join-Path $thuMucGoc ($_ + '.cpp') })
$tepDoiTuong = @($tenNguon | ForEach-Object { $_ + '.o' })
$tuyChon = @('-std=c++17', '-Wall', '-Wextra', '-Wpedantic', '-O2', '-I', $thuMucGoc)

Push-Location $thuMucBuild
try {
    & g++ @tuyChon -c @tepNguon
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich thu vien that bai' }
    & ar rcs libthuVien.a @tepDoiTuong
    if ($LASTEXITCODE -ne 0) { throw 'Tao thu vien that bai' }
    & g++ @tuyChon (Join-Path $thuMucGoc 'main.cpp') (Join-Path $thuMucGoc 'Menu.cpp') libthuVien.a -o thuVien.exe
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich menu that bai' }
    & g++ @tuyChon (Join-Path $thuMucGoc 'demoTaiLieu.cpp') (Join-Path $thuMucGoc 'Menu.cpp') libthuVien.a -o demoTaiLieu.exe
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich demo that bai' }
    & g++ @tuyChon (Join-Path $thuMucGoc 'tests/kiemThuTaiLieu.cpp') libthuVien.a -o kiemThuTaiLieu.exe
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich kiem thu tai lieu that bai' }
    & g++ @tuyChon (Join-Path $thuMucGoc 'tests/kiemThuThuVien.cpp') libthuVien.a -o kiemThuThuVien.exe
    if ($LASTEXITCODE -ne 0) { throw 'Bien dich kiem thu thu vien that bai' }
}
finally {
    Pop-Location
}

if ($KiemThu) {
    Push-Location $thuMucGoc
    try {
        & (Join-Path $thuMucBuild 'kiemThuTaiLieu.exe')
        if ($LASTEXITCODE -ne 0) { throw 'Kiem thu tai lieu that bai' }
        & (Join-Path $thuMucBuild 'kiemThuThuVien.exe')
        if ($LASTEXITCODE -ne 0) { throw 'Kiem thu thu vien that bai' }
        & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $thuMucGoc 'tests/kiemThuMenu.ps1')
        if ($LASTEXITCODE -ne 0) { throw 'Kiem thu menu that bai' }
    }
    finally {
        Pop-Location
    }
}
Write-Output "Bien dich thanh cong: $thuMucBuild/thuVien.exe"
