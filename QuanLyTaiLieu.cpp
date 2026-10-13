#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "ThuatToan.h"

#include <fstream>
#include <sstream>
#include "Tep.h"

QuanLyTaiLieu::QuanLyTaiLieu(){
    kiemTraPhieuMuon = nullptr;
}

QuanLyTaiLieu::~QuanLyTaiLieu(){
    for (int i = 0; i < ds.laySoLuong(); i++){
        delete ds[i];
    }
}

void QuanLyTaiLieu::ganKiemTraPhieuMuon(bool (*ham)(const std::string&)){
    kiemTraPhieuMuon = ham;
}

bool QuanLyTaiLieu::dangMuon(const TaiLieu& taiLieu) const{
    if (taiLieu.laySoLuongCon() < taiLieu.laySoLuongTong()){
        return true;
    }

    if (kiemTraPhieuMuon != nullptr){
        return kiemTraPhieuMuon(taiLieu.layMa());
    }

    return false;
}

int QuanLyTaiLieu::timViTri(const std::string& ma) const{
    for (int i = 0; i < ds.laySoLuong(); i++){
        if (ds[i]->layMa() == ma){
            return i;
        }
    }

    return -1;
}

bool QuanLyTaiLieu::them(TaiLieu* taiLieu){
    if (taiLieu == nullptr){
        return false;
    }

    if(!taiLieu->hopLe() || timViTri(taiLieu->layMa()) != -1){
        return false;
    }

    ds.them(taiLieu);
    // Danh sach nhan quyen so huu sau khi them thanh cong.

    return true;
}

bool QuanLyTaiLieu::sua(
    const std::string& ma,
    TaiLieu* taiLieu
){
    int viTri = timViTri(ma);
    if (viTri < 0){
        return false;
    }

    if (taiLieu == nullptr){
        return false;
    }

    if (taiLieu->layMa() != ma){
        return false;
    }

    if (taiLieu->layLoai() != ds[viTri]->layLoai()){
        return false;
    }

    int soDangMuon = ds[viTri]->laySoLuongTong() - ds[viTri]->laySoLuongCon();
    int soDangMuonMoi = taiLieu->laySoLuongTong() - taiLieu->laySoLuongCon();
    if (soDangMuonMoi != soDangMuon){
        return false;
    }

    if(!taiLieu->hopLe() || taiLieu == ds[viTri]){
        return false;
    }
    delete ds[viTri];
    ds.sua(viTri, taiLieu);

    return true;
}

bool QuanLyTaiLieu::xoa(const std::string& ma){
    int viTri = timViTri(ma);
    if (viTri < 0){
        return false;
    }

    if (dangMuon(*ds[viTri])){
        return false;
    }

    delete ds[viTri];
    ds.xoa(viTri);

    return true;
}

TaiLieu* QuanLyTaiLieu::timTheoMa(const std::string& ma) const{
    int viTri = timViTri(ma);
    if (viTri < 0){
        return nullptr;
    }

    return ds[viTri];
}

int QuanLyTaiLieu::timTheoTen(
    const std::string& ten,
    std::ostream& luong
) const{
    int soKetQua = 0;
    for (int i = 0; i < ds.laySoLuong(); i++){
        if (ds[i]->layTen().find(ten) != std::string::npos){
            if(&luong == &std::cout){
                ds[i]->xuat();
            }
            else{
                ds[i]->ghi(luong);
            }
            soKetQua++;
        }
    }

    return soKetQua;
}

int QuanLyTaiLieu::laySoLuong() const{
    return ds.laySoLuong();
}

const TaiLieu* QuanLyTaiLieu::layTaiLieu(int viTri) const{
    if(!ds.viTriHopLe(viTri)){
        return nullptr;
    }
    return ds[viTri];
}

void QuanLyTaiLieu::hienThi() const{
    if (ds.laySoLuong() == 0){
        std::cout << "Danh sach rong\n";
    }

    for (int i = 0; i < ds.laySoLuong(); i++){
        ds[i]->xuat();
    }
}

