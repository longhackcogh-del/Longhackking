#include "NhanVienThuThu.h"
#include <iomanip>

//=====ham khoi tao=====
NhanVienThuThu::NhanVienThuThu(){
    luongCoBan = 0;
    heSoLuong = 0;
}

NhanVienThuThu::NhanVienThuThu(std::string maNguoi, std::string ten, std::string ngay,
                             std::string email, std::string dienThoai, std::string maNhanVien,
                             std::string ca, std::string chuc, double luong, double heSo)
    : Nguoi(maNguoi, ten, ngay, email, dienThoai){
    this->maNhanVien = maNhanVien;
    caLamViec = ca;
    chucVu = chuc;
    luongCoBan = luong;
    heSoLuong = heSo;
}

NhanVienThuThu::~NhanVienThuThu(){
}

bool NhanVienThuThu::hopLe() const{
    return Nguoi::hopLe() && chuoiHopLe(maNhanVien) && chuoiHopLe(caLamViec)
        && chuoiHopLe(chucVu) && std::isfinite(luongCoBan) && luongCoBan > 0
        && std::isfinite(heSoLuong) && heSoLuong > 0
        && std::isfinite(luongCoBan * heSoLuong);
}

//=====ham nhap=====
bool NhanVienThuThu::nhapNhanVienRieng(std::istream& luong){
    if(!nhapChuoi(luong, "Nhap ma nhan vien: ", maNhanVien)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ca lam viec: ", caLamViec)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap chuc vu: ", chucVu)){
        return false;
    }
    if(!nhapSo(luong, "Nhap luong co ban: ", luongCoBan)){
        return false;
    }
    if(!nhapSo(luong, "Nhap he so luong: ", heSoLuong)){
        return false;
    }
    return luongCoBan > 0 && heSoLuong > 0;
}

bool NhanVienThuThu::nhap(std::istream& luong){
    NhanVienThuThu tam;
    if(!tam.Nguoi::nhap(luong) || !tam.nhapNhanVienRieng(luong)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void NhanVienThuThu::xuatNhanVienRieng() const{
    std::cout << "Ma nhan vien: " << maNhanVien << '\n';
    std::cout << "Ca lam viec: " << caLamViec << '\n';
    std::cout << "Chuc vu: " << chucVu << '\n';
    std::cout << "Luong co ban: " << luongCoBan << '\n';
    std::cout << "He so luong: " << heSoLuong << '\n';
}

void NhanVienThuThu::xuat() const{
    Nguoi::xuat();
    xuatNhanVienRieng();
}

//=====ham tinh luong=====
double NhanVienThuThu::tinhLuong() const{
    return luongCoBan * heSoLuong;
}

std::string NhanVienThuThu::layMa() const{
    return maNhanVien;
}

std::string NhanVienThuThu::layCa() const{
    return caLamViec;
}

double NhanVienThuThu::layHeSoLuong() const{
    return heSoLuong;
}

void NhanVienThuThu::ghiNhanVienRieng(std::ostream& tep) const{
    tep << maNhanVien << '\n';
    tep << caLamViec << '\n';
    tep << chucVu << '\n';
    tep << std::setprecision(17) << luongCoBan << '\n';
    tep << heSoLuong << '\n';
}

void NhanVienThuThu::ghi(std::ostream& tep) const{
    ghiNguoi(tep);
    ghiNhanVienRieng(tep);
}
