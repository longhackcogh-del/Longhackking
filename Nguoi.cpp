#include "Nguoi.h"

//=====ham khoi tao=====
Nguoi::Nguoi(){
}

Nguoi::Nguoi(std::string ma, std::string ten, std::string ngay,
             std::string thu, std::string dienThoai){
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
    std::string::size_type a = email.find('@');
    if(a == std::string::npos || a == 0 || email.find('@', a + 1) != std::string::npos){
        return false;
    }
    std::string::size_type b = email.find('.', a + 1);
    if(b == std::string::npos || b <= a + 1 || b + 1 >= email.size()){
        return false;
    }
    if(email.find_first_of(" \t") != std::string::npos){
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
bool Nguoi::nhap(std::istream& luong){
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
    std::cout << "Ma nguoi: " << maNguoi << '\n';
    std::cout << "Ho ten: " << hoTen << '\n';
    std::cout << "Ngay sinh: " << ngaySinh << '\n';
    std::cout << "Email: " << email << '\n';
    std::cout << "So dien thoai: " << soDienThoai << '\n';
}

void Nguoi::ghiNguoi(std::ostream& tep) const{
    tep << maNguoi << '\n';
    tep << hoTen << '\n';
    tep << ngaySinh << '\n';
    tep << email << '\n';
    tep << soDienThoai << '\n';
}

std::string Nguoi::layMaNguoi() const{
    return maNguoi;
}

std::string Nguoi::layHoTen() const{
    return hoTen;
}
