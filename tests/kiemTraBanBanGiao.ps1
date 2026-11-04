# Kiem tra ban sao nguon khong co .git, build cu hoac file ca nhan.
$ErrorActionPreference = 'Stop'
$gocDuAn = Split-Path -Parent $PSScriptRoot
$thuMucChay = Join-Path $gocDuAn ('build/ban-giao-' + [Guid]::NewGuid().ToString('N'))
$banSao = Join-Path $thuMucChay 'ThuVien'
New-Item -ItemType Directory -Path $banSao | Out-Null

#=====chep dung nguon, du lieu mau va huong dan=====
$tepNguon = @(Get-ChildItem -LiteralPath $gocDuAn -File | Where-Object {
    $_.Extension -in '.h', '.cpp'
})
$tepNguon += @(Get-Item -LiteralPath (Join-Path $gocDuAn 'build.ps1'),
    (Join-Path $gocDuAn 'README.md'), (Join-Path $gocDuAn '.gitignore'),
    (Join-Path $gocDuAn 'BaiTapLon_GiaoVien.docx.docx'),
    (Join-Path $gocDuAn 'DacTaChiTiet_Bai1.docx.docx'))
foreach($tep in $tepNguon){
    Copy-Item -LiteralPath $tep.FullName -Destination (Join-Path $banSao $tep.Name)
}
foreach($ten in @('tests', 'data_mau', 'data_tich_hop_mau', 'ket_qua_thuc_nghiem')){
    $dich = Join-Path $banSao $ten
    New-Item -ItemType Directory -Path $dich | Out-Null
    foreach($tep in @(Get-ChildItem -LiteralPath (Join-Path $gocDuAn $ten) -File)){
        $duoiChoPhep = @('.cpp', '.h', '.ps1', '.txt', '.csv')
        if($tep.Extension -in $duoiChoPhep){
            Copy-Item -LiteralPath $tep.FullName -Destination (Join-Path $dich $tep.Name)
        }
    }
}
$docs = Join-Path $banSao 'docs'
New-Item -ItemType Directory -Path $docs | Out-Null
Copy-Item -LiteralPath (Join-Path $gocDuAn 'docs/phancode1.cpp') -Destination $docs

#=====doi chieu ban sao voi tep goc, truoc khi tao executable=====
$dauVanTay = @()
foreach($tep in @(Get-ChildItem -LiteralPath $banSao -File -Recurse -Force)){
    $tuongDoi = $tep.FullName.Substring($banSao.Length + 1)
    $hash = (Get-FileHash -LiteralPath $tep.FullName -Algorithm SHA256).Hash
    $hashGoc = (Get-FileHash -LiteralPath (Join-Path $gocDuAn $tuongDoi) -Algorithm SHA256).Hash
    if($hash -ne $hashGoc){
        throw "Ban sao sai noi dung: $tuongDoi"
    }
    $dauVanTay += [PSCustomObject]@{ Tep = $tuongDoi; SHA256 = $hash }
}
$dauVanTay | Export-Csv -LiteralPath (Join-Path $thuMucChay 'danh-sach-nguon.csv') -NoTypeInformation -Encoding UTF8

# Nen truoc khi build, nen ZIP khong chua executable, log hoac du lieu tam.
$tepZip = Join-Path $thuMucChay 'ThuVien_MaNguon.zip'
Compress-Archive -LiteralPath $banSao -DestinationPath $tepZip

$script:ketQua = @()
function ChayBuoc($ten, [string[]]$thamSo){
    $log = Join-Path $thuMucChay ($ten + '.log')
    Write-Host "Dang chay ban sao sach: $ten"
    $cheDoCu = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    & powershell -NoProfile -ExecutionPolicy Bypass @thamSo *> $log
    $ma = $LASTEXITCODE
    $ErrorActionPreference = $cheDoCu
    $script:ketQua += [PSCustomObject]@{ Buoc = $ten; MaThoat = $ma; Log = $log }
    $script:ketQua | Export-Csv -LiteralPath (Join-Path $thuMucChay 'ket-qua-ban-giao.csv') -NoTypeInformation -Encoding UTF8
    Get-Content -LiteralPath $log | Select-String 'Kiem tra.*loi:|Dat:.*khong dat:' | ForEach-Object {
        Write-Host $_.Line
    }
    if($ma -ne 0){
        throw "Buoc $ten that bai. Kiem tra $log. Khong coi ZIP la ban da kiem chung."
    }
}

ChayBuoc 'tich-hop' @('-File', (Join-Path $banSao 'build.ps1'), '-KiemThu')
ChayBuoc 'menu' @('-File', (Join-Path $banSao 'tests/kiemThuMenu.ps1'))
ChayBuoc 'doc-gia' @('-File', (Join-Path $banSao 'tests/chayKiemThuDocGia.ps1'))
ChayBuoc 'muon-tra' @('-File', (Join-Path $banSao 'tests/chayKiemThuMuonTra.ps1'))
ChayBuoc 'tep-he-thong' @('-File', (Join-Path $banSao 'tests/chayKiemThuTepHeThong.ps1'))
ChayBuoc 'thong-ke' @('-File', (Join-Path $banSao 'tests/chayKiemThuThongKe.ps1'))

#=====xac nhan kiem thu khong doi nguon va mau trong ban sao=====
foreach($moc in $dauVanTay){
    if((Get-FileHash -LiteralPath (Join-Path $banSao $moc.Tep) -Algorithm SHA256).Hash -ne $moc.SHA256){
        throw "Nguon/mau bi thay doi trong luc chay: $($moc.Tep)"
    }
}
Write-Host 'DAT: Ban sao sach bien dich va vuot qua ca sau bo kiem thu.'
Write-Host "Ma nguon ZIP: $tepZip"
Write-Host "Bang ket qua: $thuMucChay"
