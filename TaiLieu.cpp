#include "TaiLieu.h"
#include "NhapXuat.h"
#include <iomanip>
using namespace std;

//=====ham khoi tao=====
TaiLieu::TaiLieu(){
    maTaiLieu = "";
    tenTaiLieu = "";
    nhaXuatBan = "";
    namXuatBan = 1;
    soLuongTong = 0;
    soLuongCon = 0;
    giaTri = 0;
}

TaiLieu::TaiLieu(string ma, string ten, string nxb,
                 int nam, int tong, int con, double gia){
    maTaiLieu = ma;
    tenTaiLieu = ten;
    nhaXuatBan = nxb;
    namXuatBan = nam;
    soLuongTong = tong;
    soLuongCon = con;
    giaTri = gia;
}

TaiLieu::~TaiLieu(){
}

//=====ham kiem tra=====
bool TaiLieu::chuoiHopLe(const string& chuoi){
    return ::chuoiHopLe(chuoi);
}

bool TaiLieu::ngayHopLe(const string& ngay){
    return ::ngayHopLe(ngay);
}

bool TaiLieu::hopLe() const{
    if(!chuoiHopLe(maTaiLieu) || !chuoiHopLe(tenTaiLieu) || !chuoiHopLe(nhaXuatBan)){
        return false;
    }
    if(namXuatBan < 1 || namXuatBan > 9999){
        return false;
    }
    if(soLuongTong < 0 || soLuongCon < 0 || soLuongCon > soLuongTong){
        return false;
    }
    return isfinite(giaTri) && giaTri >= 0;
}

//=====ham nhap=====
bool TaiLieu::nhap(istream& luong){
    string ma, ten, nxb;
    int nam = 0;
    int tong = 0;
    int con = 0;
    double gia = 0;
    if(!nhapChuoi(luong, "Nhap ma tai lieu: ", ma)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ten tai lieu: ", ten)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap nha xuat ban: ", nxb)){
        return false;
    }
    if(!nhapSo(luong, "Nhap nam xuat ban: ", nam)){
        return false;
    }
    if(!nhapSo(luong, "Nhap tong so luong: ", tong)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so luong con: ", con)){
        return false;
    }
    if(!nhapSo(luong, "Nhap gia tri: ", gia)){
        return false;
    }
    if(nam < 1 || nam > 9999 || tong < 0 || con < 0 || con > tong || gia < 0){
        return false;
    }
    maTaiLieu = ma;
    tenTaiLieu = ten;
    nhaXuatBan = nxb;
    namXuatBan = nam;
    soLuongTong = tong;
    soLuongCon = con;
    giaTri = gia;
    return true;
}

//=====ham xuat=====
void TaiLieu::xuatChung() const{
    cout << "\nLoai: " << layLoai() << '\n';
    cout << "Ma tai lieu: " << maTaiLieu << '\n';
    cout << "Ten tai lieu: " << tenTaiLieu << '\n';
    cout << "Nha xuat ban: " << nhaXuatBan << '\n';
    cout << "Nam xuat ban: " << namXuatBan << '\n';
    cout << "So luong con/tong: " << soLuongCon << '/' << soLuongTong << '\n';
    cout << "Gia tri: ";
    xuatTien(cout, giaTri);
    cout << '\n';
}

//=====ham ghi tep=====
void TaiLieu::ghiChung(ostream& tep) const{
    tep << maTaiLieu << '\n';
    tep << tenTaiLieu << '\n';
    tep << nhaXuatBan << '\n';
    tep << namXuatBan << '\n';
    tep << soLuongTong << '\n';
    tep << soLuongCon << '\n';
    tep << setprecision(17) << giaTri << '\n';
}

string TaiLieu::layMa() const{
    return maTaiLieu;
}

string TaiLieu::layTen() const{
    return tenTaiLieu;
}

int TaiLieu::layNam() const{
    return namXuatBan;
}

double TaiLieu::layGiaTri() const{
    return giaTri;
}

int TaiLieu::laySoLuongTong() const{
    return soLuongTong;
}

int TaiLieu::laySoLuongCon() const{
    return soLuongCon;
}

//=====ham kiem tra ton kho=====
bool TaiLieu::kiemTraConTaiLieu(int soLuong) const{
    return soLuong > 0 && soLuong <= soLuongCon;
}

bool TaiLieu::giamSoLuong(int soLuong){
    if(!kiemTraConTaiLieu(soLuong)){
        return false;
    }
    soLuongCon -= soLuong;
    return true;
}

bool TaiLieu::tangSoLuong(int soLuong){
    if(soLuong <= 0 || soLuong > soLuongTong - soLuongCon){
        return false;
    }
    soLuongCon += soLuong;
    return true;
}
