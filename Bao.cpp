#include "Bao.h"
#include "ThuatToan.h"

#include <iomanip>
#include <stdexcept>

Bao::Bao()
    : TaiLieu()
{
    ngayPhatHanh = "01/01/2000";
    loaiBao = "Chua nhap";
}

Bao::Bao(
    std::string ma,
    std::string ten,
    std::string nxb,
    int nam,
    int tong,
    int con,
    double gia,
    std::string ngayPhatHanh,
    std::string loaiBao
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
    if (!ngayHopLe(ngayPhatHanh))
    {
        throw std::invalid_argument("Thong tin Bao khong hop le");
    }

    if (!chuoiHopLe(loaiBao))
    {
        throw std::invalid_argument("Thong tin Bao khong hop le");
    }

    this->ngayPhatHanh = ngayPhatHanh;
    this->loaiBao = loaiBao;
}

Bao::~Bao()
{
}

void Bao::nhap(std::istream& luong)
{
    // Nhap vao ban tam de du lieu loi khong lam doi doi tuong hien tai.
    Bao tam;
    tam.TaiLieu::nhap(luong);

    luong >> std::quoted(tam.ngayPhatHanh);
    luong >> std::quoted(tam.loaiBao);

    if (!luong)
    {
        throw std::invalid_argument("Thong tin Bao khong hop le");
    }

    if (!ngayHopLe(tam.ngayPhatHanh))
    {
        throw std::invalid_argument("Thong tin Bao khong hop le");
    }

    if (!chuoiHopLe(tam.loaiBao))
    {
        throw std::invalid_argument("Thong tin Bao khong hop le");
    }

    *this = tam;
}

void Bao::xuat() const
{
    xuatChung();
    std::cout << " |";
    std::cout << ' ' << std::quoted(ngayPhatHanh);
    std::cout << ' ' << std::quoted(loaiBao);
    std::cout << '\n';
}

double Bao::tinhTienPhat(int soNgayTre) const
{
    int ngayTre = timMax(0, soNgayTre);
    double tienPhat = static_cast<double>(ngayTre) * 1000;

    return tienPhat;
}

std::string Bao::layLoai() const
{
    return "Bao";
}

void Bao::ghi(std::ostream& tep) const
{
    ghiChung(tep);
    tep << ' ' << std::quoted(ngayPhatHanh);
    tep << ' ' << std::quoted(loaiBao);
    tep << '\n';
}
