#ifndef QUANLYTHUVIEN_H
#define QUANLYTHUVIEN_H
#include "QuanLyTaiLieu.h"
#include "QuanLyDocGia.h"
#include "QuanLyNhanVien.h"
#include "QuanLyThuThuTruong.h"
#include "QuanLyPhieuMuon.h"
#include "QuanLyViPham.h"

class QuanLyThuVien{
private:
    QuanLyTaiLieu taiLieu;
    QuanLyDocGia docGia;
    QuanLyNhanVien nhanVien;
    QuanLyThuThuTruong thuThuTruong;
    QuanLyPhieuMuon phieuMuon;
    QuanLyViPham viPham;
    ThuThuTruong* timThuThuTheoDocGia(const std::string& ma);
    void dongBoSoMuon(const std::string& ma);
    const NhanVienThuThu* timNhanVienTheoNguoi(const std::string& ma) const;
    const ThuThuTruong* timThuThuTheoNguoi(const std::string& ma) const;
    bool nhanThanKhop(const Nguoi& nguoi) const;
    void dongBoNhanThan(const Nguoi& nguoi);
    bool maNhanVienDaDuyet(const std::string& ma) const;
    bool kiemTraDocGiaThuThu(const ThuThuTruong& nguoi) const;
    bool themHoSoThuThu(const ThuThuTruong& nguoi);

public:
    QuanLyThuVien();
    QuanLyThuVien(const QuanLyThuVien&) = delete;
    QuanLyThuVien& operator=(const QuanLyThuVien&) = delete;
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
    // Chi nhan quyen so huu con tro khi thanh cong.
    bool themTaiLieu(TaiLieu* moi);
    bool themDocGia(DocGia* moi, int viTri);
    bool suaDocGia(const std::string& ma, DocGia* moi);
    bool xoaDocGia(const std::string& ma);
    bool themNhanVien(const NhanVienThuThu& nguoi);
    bool suaNhanVien(const std::string& ma, const NhanVienThuThu& nguoi);
    bool xoaNhanVien(const std::string& ma);
    bool chuyenThanhThuThuTruong(const std::string& ma, const ThuThuTruong& nguoi);
    bool chuyenThanhNhanVien(const std::string& ma);
    bool themThuThuTruong(const ThuThuTruong& nguoi);
    bool suaThuThuTruong(const std::string& ma, const ThuThuTruong& nguoi);
    bool xoaThuThuTruong(const std::string& ma);
    bool lapPhieu(const PhieuMuon& phieu);
    bool traTaiLieu(const std::string& ma, const std::string& ngay);
    bool ghiViPham(const std::string& maPhieu);
    bool duyetViPham(const std::string& ma, const std::string& maThuThu);
    bool kiemTraNhatQuan(std::string& loi) const;
    bool docToanBo(const std::string& thuMuc, std::string& loi);
    bool luuToanBo(const std::string& thuMuc, std::string& loi) const;
    void doiDuLieu(QuanLyThuVien& khac);
};
#endif
