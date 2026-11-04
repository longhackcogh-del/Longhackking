$ErrorActionPreference = 'Stop'
$gocDuAn = Split-Path -Parent $PSScriptRoot
$thuMucChay = Join-Path $gocDuAn ('build/tep-he-thong-kiemthu-' + [Guid]::NewGuid().ToString('N'))
$thuMucDuLieu = Join-Path $thuMucChay 'du_lieu'
$tepChay = Join-Path $thuMucChay 'kiemThuTepHeThong.exe'
$tenNguon = @(
    'Nguoi.cpp', 'DocGia.cpp', 'SinhVien.cpp', 'GiangVien.cpp',
    'NhanVienThuThu.cpp', 'ThuThuTruong.cpp', 'QuanLyDocGia.cpp',
    'QuanLyNhanVien.cpp', 'QuanLyThuThuTruong.cpp', 'NhapXuat.cpp',
    'TaiLieu.cpp', 'Sach.cpp', 'TapChi.cpp', 'Bao.cpp', 'QuanLyTaiLieu.cpp',
    'PhieuMuon.cpp', 'QuanLyPhieuMuon.cpp', 'NhatKyViPham.cpp',
    'QuanLyViPham.cpp', 'QuanLyThuVien.cpp', 'TepHeThong.cpp', 'tests/kiemThuTepHeThong.cpp'
)
$tepNguon = @()
foreach($ten in $tenNguon){
    $tep = Join-Path $gocDuAn $ten
    if(!(Test-Path -LiteralPath $tep -PathType Leaf)){
        throw "Thieu ma nguon: $ten"
    }
    $tepNguon += $tep
}
Get-Command g++ -ErrorAction Stop | Out-Null
New-Item -ItemType Directory -Path $thuMucDuLieu | Out-Null

#=====luu dau van tay ma nguon de doi chieu lan chay=====
$tepCanDoiChieu = @(Get-ChildItem -LiteralPath $gocDuAn -File | Where-Object { $_.Extension -in '.cpp', '.h' })
$tepCanDoiChieu += @(Get-ChildItem -LiteralPath $PSScriptRoot -File | Where-Object { $_.Extension -in '.cpp', '.h', '.ps1' })
$truoc = @($tepCanDoiChieu | Get-FileHash -Algorithm SHA256)
$truoc | Export-Csv -LiteralPath (Join-Path $thuMucChay 'ma_nguon.csv') -NoTypeInformation

#=====bien dich va chay kiem thu=====
# Giu ma thoat cua g++ va chuong trinh khi PowerShell 5 nhan stderr.
$cheDoLoi = $ErrorActionPreference
$ErrorActionPreference = 'Continue'
& g++ -std=c++17 -Wall -Wextra -Wpedantic -g -D_GLIBCXX_ASSERTIONS @tepNguon -o $tepChay 2> (Join-Path $thuMucChay 'bien_dich.log')
$maBienDich = $LASTEXITCODE
$ErrorActionPreference = $cheDoLoi
Get-Content -LiteralPath (Join-Path $thuMucChay 'bien_dich.log')
if($maBienDich -ne 0){
    Write-Host "Bien dich that bai. Ket qua: $thuMucChay"
    exit $maBienDich
}
$ErrorActionPreference = 'Continue'
& $tepChay $thuMucDuLieu (Join-Path $gocDuAn 'data_tich_hop_mau') 2> (Join-Path $thuMucChay 'loi_kiem_thu.log') | Tee-Object -FilePath (Join-Path $thuMucChay 'ket_qua.txt')
$maKetQua = $LASTEXITCODE
$ErrorActionPreference = $cheDoLoi
Get-Content -LiteralPath (Join-Path $thuMucChay 'loi_kiem_thu.log')
foreach($moc in $truoc){
    if((Get-FileHash -LiteralPath $moc.Path -Algorithm SHA256).Hash -ne $moc.Hash){
        Write-Error "Ma nguon thay doi trong luc kiem thu: $($moc.Path)"
        exit 3
    }
}
Write-Host "Ket qua va dau van tay ma nguon: $thuMucChay"
exit $maKetQua
