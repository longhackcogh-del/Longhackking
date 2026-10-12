#include "TapChi.h"
#include "ThuatToan.h"

#include <iomanip>
#include <stdexcept>

TapChi::TapChi()
    : TaiLieu()
{
    soPhatHanh = 1;
    thangPhatHanh = 1;
    linhVuc = "Chua nhap";
}

TapChi::TapChi(
    std::string ma,
    std::string ten,
    std::string nxb,
    int nam,
    int tong,
    int con,
    double gia,
    int soPhatHanh,
    int thangPhatHanh,
    std::string linhVuc
)
    : TaiLieu(
        ma,
        ten,
        nxb,
        nam,
        tong,
        con,
        gia
    )
{
    if (soPhatHanh <= 0)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (thangPhatHanh < 1)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (thangPhatHanh > 12)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (!chuoiHopLe(linhVuc))
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    this->soPhatHanh = soPhatHanh;
    this->thangPhatHanh = thangPhatHanh;
    this->linhVuc = linhVuc;
}

TapChi::~TapChi()
{
}

void TapChi::nhap(std::istream& luong)
{
    // Nhap vao ban tam de du lieu loi khong lam doi doi tuong hien tai.
    TapChi tam;
    tam.TaiLieu::nhap(luong);

    luong >> tam.soPhatHanh;
    luong >> tam.thangPhatHanh;
    luong >> std::quoted(tam.linhVuc);

    if (!luong)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (tam.soPhatHanh <= 0)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (tam.thangPhatHanh < 1)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (tam.thangPhatHanh > 12)
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    if (!chuoiHopLe(tam.linhVuc))
    {
        throw std::invalid_argument("Thong tin TapChi khong hop le");
    }

    *this = tam;
}

void TapChi::xuat() const
{
    xuatChung();
    std::cout << " |";
    std::cout << ' ' << soPhatHanh;
    std::cout << ' ' << thangPhatHanh;
    std::cout << ' ' << std::quoted(linhVuc);
    std::cout << '\n';
}

double TapChi::tinhTienPhat(int soNgayTre) const
{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 3000;

    return tienPhat;
}

std::string TapChi::layLoai() const
{
    return "TapChi";
}

void TapChi::ghi(std::ostream& tep) const
{
    ghiChung(tep);
    tep << ' ' << soPhatHanh;
    tep << ' ' << thangPhatHanh;
    tep << ' ' << std::quoted(linhVuc);
    tep << '\n';
}
