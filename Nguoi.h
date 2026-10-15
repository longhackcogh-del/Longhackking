#ifndef NGUOI_H
#define NGUOI_H
#include "NhapXuat.h"

class Nguoi{
protected:
    std::string maNguoi;
    std::string hoTen;
    std::string ngaySinh;
    std::string email;
    std::string soDienThoai;
    void ghiNguoi(std::ostream& tep) const;

public:
    Nguoi();
    Nguoi(std::string ma, std::string ten, std::string ngay,
          std::string thu, std::string dienThoai);
    virtual ~Nguoi();
    virtual bool nhap(std::istream& luong = std::cin);
    virtual void xuat() const;
    virtual bool hopLe() const;
    std::string layMaNguoi() const;
    std::string layHoTen() const;
};
#endif
