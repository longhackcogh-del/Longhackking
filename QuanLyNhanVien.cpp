#include "QuanLyNhanVien.h"
#include "Tep.h"

//=====ham tim kiem=====
int QuanLyNhanVien::timViTri(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return i;
        }
    }
    return -1;
}

NhanVienThuThu* QuanLyNhanVien::timTheoMa(const std::string& ma){
    int k = timViTri(ma);
    if(k < 0){
        return nullptr;
    }
    return &ds[k];
}

const NhanVienThuThu* QuanLyNhanVien::timTheoMa(const std::string& ma) const{
    int k = timViTri(ma);
    if(k < 0){
        return nullptr;
    }
    return &ds[k];
}

int QuanLyNhanVien::timTheoCa(const std::string& ca) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layCa() == ca){
            ds[i].xuat();
            n++;
        }
    }
    return n;
}

//=====ham them=====
bool QuanLyNhanVien::them(const NhanVienThuThu& nguoi){
    if(!nguoi.hopLe() || timViTri(nguoi.layMa()) >= 0){
        return false;
    }
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaNguoi() == nguoi.layMaNguoi()){
            return false;
        }
    }
    return ds.them(nguoi);
}

//=====ham sua=====
bool QuanLyNhanVien::sua(const std::string& ma, const NhanVienThuThu& nguoi){
    int k = timViTri(ma);
    if(k < 0 || !nguoi.hopLe() || nguoi.layMa() != ma
       || nguoi.layMaNguoi() != ds[k].layMaNguoi()){
        return false;
    }
    return ds.sua(k, nguoi);
}

//=====ham xoa=====
bool QuanLyNhanVien::xoa(const std::string& ma){
    return ds.xoa(timViTri(ma));
}

int QuanLyNhanVien::laySoLuong() const{
    return ds.laySoLuong();
}

const NhanVienThuThu* QuanLyNhanVien::lay(int k) const{
    if(!ds.viTriHopLe(k)){
        return nullptr;
    }
    return &ds[k];
}

//=====ham xuat=====
void QuanLyNhanVien::hienThi() const{
    if(ds.laySoLuong() == 0){
        std::cout << "Danh sach rong\n";
    }
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].xuat();
    }
}

//=====ham sap xep=====
void QuanLyNhanVien::sapXepTheoHeSoLuong(){
    for(int i = 0; i < ds.laySoLuong() - 1; i++){
        for(int j = i + 1; j < ds.laySoLuong(); j++){
            if(ds[i].layHeSoLuong() > ds[j].layHeSoLuong()){
                hoanDoi(ds[i], ds[j]);
            }
        }
    }
}

//=====ham luu tep=====
bool QuanLyNhanVien::luu(const std::string& thuMuc, std::string& loi) const{
    loi.clear();
    std::ofstream tep(thuMuc + "/NhanVienThuThu.txt");
    if(!tep){
        loi = "Khong mo tep NhanVienThuThu";
        return false;
    }
    ghiDauTep(tep, ds.laySoLuong());
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].ghi(tep);
    }
    tep.close();
    if(!tep){
        loi = "Loi ghi tep NhanVienThuThu";
        return false;
    }
    return true;
}

//=====ham doc tep=====
bool QuanLyNhanVien::doc(const std::string& thuMuc, std::string& loi){
    loi.clear();
    std::ifstream tep(thuMuc + "/NhanVienThuThu.txt");
    int n = 0;
    if(!tep || !docDauTep(tep, n)){
        loi = "Khong doc duoc dau tep NhanVienThuThu";
        return false;
    }
    QuanLyNhanVien tam;
    for(int i = 0; i < n; i++){
        NhanVienThuThu nguoi;
        if(!nguoi.nhap(tep) || !tam.them(nguoi)){
            loi = "Du lieu sai hoac trung ma NhanVienThuThu";
            return false;
        }
    }
    if(!hetTep(tep)){
        loi = "Tep du du lieu NhanVienThuThu";
        return false;
    }
    ds.doi(tam.ds);
    return true;
}

void QuanLyNhanVien::doi(QuanLyNhanVien& khac){
    ds.doi(khac.ds);
}
