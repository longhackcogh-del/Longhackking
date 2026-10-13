#include "Bao.h"
#include "NhapXuat.h"
#include "ThuatToan.h"

//=====ham khoi tao=====
Bao::Bao(){
    ngayPhatHanh = "";
    loaiBao = "";
}

Bao::Bao(std::string ma, std::string ten, std::string nxb,
              int nam, int tong, int con, double gia, std::string ngayPhatHanh, std::string loaiBao)
    : TaiLieu(ma, ten, nxb, nam, tong, con, gia){
    this->ngayPhatHanh = ngayPhatHanh;
    this->loaiBao = loaiBao;
}

Bao::~Bao(){
}

bool Bao::hopLe() const{
    return TaiLieu::hopLe() && ngayHopLe(ngayPhatHanh) && chuoiHopLe(loaiBao);
}

//=====ham nhap=====
bool Bao::nhap(std::istream& luong){
    Bao tam;
    if(!tam.TaiLieu::nhap(luong)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ngay phat hanh (dd/mm/yyyy): ", tam.ngayPhatHanh)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap loai bao: ", tam.loaiBao)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void Bao::xuat() const{
    xuatChung();
    std::cout << "ngay phat hanh (dd/mm/yyyy): " << ngayPhatHanh << '\n';
    std::cout << "loai bao: " << loaiBao << '\n';
}

//=====ham tinh tien phat=====
double Bao::tinhTienPhat(int soNgayTre) const{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 1000;
    return tienPhat;
}

std::string Bao::layLoai() const{
    return "Bao";
}

//=====ham ghi tep=====
void Bao::ghi(std::ostream& tep) const{
    ghiChung(tep);
    tep << ngayPhatHanh << '\n';
    tep << loaiBao << '\n';
}
