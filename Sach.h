#ifndef SACH_H
#define SACH_H

#include "TaiLieu.h"

class Sach : public TaiLieu
{
private:
    std::string tacGia;
    std::string theLoai;
    std::string ISBN;
    int soTrang;

public:
    Sach();

    Sach(
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
    );

    ~Sach() override;

    void nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    double tinhTienPhat(int soNgayTre) const override;

    std::string layLoai() const override;
    void ghi(std::ostream& tep) const override;
};

#endif
