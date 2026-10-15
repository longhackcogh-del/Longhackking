#ifndef QUANLYTHUVIEN_H
#define QUANLYTHUVIEN_H
#include "QuanLyTaiLieu.h"
#include "QuanLyDocGia.h"
#include "QuanLyNhanVien.h"
#include "QuanLyThuThuTruong.h"
#include "QuanLyPhieuMuon.h"
#include "QuanLyViPham.h"

// Dieu phoi du lieu lien quan khi doc/ghi toan he thong.
class QuanLyThuVien{
private:
    QuanLyTaiLieu taiLieu;
    QuanLyDocGia docGia;
    QuanLyNhanVien nhanVien;
    QuanLyThuThuTruong thuThuTruong;
    QuanLyPhieuMuon phieuMuon;
    QuanLyViPham viPham;

public:
    QuanLyThuVien();
    QuanLyTaiLieu& layTaiLieu();
    QuanLyDocGia& layDocGia();
    QuanLyNhanVien& layNhanVien();
    QuanLyThuThuTruong& layThuThuTruong();
    QuanLyPhieuMuon& layPhieuMuon();
    QuanLyViPham& layViPham();
    const QuanLyTaiLieu& layTaiLieu() const;
    const QuanLyDocGia& layDocGia() const;
    const QuanLyNhanVien& layNhanVien() const;
    const QuanLyThuThuTruong& layThuThuTruong() const;
    const QuanLyPhieuMuon& layPhieuMuon() const;
    const QuanLyViPham& layViPham() const;
    bool kiemTraNhatQuan(std::string& loi) const;
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
};
#endif
