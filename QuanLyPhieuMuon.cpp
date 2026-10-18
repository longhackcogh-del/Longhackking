#include "QuanLyPhieuMuon.h"
#include "QuanLyDocGia.h"
#include "QuanLyTaiLieu.h"
#include "QuanLyViPham.h"
#include "Tep.h"
#include "TepMuonTra.h"

//=====ham tim kiem=====
PhieuMuon* QuanLyPhieuMuon::timTheoMa(const std::string& ma){
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

const PhieuMuon* QuanLyPhieuMuon::timTheoMa(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMa() == ma){
            return &ds[i];
        }
    }
    return nullptr;
}

//=====ham lap phieu=====
bool QuanLyPhieuMuon::lapPhieu(const PhieuMuon& phieu, QuanLyDocGia& docGia, QuanLyTaiLieu& taiLieu){
    if(!phieu.hopLe() || !phieu.dangMuon() || timTheoMa(phieu.layMa()) != nullptr){
        return false;
    }
    DocGia* nguoi = docGia.timBangBam(phieu.layMaDocGia());
    TaiLieu* sach = taiLieu.timNhiPhan(phieu.layMaTaiLieu());
    if(nguoi == nullptr || sach == nullptr){
        return false;
    }
    if(!kiemTraDieuKienMuon(*nguoi, *sach)
       || !nguoi->kiemTraDieuKienMuon(phieu.laySoLuong())
       || !sach->kiemTraConTaiLieu(phieu.laySoLuong())){
        return false;
    }
    int k = ds.laySoLuong();
    ds.them(phieu);
    if(!ds[k].lapPhieu(*nguoi, *sach)){
        ds.xoa(k);
        return false;
    }
    return true;
}

//=====ham tra tai lieu=====
bool QuanLyPhieuMuon::traTaiLieu(const std::string& ma, const std::string& ngay,
                                QuanLyDocGia& docGia, QuanLyTaiLieu& taiLieu, QuanLyViPham& viPham){
    PhieuMuon* phieu = timTheoMa(ma);
    if(phieu == nullptr || !phieu->dangMuon() || viPham.timTheoPhieu(ma) != nullptr
       || viPham.timTheoMa("VP_" + ma) != nullptr){
        return false;
    }
    DocGia* nguoi = docGia.timTheoMa(phieu->layMaDocGia());
    TaiLieu* sach = taiLieu.timTheoMa(phieu->layMaTaiLieu());
    if(nguoi == nullptr || sach == nullptr){
        return false;
    }
    if(!phieu->traTaiLieu(*nguoi, *sach, ngay)){
        return false;
    }
    if(phieu->layTienPhat() > 0){
        return viPham.ghiViPham(*phieu);
    }
    return true;
}

//=====ham liet ke=====
int QuanLyPhieuMuon::lietKeTheoDocGia(const std::string& ma) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaDocGia() == ma){
            std::cout << ds[i];
            n++;
        }
    }
    return n;
}

int QuanLyPhieuMuon::lietKeDocGiaMuonTaiLieu(const std::string& ma, const QuanLyDocGia& docGia) const{
    DanhSachQuanLy<std::string> daXuat;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaTaiLieu() == ma && ds[i].dangMuon()){
            std::string maDocGia = ds[i].layMaDocGia();
            if(daXuat.timTheoKhoa(maDocGia) < 0){
                DocGia* nguoi = docGia.timTheoMa(maDocGia);
                if(nguoi != nullptr){
                    daXuat.them(maDocGia);
                }
            }
        }
    }
    daXuat.sapXep();
    for(int i = 0; i < daXuat.laySoLuong(); i++){
        docGia.timTheoMa(daXuat[i])->xuat();
    }
    return daXuat.laySoLuong();
}

bool QuanLyPhieuMuon::coThamChieuDocGia(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaDocGia() == ma){
            return true;
        }
    }
    return false;
}

