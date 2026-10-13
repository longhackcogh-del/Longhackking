#ifndef QUANLYTAILIEU_H
#define QUANLYTAILIEU_H
#include "TaiLieu.h"
#include "DanhSachQuanLy.h"

class QuanLyTaiLieu{
private:
    DanhSachQuanLy<TaiLieu*> ds;
    bool (*kiemTraPhieuMuon)(const std::string&);
    int timViTri(const std::string& ma) const;
    void quickSort(int trai, int phai);
    bool dangMuon(const TaiLieu& taiLieu) const;

public:
    QuanLyTaiLieu();
    ~QuanLyTaiLieu();
    QuanLyTaiLieu(const QuanLyTaiLieu&) = delete;
    QuanLyTaiLieu& operator=(const QuanLyTaiLieu&) = delete;
    void ganKiemTraPhieuMuon(bool (*ham)(const std::string&));
    // Chi nhan quyen so huu khi them/sua thanh cong.
    bool them(TaiLieu* taiLieu);
    bool sua(const std::string& ma, TaiLieu* taiLieu);
    bool xoa(const std::string& ma);
    TaiLieu* timTheoMa(const std::string& ma) const;
    TaiLieu* timNhiPhan(const std::string& ma) const;
    int timTheoTen(const std::string& ten, std::ostream& luong = std::cout) const;
    int laySoLuong() const;
    const TaiLieu* layTaiLieu(int viTri) const;
    void hienThi() const;
    void sapXepTheoNam();
    void sapXepTheoGiaTri();
    void thongKe(std::ostream& luong = std::cout) const;
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
    void doi(QuanLyTaiLieu& khac);
};
#endif
