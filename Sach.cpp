#include "Sach.h"
#include "ThuatToan.h"

#include <iomanip>
#include <stdexcept>

Sach::Sach()
    : TaiLieu()
{
    tacGia = "Chua nhap";
    theLoai = "Chua nhap";
    ISBN = "Chua nhap";
    soTrang = 1;
}

Sach::Sach(
    std::string ma,
    std::string ten,
    std::string nxb,
    int nam,
    int tong,
    int con,
    double gia,
    std::string tacGia,
    std::string theLoai,
    std::string ISBN,
    int soTrang
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
    if (!chuoiHopLe(tacGia))
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (!chuoiHopLe(theLoai))
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (!chuoiHopLe(ISBN))
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (soTrang <= 0)
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    this->tacGia = tacGia;
    this->theLoai = theLoai;
    this->ISBN = ISBN;
    this->soTrang = soTrang;
}

Sach::~Sach()
{
}

void Sach::nhap(std::istream& luong)
{
    // Nhap vao ban tam de du lieu loi khong lam doi doi tuong hien tai.
    Sach tam;
    tam.TaiLieu::nhap(luong);

    luong >> std::quoted(tam.tacGia);
    luong >> std::quoted(tam.theLoai);
    luong >> std::quoted(tam.ISBN);
    luong >> tam.soTrang;

    if (!luong)
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (!chuoiHopLe(tam.tacGia))
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (!chuoiHopLe(tam.theLoai))
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (!chuoiHopLe(tam.ISBN))
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    if (tam.soTrang <= 0)
    {
        throw std::invalid_argument("Thong tin Sach khong hop le");
    }

    *this = tam;
}

void Sach::xuat() const
{
    xuatChung();
    std::cout << " |";
    std::cout << ' ' << std::quoted(tacGia);
    std::cout << ' ' << std::quoted(theLoai);
    std::cout << ' ' << std::quoted(ISBN);
    std::cout << ' ' << soTrang;
    std::cout << '\n';
}

double Sach::tinhTienPhat(int soNgayTre) const
{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 2000;

    return tienPhat;
}

std::string Sach::layLoai() const
{
    return "Sach";
}

void Sach::ghi(std::ostream& tep) const
{
    ghiChung(tep);
    tep << ' ' << std::quoted(tacGia);
    tep << ' ' << std::quoted(theLoai);
    tep << ' ' << std::quoted(ISBN);
    tep << ' ' << soTrang;
    tep << '\n';
}
