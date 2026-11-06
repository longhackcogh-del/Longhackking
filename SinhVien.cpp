#include "SinhVien.h"
using namespace std;

//=====ham khoi tao=====
SinhVien::SinhVien(){
    gioiHanMuon = 5;
    maSinhVien = "";
    lop = "";
    khoa = "";
    nganhHoc = "";
}

SinhVien::SinhVien(string maNguoi, string ten, string ngay,
              string email, string dienThoai, string maDocGia,
              int soMuon, bool hoatDong, string maSinhVien, string lop, string khoa, string nganhHoc)
    : Nguoi(maNguoi, ten, ngay, email, dienThoai),
      DocGia(maDocGia, soMuon, 5, hoatDong){
    this->maSinhVien = maSinhVien;
    this->lop = lop;
    this->khoa = khoa;
    this->nganhHoc = nganhHoc;
}

SinhVien::~SinhVien(){
}

bool SinhVien::hopLe() const{
    return DocGia::hopLe()
        && chuoiHopLe(maSinhVien)
        && chuoiHopLe(lop)
        && chuoiHopLe(khoa)
        && chuoiHopLe(nganhHoc);
}

int SinhVien::layGioiHanMuon() const{
    return 5;
}

string SinhVien::layLoai() const{
    return "SinhVien";
}

//=====ham nhap=====

bool SinhVien::nhap(istream& luong){
    SinhVien tam;
    if(!tam.DocGia::nhap(luong)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ma sinh vien: ", tam.maSinhVien)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap lop: ", tam.lop)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap khoa: ", tam.khoa)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap nganh hoc: ", tam.nganhHoc)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====

void SinhVien::xuat() const{
    DocGia::xuat();
    cout << "ma sinh vien: " << maSinhVien << '\n';
    cout << "lop: " << lop << '\n';
    cout << "khoa: " << khoa << '\n';
    cout << "nganh hoc: " << nganhHoc << '\n';
}

//=====ham ghi tep=====

void SinhVien::ghi(ostream& tep) const{
    ghiNguoi(tep);
    ghiDocGiaRieng(tep);
    tep << maSinhVien << '\n';
    tep << lop << '\n';
    tep << khoa << '\n';
    tep << nganhHoc << '\n';
}
