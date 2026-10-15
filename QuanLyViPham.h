#ifndef QUANLYVIPHAM_H
#define QUANLYVIPHAM_H
#include "NhatKyViPham.h"
#include "DanhSachQuanLy.h"
class PhieuMuon;

class QuanLyViPham{
private:
    DanhSachQuanLy<NhatKyViPham> ds;
    bool them(const NhatKyViPham& viPham);

public:
    bool ghiViPham(const PhieuMuon& phieu);
    NhatKyViPham* timTheoMa(const std::string& ma);
    const NhatKyViPham* timTheoMa(const std::string& ma) const;
    const NhatKyViPham* timTheoPhieu(const std::string& ma) const;
    int timTheoDocGia(const std::string& ma) const;
    int laySoLuong() const;
    const NhatKyViPham* lay(int k) const;
    void hienThi() const;
    void lietKeChuaThanhToan() const;
    bool thanhToanPhat(const std::string& ma);
    bool duyet(const std::string& ma, const std::string& nguoiDuyet);
    double tinhTongTienPhatChuaThanhToan() const;
    double tinhTongTienPhatDaThanhToan() const;
    int demViPham(const std::string& maDocGia) const;
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
    void doi(QuanLyViPham& khac);
};
#endif
