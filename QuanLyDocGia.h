#ifndef QUANLYDOCGIA_H
#define QUANLYDOCGIA_H
#include "DocGia.h"
#include "DanhSachQuanLy.h"
class QuanLyPhieuMuon;

class QuanLyDocGia{
private:
    DanhSachQuanLy<DocGia*> ds;
    const QuanLyPhieuMuon* phieuMuon;
    int timViTri(const std::string& ma) const;

public:
    QuanLyDocGia();
    ~QuanLyDocGia();
    QuanLyDocGia(const QuanLyDocGia&) = delete;
    QuanLyDocGia& operator=(const QuanLyDocGia&) = delete;
    void ganQuanLyPhieuMuon(const QuanLyPhieuMuon* quanLy);
    bool them(DocGia* docGia);
    bool chen(int k, DocGia* docGia);
    bool sua(const std::string& ma, DocGia* docGia);
    bool xoa(const std::string& ma);
    DocGia* timTheoMa(const std::string& ma) const;
    DocGia* timBangBam(const std::string& ma) const;
    int timTheoTen(const std::string& ten) const;
    int laySoLuong() const;
    DocGia* layDocGia(int k) const;
    void hienThi() const;
    void sapXepTheoSoMuon();
    bool luu(const std::string& thuMuc, std::string& loi) const;
    bool doc(const std::string& thuMuc, std::string& loi);
    void doi(QuanLyDocGia& khac);
};
#endif
