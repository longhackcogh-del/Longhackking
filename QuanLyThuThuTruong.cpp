#include "QuanLyThuThuTruong.h"
#include "Tep.h"
using namespace std;

//=====ham tim kiem=====
int QuanLyThuThuTruong::timViTri(const string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return i;
        }
    }
    return -1;
}

ThuThuTruong* QuanLyThuThuTruong::timTheoMa(const string& ma){
    int k = timViTri(ma);
    if(k < 0){
        return nullptr;
    }
    return &ds[k];
}

const ThuThuTruong* QuanLyThuThuTruong::timTheoMa(const string& ma) const{
    int k = timViTri(ma);
    if(k < 0){
        return nullptr;
    }
    return &ds[k];
}

int QuanLyThuThuTruong::timTheoSoNhanVien(int soNhanVien) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].laySoNhanVienQuanLy() > soNhanVien){
            ds[i].xuat();
            n++;
        }
    }
    return n;
}

//=====ham them=====
bool QuanLyThuThuTruong::them(const ThuThuTruong& nguoi){
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
bool QuanLyThuThuTruong::sua(const string& ma, const ThuThuTruong& nguoi){
    int k = timViTri(ma);
    if(k < 0 || !nguoi.hopLe() || nguoi.layMa() != ma
       || nguoi.layMaNguoi() != ds[k].layMaNguoi()
       || nguoi.DocGia::layMa() != ds[k].DocGia::layMa()
       || nguoi.laySoDangMuon() != ds[k].laySoDangMuon()){
        return false;
    }
    return ds.sua(k, nguoi);
}

//=====ham xoa=====
bool QuanLyThuThuTruong::xoa(const string& ma){
    return ds.xoa(timViTri(ma));
}

int QuanLyThuThuTruong::laySoLuong() const{
    return ds.laySoLuong();
}

const ThuThuTruong* QuanLyThuThuTruong::lay(int k) const{
    if(!ds.viTriHopLe(k)){
        return nullptr;
    }
    return &ds[k];
}

//=====ham xuat=====
void QuanLyThuThuTruong::hienThi() const{
    if(ds.laySoLuong() == 0){
        cout << "Danh sach rong\n";
    }
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].xuat();
    }
}

//=====ham sap xep=====
void QuanLyThuThuTruong::sapXepTheoPhuCap(){
    for(int i = 0; i < ds.laySoLuong() - 1; i++){
        for(int j = i + 1; j < ds.laySoLuong(); j++){
            if(ds[i].layPhuCap() > ds[j].layPhuCap()){
                hoanDoi(ds[i], ds[j]);
            }
        }
    }
}

//=====ham luu tep=====
bool QuanLyThuThuTruong::luu(const string& thuMuc, string& loi) const{
    loi.clear();
    ofstream tep(thuMuc + "/ThuThuTruong.txt");
    if(!tep){
        loi = "Khong mo tep ThuThuTruong";
        return false;
    }
    ghiDauTep(tep, ds.laySoLuong());
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].ghi(tep);
    }
    tep.close();
    if(!tep){
        loi = "Loi ghi tep ThuThuTruong";
        return false;
    }
    return true;
}

//=====ham doc tep=====
bool QuanLyThuThuTruong::doc(const string& thuMuc, string& loi){
    loi.clear();
    ifstream tep(thuMuc + "/ThuThuTruong.txt");
    int n = 0;
    if(!tep || !docDauTep(tep, n)){
        loi = "Khong doc duoc dau tep ThuThuTruong";
        return false;
    }
    QuanLyThuThuTruong tam;
    for(int i = 0; i < n; i++){
        ThuThuTruong nguoi;
        if(!nguoi.nhap(tep) || !tam.them(nguoi)){
            loi = "Du lieu sai hoac trung ma ThuThuTruong";
            return false;
        }
    }
    if(!hetTep(tep)){
        loi = "Tep du du lieu ThuThuTruong";
        return false;
    }
    ds.doi(tam.ds);
    return true;
}

void QuanLyThuThuTruong::doi(QuanLyThuThuTruong& khac){
    ds.doi(khac.ds);
}
