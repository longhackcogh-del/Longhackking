#include "QuanLyViPham.h"
#include "PhieuMuon.h"
#include "Tep.h"
#include "TepMuonTra.h"
using namespace std;

//=====ham ghi vi pham=====
bool QuanLyViPham::them(const NhatKyViPham& viPham){
    if(!viPham.hopLe() || timTheoMa(viPham.layMa()) != nullptr
       || timTheoPhieu(viPham.layMaPhieu()) != nullptr){
        return false;
    }
    return ds.them(viPham);
}

bool QuanLyViPham::ghiViPham(const PhieuMuon& phieu){
    if(!phieu.hopLe() || phieu.dangMuon() || phieu.layTienPhat() <= 0){
        return false;
    }
    NhatKyViPham viPham("VP_" + phieu.layMa(), phieu.layMa(), phieu.layMaDocGia(),
                       phieu.tinhSoNgayTre(phieu.layNgayTra()), phieu.layTienPhat());
    return them(viPham);
}

//=====ham tim kiem=====
NhatKyViPham* QuanLyViPham::timTheoMa(const string& ma){
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

const NhatKyViPham* QuanLyViPham::timTheoMa(const string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

const NhatKyViPham* QuanLyViPham::timTheoPhieu(const string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaPhieu() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

int QuanLyViPham::timTheoDocGia(const string& ma) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaDocGia() == ma){
            ds[i].xuat();
            n++;
        }
    }
    return n;
}

int QuanLyViPham::demViPham(const string& maDocGia) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaDocGia() == maDocGia){
            n++;
        }
    }
    return n;
}

//=====ham xuat=====
void QuanLyViPham::hienThi() const{
    if(ds.laySoLuong() == 0){
        cout << "Danh sach rong\n";
    }
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].xuat();
    }
}

void QuanLyViPham::lietKeChuaThanhToan() const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(!ds[i].layDaThanhToan()){
            ds[i].xuat();
            n++;
        }
    }
    cout << "So vi pham chua thanh toan: " << n << '\n';
}

//=====ham thanh toan va duyet=====
bool QuanLyViPham::thanhToanPhat(const string& ma){
    NhatKyViPham* viPham = timTheoMa(ma);
    if(viPham == nullptr){
        return false;
    }
    return viPham->thanhToanPhat();
}

bool QuanLyViPham::duyet(const string& ma, const string& nguoiDuyet){
    NhatKyViPham* viPham = timTheoMa(ma);
    if(viPham == nullptr){
        return false;
    }
    return viPham->duyet(nguoiDuyet);
}

//=====ham tinh tong tien phat=====
double QuanLyViPham::tinhTongTienPhatChuaThanhToan() const{
    double tong = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(!ds[i].layDaThanhToan()){
            tong += ds[i].layTienPhat();
        }
    }
    return tong;
}

double QuanLyViPham::tinhTongTienPhatDaThanhToan() const{
    double tong = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layDaThanhToan()){
            tong += ds[i].layTienPhat();
        }
    }
    return tong;
}

int QuanLyViPham::laySoLuong() const{
    return ds.laySoLuong();
}

const NhatKyViPham* QuanLyViPham::lay(int k) const{
    if(!ds.viTriHopLe(k)){
        return nullptr;
    }
    return &ds[k];
}

//=====ham doc ghi tep=====
bool QuanLyViPham::luu(const string& thuMuc, string& loi) const{
    loi.clear();
    if(ds.laySoLuong() > 1000000){
        loi = "So ban ghi vuot gioi han dinh dang tep";
        return false;
    }
    // Kiem tra het danh sach truoc khi tao tep.
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(!ds[i].hopLe()){
            loi = "Khong luu ban ghi khong hop le";
            return false;
        }
        for(int j = 0; j < i; j++){
            if(ds[i].layMa() == ds[j].layMa() || ds[i].layMaPhieu() == ds[j].layMaPhieu()){
                loi = "Khong luu ban ghi trung ma hoac trung su kien";
                return false;
            }
        }
    }
    ostringstream noiDung;
    ghiDauTep(noiDung, ds.laySoLuong());
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].ghi(noiDung);
    }
    if(!noiDung){
        loi = "Khong tao duoc noi dung tep";
        return false;
    }
    return ghiTepMuonTra(thuMuc + "/NhatKyViPham.txt", noiDung.str(), loi);
}

bool QuanLyViPham::doc(const string& thuMuc, string& loi){
    loi.clear();
    ifstream tep(thuMuc + "/NhatKyViPham.txt");
    int n = 0;
    if(!tep || !docDauTep(tep, n)){
        loi = "Khong doc duoc dau tep NhatKyViPham";
        return false;
    }
    QuanLyViPham tam;
    for(int i = 0; i < n; i++){
        NhatKyViPham viPham;
        if(!viPham.nhap(tep) || !tam.them(viPham)){
            loi = "Vi pham sai hoac trung";
            return false;
        }
    }
    if(!hetTep(tep)){
        loi = "Tep du du lieu NhatKyViPham";
        return false;
    }
    ds.doi(tam.ds);
    return true;
}

void QuanLyViPham::doi(QuanLyViPham& khac){
    ds.doi(khac.ds);
}
