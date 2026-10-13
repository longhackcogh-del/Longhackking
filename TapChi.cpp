#include "TapChi.h"
#include "NhapXuat.h"
#include "ThuatToan.h"

//=====ham khoi tao=====
TapChi::TapChi(){
    soPhatHanh = 0;
    thangPhatHanh = 0;
    linhVuc = "";
}

TapChi::TapChi(std::string ma, std::string ten, std::string nxb,
              int nam, int tong, int con, double gia, int soPhatHanh, int thangPhatHanh, std::string linhVuc)
    : TaiLieu(ma, ten, nxb, nam, tong, con, gia){
    this->soPhatHanh = soPhatHanh;
    this->thangPhatHanh = thangPhatHanh;
    this->linhVuc = linhVuc;
}

TapChi::~TapChi(){
}

bool TapChi::hopLe() const{
    return TaiLieu::hopLe() && soPhatHanh > 0 && thangPhatHanh >= 1 && thangPhatHanh <= 12 && chuoiHopLe(linhVuc);
}

//=====ham nhap=====
bool TapChi::nhap(std::istream& luong){
    TapChi tam;
    if(!tam.TaiLieu::nhap(luong)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so phat hanh: ", tam.soPhatHanh)){
        return false;
    }
    if(!nhapSo(luong, "Nhap thang phat hanh: ", tam.thangPhatHanh)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap linh vuc: ", tam.linhVuc)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void TapChi::xuat() const{
    xuatChung();
    std::cout << "so phat hanh: " << soPhatHanh << '\n';
    std::cout << "thang phat hanh: " << thangPhatHanh << '\n';
    std::cout << "linh vuc: " << linhVuc << '\n';
}

//=====ham tinh tien phat=====
double TapChi::tinhTienPhat(int soNgayTre) const{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 3000;
    return tienPhat;
}

std::string TapChi::layLoai() const{
    return "TapChi";
}

//=====ham ghi tep=====
void TapChi::ghi(std::ostream& tep) const{
    ghiChung(tep);
    tep << soPhatHanh << '\n';
    tep << thangPhatHanh << '\n';
    tep << linhVuc << '\n';
}