void QuanLyTaiLieu::sapXepTheoNam(){
    // Selection Sort: chon nam nho nhat trong doan chua sap xep.
    for (int i = 0; i < ds.laySoLuong() - 1; i++){
        int nhoNhat = i;
        for (int j = i + 1; j < ds.laySoLuong(); j++){
            if (ds[j]->layNam() < ds[nhoNhat]->layNam()){
                nhoNhat = j;
            }
        }

        hoanDoi(ds[i], ds[nhoNhat]);
    }
}

void QuanLyTaiLieu::quickSort(int trai, int phai){
    if (trai >= phai){
        return;
    }

    int i = trai;
    int j = phai;
    int giua = trai + (phai - trai) / 2;
    double chot = ds[giua]->layGiaTri();

    // Phan hoach: gia nho sang trai, gia lon sang phai.
    while (i <= j){
        while (ds[i]->layGiaTri() < chot){
            i++;
        }

        while (ds[j]->layGiaTri() > chot){
            j--;
        }

        if (i <= j){
            hoanDoi(ds[i], ds[j]);
            i++;
            j--;
        }
    }

    if (trai < j){
        quickSort(trai, j);
    }

    if (i < phai){
        quickSort(i, phai);
    }
}

void QuanLyTaiLieu::sapXepTheoGiaTri(){
    quickSort(0, ds.laySoLuong() - 1);
}

void QuanLyTaiLieu::thongKe(std::ostream& luong) const{
    std::string loai[] = {"Sach", "TapChi", "Bao"};

    for (int k = 0; k < 3; k++){
        int soDau = 0;
        long long tong = 0;
        long long con = 0;

        for (int i = 0; i < ds.laySoLuong(); i++){
            if (ds[i]->layLoai() == loai[k]){
                soDau++;
                tong += ds[i]->laySoLuongTong();
                con += ds[i]->laySoLuongCon();
            }
        }

        luong << loai[k] << ": dau=" << soDau;
        luong << ", tong=" << tong;
        luong << ", con=" << con;
        luong << ", dang muon=" << tong - con << '\n';
    }
}


//=====ham tim kiem nhi phan=====
TaiLieu* QuanLyTaiLieu::timNhiPhan(const std::string& ma) const{
    int n = ds.laySoLuong();
    TaiLieu** mang = new TaiLieu*[n];
    for(int i = 0; i < n; i++){
        mang[i] = ds[i];
    }
    for(int i = 0; i < n - 1; i++){
        int nhoNhat = i;
        for(int j = i + 1; j < n; j++){
            if(mang[j]->layMa() < mang[nhoNhat]->layMa()){
                nhoNhat = j;
            }
        }
        hoanDoi(mang[i], mang[nhoNhat]);
    }
    int trai = 0;
    int phai = n - 1;
    TaiLieu* ketQua = nullptr;
    while(trai <= phai){
        int giua = trai + (phai - trai) / 2;
        if(mang[giua]->layMa() == ma){
            ketQua = mang[giua];
            break;
        }
        if(mang[giua]->layMa() < ma){
            trai = giua + 1;
        }
        else{
            phai = giua - 1;
        }
    }
    delete[] mang;
    return ketQua;
}

//=====ham luu tep=====
bool QuanLyTaiLieu::luu(const std::string& thuMuc, std::string& loi) const{
    loi.clear();
    std::string loai[] = {"Sach", "TapChi", "Bao"};
    for(int k = 0; k < 3; k++){
        std::ofstream tep(thuMuc + "/" + loai[k] + ".txt");
        if(!tep){
            loi = "Khong mo duoc tep " + loai[k];
            return false;
        }
        int n = 0;
        for(int i = 0; i < ds.laySoLuong(); i++){
            if(ds[i]->layLoai() == loai[k]){
                n++;
            }
        }
        ghiDauTep(tep, n);
        for(int i = 0; i < ds.laySoLuong(); i++){
            if(ds[i]->layLoai() == loai[k]){
                ds[i]->ghi(tep);
            }
        }
        tep.close();
        if(!tep){
            loi = "Loi ghi tep " + loai[k];
            return false;
        }
    }
    return true;
}

