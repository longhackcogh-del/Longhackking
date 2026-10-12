#ifndef TAPCHI_H
#define TAPCHI_H

#include "TaiLieu.h"

class TapChi : public TaiLieu
{
private:
    int soPhatHanh;
    int thangPhatHanh;
    std::string linhVuc;

public:
    TapChi();

    TapChi(
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
    );

    ~TapChi() override;

    void nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    double tinhTienPhat(int soNgayTre) const override;

    std::string layLoai() const override;
    void ghi(std::ostream& tep) const override;
};

#endif
