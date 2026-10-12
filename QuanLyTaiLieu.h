#ifndef QUANLYTAILIEU_H
#define QUANLYTAILIEU_H

#include "TaiLieu.h"
#include "DanhSachQuanLy.h"

#include <memory>

class QuanLyTaiLieu
{
private:
    DanhSachQuanLy<TaiLieu*> ds;
    bool (*kiemTraPhieuMuon)(const std::string&);

    int timViTri(const std::string& ma) const;
    void quickSort(int trai, int phai);
    bool dangMuon(const TaiLieu& taiLieu) const;

public:
    QuanLyTaiLieu();
    ~QuanLyTaiLieu();

    // Khong sao chep danh sach so huu con tro de tranh giai phong hai lan.
    QuanLyTaiLieu(const QuanLyTaiLieu&) = delete;
    QuanLyTaiLieu& operator=(const QuanLyTaiLieu&) = delete;

    void ganKiemTraPhieuMuon(bool (*ham)(const std::string&));

    // unique_ptr giup huy doi tuong moi neu them hoac sua bi tu choi.
    bool them(std::unique_ptr<TaiLieu> taiLieu);
    bool sua(const std::string& ma, std::unique_ptr<TaiLieu> taiLieu);
    bool xoa(const std::string& ma);

    // Con tro tra ve chi duoc muon, khong duoc delete.
    TaiLieu* timTheoMa(const std::string& ma) const;
    int timTheoTen(
        const std::string& ten,
        std::ostream& luong = std::cout
    ) const;

    int laySoLuong() const;
    const TaiLieu* layTaiLieu(int viTri) const;
    void hienThi() const;

    void sapXepTheoNam();
    void sapXepTheoGiaTri();
    void thongKe(std::ostream& luong = std::cout) const;

    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
};

#endif
