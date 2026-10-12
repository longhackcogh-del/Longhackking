#include "TapChi.h"
#include "ThuatToan.h"
#include <iomanip>
#include <stdexcept>
TapChi::TapChi() : TapChi("CHUA_NHAP", "Chua nhap", "Chua nhap", 1, 0, 0, 0, 1, 1, "Chua nhap") {}
TapChi::TapChi(std::string ma, std::string ten, std::string nxb, int nam,
              int tong, int con, double gia, int soPhatHanh, int thangPhatHanh, std::string linhVuc)
    : TaiLieu(ma, ten, nxb, nam, tong, con, gia), soPhatHanh(soPhatHanh), thangPhatHanh(thangPhatHanh), linhVuc(linhVuc) {
    if (soPhatHanh <= 0 || thangPhatHanh < 1 || thangPhatHanh > 12 || !chuoiHopLe(linhVuc)) throw std::invalid_argument("Thong tin TapChi khong hop le");
}
TapChi::~TapChi() {}
void TapChi::nhap(std::istream& luong) {
    // Chi cap nhat doi tuong khi tat ca truong da hop le.
    TapChi tam;
    tam.TaiLieu::nhap(luong);
    if (!(luong >> tam.soPhatHanh >> tam.thangPhatHanh >> std::quoted(tam.linhVuc)) || tam.soPhatHanh <= 0 || tam.thangPhatHanh < 1 || tam.thangPhatHanh > 12 || !chuoiHopLe(tam.linhVuc)) {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }
    *this = tam;
}
void TapChi::xuat() const {
    xuatChung();
    std::cout << " | " << soPhatHanh << ' ' << thangPhatHanh << ' ' << std::quoted(linhVuc) << '\n';
}
double TapChi::tinhTienPhat(int soNgayTre) const {
    return static_cast<double>(timMax(0, soNgayTre)) * 3000;
}
std::string TapChi::layLoai() const { return "TapChi"; }
void TapChi::ghi(std::ostream& tep) const {
    ghiChung(tep);
    tep << ' ' << soPhatHanh << ' ' << thangPhatHanh << ' ' << std::quoted(linhVuc) << '\n';
}