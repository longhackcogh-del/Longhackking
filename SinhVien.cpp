#include "SinhVien.h"

//=====ham khoi tao=====
SinhVien::SinhVien(){
    gioiHanMuon = 5;
    maSinhVien = "";
    lop = "";
    khoa = "";
    nganhHoc = "";
}

SinhVien::SinhVien(std::string maNguoi, std::string ten, std::string ngay,
              std::string email, std::string dienThoai, std::string maDocGia,
              int soMuon, bool hoatDong, std::string maSinhVien, std::string lop, std::string khoa, std::string nganhHoc)
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

std::string SinhVien::layLoai() const{
    return "SinhVien";
}

//=====ham nhap=====

bool SinhVien::nhap(std::istream& luong){
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
    std::cout << "ma sinh vien: " << maSinhVien << '\n';
    std::cout << "lop: " << lop << '\n';
    std::cout << "khoa: " << khoa << '\n';
    std::cout << "nganh hoc: " << nganhHoc << '\n';
}

//=====ham ghi tep=====

void SinhVien::ghi(std::ostream& tep) const{
    ghiNguoi(tep);
    ghiDocGiaRieng(tep);
    tep << maSinhVien << '\n';
    tep << lop << '\n';
    tep << khoa << '\n';
    tep << nganhHoc << '\n';
}
