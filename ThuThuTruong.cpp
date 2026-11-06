#include "ThuThuTruong.h"
#include "QuanLyViPham.h"
#include <iomanip>
using namespace std;

//=====ham khoi tao=====
ThuThuTruong::ThuThuTruong(){
    soNhanVienQuanLy = 0;
    heSoPhuCap = 0;
}

ThuThuTruong::ThuThuTruong(string maNguoi, string ten, string ngay,
                         string email, string dienThoai,
                         string maDocGia, string maGiangVien,
                         string boMon, string hocVi, int soNam,
                         string maNhanVien, string ca, string chuc,
                         double luong, double heSo, string khuVuc, int soNhanVien, double phuCap)
    : Nguoi(maNguoi, ten, ngay, email, dienThoai),
      GiangVien(maNguoi, ten, ngay, email, dienThoai, maDocGia, 0, true,
                maGiangVien, boMon, hocVi, soNam),
      NhanVienThuThu(maNguoi, ten, ngay, email, dienThoai, maNhanVien, ca, chuc, luong, heSo){
    khuVucQuanLy = khuVuc;
    soNhanVienQuanLy = soNhanVien;
    heSoPhuCap = phuCap;
}

ThuThuTruong::~ThuThuTruong(){
}

bool ThuThuTruong::hopLe() const{
    return GiangVien::hopLe() && NhanVienThuThu::hopLe()
        && chuoiHopLe(khuVucQuanLy) && soNhanVienQuanLy >= 0
        && isfinite(heSoPhuCap) && heSoPhuCap >= 0
        && isfinite(tinhThuNhap());
}

//=====ham nhap=====
bool ThuThuTruong::nhap(istream& luong){
    ThuThuTruong tam;
    if(!tam.Nguoi::nhap(luong)){
        return false;
    }
    if(!tam.nhapDocGiaRieng(luong) || !tam.nhapGiangVienRieng(luong)){
        return false;
    }
    if(!tam.nhapNhanVienRieng(luong)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap khu vuc quan ly: ", tam.khuVucQuanLy)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so nhan vien quan ly: ", tam.soNhanVienQuanLy)){
        return false;
    }
    if(!nhapSo(luong, "Nhap he so phu cap: ", tam.heSoPhuCap)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham xuat=====
void ThuThuTruong::xuat() const{
    Nguoi::xuat();
    xuatDocGiaRieng();
    xuatGiangVienRieng();
    xuatNhanVienRieng();
    cout << "Khu vuc quan ly: " << khuVucQuanLy << '\n';
    cout << "So nhan vien quan ly: " << soNhanVienQuanLy << '\n';
    cout << "He so phu cap: " << heSoPhuCap << '\n';
}

//=====ham tinh thu nhap=====
double ThuThuTruong::tinhThuNhap() const{
    return tinhLuong() + heSoPhuCap * 2000000;
}

string ThuThuTruong::layMa() const{
    return NhanVienThuThu::layMa();
}

int ThuThuTruong::laySoNhanVienQuanLy() const{
    return soNhanVienQuanLy;
}

double ThuThuTruong::layPhuCap() const{
    return heSoPhuCap;
}

void ThuThuTruong::ghi(ostream& tep) const{
    ghiNguoi(tep);
    ghiDocGiaRieng(tep);
    ghiGiangVienRieng(tep);
    ghiNhanVienRieng(tep);
    tep << khuVucQuanLy << '\n';
    tep << soNhanVienQuanLy << '\n';
    tep << setprecision(17) << heSoPhuCap << '\n';
}

//=====ham xem va duyet vi pham=====
void ThuThuTruong::xemNhatKyViPham(const QuanLyViPham& quanLy) const{
    quanLy.hienThi();
}

bool ThuThuTruong::duyetViPham(QuanLyViPham& quanLy, const string& ma) const{
    if(!hopLe()){
        return false;
    }
    return quanLy.duyet(ma, layMa());
}
