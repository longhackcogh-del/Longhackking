#ifndef NHATKYVIPHAM_H
#define NHATKYVIPHAM_H
#include "NhapXuat.h"

class NhatKyViPham{
private:
    std::string maViPham;
    std::string maPhieu;
    std::string maDocGia;
    std::string loaiViPham;
    int soNgayTre;
    double soTienPhat;
    bool daThanhToan;
    std::string maNguoiDuyet;

public:
    NhatKyViPham();
    NhatKyViPham(std::string ma, std::string phieu, std::string docGia, int soNgay, double tien);
    ~NhatKyViPham();
    bool nhap(std::istream& luong = std::cin);
    bool hopLe() const;
    void xuat() const;
    void ghi(std::ostream& tep) const;
    bool thanhToanPhat();
    bool duyet(const std::string& maThuThu);
    std::string layMa() const;
    std::string layMaPhieu() const;
    std::string layMaDocGia() const;
    int laySoNgayTre() const;
    double layTienPhat() const;
    bool layDaThanhToan() const;
    std::string layNguoiDuyet() const;
};
#endif
