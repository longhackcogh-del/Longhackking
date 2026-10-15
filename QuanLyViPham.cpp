#include "QuanLyViPham.h"
#include "PhieuMuon.h"
#include "Tep.h"

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
NhatKyViPham* QuanLyViPham::timTheoMa(const std::string& ma){
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

const NhatKyViPham* QuanLyViPham::timTheoMa(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

const NhatKyViPham* QuanLyViPham::timTheoPhieu(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaPhieu() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

int QuanLyViPham::timTheoDocGia(const std::string& ma) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaDocGia() == ma){
            ds[i].xuat();
            n++;
        }
    }
    return n;
}

int QuanLyViPham::demViPham(const std::string& maDocGia) const{
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
        std::cout << "Danh sach rong\n";
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
    std::cout << "So vi pham chua thanh toan: " << n << '\n';
}

//=====ham thanh toan va duyet=====
bool QuanLyViPham::thanhToanPhat(const std::string& ma){
    NhatKyViPham* viPham = timTheoMa(ma);
    if(viPham == nullptr){
        return false;
    }
    return viPham->thanhToanPhat();
}

bool QuanLyViPham::duyet(const std::string& ma, const std::string& nguoiDuyet){
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
bool QuanLyViPham::luu(const std::string& thuMuc, std::string& loi) const{
    loi.clear();
    std::ofstream tep(thuMuc + "/NhatKyViPham.txt");
    if(!tep){
        loi = "Khong mo tep NhatKyViPham";
        return false;
    }
    ghiDauTep(tep, ds.laySoLuong());
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].ghi(tep);
    }
    tep.close();
    if(!tep){
        loi = "Loi ghi tep NhatKyViPham";
        return false;
    }
    return true;
}

bool QuanLyViPham::doc(const std::string& thuMuc, std::string& loi){
    loi.clear();
    std::ifstream tep(thuMuc + "/NhatKyViPham.txt");
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
