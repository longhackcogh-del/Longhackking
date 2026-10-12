#include "Bao.h"
#include "ThuatToan.h"
#include <iomanip>
#include <stdexcept>
Bao::Bao() : Bao("CHUA_NHAP", "Chua nhap", "Chua nhap", 1, 0, 0, 0, "01/01/2000", "Chua nhap") {}
Bao::Bao(std::string ma, std::string ten, std::string nxb, int nam,
              int tong, int con, double gia, std::string ngayPhatHanh, std::string loaiBao)
    : TaiLieu(ma, ten, nxb, nam, tong, con, gia), ngayPhatHanh(ngayPhatHanh), loaiBao(loaiBao) {
    if (!ngayHopLe(ngayPhatHanh) || !chuoiHopLe(loaiBao)) throw std::invalid_argument("Thong tin Bao khong hop le");
}
Bao::~Bao() {}
void Bao::nhap(std::istream& luong) {
    // Chi cap nhat doi tuong khi tat ca truong da hop le.
    Bao tam;
    tam.TaiLieu::nhap(luong);
    if (!(luong >> std::quoted(tam.ngayPhatHanh) >> std::quoted(tam.loaiBao)) || !ngayHopLe(tam.ngayPhatHanh) || !chuoiHopLe(tam.loaiBao)) {
        throw std::invalid_argument("Thong tin Bao khong hop le");
    }
    *this = tam;
}
void Bao::xuat() const {
    xuatChung();
    std::cout << " | " << std::quoted(ngayPhatHanh) << ' ' << std::quoted(loaiBao) << '\n';
}
double Bao::tinhTienPhat(int soNgayTre) const {
    return static_cast<double>(timMax(0, soNgayTre)) * 1000;
}
std::string Bao::layLoai() const { return "Bao"; }
void Bao::ghi(std::ostream& tep) const {
    ghiChung(tep);
    tep << ' ' << std::quoted(ngayPhatHanh) << ' ' << std::quoted(loaiBao) << '\n';
}