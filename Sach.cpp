#include "Sach.h"
#include "NhapXuat.h"
#include "ThuatToan.h"
using namespace std;

//=====ham khoi tao=====
Sach::Sach(){
    tacGia = "";
    theLoai = "";
    ISBN = "";
    soTrang = 0;
}

Sach::Sach(string ma, string ten, string nxb,
              int nam, int tong, int con, double gia, string tacGia, string theLoai, string ISBN, int soTrang)
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
bool Sach::nhap(istream& luong){
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
    cout << "tac gia: " << tacGia << '\n';
    cout << "the loai: " << theLoai << '\n';
    cout << "ISBN: " << ISBN << '\n';
    cout << "so trang: " << soTrang << '\n';
}

//=====ham tinh tien phat=====
double Sach::tinhTienPhat(int soNgayTre) const{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 2000;
    return tienPhat;
}

string Sach::layLoai() const{
    return "Sach";
}

//=====ham ghi tep=====
void Sach::ghi(ostream& tep) const{
    ghiChung(tep);
    tep << tacGia << '\n';
    tep << theLoai << '\n';
    tep << ISBN << '\n';
    tep << soTrang << '\n';
}
