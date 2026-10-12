#include "Sach.h"
#include "ThuatToan.h"
#include <iomanip>
#include <stdexcept>
Sach::Sach() : Sach("CHUA_NHAP", "Chua nhap", "Chua nhap", 1, 0, 0, 0, "Chua nhap", "Chua nhap", "Chua nhap", 1) {}
Sach::Sach(std::string ma, std::string ten, std::string nxb, int nam,
              int tong, int con, double gia, std::string tacGia, std::string theLoai, std::string ISBN, int soTrang)
    : TaiLieu(ma, ten, nxb, nam, tong, con, gia), tacGia(tacGia), theLoai(theLoai), ISBN(ISBN), soTrang(soTrang) {
    if (!chuoiHopLe(tacGia) || !chuoiHopLe(theLoai) || !chuoiHopLe(ISBN) || soTrang <= 0) throw std::invalid_argument("Thong tin Sach khong hop le");
}
Sach::~Sach() {}
void Sach::nhap(std::istream& luong) {
    // Chi cap nhat doi tuong khi tat ca truong da hop le.
    Sach tam;
    tam.TaiLieu::nhap(luong);
    if (!(luong >> std::quoted(tam.tacGia) >> std::quoted(tam.theLoai) >> std::quoted(tam.ISBN) >> tam.soTrang) || !chuoiHopLe(tam.tacGia) || !chuoiHopLe(tam.theLoai) || !chuoiHopLe(tam.ISBN) || tam.soTrang <= 0) {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }
    *this = tam;
}
void Sach::xuat() const {
    xuatChung();
    std::cout << " | " << std::quoted(tacGia) << ' ' << std::quoted(theLoai) << ' ' << std::quoted(ISBN) << ' ' << soTrang << '\n';
}
double Sach::tinhTienPhat(int soNgayTre) const {
    return static_cast<double>(timMax(0, soNgayTre)) * 2000;
}
std::string Sach::layLoai() const { return "Sach"; }
void Sach::ghi(std::ostream& tep) const {
    ghiChung(tep);
    tep << ' ' << std::quoted(tacGia) << ' ' << std::quoted(theLoai) << ' ' << std::quoted(ISBN) << ' ' << soTrang << '\n';
}