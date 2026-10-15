#ifndef SINHVIEN_H
#define SINHVIEN_H
#include "DocGia.h"
class SinhVien : public DocGia{
private:
    std::string maSinhVien;
    std::string lop;
    std::string khoa;
    std::string nganhHoc;

public:
    SinhVien();
    SinhVien(std::string maNguoi, std::string ten, std::string ngay,
           std::string email, std::string dienThoai, std::string maDocGia,
           int soMuon, bool hoatDong, std::string maSinhVien, std::string lop, std::string khoa, std::string nganhHoc);
    ~SinhVien() override;
    bool nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    bool hopLe() const override;
    int layGioiHanMuon() const override;
    std::string layLoai() const override;
    void ghi(std::ostream& tep) const override;
};
#endif
