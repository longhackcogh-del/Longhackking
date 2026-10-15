#ifndef QUANLYNHANVIEN_H
#define QUANLYNHANVIEN_H
#include "NhanVienThuThu.h"
#include "DanhSachQuanLy.h"

class QuanLyNhanVien{
private:
    DanhSachQuanLy<NhanVienThuThu> ds;
    int timViTri(const std::string& ma) const;

public:
    bool them(const NhanVienThuThu& nguoi);
    bool sua(const std::string& ma, const NhanVienThuThu& nguoi);
    bool xoa(const std::string& ma);
    NhanVienThuThu* timTheoMa(const std::string& ma);
    const NhanVienThuThu* timTheoMa(const std::string& ma) const;
    int timTheoCa(const std::string& ca) const;
    int laySoLuong() const;
    const NhanVienThuThu* lay(int k) const;
    void hienThi() const;
    void sapXepTheoHeSoLuong();
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
    void doi(QuanLyNhanVien& khac);
};
#endif
