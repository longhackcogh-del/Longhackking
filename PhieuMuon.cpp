#include "PhieuMuon.h"
#include "DocGia.h"
#include "TaiLieu.h"
#include "ThuatToan.h"
#include <iomanip>
using namespace std;

//=====ham khoi tao=====
PhieuMuon::PhieuMuon(){
    soLuongMuon = 0;
    tienPhat = 0;
    ngayTra = "-";
    trangThai = "Dang muon";
}

PhieuMuon::PhieuMuon(string ma, string docGia, string taiLieu,
                     string ngay, string han, int soLuong){
    maPhieu = ma;
    maDocGia = docGia;
    maTaiLieu = taiLieu;
    ngayMuon = ngay;
    hanTra = han;
    soLuongMuon = soLuong;
    ngayTra = "-";
    trangThai = "Dang muon";
    tienPhat = 0;
}

PhieuMuon::~PhieuMuon(){
}

bool PhieuMuon::hopLe() const{
    if(!chuoiHopLe(maPhieu) || !chuoiHopLe(maDocGia) || !chuoiHopLe(maTaiLieu)){
        return false;
    }
    if(!ngayHopLe(ngayMuon) || !ngayHopLe(hanTra) || doiNgay(hanTra) < doiNgay(ngayMuon)){
        return false;
    }
    if(soLuongMuon <= 0 || !isfinite(tienPhat) || tienPhat < 0){
        return false;
    }
    if(trangThai == "Dang muon"){
        return ngayTra == "-" && tienPhat == 0;
    }
    if(trangThai == "Da tra"){
        if(!ngayHopLe(ngayTra) || doiNgay(ngayTra) < doiNgay(ngayMuon)){
            return false;
        }
        // Tra dung han khong phat qua han.
        if(doiNgay(ngayTra) <= doiNgay(hanTra) && tienPhat != 0){
            return false;
        }
        return true;
    }
    return false;
}

