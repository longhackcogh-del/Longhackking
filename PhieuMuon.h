#ifndef PHIEUMUON_H
#define PHIEUMUON_H
#include "NhapXuat.h"
class DocGia;
class TaiLieu;

class PhieuMuon{
private:
    std::string maPhieu;
    std::string maDocGia;
    std::string maTaiLieu;
    std::string ngayMuon;
    std::string hanTra;
    std::string ngayTra;
    std::string trangThai;
    int soLuongMuon;
    double tienPhat;

public:
    PhieuMuon();
    PhieuMuon(std::string ma, std::string docGia, std::string taiLieu,
              std::string ngay, std::string han, int soLuong);
    ~PhieuMuon();
    bool nhap(std::istream& luong = std::cin);
    bool doc(std::istream& tep);
    void ghi(std::ostream& tep) const;
    bool hopLe() const;
    bool lapPhieu(DocGia& docGia, TaiLieu& taiLieu);
    bool traTaiLieu(DocGia& docGia, TaiLieu& taiLieu, const std::string& ngay);
    int tinhSoNgayTre(const std::string& ngay) const;
    double tinhTienPhat(const TaiLieu& taiLieu, const std::string& ngay) const;
    bool quaHan(const std::string& ngay) const;
    bool dangMuon() const;
    std::string layMa() const;
    std::string layMaDocGia() const;
    std::string layMaTaiLieu() const;
    std::string layNgayMuon() const;
    std::string layNgayTra() const;
    int laySoLuong() const;
    double layTienPhat() const;
    bool operator<(const PhieuMuon& khac) const;
    friend bool kiemTraHanMuon(const DocGia&, const PhieuMuon&);
    friend std::ostream& operator<<(std::ostream&, const PhieuMuon&);
};
#endif
