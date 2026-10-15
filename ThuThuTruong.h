#ifndef THUTHUTRUONG_H
#define THUTHUTRUONG_H
#include "GiangVien.h"
#include "NhanVienThuThu.h"
class QuanLyViPham;

class ThuThuTruong : public GiangVien, public NhanVienThuThu{
private:
    std::string khuVucQuanLy;
    int soNhanVienQuanLy;
    double heSoPhuCap;

public:
    ThuThuTruong();
    ThuThuTruong(std::string maNguoi, std::string ten, std::string ngay,
                 std::string email, std::string dienThoai,
                 std::string maDocGia, std::string maGiangVien,
                 std::string boMon, std::string hocVi, int soNam,
                 std::string maNhanVien, std::string ca, std::string chuc,
                 double luong, double heSo, std::string khuVuc, int soNhanVien, double phuCap);
    ~ThuThuTruong() override;
    bool nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    bool hopLe() const override;
    void ghi(std::ostream& tep) const override;
    std::string layMa() const;
    int laySoNhanVienQuanLy() const;
    double layPhuCap() const;
    double tinhThuNhap() const;
    void xemNhatKyViPham(const QuanLyViPham& quanLy) const;
    bool duyetViPham(QuanLyViPham& quanLy, const std::string& ma) const;
};
#endif
