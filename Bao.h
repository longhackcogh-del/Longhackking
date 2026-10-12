#ifndef BAO_H
#define BAO_H

#include "TaiLieu.h"

class Bao : public TaiLieu
{
private:
    std::string ngayPhatHanh;
    std::string loaiBao;

public:
    Bao();

    Bao(
        std::string ma,
        std::string ten,
        std::string nxb,
        int nam,
        int tong,
        int con,
        double gia,
        std::string ngayPhatHanh,
        std::string loaiBao
    );

    ~Bao() override;

    void nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    double tinhTienPhat(int soNgayTre) const override;

    std::string layLoai() const override;
    void ghi(std::ostream& tep) const override;
};

#endif
