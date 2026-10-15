#ifndef GIANGVIEN_H
#define GIANGVIEN_H
#include "DocGia.h"
class GiangVien : public DocGia{
protected:
    std::string maGiangVien;
    std::string boMon;
    std::string hocVi;
    int soNamCongTac;
    bool nhapGiangVienRieng(std::istream& luong);
    void xuatGiangVienRieng() const;
    void ghiGiangVienRieng(std::ostream& tep) const;
public:
    GiangVien();
    GiangVien(std::string maNguoi, std::string ten, std::string ngay,
           std::string email, std::string dienThoai, std::string maDocGia,
           int soMuon, bool hoatDong, std::string maGiangVien, std::string boMon, std::string hocVi, int soNamCongTac);
    ~GiangVien() override;
    bool nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    bool hopLe() const override;
    int layGioiHanMuon() const override;
    std::string layLoai() const override;
    void ghi(std::ostream& tep) const override;
};
#endif
