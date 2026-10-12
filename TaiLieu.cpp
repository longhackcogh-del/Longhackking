#include "TaiLieu.h"

#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <cctype>

TaiLieu::TaiLieu()
{
    maTaiLieu = "CHUA_NHAP";
    tenTaiLieu = "Chua nhap";
    nhaXuatBan = "Chua nhap";
    namXuatBan = 1;
    soLuongTong = 0;
    soLuongCon = 0;
    giaTri = 0;
}

TaiLieu::TaiLieu(
    std::string ma,
    std::string ten,
    std::string nxb,
    int nam,
    int tong,
    int con,
    double gia
)
{
    if (!chuoiHopLe(ma))
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (!chuoiHopLe(ten))
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (!chuoiHopLe(nxb))
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (nam < 1 || nam > 9999)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (tong < 0)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (con < 0 || con > tong)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (!std::isfinite(gia) || gia < 0)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    maTaiLieu = ma;
    tenTaiLieu = ten;
    nhaXuatBan = nxb;
    namXuatBan = nam;
    soLuongTong = tong;
    soLuongCon = con;
    giaTri = gia;
}

TaiLieu::~TaiLieu()
{
}

bool TaiLieu::chuoiHopLe(const std::string& chuoi)
{
    if (chuoi.find_first_of("\r\n") != std::string::npos)
    {
        return false;
    }

    for (unsigned char kyTu : chuoi)
    {
        if (!std::isspace(kyTu))
        {
            return true;
        }
    }

    return false;
}

bool TaiLieu::ngayHopLe(const std::string& ngay)
{
    if (ngay.size() != 10)
    {
        return false;
    }

    if (ngay[2] != '/' || ngay[5] != '/')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
        {
            continue;
        }

        unsigned char kyTu = static_cast<unsigned char>(ngay[i]);
        if (!std::isdigit(kyTu))
        {
            return false;
        }
    }

    int ngaySo = std::stoi(ngay.substr(0, 2));
    int thang = std::stoi(ngay.substr(3, 2));
    int nam = std::stoi(ngay.substr(6, 4));

    if (nam < 1)
    {
        return false;
    }

    if (thang < 1 || thang > 12)
    {
        return false;
    }

    int soNgay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool namNhuan = false;

    if (nam % 400 == 0)
    {
        namNhuan = true;
    }
    else if (nam % 4 == 0 && nam % 100 != 0)
    {
        namNhuan = true;
    }

    if (namNhuan)
    {
        soNgay[1] = 29;
    }

    if (ngaySo < 1 || ngaySo > soNgay[thang - 1])
    {
        return false;
    }

    return true;
}

void TaiLieu::nhap(std::istream& luong)
{
    std::string ma;
    std::string ten;
    std::string nxb;
    int nam;
    int tong;
    int con;
    double gia;

    luong >> std::quoted(ma);
    luong >> std::quoted(ten);
    luong >> std::quoted(nxb);
    luong >> nam;
    luong >> tong;
    luong >> con;
    luong >> gia;

    if (!luong)
    {
        throw std::invalid_argument("Khong doc du thong tin");
    }

    if (!chuoiHopLe(ma))
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (!chuoiHopLe(ten))
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (!chuoiHopLe(nxb))
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (nam < 1 || nam > 9999)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (tong < 0)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (con < 0 || con > tong)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    if (!std::isfinite(gia) || gia < 0)
    {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }

    // Cap nhat sau khi tat ca thong tin chung da hop le.
    maTaiLieu = ma;
    tenTaiLieu = ten;
    nhaXuatBan = nxb;
    namXuatBan = nam;
    soLuongTong = tong;
    soLuongCon = con;
    giaTri = gia;
}

void TaiLieu::xuatChung() const
{
    std::cout << layLoai();
    std::cout << " | " << maTaiLieu;
    std::cout << " | " << tenTaiLieu;
    std::cout << " | " << nhaXuatBan;
    std::cout << " | " << namXuatBan;
    std::cout << " | " << soLuongCon << '/' << soLuongTong;
    std::cout << " | " << giaTri;
}

void TaiLieu::ghiChung(std::ostream& tep) const
{
    tep << std::quoted(maTaiLieu);
    tep << ' ' << std::quoted(tenTaiLieu);
    tep << ' ' << std::quoted(nhaXuatBan);
    tep << ' ' << namXuatBan;
    tep << ' ' << soLuongTong;
    tep << ' ' << soLuongCon;
    tep << ' ' << std::setprecision(17) << giaTri;
}

std::string TaiLieu::layMa() const
{
    return maTaiLieu;
}

std::string TaiLieu::layTen() const
{
    return tenTaiLieu;
}

int TaiLieu::layNam() const
{
    return namXuatBan;
}

double TaiLieu::layGiaTri() const
{
    return giaTri;
}

int TaiLieu::laySoLuongTong() const
{
    return soLuongTong;
}

int TaiLieu::laySoLuongCon() const
{
    return soLuongCon;
}

bool TaiLieu::kiemTraConTaiLieu(int soLuong) const
{
    if (soLuong <= 0)
    {
        return false;
    }

    if (soLuong > soLuongCon)
    {
        return false;
    }

    return true;
}

bool TaiLieu::giamSoLuong(int soLuong)
{
    if (!kiemTraConTaiLieu(soLuong))
    {
        return false;
    }

    soLuongCon -= soLuong;
    return true;
}

bool TaiLieu::tangSoLuong(int soLuong)
{
    if (soLuong <= 0)
    {
        return false;
    }

    int soDangMuon = soLuongTong - soLuongCon;
    if (soLuong > soDangMuon)
    {
        return false;
    }

    soLuongCon += soLuong;
    return true;
}