bool QuanLyPhieuMuon::coThamChieuTaiLieu(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaTaiLieu() == ma){
            return true;
        }
    }
    return false;
}

long long QuanLyPhieuMuon::demDangMuonDocGia(const std::string& ma) const{
    long long tong = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].dangMuon() && ds[i].layMaDocGia() == ma){
            tong += ds[i].laySoLuong();
        }
    }
    return tong;
}

long long QuanLyPhieuMuon::demDangMuonTaiLieu(const std::string& ma) const{
    long long tong = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].dangMuon() && ds[i].layMaTaiLieu() == ma){
            tong += ds[i].laySoLuong();
        }
    }
    return tong;
}

long long QuanLyPhieuMuon::demLuotMuonTaiLieu(const std::string& ma) const{
    long long tong = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i].layMaTaiLieu() == ma){
            tong += ds[i].laySoLuong();
        }
    }
    return tong;
}

int QuanLyPhieuMuon::laySoLuong() const{
    return ds.laySoLuong();
}

const PhieuMuon* QuanLyPhieuMuon::lay(int k) const{
    if(!ds.viTriHopLe(k)){
        return nullptr;
    }
    return &ds[k];
}

//=====ham xuat=====
void QuanLyPhieuMuon::hienThi() const{
    if(ds.laySoLuong() == 0){
        std::cout << "Danh sach rong\n";
    }
    ds.xuat();
}

void QuanLyPhieuMuon::lietKeQuaHan(const QuanLyDocGia& docGia) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        DocGia* nguoi = docGia.timTheoMa(ds[i].layMaDocGia());
        if(nguoi != nullptr && kiemTraHanMuon(*nguoi, ds[i])){
            std::cout << ds[i];
            n++;
        }
    }
    std::cout << "So phieu qua han: " << n << '\n';
}

//=====ham sap xep merge sort=====
void QuanLyPhieuMuon::sapXepTheoMa(){
    int n = ds.laySoLuong();
    PhieuMuon* mang = new PhieuMuon[n];
    PhieuMuon* tam = new PhieuMuon[n];
    for(int i = 0; i < n; i++){
        mang[i] = ds[i];
    }
    mergeSort(mang, 0, n - 1, tam);
    for(int i = 0; i < n; i++){
        ds.sua(i, mang[i]);
    }
    delete[] mang;
    delete[] tam;
}

//=====ham doc ghi tep=====
bool QuanLyPhieuMuon::luu(const std::string& thuMuc, std::string& loi) const{
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
            if(ds[i].layMa() == ds[j].layMa()){
                loi = "Khong luu ban ghi trung ma hoac trung su kien";
                return false;
            }
        }
    }
    std::ostringstream noiDung;
    ghiDauTep(noiDung, ds.laySoLuong());
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i].ghi(noiDung);
    }
    if(!noiDung){
        loi = "Khong tao duoc noi dung tep";
        return false;
    }
    return ghiTepMuonTra(thuMuc + "/PhieuMuon.txt", noiDung.str(), loi);
}

bool QuanLyPhieuMuon::doc(const std::string& thuMuc, std::string& loi){
    loi.clear();
    std::ifstream tep(thuMuc + "/PhieuMuon.txt");
    int n = 0;
    if(!tep || !docDauTep(tep, n)){
        loi = "Khong doc duoc dau tep PhieuMuon";
        return false;
    }
    QuanLyPhieuMuon tam;
    for(int i = 0; i < n; i++){
        PhieuMuon phieu;
        if(!phieu.doc(tep) || tam.timTheoMa(phieu.layMa()) != nullptr){
            loi = "Phieu sai hoac trung ma";
            return false;
        }
        tam.ds.them(phieu);
    }
    if(!hetTep(tep)){
        loi = "Tep du du lieu PhieuMuon";
        return false;
    }
    ds.doi(tam.ds);
    return true;
}

void QuanLyPhieuMuon::doi(QuanLyPhieuMuon& khac){
    ds.doi(khac.ds);
}
