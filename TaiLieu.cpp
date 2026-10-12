#include "TaiLieu.h"
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <cctype>
TaiLieu::TaiLieu() : TaiLieu("CHUA_NHAP", "Chua nhap", "Chua nhap", 1, 0, 0, 0) {}
TaiLieu::TaiLieu(std::string ma, std::string ten, std::string nxb, int nam,
                 int tong, int con, double gia)
    : maTaiLieu(ma), tenTaiLieu(ten), nhaXuatBan(nxb), namXuatBan(nam),
      soLuongTong(tong), soLuongCon(con), giaTri(gia) {
    if (!chuoiHopLe(ma) || !chuoiHopLe(ten) || !chuoiHopLe(nxb) ||
        nam < 1 || nam > 9999 || tong < 0 || con < 0 || con > tong ||
        !std::isfinite(gia) || gia < 0) {
        throw std::invalid_argument("Thong tin chung khong hop le");
    }
}
TaiLieu::~TaiLieu() {}
bool TaiLieu::chuoiHopLe(const std::string& chuoi) {
    if (chuoi.find_first_of("\r\n") != std::string::npos) return false;
    for (unsigned char kyTu : chuoi) {
        if (!std::isspace(kyTu)) return true;
    }
    return false;
}
bool TaiLieu::ngayHopLe(const std::string& ngay) {
    if (ngay.size() != 10 || ngay[2] != '/' || ngay[5] != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !std::isdigit(static_cast<unsigned char>(ngay[i]))) return false;
    }
    int ngaySo = std::stoi(ngay.substr(0, 2));
    int thang = std::stoi(ngay.substr(3, 2));
    int nam = std::stoi(ngay.substr(6, 4));
    if (nam < 1 || thang < 1 || thang > 12) return false;
    int soNgay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0)) soNgay[1] = 29;
    return ngaySo >= 1 && ngaySo <= soNgay[thang - 1];
}
void TaiLieu::nhap(std::istream& luong) {
    std::string ma, ten, nxb;
    int nam, tong, con;
    double gia;
    if (!(luong >> std::quoted(ma) >> std::quoted(ten) >> std::quoted(nxb)
          >> nam >> tong >> con >> gia)) throw std::invalid_argument("Khong doc du thong tin");
    if (!chuoiHopLe(ma) || !chuoiHopLe(ten) || !chuoiHopLe(nxb) ||
        nam < 1 || nam > 9999 || tong < 0 || con < 0 || con > tong ||
        !std::isfinite(gia) || gia < 0) throw std::invalid_argument("Thong tin chung khong hop le");
    maTaiLieu = ma;
    tenTaiLieu = ten;
    nhaXuatBan = nxb;
    namXuatBan = nam;
    soLuongTong = tong;
    soLuongCon = con;
    giaTri = gia;
}
void TaiLieu::xuatChung() const {
    std::cout << layLoai() << " | " << maTaiLieu << " | " << tenTaiLieu
              << " | " << nhaXuatBan << " | " << namXuatBan << " | "
              << soLuongCon << '/' << soLuongTong << " | " << giaTri;
}
void TaiLieu::ghiChung(std::ostream& tep) const {
    tep << std::quoted(maTaiLieu) << ' ' << std::quoted(tenTaiLieu) << ' '
        << std::quoted(nhaXuatBan) << ' ' << namXuatBan << ' ' << soLuongTong
        << ' ' << soLuongCon << ' ' << std::setprecision(17) << giaTri;
}
std::string TaiLieu::layMa() const { return maTaiLieu; }
std::string TaiLieu::layTen() const { return tenTaiLieu; }
int TaiLieu::layNam() const { return namXuatBan; }
double TaiLieu::layGiaTri() const { return giaTri; }
int TaiLieu::laySoLuongTong() const { return soLuongTong; }
int TaiLieu::laySoLuongCon() const { return soLuongCon; }
bool TaiLieu::kiemTraConTaiLieu(int soLuong) const { return soLuong > 0 && soLuong <= soLuongCon; }
bool TaiLieu::giamSoLuong(int soLuong) {
    if (!kiemTraConTaiLieu(soLuong)) return false;
    soLuongCon -= soLuong;
    return true;
}
bool TaiLieu::tangSoLuong(int soLuong) {
    if (soLuong <= 0 || soLuong > soLuongTong - soLuongCon) return false;
    soLuongCon += soLuong;
    return true;
}
