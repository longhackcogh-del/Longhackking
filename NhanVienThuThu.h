#ifndef NHANVIENTHUTHU_H
#define NHANVIENTHUTHU_H
#include "Nguoi.h"

class NhanVienThuThu : virtual public Nguoi{
protected:
    std::string maNhanVien;
    std::string caLamViec;
    std::string chucVu;
    double luongCoBan;
    double heSoLuong;
    bool nhapNhanVienRieng(std::istream& luong);
    void xuatNhanVienRieng() const;
    void ghiNhanVienRieng(std::ostream& tep) const;

public:
    NhanVienThuThu();
    NhanVienThuThu(std::string maNguoi, std::string ten, std::string ngay,
                  std::string email, std::string dienThoai, std::string maNhanVien,
                  std::string ca, std::string chuc, double luong, double heSo);
    ~NhanVienThuThu() override;
    bool nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    bool hopLe() const override;
    std::string layMa() const;
    std::string layCa() const;
    double layHeSoLuong() const;
    double tinhLuong() const;
    virtual void ghi(std::ostream& tep) const;
};
#endif
