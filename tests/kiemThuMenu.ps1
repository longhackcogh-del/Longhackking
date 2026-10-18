$ErrorActionPreference = 'Stop'
$gocDuAn = Split-Path -Parent $PSScriptRoot
& powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $gocDuAn 'build.ps1')
if($LASTEXITCODE -ne 0){
    exit $LASTEXITCODE
}
$tepChay = Join-Path $gocDuAn 'build/tich-hop/thuVien.exe'
$thuMucChay = Join-Path $gocDuAn ('build/menu-kiemthu-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $thuMucChay | Out-Null
$script:soKiemTra = 0
$script:soLoi = 0

function KiemTra($dieuKien, $ten){
    $script:soKiemTra++
    if(!$dieuKien){
        $script:soLoi++
        Write-Host "THAT BAI: $ten"
    }
}

#=====chay executable ung dung that, tach biet du lieu nguoi dung=====
function ChayCa($ten, [string[]]$dong){
    $thuMucCa = Join-Path $thuMucChay $ten
    New-Item -ItemType Directory -Path $thuMucCa | Out-Null
    $dauVao = ($dong -join "`n") + "`n"
    Set-Content -LiteralPath (Join-Path $thuMucCa 'nhap.txt') -Value $dauVao -Encoding UTF8
    $tienTrinh = New-Object System.Diagnostics.Process
    $tienTrinh.StartInfo.FileName = $tepChay
    $tienTrinh.StartInfo.WorkingDirectory = $thuMucCa
    $tienTrinh.StartInfo.UseShellExecute = $false
    $tienTrinh.StartInfo.CreateNoWindow = $true
    $tienTrinh.StartInfo.RedirectStandardInput = $true
    $tienTrinh.StartInfo.RedirectStandardOutput = $true
    $tienTrinh.StartInfo.RedirectStandardError = $true
    [void]$tienTrinh.Start()
    $docXuat = $tienTrinh.StandardOutput.ReadToEndAsync()
    $docLoi = $tienTrinh.StandardError.ReadToEndAsync()
    $tienTrinh.StandardInput.Write($dauVao)
    $tienTrinh.StandardInput.Close()
    if(!$tienTrinh.WaitForExit(15000)){
        $tienTrinh.Kill()
        throw "Ung dung bi treo o ca $ten"
    }
    $xuat = $docXuat.GetAwaiter().GetResult()
    $loi = $docLoi.GetAwaiter().GetResult()
    KiemTra ($tienTrinh.ExitCode -eq 0) "$ten : ma thoat"
    KiemTra ($loi.Length -eq 0) "$ten : khong co stderr"
    $tienTrinh.Dispose()
    # Chi co nhap.txt truoc khi ghi ket qua: ung dung khong tu luu du lieu.
    KiemTra (@(Get-ChildItem -LiteralPath $thuMucCa -Force).Count -eq 1) "$ten : khong tu tao tep du lieu"
    Set-Content -LiteralPath (Join-Path $thuMucCa 'xuat.txt') -Value $xuat -Encoding UTF8
    Set-Content -LiteralPath (Join-Path $thuMucCa 'loi.txt') -Value $loi -Encoding UTF8
    return $xuat
}

function Sach($ma = 'S01', $ten = 'Lap trinh', $tong = '3', $con = '3'){
    return @($ma, $ten, 'NXB DH', '2022', $tong, $con, '120000', 'Nguyen Van A', 'Tin hoc', 'ISBN01', '100')
}

function SinhVien($ma = 'DG01', $ten = 'Nguyen Van An', $soMuon = '0', $hoatDong = '1'){
    return @(('N_' + $ma), $ten, '01/01/2004', 'an@dh.edu', '0901234567', $ma,
             $soMuon, $hoatDong, ('SV_' + $ma), 'CT1', 'CNTT', 'Phan mem')
}

function GiangVien{
    return @('N_DG02', 'Tran Van Binh', '01/01/1980', 'binh@dh.edu', '0901234568',
             'DG02', '0', '1', 'GV02', 'CNTT', 'Tien si', '10')
}

function NhanVien($ten = 'Le Thi Hoa'){
    return @('N_NV01', $ten, '01/01/1990', 'hoa@dh.edu', '0901234569', 'NV01', 'Sang', 'Thu thu', '5000000', '2')
}

function ThuThu($ten = 'Tran Thi Thu', $soMuon = '0'){
    return @('N_TT', $ten, '01/01/1980', 'thu@dh.edu', '0901234568', 'DG_TT', $soMuon, '1',
             'GV_TT', 'CNTT', 'Tien si', '10', 'TT01', 'Sang', 'Truong', '5000000', '2', 'Tang 1', '12', '1')
}

#=====dieu huong va dau vao sai=====
$dong = @('abc', '99')
foreach($i in 1..7){
    $dong += @("$i", 'abc', '99', '0')
}
$dong += @('8', '9', '10', '11')
$xuat = ChayCa 'dieu-huong' $dong
KiemTra ($xuat.Contains('HE THONG QUAN LY THU VIEN')) 'tieu de menu chinh'
KiemTra ([regex]::Matches($xuat, 'Nhap sai dinh dang so').Count -eq 8) 'nhap chu o menu chinh va bay menu con'
KiemTra ([regex]::Matches($xuat, 'Lua chon khong hop le').Count -eq 8) 'lua chon ngoai pham vi'
KiemTra ([regex]::Matches($xuat, 'Chua trien khai trong giai doan 1').Count -eq 3) 'ba muc chua trien khai duoc bao ro'
KiemTra ($xuat.Contains('Thoat chuong trinh. Khong tu dong luu du lieu.')) 'thoat bang 11'
foreach($i in 0..7){
    if($i -eq 0){
        $dong = @()
    }
    else{
        $dong = @("$i")
    }
    $xuat = ChayCa "het-dau-vao-$i" $dong
    KiemTra ($xuat.Contains('HE THONG QUAN LY THU VIEN')) "EOF menu $i ket thuc an toan"
}

#=====muon tra va vi pham qua menu that=====
$dong = @('1', '1', '1') + (Sach)
$dong += @('1', '2', 'T01', 'Tap chi khoa hoc', 'NXB DH', '2024', '2', '2', '40000', '1', '1', 'Khoa hoc')
$dong += @('1', '3', 'B01', 'Bao dai hoc', 'NXB DH', '2023', '4', '4', '10000', '01/01/2026', 'Ngay')
$dong += @('2', '3', 'S01', '4', 'Lap', '7', '8', '9', '0', '2', '1', '1') + (SinhVien)
$dong += @('1', '2') + (GiangVien)
$dong += @('2', '3', 'DG01', '4', 'Nguyen', '7', '9', 'DG01', '1', '0', '3', '1') + (NhanVien)
$dong += @('2', '3', 'NV01', '4', 'Sang', '7', '8', 'NV01', '0', '4', '1') + (ThuThu)
$dong += @('2', '3', 'TT01', '4', '5', '6', 'TT01', '0')
$dong += @('5', '1', 'P01', 'DG01', 'S01', '01/01/2026', '03/01/2026', '1', '3', '0')
$dong += @('1', '3', 'S01', '0', '2', '3', 'DG01', '0')
$dong += @('5', '2', 'P01', '03/01/2026', '1', 'P02', 'DG01', 'T01', '01/01/2026', '03/01/2026', '1')
$dong += @('8', 'P02', '05/01/2026', '2', 'P02', '05/01/2026')
$dong += @('1', 'P03', 'DG02', 'B01', '01/01/2026', '03/01/2026', '1', '2', 'P03', '04/01/2026')
$dong += @('1', 'P04', 'DG_TT', 'S01', '01/01/2026', '03/01/2026', '1', '0', '4', '3', 'TT01', '0')
$dong += @('5', '2', 'P04', '05/01/2026', '4', 'P02', '5', 'DG01', '6', 'S01', '7', '9', '0')
$dong += @('4', '9', 'TT01', '10', 'TT01', 'VP_P02', '0')
$dong += @('6', '2', '3', 'DG01', '4', '8', 'VP_P03', 'TT01', '8', 'VP_P04', 'TT01')
$dong += @('5', 'VP_P02', '6', '7', 'DG01', '9', 'VP_P02', '0')
$dong += @('1', '9', '0', '2', '2', '0', '4', '3', 'TT01', '0')
$dong += @('7', '1', 'S01', '2', 'DG01', '3', '4', '5', '6', '0', '11')
$xuat = ChayCa 'nghiep-vu' $dong
KiemTra (!$xuat.Contains('Thao tac that bai')) 'luong hop le khong co thao tac that bai'
foreach($chuoi in @('Ten tai lieu: Lap trinh', 'Loai: TapChi', 'Loai: Bao', 'Ho ten: Nguyen Van An',
                    'Ho ten: Tran Van Binh', 'Ho ten: Le Thi Hoa', 'Ho ten: Tran Thi Thu',
                    'Luong co ban: 5000000', 'He so luong: 2',
                    'Luong: 10000000', 'Thu nhap: 12000000', 'So luong con/tong: 2/3',
                    'So dang muon: 1', 'Tien phat du kien: 6000', 'Tien phat: 6000',
                    'Tien phat: 1000', 'Tien phat: 4000', 'Da tu dong ghi vi pham VP_P02.',
                    'Nguoi duyet: TT01', 'Da thanh toan', 'Da thu: 6000', 'Chua thu: 5000',
                    'So luong con/tong: 3/3', 'So luong con/tong: 2/2', 'So luong con/tong: 4/4')){
    KiemTra ($xuat.Contains($chuoi)) "luong nghiep vu : $chuoi"
}
KiemTra ($xuat -match '(?s)Ma phieu: P01.*?Ngay tra: 03/01/2026.*?Tien phat: 0') 'tra dung han khong phat'
KiemTra ($xuat -match '(?s)Ma doc gia: DG_TT\r?\nSo dang muon: 1') 'thu thu dong bo sau muon qua menu'
KiemTra ($xuat -match '(?s)Ma doc gia: DG_TT\r?\nSo dang muon: 0') 'thu thu dong bo sau tra qua menu'

#=====them sua xoa va chen qua menu=====
$dong = @('1', '1', '1') + (Sach)
$dong += @('5', 'S01') + (Sach 'S01' 'Lap trinh moi')
$dong += @('3', 'S01', '6', 'S01', '2', '0', '2', '1', '1') + (SinhVien)
$dong += @('5', 'DG01') + (SinhVien 'DG01' 'Nguyen Van An Moi')
$dong += @('3', 'DG01', '8', '0', '1') + (SinhVien 'DG03' 'Sinh vien chen')
$dong += @('2', '6', 'DG01', '6', 'DG03', '2', '0', '3', '1') + (NhanVien)
$dong += @('5', 'NV01') + (NhanVien 'Le Thi Hoa Moi')
$dong += @('3', 'NV01', '6', 'NV01', '2', '0', '4', '1') + (ThuThu)
$dong += @('7', 'TT01') + (ThuThu 'Tran Thi Thu Moi')
$dong += @('3', 'TT01', '0', '2', '3', 'DG_TT', '0', '4', '8', 'TT01', '2', '0')
$dong += @('2', '3', 'DG_TT', '6', 'DG_TT', '2', '0', '11')
$xuat = ChayCa 'cap-nhat-xoa-chen' $dong
KiemTra (!$xuat.Contains('Thao tac that bai')) 'CRUD hop le khong that bai'
foreach($chuoi in @('Ten tai lieu: Lap trinh moi', 'Ho ten: Nguyen Van An Moi',
                    'Ho ten: Sinh vien chen', 'Ho ten: Le Thi Hoa Moi', 'Ho ten: Tran Thi Thu Moi')){
    KiemTra ($xuat.Contains($chuoi)) "CRUD : $chuoi"
}
KiemTra ([regex]::Matches($xuat, 'Ho ten: Tran Thi Thu Moi').Count -ge 3) 'sua thu thu dong bo sang doc gia'
KiemTra ([regex]::Matches($xuat, 'Danh sach rong').Count -ge 5) 'xoa dung cac danh sach'

#=====loi nghiep vu khong lam sai du lieu=====
$dong = @('1', '1', '1') + (Sach)
$dong += @('1', '1') + (Sach)
$dong += @('0', '2', '1', '1') + (SinhVien)
$dong += @('0', '5', '1', 'P01', 'DG01', 'S01', '01/01/2026', '03/01/2026', '1')
$dong += @('1', 'P01', 'DG01', 'S01', '01/01/2026', '03/01/2026', '1')
$dong += @('1', 'P_X', 'DG01', 'S01', '01/01/2026', '03/01/2026', '6')
$dong += @('2', 'P01', '31/02/2026', '0', '1', '6', 'S01', '0', '2', '6', 'DG01', '0')
$dong += @('5', '2', 'P01', '05/01/2026', '2', 'P01', '05/01/2026', '0')
$dong += @('6', '1', 'P01', '8', 'VP_P01', 'KHONGCO', '5', 'VP_P01', '5', 'VP_P01', '2', '6', '0')
$dong += @('1', '3', 'S01', '0', '2', '3', 'DG01', '0', '11')
$xuat = ChayCa 'loi-nghiep-vu' $dong
KiemTra ([regex]::Matches($xuat, 'Thao tac that bai').Count -eq 10) 'tu choi dung muoi thao tac sai'
KiemTra ($xuat.Contains('So luong con/tong: 3/3')) 'loi khong lam sai ton kho sau tra'
KiemTra ($xuat -match 'Ma doc gia: DG01\r?\nSo dang muon: 0') 'loi khong lam sai so muon sau tra'
KiemTra ($xuat.Contains('Da thu: 4000')) 'khong thu tien phat hai lan'
KiemTra ($xuat.Contains('Chua thu: 0')) 'khong tao vi pham trung'

#=====dinh dang tien khong phu thuoc thu tu vao menu=====
$dong = @('3', '1') + (NhanVien)
$dong += @('2', '8', 'NV01', '0', '4', '1') + (ThuThu)
$dong += @('2', '6', 'TT01', '0', '1', '1', '1') + (Sach)
$dong += @('2', '0', '3', '8', 'NV01', '0', '4', '6', 'TT01', '0', '11')
$xuat = ChayCa 'tien-truoc-sau-tai-lieu' $dong
KiemTra (!$xuat.Contains('Thao tac that bai')) 'tien : tao ho so hop le'
KiemTra ([regex]::Matches($xuat, 'Luong: 10000000\r?\n').Count -eq 2) 'tien : luong truoc va sau xuat tai lieu'
KiemTra ([regex]::Matches($xuat, 'Thu nhap: 12000000\r?\n').Count -eq 2) 'tien : thu nhap truoc va sau xuat tai lieu'
KiemTra ([regex]::Matches($xuat, 'Luong co ban: 5000000\r?\n').Count -eq 2) 'tien : luong co ban hai vai tro'
KiemTra ($xuat.Contains('Gia tri: 120000')) 'tien : gia tri tai lieu'
KiemTra (!($xuat -match '(?:Gia tri|Luong co ban|Luong|Thu nhap): [^\r\n]*[eE][+-]')) 'tien : khong co ky hieu khoa hoc'

$dong = @('1', '1', '1') + (Sach)
$dong += @('0', '2', '1', '1') + (SinhVien)
$dong += @('0', '4', '1') + (ThuThu)
$dong += @('0', '5', '1', 'P_LON', 'DG01', 'S01', '01/01/2000', '01/01/2000', '1')
$dong += @('8', 'P_LON', '01/01/2020', '2', 'P_LON', '01/01/2020', '8', 'P_LON', '0')
$dong += @('6', '2', '6', '8', 'VP_P_LON', 'TT01', '5', 'VP_P_LON', '6', '9', 'VP_P_LON', '0', '11')
$xuat = ChayCa 'tien-phat-lon' $dong
KiemTra (!$xuat.Contains('Thao tac that bai')) 'tien phat lon : cac thao tac hop le'
foreach($chuoi in @('Tien phat du kien: 14610000', 'Tien phat da chot: 14610000',
                    'Tien phat: 14610000', 'Chua thu: 14610000', 'Da thu: 14610000',
                    'Nguoi duyet: TT01', 'Da thanh toan')){
    KiemTra ($xuat.Contains($chuoi)) "tien phat lon : $chuoi"
}
KiemTra (!($xuat -match '(?:Tien phat|Tien phat du kien|Tien phat da chot|Da thu|Chua thu): [^\r\n]*[eE][+-]')) 'tien phat lon : khong co ky hieu khoa hoc'

#=====chuyen vai tro nhan su qua menu that=====
$hoSoTT = @(ThuThu)
$hoSoNV = @($hoSoTT[0..4]) + @($hoSoTT[12..16])
$dong = @('3', '1') + $hoSoNV
$dong += @('9', 'TT01') + $hoSoTT
$dong += @('2', '0', '4', '2', '11', 'TT01', '2', '0', '3', '2', '0', '2', '3', 'DG_TT', '0', '11')
$xuat = ChayCa 'chuyen-vai-tro-co-ban' $dong
KiemTra (!$xuat.Contains('Thao tac that bai')) 'chuyen vai tro : thanh cong hai chieu'
KiemTra ([regex]::Matches($xuat, 'Danh sach rong').Count -eq 2) 'chuyen vai tro : khong luu ban sao nhan su o danh sach cu'
KiemTra ($xuat.Contains('Ma doc gia: DG_TT') -and $xuat.Contains('Ma nhan vien: TT01')) 'chuyen vai tro : giu ma doc gia va nhan vien'

$dong = @('3', '1') + $hoSoNV
$dong += @('0', '2', '1', '2') + @($hoSoTT[0..11])
$dong += @('0', '1', '1', '1') + (Sach)
$dong += @('0', '5', '1', 'P_CT1', 'DG_TT', 'S01', '01/01/2026', '03/01/2026', '1', '0', '3', '9', 'TT01')
$dong += @(ThuThu 'Tran Thi Thu' '1')
$dong += @('0', '4', '3', 'TT01', '0', '5', '2', 'P_CT1', '05/01/2026', '0')
$dong += @('4', '10', 'TT01', 'VP_P_CT1', '0')
$dong += @('5', '1', 'P_CT2', 'DG_TT', 'S01', '01/01/2026', '03/01/2026', '1', '0')
$dong += @('4', '11', 'TT01', '0', '5', '2', 'P_CT2', '05/01/2026', '0')
$dong += @('6', '8', 'VP_P_CT2', 'TT01', '9', 'VP_P_CT1', '9', 'VP_P_CT2', '0')
$dong += @('3', '9', 'TT01') + $hoSoTT
$dong += @('0', '6', '8', 'VP_P_CT2', 'TT01', '9', 'VP_P_CT2', '0', '2', '3', 'DG_TT', '0', '1', '3', 'S01', '0', '11')
$xuat = ChayCa 'chuyen-vai-tro-muon-tra-duyet' $dong
KiemTra ([regex]::Matches($xuat, 'Thao tac that bai').Count -eq 1) 'chuyen dang muon : chi tu choi duyet khi khong con la truong'
KiemTra ($xuat -match 'Ma doc gia: DG_TT\r?\nSo dang muon: 1') 'chuyen dang muon : giu so muon'
KiemTra ($xuat -match 'Ma doc gia: DG_TT\r?\nSo dang muon: 0') 'chuyen dang muon : tra het cap nhat so muon'
KiemTra ($xuat.Contains('So luong con/tong: 3/3')) 'chuyen dang muon : ton kho duoc phuc hoi'
KiemTra ($xuat -match '(?s)Ma vi pham: VP_P_CT1\r?\n.*?Nguoi duyet: TT01') 'chuyen dang muon : giu nguoi duyet cu'
KiemTra ($xuat -match '(?s)Ma vi pham: VP_P_CT2\r?\n.*?Nguoi duyet: -') 'chuyen dang muon : vi pham moi chua duoc duyet khi mat vai tro'
KiemTra ($xuat -match '(?s)Ma vi pham: VP_P_CT2\r?\n.*?Nguoi duyet: TT01') 'chuyen dang muon : duyet duoc sau khi gan lai vai tro'

#=====trung ma cheo va trung ma nguoi khong duoc tao ho so mau thuan=====
$trungMa = @(NhanVien)
$trungMa[5] = 'TT01'
$trungNguoi = @($hoSoNV)
$trungNguoi[5] = 'NV_KHAC'
$dong = @('4', '1') + $hoSoTT
$dong += @('0', '3', '1') + $trungMa
$dong += @('1') + $trungNguoi
$dong += @('2', '0', '4', '3', 'TT01', '0', '11')
$xuat = ChayCa 'trung-ma-nhan-su-cheo' $dong
KiemTra ([regex]::Matches($xuat, 'Thao tac that bai').Count -eq 2) 'nhan su : tu choi trung ma nhan vien va trung nguoi cheo danh sach'
KiemTra ($xuat.Contains('Danh sach rong')) 'nhan su : khong de lai nhan vien thuong trung voi truong'
KiemTra ($xuat.Contains('Ho ten: Tran Thi Thu')) 'nhan su : ho so truong goc van giu nguyen'

$ketQua = "Kiem tra menu: $script:soKiemTra, loi: $script:soLoi"
Write-Host $ketQua
Set-Content -LiteralPath (Join-Path $thuMucChay 'ket_qua.txt') -Value $ketQua -Encoding UTF8
Write-Host "Dau vao va dau ra thuc te: $thuMucChay"
if($script:soLoi -gt 0){
    exit 1
}
exit 0
