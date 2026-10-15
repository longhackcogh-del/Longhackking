#include "GiangVien.h"

//=====ham khoi tao=====
GiangVien::GiangVien(){
    gioiHanMuon = 10;
    maGiangVien = "";
    boMon = "";
    hocVi = "";
    soNamCongTac = 0;
}

GiangVien::GiangVien(std::string maNguoi, std::string ten, std::string ngay,
              std::string email, std::string dienThoai, std::string maDocGia,
              int soMuon, bool hoatDong, std::string maGiangVien, std::string boMon, std::string hocVi, int soNamCongTac)
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

std::string GiangVien::layLoai() const{
    return "GiangVien";
}

//=====ham nhap=====
bool GiangVien::nhapGiangVienRieng(std::istream& luong){
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

bool GiangVien::nhap(std::istream& luong){
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
    std::cout << "ma giang vien: " << maGiangVien << '\n';
    std::cout << "bo mon: " << boMon << '\n';
    std::cout << "hoc vi: " << hocVi << '\n';
    std::cout << "so nam cong tac: " << soNamCongTac << '\n';
}

void GiangVien::xuat() const{
    DocGia::xuat();
    xuatGiangVienRieng();
}

//=====ham ghi tep=====
void GiangVien::ghiGiangVienRieng(std::ostream& tep) const{
    tep << maGiangVien << '\n';
    tep << boMon << '\n';
    tep << hocVi << '\n';
    tep << soNamCongTac << '\n';
}

void GiangVien::ghi(std::ostream& tep) const{
    ghiNguoi(tep);
    ghiDocGiaRieng(tep);
    ghiGiangVienRieng(tep);
}
