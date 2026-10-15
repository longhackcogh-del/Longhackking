#include "ThuThuTruong.h"
#include "QuanLyViPham.h"
#include <iomanip>

//=====ham khoi tao=====
ThuThuTruong::ThuThuTruong(){
    soNhanVienQuanLy = 0;
    heSoPhuCap = 0;
}

ThuThuTruong::ThuThuTruong(std::string maNguoi, std::string ten, std::string ngay,
                         std::string email, std::string dienThoai,
                         std::string maDocGia, std::string maGiangVien,
                         std::string boMon, std::string hocVi, int soNam,
                         std::string maNhanVien, std::string ca, std::string chuc,
                         double luong, double heSo, std::string khuVuc, int soNhanVien, double phuCap)
    : Nguoi(maNguoi, ten, ngay, email, dienThoai),
      GiangVien(maNguoi, ten, ngay, email, dienThoai, maDocGia, 0, true,
                maGiangVien, boMon, hocVi, soNam),
      NhanVienThuThu(maNguoi, ten, ngay, email, dienThoai, maNhanVien, ca, chuc, luong, heSo){
    khuVucQuanLy = khuVuc;
    soNhanVienQuanLy = soNhanVien;
    heSoPhuCap = phuCap;
}

ThuThuTruong::~ThuThuTruong(){
}

bool ThuThuTruong::hopLe() const{
    return GiangVien::hopLe() && NhanVienThuThu::hopLe()
        && chuoiHopLe(khuVucQuanLy) && soNhanVienQuanLy >= 0
        && std::isfinite(heSoPhuCap) && heSoPhuCap >= 0
        && std::isfinite(tinhThuNhap());
}

//=====ham nhap=====
bool ThuThuTruong::nhap(std::istream& luong){
    ThuThuTruong tam;
    if(!tam.Nguoi::nhap(luong)){
        return false;
    }
    if(!tam.nhapDocGiaRieng(luong) || !tam.nhapGiangVienRieng(luong)){
        return false;
    }
    if(!tam.nhapNhanVienRieng(luong)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap khu vuc quan ly: ", tam.khuVucQuanLy)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so nhan vien quan ly: ", tam.soNhanVienQuanLy)){
        return false;
    }
    if(!nhapSo(luong, "Nhap he so phu cap: ", tam.heSoPhuCap)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void ThuThuTruong::xuat() const{
    Nguoi::xuat();
    xuatDocGiaRieng();
    xuatGiangVienRieng();
    xuatNhanVienRieng();
    std::cout << "Khu vuc quan ly: " << khuVucQuanLy << '\n';
    std::cout << "So nhan vien quan ly: " << soNhanVienQuanLy << '\n';
    std::cout << "He so phu cap: " << heSoPhuCap << '\n';
}

//=====ham tinh thu nhap=====
double ThuThuTruong::tinhThuNhap() const{
    return tinhLuong() + heSoPhuCap * 2000000;
}

std::string ThuThuTruong::layMa() const{
    return NhanVienThuThu::layMa();
}

int ThuThuTruong::laySoNhanVienQuanLy() const{
    return soNhanVienQuanLy;
}

double ThuThuTruong::layPhuCap() const{
    return heSoPhuCap;
}

void ThuThuTruong::ghi(std::ostream& tep) const{
    ghiNguoi(tep);
    ghiDocGiaRieng(tep);
    ghiGiangVienRieng(tep);
    ghiNhanVienRieng(tep);
    tep << khuVucQuanLy << '\n';
    tep << soNhanVienQuanLy << '\n';
    tep << std::setprecision(17) << heSoPhuCap << '\n';
}

//=====ham xem va duyet vi pham=====
void ThuThuTruong::xemNhatKyViPham(const QuanLyViPham& quanLy) const{
    quanLy.hienThi();
}

bool ThuThuTruong::duyetViPham(QuanLyViPham& quanLy, const std::string& ma) const{
    if(!hopLe()){
        return false;
    }
    return quanLy.duyet(ma, layMa());
}