//=====ham nhap=====
bool PhieuMuon::nhap(istream& luong){
    PhieuMuon tam;
    if(!nhapChuoi(luong, "Nhap ma phieu: ", tam.maPhieu)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ma doc gia: ", tam.maDocGia)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ma tai lieu: ", tam.maTaiLieu)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap ngay muon (dd/mm/yyyy): ", tam.ngayMuon)){
        return false;
    }
    if(!nhapChuoi(luong, "Nhap han tra (dd/mm/yyyy): ", tam.hanTra)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so luong muon: ", tam.soLuongMuon)){
        return false;
    }
    if(!tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

//=====ham lap phieu=====
bool PhieuMuon::lapPhieu(DocGia& docGia, TaiLieu& taiLieu){
    if(!hopLe() || !dangMuon()){
        return false;
    }
    if(docGia.layMa() != maDocGia || taiLieu.layMa() != maTaiLieu){
        return false;
    }
    if(!kiemTraDieuKienMuon(docGia, taiLieu)){
        return false;
    }
    if(!docGia.kiemTraDieuKienMuon(soLuongMuon) || !taiLieu.kiemTraConTaiLieu(soLuongMuon)){
        return false;
    }
    docGia.tangSoDangMuon(soLuongMuon);
    taiLieu.giamSoLuong(soLuongMuon);
    return true;
}

//=====ham tinh so ngay tre=====
int PhieuMuon::tinhSoNgayTre(const string& ngay) const{
    if(!ngayHopLe(ngay) || !hopLe() || doiNgay(ngay) < doiNgay(ngayMuon)){
        return -1;
    }
    return timMax(0, doiNgay(ngay) - doiNgay(hanTra));
}

double PhieuMuon::tinhTienPhat(const TaiLieu& taiLieu, const string& ngay) const{
    int soNgayTre = tinhSoNgayTre(ngay);
    if(!taiLieu.hopLe() || taiLieu.layMa() != maTaiLieu || soNgayTre < 0){
        return -1;
    }
    double phat = taiLieu.tinhTienPhat(soNgayTre) * soLuongMuon;
    if(!isfinite(phat) || phat < 0 || (soNgayTre == 0 && phat != 0)){
        return -1;
    }
    return phat;
}

//=====ham tra tai lieu=====
bool PhieuMuon::traTaiLieu(DocGia& docGia, TaiLieu& taiLieu, const string& ngay){
    int soNgayTre = tinhSoNgayTre(ngay);
    if(!hopLe() || !dangMuon() || soNgayTre < 0){
        return false;
    }
    if(docGia.layMa() != maDocGia || taiLieu.layMa() != maTaiLieu){
        return false;
    }
    // Kiem tra truoc khi thay doi kho va so dang muon.
    if(!docGia.hopLe() || !taiLieu.hopLe()){
        return false;
    }
    if(docGia.laySoDangMuon() < soLuongMuon
       || taiLieu.laySoLuongTong() - taiLieu.laySoLuongCon() < soLuongMuon){
        return false;
    }
    double phat = tinhTienPhat(taiLieu, ngay);
    if(!isfinite(phat) || phat < 0 || (soNgayTre == 0 && phat != 0)){
        return false;
    }
    taiLieu.tangSoLuong(soLuongMuon);
    docGia.giamSoDangMuon(soLuongMuon);
    ngayTra = ngay;
    trangThai = "Da tra";
    tienPhat = phat;
    return true;
}

bool PhieuMuon::quaHan(const string& ngay) const{
    return dangMuon() && tinhSoNgayTre(ngay) > 0;
}

bool PhieuMuon::dangMuon() const{
    return trangThai == "Dang muon";
}

//=====ham ban kiem tra han muon=====
bool kiemTraHanMuon(const DocGia& docGia, const PhieuMuon& phieu){
    return docGia.maDocGia == phieu.maDocGia && phieu.quaHan(ngayHienTai());
}

//=====ham nap chong toan tu=====
bool PhieuMuon::operator<(const PhieuMuon& khac) const{
    return maPhieu < khac.maPhieu;
}

ostream& operator<<(ostream& luong, const PhieuMuon& phieu){
    luong << "Ma phieu: " << phieu.maPhieu << '\n';
    luong << "Doc gia: " << phieu.maDocGia << '\n';
    luong << "Tai lieu: " << phieu.maTaiLieu << '\n';
    luong << "Ngay muon: " << phieu.ngayMuon << '\n';
    luong << "Han tra: " << phieu.hanTra << '\n';
    luong << "Ngay tra: " << phieu.ngayTra << '\n';
    luong << "Trang thai: " << phieu.trangThai << '\n';
    luong << "So luong: " << phieu.soLuongMuon << '\n';
    luong << "Tien phat: ";
    xuatTien(luong, phieu.tienPhat);
    luong << '\n';
    return luong;
}

//=====ham doc ghi tep=====
void PhieuMuon::ghi(ostream& tep) const{
    tep << maPhieu << '\n';
    tep << maDocGia << '\n';
    tep << maTaiLieu << '\n';
    tep << ngayMuon << '\n';
    tep << hanTra << '\n';
    tep << soLuongMuon << '\n';
    tep << ngayTra << '\n';
    tep << trangThai << '\n';
    tep << setprecision(17) << tienPhat << '\n';
}

bool PhieuMuon::doc(istream& tep){
    PhieuMuon tam;
    if(!tam.nhap(tep)){
        return false;
    }
    if(!nhapChuoi(tep, "", tam.ngayTra) || !nhapChuoi(tep, "", tam.trangThai)){
        return false;
    }
    if(!nhapSo(tep, "", tam.tienPhat) || !tam.hopLe()){
        return false;
    }
    *this = tam;
    return true;
}

string PhieuMuon::layMa() const{
    return maPhieu;
}

string PhieuMuon::layMaDocGia() const{
    return maDocGia;
}

string PhieuMuon::layMaTaiLieu() const{
    return maTaiLieu;
}

string PhieuMuon::layNgayMuon() const{
    return ngayMuon;
}

string PhieuMuon::layNgayTra() const{
    return ngayTra;
}

int PhieuMuon::laySoLuong() const{
    return soLuongMuon;
}

double PhieuMuon::layTienPhat() const{
    return tienPhat;
}
