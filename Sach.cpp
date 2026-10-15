#include "Sach.h"
#include "NhapXuat.h"
#include "ThuatToan.h"

//=====ham khoi tao=====
Sach::Sach(){
    tacGia = "";
    theLoai = "";
    ISBN = "";
    soTrang = 0;
}

Sach::Sach(std::string ma, std::string ten, std::string nxb,
              int nam, int tong, int con, double gia, std::string tacGia, std::string theLoai, std::string ISBN, int soTrang)
    : TaiLieu(ma, ten, nxb, nam, tong, con, gia){
    this->tacGia = tacGia;
    this->theLoai = theLoai;
    this->ISBN = ISBN;
    this->soTrang = soTrang;
}

Sach::~Sach(){
}

bool Sach::hopLe() const{
    return TaiLieu::hopLe() && chuoiHopLe(tacGia) && chuoiHopLe(theLoai) && chuoiHopLe(ISBN) && soTrang > 0;
}

//=====ham nhap=====
bool Sach::nhap(std::istream& luong){
    Sach tam;
    if(!tam.TaiLieu::nhap(luong)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap tac gia: ", tam.tacGia)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap the loai: ", tam.theLoai)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ISBN: ", tam.ISBN)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so trang: ", tam.soTrang)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void Sach::xuat() const{
    xuatChung();
    std::cout << "tac gia: " << tacGia << '\n';
    std::cout << "the loai: " << theLoai << '\n';
    std::cout << "ISBN: " << ISBN << '\n';
    std::cout << "so trang: " << soTrang << '\n';
}

//=====ham tinh tien phat=====
double Sach::tinhTienPhat(int soNgayTre) const{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 2000;
    return tienPhat;
}

std::string Sach::layLoai() const{
    return "Sach";
}

//=====ham ghi tep=====
void Sach::ghi(std::ostream& tep) const{
    ghiChung(tep);
    tep << tacGia << '\n';
    tep << theLoai << '\n';
    tep << ISBN << '\n';
    tep << soTrang << '\n';
}
