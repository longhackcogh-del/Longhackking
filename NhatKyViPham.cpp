#include "NhatKyViPham.h"
#include <iomanip>
using namespace std;

//=====ham khoi tao=====
NhatKyViPham::NhatKyViPham(){
    soNgayTre = 0;
    soTienPhat = 0;
    daThanhToan = false;
    loaiViPham = "Qua han";
    maNguoiDuyet = "-";
}

NhatKyViPham::NhatKyViPham(string ma, string phieu, string docGia, int soNgay, double tien){
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
        && isfinite(soTienPhat) && soTienPhat > 0
        && chuoiHopLe(maNguoiDuyet);
}

//=====ham nhap=====
bool NhatKyViPham::nhap(istream& luong){
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
    cout << "Ma vi pham: " << maViPham << '\n';
    cout << "Ma phieu: " << maPhieu << '\n';
    cout << "Ma doc gia: " << maDocGia << '\n';
    cout << "Loai: " << loaiViPham << '\n';
    cout << "So ngay tre: " << soNgayTre << '\n';
    cout << "Tien phat: ";
    xuatTien(cout, soTienPhat);
    cout << '\n';
    if(daThanhToan){
        cout << "Da thanh toan\n";
    }
    else{
        cout << "Chua thanh toan\n";
    }
    cout << "Nguoi duyet: " << maNguoiDuyet << '\n';
}

//=====ham thanh toan=====
bool NhatKyViPham::thanhToanPhat(){
    if(!hopLe() || daThanhToan){
        return false;
    }
    daThanhToan = true;
    return true;
}

bool NhatKyViPham::duyet(const string& maThuThu){
    if(!hopLe() || !chuoiHopLe(maThuThu) || maThuThu == "-" || maNguoiDuyet != "-"){
        return false;
    }
    maNguoiDuyet = maThuThu;
    return true;
}

//=====ham ghi tep=====
void NhatKyViPham::ghi(ostream& tep) const{
    tep << maViPham << '\n';
    tep << maPhieu << '\n';
    tep << maDocGia << '\n';
    tep << loaiViPham << '\n';
    tep << soNgayTre << '\n';
    tep << setprecision(17) << soTienPhat << '\n';
    if(daThanhToan){
        tep << 1 << '\n';
    }
    else{
        tep << 0 << '\n';
    }
    tep << maNguoiDuyet << '\n';
}

string NhatKyViPham::layMa() const{
    return maViPham;
}

string NhatKyViPham::layMaPhieu() const{
    return maPhieu;
}

string NhatKyViPham::layMaDocGia() const{
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

string NhatKyViPham::layNguoiDuyet() const{
    return maNguoiDuyet;
}
