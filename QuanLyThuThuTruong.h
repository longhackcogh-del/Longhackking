#ifndef QUANLYTHUTHUTRUONG_H
#define QUANLYTHUTHUTRUONG_H
#include "ThuThuTruong.h"
#include "DanhSachQuanLy.h"

class QuanLyThuThuTruong{
private:
    DanhSachQuanLy<ThuThuTruong> ds;
    int timViTri(const std::string& ma) const;

public:
    bool them(const ThuThuTruong& nguoi);
    bool sua(const std::string& ma, const ThuThuTruong& nguoi);
    bool xoa(const std::string& ma);
    ThuThuTruong* timTheoMa(const std::string& ma);
    const ThuThuTruong* timTheoMa(const std::string& ma) const;
    int timTheoSoNhanVien(int soNhanVien) const;
    int laySoLuong() const;
    const ThuThuTruong* lay(int k) const;
    void hienThi() const;
    void sapXepTheoPhuCap();
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
    void doi(QuanLyThuThuTruong& khac);
};
#endif
