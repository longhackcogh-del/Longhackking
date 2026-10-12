#ifndef TAILIEU_H
#define TAILIEU_H

#include <string>
#include <iostream>

class TaiLieu
{
protected:
    std::string maTaiLieu;
    std::string tenTaiLieu;
    std::string nhaXuatBan;
    int namXuatBan;
    int soLuongTong;
    int soLuongCon;
    double giaTri;

    void xuatChung() const;
    void ghiChung(std::ostream& tep) const;

public:
    TaiLieu();

    TaiLieu(
        std::string ma,
        std::string ten,
        std::string nxb,
        int nam,
        int tong,
        int con,
        double gia
    );

    virtual ~TaiLieu();

    virtual void nhap(std::istream& luong = std::cin);
    virtual void xuat() const = 0;
    virtual double tinhTienPhat(int soNgayTre) const = 0;
    virtual std::string layLoai() const = 0;
    virtual void ghi(std::ostream& tep) const = 0;

    std::string layMa() const;
    std::string layTen() const;
    int layNam() const;
    double layGiaTri() const;
    int laySoLuongTong() const;
    int laySoLuongCon() const;

    bool kiemTraConTaiLieu(int soLuong = 1) const;
    bool giamSoLuong(int soLuong = 1);
    bool tangSoLuong(int soLuong = 1);

    static bool chuoiHopLe(const std::string& chuoi);
    static bool ngayHopLe(const std::string& ngay);
};

#endif
