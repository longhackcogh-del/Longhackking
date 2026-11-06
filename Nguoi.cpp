#include "Nguoi.h"
using namespace std;

//=====ham khoi tao=====
Nguoi::Nguoi(){
}

Nguoi::Nguoi(string ma, string ten, string ngay,
             string thu, string dienThoai){
    maNguoi = ma;
    hoTen = ten;
    ngaySinh = ngay;
    email = thu;
    soDienThoai = dienThoai;
}

Nguoi::~Nguoi(){
}

//=====ham kiem tra=====
bool Nguoi::hopLe() const{
    if(!chuoiHopLe(maNguoi) || !chuoiHopLe(hoTen) || !ngayHopLe(ngaySinh)){
        return false;
    }
    if(!chuoiHopLe(email) || !chuoiHopLe(soDienThoai)){
        return false;
    }
    string::size_type a = email.find('@');
    if(a == string::npos || a == 0 || email.find('@', a + 1) != string::npos){
        return false;
    }
    string::size_type b = email.find('.', a + 1);
    if(b == string::npos || b <= a + 1 || b + 1 >= email.size()){
        return false;
    }
    if(email.find_first_of(" \t") != string::npos){
        return false;
    }
    for(unsigned int i = 0; i < soDienThoai.size(); i++){
        if(soDienThoai[i] < '0' || soDienThoai[i] > '9'){
            return false;
        }
    }
    return true;
}

//=====ham nhap=====
bool Nguoi::nhap(istream& luong){
    Nguoi tam;
    if(!nhapChuoi(luong, "Nhap ma nguoi: ", tam.maNguoi)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ho ten: ", tam.hoTen)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ngay sinh (dd/mm/yyyy): ", tam.ngaySinh)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap email: ", tam.email)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap so dien thoai: ", tam.soDienThoai)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void Nguoi::xuat() const{
    cout << "Ma nguoi: " << maNguoi << '\n';
    cout << "Ho ten: " << hoTen << '\n';
    cout << "Ngay sinh: " << ngaySinh << '\n';
    cout << "Email: " << email << '\n';
    cout << "So dien thoai: " << soDienThoai << '\n';
}

void Nguoi::ghiNguoi(ostream& tep) const{
    tep << maNguoi << '\n';
    tep << hoTen << '\n';
    tep << ngaySinh << '\n';
    tep << email << '\n';
    tep << soDienThoai << '\n';
}

string Nguoi::layMaNguoi() const{
    return maNguoi;
}

string Nguoi::layHoTen() const{
    return hoTen;
}

//=====ham doi chieu nhan than=====
bool Nguoi::cungThongTinCaNhan(const Nguoi& khac) const{
    return maNguoi == khac.maNguoi && hoTen == khac.hoTen
        && ngaySinh == khac.ngaySinh && email == khac.email
        && soDienThoai == khac.soDienThoai;
}
