#include "NhatKyViPham.h"
#include <iomanip>

//=====ham khoi tao=====
NhatKyViPham::NhatKyViPham(){
    soNgayTre = 0;
    soTienPhat = 0;
    daThanhToan = false;
    loaiViPham = "Qua han";
    maNguoiDuyet = "-";
}

NhatKyViPham::NhatKyViPham(std::string ma, std::string phieu, std::string docGia, int soNgay, double tien){
    maViPham = ma;
    maPhieu = phieu;
    maDocGia = docGia;
    loaiViPham = "Qua han";
    soNgayTre = soNgay;
    soTienPhat = tien;
    daThanhToan = false;
    maNguoiDuyet = "-";
}

NhatKyViPham::~NhatKyViPham(){
}

bool NhatKyViPham::hopLe() const{
    return chuoiHopLe(maViPham) && chuoiHopLe(maPhieu) && chuoiHopLe(maDocGia)
        && loaiViPham == "Qua han" && soNgayTre > 0
        && std::isfinite(soTienPhat) && soTienPhat > 0
        && chuoiHopLe(maNguoiDuyet);
}

//=====ham nhap=====
bool NhatKyViPham::nhap(std::istream& luong){
    NhatKyViPham tam;
    int thanhToan = 0;
    if(!nhapChuoi(luong, "Nhap ma vi pham: ", tam.maViPham)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ma phieu: ", tam.maPhieu)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ma doc gia: ", tam.maDocGia)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap loai vi pham (Qua han): ", tam.loaiViPham)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so ngay tre: ", tam.soNgayTre)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so tien phat: ", tam.soTienPhat)){
        return false;
    }
    if(!nhapSo(luong, "Da thanh toan (0/1): ", thanhToan)){
        return false;
    }
    if(thanhToan != 0 && thanhToan != 1){
        return false;
    }
    tam.daThanhToan = thanhToan == 1;
    if(!nhapChuoi(luong, "Nhap ma nguoi duyet (- neu chua duyet): ", tam.maNguoiDuyet)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void NhatKyViPham::xuat() const{
    std::cout << "Ma vi pham: " << maViPham << '\n';
    std::cout << "Ma phieu: " << maPhieu << '\n';
    std::cout << "Ma doc gia: " << maDocGia << '\n';
    std::cout << "Loai: " << loaiViPham << '\n';
    std::cout << "So ngay tre: " << soNgayTre << '\n';
    std::cout << "Tien phat: " << soTienPhat << '\n';
    if(daThanhToan){
        std::cout << "Da thanh toan\n";
    }
    else{
        std::cout << "Chua thanh toan\n";
    }
    std::cout << "Nguoi duyet: " << maNguoiDuyet << '\n';
}

//=====ham thanh toan=====
bool NhatKyViPham::thanhToanPhat(){
    if(!hopLe() || daThanhToan){
        return false;
    }
    daThanhToan = true;
    return true;
}

bool NhatKyViPham::duyet(const std::string& maThuThu){
    if(!chuoiHopLe(maThuThu) || maThuThu == "-" || maNguoiDuyet != "-"){
        return false;
    }
    maNguoiDuyet = maThuThu;
    return true;
}

//=====ham ghi tep=====
void NhatKyViPham::ghi(std::ostream& tep) const{
    tep << maViPham << '\n';
    tep << maPhieu << '\n';
    tep << maDocGia << '\n';
    tep << loaiViPham << '\n';
    tep << soNgayTre << '\n';
    tep << std::setprecision(17) << soTienPhat << '\n';
    tep << daThanhToan << '\n';
    tep << maNguoiDuyet << '\n';
}

std::string NhatKyViPham::layMa() const{
    return maViPham;
}

std::string NhatKyViPham::layMaPhieu() const{
    return maPhieu;
}

std::string NhatKyViPham::layMaDocGia() const{
    return maDocGia;
}

int NhatKyViPham::laySoNgayTre() const{
    return soNgayTre;
}

double NhatKyViPham::layTienPhat() const{
    return soTienPhat;
}

bool NhatKyViPham::layDaThanhToan() const{
    return daThanhToan;
}

std::string NhatKyViPham::layNguoiDuyet() const{
    return maNguoiDuyet;
}
