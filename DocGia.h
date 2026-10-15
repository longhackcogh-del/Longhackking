#ifndef DOCGIA_H
#define DOCGIA_H
#include "Nguoi.h"
class TaiLieu;
class PhieuMuon;

class DocGia : virtual public Nguoi{
protected:
    std::string maDocGia;
    int soTaiLieuDangMuon;
    int gioiHanMuon;
    bool dangHoatDong;
    bool nhapDocGiaRieng(std::istream& luong);
    void xuatDocGiaRieng() const;
    void ghiDocGiaRieng(std::ostream& tep) const;

public:
    DocGia();
    DocGia(std::string ma, int soMuon, int gioiHan, bool hoatDong);
    ~DocGia() override;
    bool nhap(std::istream& luong = std::cin) override;
    void xuat() const override;
    bool hopLe() const override;
    virtual int layGioiHanMuon() const = 0;
    virtual std::string layLoai() const = 0;
    virtual void ghi(std::ostream& tep) const = 0;
    std::string layMa() const;
    int laySoDangMuon() const;
    bool layHoatDong() const;
    bool kiemTraDieuKienMuon(int soLuong = 1) const;
    bool tangSoDangMuon(int soLuong);
    bool giamSoDangMuon(int soLuong);
    long long operator+(const DocGia& khac) const;
    friend bool kiemTraHanMuon(const DocGia&, const PhieuMuon&);
    friend bool kiemTraDieuKienMuon(const DocGia&, const TaiLieu&);
};
#endif
