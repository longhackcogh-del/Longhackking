#include "GiangVien.h"
using namespace std;

//=====ham khoi tao=====
GiangVien::GiangVien(){
    gioiHanMuon = 10;
    maGiangVien = "";
    boMon = "";
    hocVi = "";
    soNamCongTac = 0;
}

GiangVien::GiangVien(string maNguoi, string ten, string ngay,
              string email, string dienThoai, string maDocGia,
              int soMuon, bool hoatDong, string maGiangVien, string boMon, string hocVi, int soNamCongTac)
    : Nguoi(maNguoi, ten, ngay, email, dienThoai),
      DocGia(maDocGia, soMuon, 10, hoatDong){
    this->maGiangVien = maGiangVien;
    this->boMon = boMon;
    this->hocVi = hocVi;
    this->soNamCongTac = soNamCongTac;
}

GiangVien::~GiangVien(){
}

bool GiangVien::hopLe() const{
    return DocGia::hopLe()
        && chuoiHopLe(maGiangVien)
        && chuoiHopLe(boMon)
        && chuoiHopLe(hocVi)
        && soNamCongTac >= 0;
}

int GiangVien::layGioiHanMuon() const{
    return 10;
}

string GiangVien::layLoai() const{
    return "GiangVien";
}

//=====ham nhap=====
bool GiangVien::nhapGiangVienRieng(istream& luong){
    if(!nhapChuoi(luong, "Nhap ma giang vien: ", maGiangVien)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap bo mon: ", boMon)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap hoc vi: ", hocVi)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so nam cong tac: ", soNamCongTac)){
        return false;
    }
    return soNamCongTac >= 0;
}

bool GiangVien::nhap(istream& luong){
    GiangVien tam;
    if(!tam.DocGia::nhap(luong)){
        return false;
    }
    if(!tam.nhapGiangVienRieng(luong)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void GiangVien::xuatGiangVienRieng() const{
    cout << "ma giang vien: " << maGiangVien << '\n';
    cout << "bo mon: " << boMon << '\n';
    cout << "hoc vi: " << hocVi << '\n';
    cout << "so nam cong tac: " << soNamCongTac << '\n';
}

void GiangVien::xuat() const{
    DocGia::xuat();
    xuatGiangVienRieng();
}

//=====ham ghi tep=====
void GiangVien::ghiGiangVienRieng(ostream& tep) const{
    tep << maGiangVien << '\n';
    tep << boMon << '\n';
    tep << hocVi << '\n';
    tep << soNamCongTac << '\n';
}

void GiangVien::ghi(ostream& tep) const{
    ghiNguoi(tep);
    ghiDocGiaRieng(tep);
    ghiGiangVienRieng(tep);
}
