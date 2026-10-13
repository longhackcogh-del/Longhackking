param([string]$TepChay = (Join-Path $PSScriptRoot '../build/demoTaiLieu.exe'))
$ErrorActionPreference = 'Stop'
$tepChayDayDu = (Resolve-Path -LiteralPath $TepChay).Path
$thuMucGoc = Split-Path $PSScriptRoot -Parent
$thuMucThu = Join-Path $thuMucGoc 'build/kiem_thu_menu_tai_lieu'
New-Item -ItemType Directory -Path $thuMucThu -Force | Out-Null
$script:soKiemTra = 0

function KiemTra($dieuKien, [string]$ten) {
    $script:soKiemTra++
    if (-not $dieuKien) { throw "THAT BAI: $ten" }
}

function Chay([string]$ten, [object[]]$cacDong) {
    (($cacDong | ForEach-Object { [string]$_ }) -join "`n") | & $tepChayDayDu | Out-File -LiteralPath "$ten.txt" -Encoding utf8
    KiemTra ($LASTEXITCODE -eq 0) "$ten ket thuc binh thuong"
    return Get-Content -LiteralPath "$ten.txt" -Raw -Encoding utf8
}

Push-Location $thuMucThu
try {
    $sach = @('S1','Lap trinh C++','NXB GD',2020,5,5,125000.125,'Nguyen A','CNTT','ISBN',100)
    $tapChi = @('T1','Khoa hoc','NXB',2018,2,2,30000,1,12,'Ky thuat')
    $bao = @('B1','Tin tuc','NXB',2024,3,3,10000,'29/02/2024','Ngay')
    $sua = @('S1','Lap trinh C++ moi','NXB GD',2021,6,6,125000.125,'Nguyen A','CNTT','ISBN',120)
    $dong = @(1,1) + $sach + @(1,2) + $tapChi + @(1,3) + $bao
    $dong += @(1,1) + $sach
    $dong += @(2,3,'S1',3,'KHONG',4,'Lap',5,'S1') + $sua
    $dong += @(7,8,9,10,11,2,6,'B1',2,10,11,2,0)
    $kq = Chay 'day_du' $dong
    KiemTra ($kq.Contains('Thao tac that bai:')) 'Tu choi ma trung'
    KiemTra ($kq.Contains('Khong tim thay.')) 'Tim ma khong ton tai'
    KiemTra ($kq.Contains('Lap trinh C++ moi')) 'Sua thong tin'
    KiemTra ($kq.Contains('So ket qua: 1')) 'So ket qua tim ten ro rang'
    KiemTra ($kq.Contains('Gia tri: 125000.125')) 'Xuat gia khong mat phan thap phan'
    KiemTra (-not $kq.Contains('Thao tac file that bai:')) 'Luu doc ba tep'
    $sauLuu = Get-Content data/Sach.txt -Encoding utf8
    KiemTra ($sauLuu[2] -eq 'S1' -and $sauLuu[3] -eq 'Lap trinh C++ moi' -and $sauLuu[8] -eq '125000.125') 'Tep luu dung ma, ten va gia'
    KiemTra ((Get-Content data/Bao.txt -Encoding utf8)[1] -eq '0') 'Xoa bao duoc luu'
    KiemTra (@(Get-ChildItem data -Filter '*.txt').Count -eq 3) 'Chi luu ba tep phan 1'

    $kq = Chay 'so_sai' @('abc','1abc','2147483648','',-1,0)
    KiemTra ($kq.Contains('Nhap sai dinh dang so')) 'Chu, ky tu du, so tran va rong bi tu choi'
    KiemTra ($kq.Contains('Lua chon khong hop le.')) 'Lua chon am bi tu choi'
    $kq = Chay 'nhap_so_lai' (@(1,1,'S2','Ten co khoang trang','NXB','abc','2147483648',2024,1,1,'nan','inf','1e309',2.5,'A','B','C',10,2,0))
    KiemTra ($kq.Contains('Ma tai lieu: S2')) 'Nhap lai so sai van them duoc'
    KiemTra ($kq.Contains('Gia tri: 2.5')) 'Gia sau nhap lai dung'

    foreach ($nam in @(0,10000)) {
        $kq = Chay "nam_$nam" @(1,1,'SAI','Ten','NXB',$nam,1,1,1,2,0)
        KiemTra ($kq.Contains('Thao tac that bai:') -and -not $kq.Contains('Ma tai lieu: SAI')) 'Tu choi nam sai'
    }
    foreach ($ton in @(@(-1,0),@(1,-1),@(1,2))) {
        $kq = Chay "ton_$($ton[0])_$($ton[1])" @(1,1,'SAI','Ten','NXB',2024,$ton[0],$ton[1],1,2,0)
        KiemTra ($kq.Contains('Thao tac that bai:') -and -not $kq.Contains('Ma tai lieu: SAI')) 'Tu choi ton kho sai'
    }
    $kq = Chay 'gia_am' @(1,1,'SAI','Ten','NXB',2024,1,1,-1,2,0)
    KiemTra ($kq.Contains('Thao tac that bai:') -and -not $kq.Contains('Ma tai lieu: SAI')) 'Tu choi gia am'
    $kq = Chay 'trang_0' @(1,1,'SAI','Ten','NXB',2024,1,1,1,'A','B','C',0,2,0)
    KiemTra ($kq.Contains('Thao tac that bai:') -and -not $kq.Contains('Ma tai lieu: SAI')) 'Tu choi so trang 0'
    foreach ($thang in @(0,13)) {
        $kq = Chay "thang_$thang" @(1,2,'SAI','Ten','NXB',2024,1,1,1,1,$thang,'Khoa hoc',2,0)
        KiemTra ($kq.Contains('Thao tac that bai:') -and -not $kq.Contains('Ma tai lieu: SAI')) 'Tu choi thang sai'
    }
    $kq = Chay 'ngay_sai' @(1,3,'SAI','Ten','NXB',2023,1,1,1,'29/02/2023','Ngay',2,0)
    KiemTra ($kq.Contains('Thao tac that bai:') -and -not $kq.Contains('Ma tai lieu: SAI')) 'Tu choi ngay sai'
    $kq = Chay 'chuoi_rong' @(1,1,'   ',2,0)
    KiemTra ($kq.Contains('Thao tac that bai:') -and $kq.Contains('Danh sach rong')) 'Tu choi ma toan khoang trang'
    $kq = Chay 'eof' @(1,1,'THIEU')
    KiemTra ($kq.Contains('Thao tac that bai:')) 'EOF giua nhap khong them doi tuong'
    $kq = Chay 'sua_sai' (@(1,1) + $sach + @(5,'S1','S1','Ten sai','NXB',2024,1,1,1,'A','B','C',0,2,0))
    KiemTra ($kq.Contains('Ten tai lieu: Lap trinh C++') -and -not $kq.Contains('Ten tai lieu: Ten sai')) 'Nhap sua sai giu doi tuong cu'
    $kq = Chay 'rong' @(2,3,'X',4,'X',6,'X',7,8,9,0)
    KiemTra ($kq.Contains('Danh sach rong') -and $kq.Contains('So ket qua: 0')) 'Danh sach rong van tim sap xep duoc'

    'du lieu hong' | Set-Content data/Bao.txt -Encoding ascii
    $kq = Chay 'doc_hong' (@(1,1) + $sach + @(11,2,0))
    KiemTra ($kq.Contains('Thao tac file that bai:') -and $kq.Contains('Ma tai lieu: S1')) 'Doc tep hong giu danh sach'
    Copy-Item -Path (Join-Path $thuMucGoc 'data_mau/*.txt') -Destination data
    $kq = Chay 'doc_mau' @(11,2,9,0)
    KiemTra ($kq.Contains('Ma tai lieu: S1') -and $kq.Contains('Ma tai lieu: T1') -and $kq.Contains('Ma tai lieu: B1')) 'Doc mau du ba loai'
    KiemTra (-not $kq.Contains('Thao tac file that bai:')) 'Du lieu mau doc duoc'
}
finally { Pop-Location }
Write-Output "Menu tai lieu: $script:soKiemTra kiem tra, loi: 0"