//=====ham chuyen mot dong tai lieu cu=====
static bool chuyenDongCu(const std::string& dong, int loai, std::string& ketQua){
    std::istringstream luong(dong);
    std::ostringstream moi;
    std::string chuoi;
    for(int i = 0; i < 3; i++){
        if(!docChuoiCu(luong, chuoi)){
            return false;
        }
        moi << chuoi << '\n';
    }
    for(int i = 0; i < 4; i++){
        if(!(luong >> chuoi)){
            return false;
        }
        moi << chuoi << '\n';
    }
    if(loai == 0){
        for(int i = 0; i < 3; i++){
            if(!docChuoiCu(luong, chuoi)){
                return false;
            }
            moi << chuoi << '\n';
        }
        if(!(luong >> chuoi)){
            return false;
        }
        moi << chuoi << '\n';
    }
    else if(loai == 1){
        for(int i = 0; i < 2; i++){
            if(!(luong >> chuoi)){
                return false;
            }
            moi << chuoi << '\n';
        }
        if(!docChuoiCu(luong, chuoi)){
            return false;
        }
        moi << chuoi << '\n';
    }
    else{
        for(int i = 0; i < 2; i++){
            if(!docChuoiCu(luong, chuoi)){
                return false;
            }
            moi << chuoi << '\n';
        }
    }
    if(!hetTep(luong)){
        return false;
    }
    ketQua = moi.str();
    return true;
}

//=====ham doc tep=====
bool QuanLyTaiLieu::doc(const std::string& thuMuc, std::string& loi){
    loi.clear();
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(dangMuon(*ds[i])){
            loi = "Khong thay rieng danh sach tai lieu khi con lien ket phieu";
            return false;
        }
    }
    QuanLyTaiLieu tam;
    std::string loai[] = {"Sach", "TapChi", "Bao"};
    for(int k = 0; k < 3; k++){
        std::ifstream tep(thuMuc + "/" + loai[k] + ".txt");
        if(!tep){
            loi = "Khong mo duoc tep " + loai[k];
            return false;
        }
        int n = 0;
        bool dinhDangMoi = docDauTep(tep, n);
        if(!dinhDangMoi){
            tep.clear();
            tep.seekg(0);
        }
        int soBanGhi = 0;
        while(true){
            std::string noiDung;
            if(dinhDangMoi){
                if(soBanGhi == n){
                    break;
                }
            }
            else{
                std::string dong;
                if(!std::getline(tep, dong)){
                    break;
                }
                if(!chuoiHopLe(dong)){
                    continue;
                }
                if(!chuyenDongCu(dong, k, noiDung)){
                    loi = "Sai dinh dang cu: " + loai[k];
                    return false;
                }
            }
            TaiLieu* taiLieu = nullptr;
            switch(k){
                case 0:
                    taiLieu = new Sach;
                    break;
                case 1:
                    taiLieu = new TapChi;
                    break;
                case 2:
                    taiLieu = new Bao;
                    break;
            }
            bool docDuoc = false;
            if(dinhDangMoi){
                docDuoc = taiLieu->nhap(tep);
            }
            else{
                std::istringstream luong(noiDung);
                docDuoc = taiLieu->nhap(luong);
            }
            if(!docDuoc || !tam.them(taiLieu)){
                delete taiLieu;
                loi = "Du lieu sai hoac trung ma: " + loai[k];
                return false;
            }
            soBanGhi++;
        }
        if(!hetTep(tep)){
            loi = "Tep du du lieu hoac loi doc: " + loai[k];
            return false;
        }
    }
    ds.doi(tam.ds);
    return true;
}

void QuanLyTaiLieu::doi(QuanLyTaiLieu& khac){
    ds.doi(khac.ds);
}
