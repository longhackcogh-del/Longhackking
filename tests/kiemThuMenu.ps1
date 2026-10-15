param([string]$TepChay = (Join-Path $PSScriptRoot '../build/verification/thuVien.exe'))

$ErrorActionPreference = 'Stop'
$tepChayDayDu = (Resolve-Path -LiteralPath $TepChay).Path
$thuMucGoc = Split-Path $PSScriptRoot -Parent
$thuMucThu = Join-Path $thuMucGoc 'build/verification/kiem_thu_menu'
New-Item -ItemType Directory -Path $thuMucThu -Force | Out-Null
$script:soKiemTraMenu = 0

function KiemTra($dieuKien, [string]$ten) {
    $script:soKiemTraMenu++
    if (-not $dieuKien) { throw "THAT BAI: $ten" }
}

function ChayMenu([string]$ten, [object[]]$cacDong) {
    $noiDung = ($cacDong | ForEach-Object { [string]$_ }) -join "`n"
    $noiDung | & $tepChayDayDu | Out-File -LiteralPath "$ten.txt" -Encoding utf8
    KiemTra ($LASTEXITCODE -eq 0) "Menu $ten ket thuc binh thuong"
    return Get-Content -LiteralPath "$ten.txt" -Raw -Encoding utf8
}

Push-Location $thuMucThu
try {
    $sach = @('S1', 'Lap trinh C++', 'NXB GD', 2020, 5, 5, 100000, 'Nguyen A', 'CNTT', 'ISBN', 100)
    $sachSua = @('S1', 'Lap trinh C++ moi', 'NXB GD', 2021, 5, 5, 120000, 'Nguyen A', 'CNTT', 'ISBN', 120)
    $sinhVien = @('N_D1', 'Nguyen Sinh Vien', '01/01/2004', 'sv@dh.edu', '0901234567', 'D1', 0, 1, 'SV1', 'CT01', 'CNTT', 'Phan mem')
    $giangVien = @('N_D2', 'Nguyen Giang Vien', '01/01/1980', 'gv@dh.edu', '0901234568', 'D2', 0, 1, 'GV1', 'CNTT', 'Tien si', 10)
    $nhanVien = @('N_NV1', 'Le Thu Thu', '01/01/1990', 'nv@dh.edu', '0901234560', 'NV1', 'Sang', 'Thu thu', 4000000, 1.5)
    $thuThu = @('N_TT1', 'Tran Thu Thu', '01/01/1975', 'tt@dh.edu', '0901234569', 'DG_TT1', 0, 1, 'GV_TT1', 'CNTT', 'Tien si', 20, 'TT1', 'Sang', 'Truong thu thu', 5000000, 2, 'Tang 1', 12, 2)
    $phieu = @('P1', 'D1', 'S1', '01/01/2024', '01/01/2024', 2)

    $cacDong = @(1, 1, 1) + $sach + @(2, 3, 'S1', 4, 'Lap', 5, 'S1') + $sachSua + @(7, 8, 9, 10, 11, 0)
    $cacDong += @(2, 1, 1) + $sinhVien + @(2, 3, 'D1', 4, 'Nguyen', 5, 'D1') + $sinhVien + @(7, 8, 0, 2) + $giangVien + @(9, 'D1', 2, 10, 11, 0)
    $cacDong += @(3, 1) + $nhanVien + @(2, 3, 'NV1', 4, 'Sang', 5, 'NV1') + $nhanVien + @(7, 8, 'NV1', 9, 10, 6, 'NV1', 0)
    $cacDong += @(4, 1) + $thuThu + @(2, 3, 'TT1', 4, 5, 6, 'TT1', 7, 8, 9, 'TT1', 0)
    $cacDong += @(5, 1) + $phieu + @(1) + $phieu + @(3, 4, 'P1', 5, 'D1', 6, 'S1', 7, 8, 'P1', '03/01/2024', 11, 9, 10, 2, 'P1', '03/01/2024', 2, 'P1', '03/01/2024', 9, 10, 0)
    $cacDong += @(6, 1, 'P1', 2, 3, 'D1', 4, 5, 'VP_P1', 5, 'VP_P1', 6, 7, 'D1', 8, 9, 0)
    $cacDong += @(4, 10, 'TT1', 'VP_P1', 9, 'TT1', 7, 0)
    $cacDong += @(7, 1, 2, 3, 4, 5, 6, 7, 0, 0)
    $ketQua = ChayMenu 'day_du' $cacDong
    KiemTra ($ketQua.Contains('Thoat chuong trinh.')) 'Thoat menu chinh'
    KiemTra ($ketQua.Contains('Lap trinh C++ moi')) 'Menu sua tai lieu'
    KiemTra ($ketQua.Contains('Tien phat du kien: 8000')) 'Menu tinh tien phat'
    KiemTra ($ketQua.Contains('Tien phat da thu: 8000')) 'Menu thanh toan phat'
    KiemTra ($ketQua.Contains('Nguoi duyet: TT1')) 'Menu duyet vi pham'
    KiemTra ($ketQua.Contains('Vi pham da duoc ghi khi tra tai lieu')) 'Menu chan ghi vi pham trung'
    KiemTra (-not $ketQua.Contains('Thao tac tep that bai')) 'Tat ca thao tac tep tren menu thanh cong'
    KiemTra ($ketQua.Contains('Thao tac that bai:')) 'Menu co tu choi phieu, tra va thanh toan trung'
    $nhatKy = Get-Content -LiteralPath data/NhatKyViPham.txt -Encoding utf8
    KiemTra ($nhatKy[1] -eq '1' -and $nhatKy[7] -eq '8000' -and $nhatKy[8] -eq '1' -and $nhatKy[9] -eq 'TT1') 'Tep luu dung phat, thanh toan va nguoi duyet'
    $taiLieu = Get-Content -LiteralPath data/Sach.txt -Encoding utf8
    KiemTra ($taiLieu[7] -eq '5') 'Ton kho duoc khoi phuc sau tra'
    $tepDuLieu = @(Get-ChildItem -LiteralPath data -Filter '*.txt')
    KiemTra ($tepDuLieu.Count -eq 9) 'Du chin tep'
    KiemTra ((Get-Content ket_qua_thuc_nghiem.csv).Count -eq 29) 'Thuc nghiem co 28 ket qua'

    $ketQua = ChayMenu 'so_sai' @('abc', '1abc', -1, 0)
    KiemTra ($ketQua.Contains('Nhap sai dinh dang so')) 'Tu choi chu thay so'
    KiemTra ($ketQua.Contains('Lua chon khong hop le.')) 'Tu choi lua chon am'
    $ketQua = ChayMenu 'eof' @(2, 1, 1, 'N_THIEU')
    KiemTra ($ketQua.Contains('Thao tac that bai:')) 'EOF giua nhap khong them doi tuong'

    $ketQua = ChayMenu 'xoa' @(1, 11, 6, 'S1', 2, 0, 2, 6, 'D1', 2, 10, 0, 0)
    KiemTra (-not $ketQua.Contains('Thao tac that bai:')) 'Xoa tai lieu va doc gia sau tra'
    $ketQua = ChayMenu 'doc_lich_su' @(1, 11, 2, 0, 5, 3, 0, 0)
    KiemTra (-not $ketQua.Contains('Thao tac tep that bai')) 'Doc lai lich su sau xoa'
    KiemTra ($ketQua.Contains('Ma phieu: P1')) 'Lich su phieu duoc giu'
}
finally {
    Pop-Location
}
Write-Output "Menu: $script:soKiemTraMenu kiem tra, loi: 0"
