#ifndef QUANLYPHIEUMUON_H
#define QUANLYPHIEUMUON_H
#include "PhieuMuon.h"
#include "DanhSachQuanLy.h"
class QuanLyTaiLieu;
class QuanLyDocGia;
class QuanLyViPham;

class QuanLyPhieuMuon{
private:
    DanhSachQuanLy<PhieuMuon> ds;

public:
    PhieuMuon* timTheoMa(const std::string& ma);
    const PhieuMuon* timTheoMa(const std::string& ma) const;
    bool lapPhieu(const PhieuMuon& phieu, QuanLyDocGia& docGia, QuanLyTaiLieu& taiLieu);
    bool traTaiLieu(const std::string& ma, const std::string& ngay,
                   QuanLyDocGia& docGia, QuanLyTaiLieu& taiLieu, QuanLyViPham& viPham);
    int lietKeTheoDocGia(const std::string& ma) const;
    int lietKeDocGiaMuonTaiLieu(const std::string& ma, const QuanLyDocGia& docGia) const;
    bool coThamChieuDocGia(const std::string& ma) const;
    bool coThamChieuTaiLieu(const std::string& ma) const;
    long long demDangMuonDocGia(const std::string& ma) const;
    long long demDangMuonTaiLieu(const std::string& ma) const;
    long long demLuotMuonTaiLieu(const std::string& ma) const;
    int laySoLuong() const;
    const PhieuMuon* lay(int k) const;
    void hienThi() const;
    void lietKeQuaHan(const QuanLyDocGia& docGia) const;
    void sapXepTheoMa();
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
    void doi(QuanLyPhieuMuon& khac);
};
#endif
