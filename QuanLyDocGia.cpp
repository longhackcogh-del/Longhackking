#include "QuanLyDocGia.h"
#include "SinhVien.h"
#include "GiangVien.h"
#include "QuanLyPhieuMuon.h"
#include "Tep.h"

//=====ham khoi tao va huy=====
QuanLyDocGia::QuanLyDocGia(){
    phieuMuon = nullptr;
}

QuanLyDocGia::~QuanLyDocGia(){
    for(int i = 0; i < ds.laySoLuong(); i++){
        delete ds[i];
    }
}

void QuanLyDocGia::ganQuanLyPhieuMuon(const QuanLyPhieuMuon* quanLy){
    phieuMuon = quanLy;
}

//=====ham tim kiem=====
int QuanLyDocGia::timViTri(const std::string& ma) const{
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i]->layMa() == ma){
            return i;
        }
    }
    return -1;
}

DocGia* QuanLyDocGia::timTheoMa(const std::string& ma) const{
    int k = timViTri(ma);
    if(k < 0){
        return nullptr;
    }
    return ds[k];
}

DocGia* QuanLyDocGia::timBangBam(const std::string& ma) const{
    BangBamMa bang(ds.laySoLuong());
    for(int i = 0; i < ds.laySoLuong(); i++){
        bang.them(ds[i]->layMa(), i);
    }
    int k = bang.tim(ma);
    if(k < 0){
        return nullptr;
    }
    return ds[k];
}

int QuanLyDocGia::timTheoTen(const std::string& ten) const{
    int n = 0;
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i]->layHoTen().find(ten) != std::string::npos){
            ds[i]->xuat();
            n++;
        }
    }
    return n;
}

//=====ham them va chen=====
bool QuanLyDocGia::chen(int k, DocGia* docGia){
    if(docGia == nullptr || !docGia->hopLe() || timViTri(docGia->layMa()) >= 0){
        return false;
    }
    if(phieuMuon != nullptr && phieuMuon->coThamChieuDocGia(docGia->layMa())){
        return false;
    }
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i]->layMaNguoi() == docGia->layMaNguoi()){
            return false;
        }
    }
    return ds.chen(k, docGia);
}

bool QuanLyDocGia::them(DocGia* docGia){
    return chen(ds.laySoLuong(), docGia);
}

//=====ham sua=====
bool QuanLyDocGia::sua(const std::string& ma, DocGia* docGia){
    int k = timViTri(ma);
    if(k < 0 || docGia == nullptr || !docGia->hopLe() || ds[k] == docGia){
        return false;
    }
    if(docGia->layMa() != ma || docGia->layLoai() != ds[k]->layLoai()
       || docGia->layMaNguoi() != ds[k]->layMaNguoi()
       || docGia->laySoDangMuon() != ds[k]->laySoDangMuon()){
        return false;
    }
    delete ds[k];
    ds.sua(k, docGia);
    return true;
}

//=====ham xoa=====
bool QuanLyDocGia::xoa(const std::string& ma){
    int k = timViTri(ma);
    if(k < 0 || ds[k]->laySoDangMuon() != 0){
        return false;
    }
    if(phieuMuon != nullptr && phieuMuon->demDangMuonDocGia(ma) > 0){
        return false;
    }
    delete ds[k];
    return ds.xoa(k);
}

int QuanLyDocGia::laySoLuong() const{
    return ds.laySoLuong();
}

DocGia* QuanLyDocGia::layDocGia(int k) const{
    if(!ds.viTriHopLe(k)){
        return nullptr;
    }
    return ds[k];
}

//=====ham xuat=====
void QuanLyDocGia::hienThi() const{
    if(ds.laySoLuong() == 0){
        std::cout << "Danh sach rong\n";
    }
    for(int i = 0; i < ds.laySoLuong(); i++){
        ds[i]->xuat();
    }
}

//=====ham sap xep bubble sort=====
void QuanLyDocGia::sapXepTheoSoMuon(){
    for(int i = 0; i < ds.laySoLuong() - 1; i++){
        bool daDoi = false;
        for(int j = 0; j < ds.laySoLuong() - i - 1; j++){
            if(ds[j]->laySoDangMuon() > ds[j + 1]->laySoDangMuon()){
                hoanDoi(ds[j], ds[j + 1]);
                daDoi = true;
            }
        }
        if(!daDoi){
            break;
        }
    }
}

//=====ham luu tep=====
bool QuanLyDocGia::luu(const std::string& thuMuc, std::string& loi) const{
    std::string loai[] = {"SinhVien", "GiangVien"};
    loi.clear();
    for(int k = 0; k < 2; k++){
        std::ofstream tep(thuMuc + "/" + loai[k] + ".txt");
        if(!tep){
            loi = "Khong mo tep " + loai[k];
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
            loi = "Loi ghi " + loai[k];
            return false;
        }
    }
    return true;
}

//=====ham doc tep=====
bool QuanLyDocGia::doc(const std::string& thuMuc, std::string& loi){
    loi.clear();
    for(int i = 0; i < ds.laySoLuong(); i++){
        if(ds[i]->laySoDangMuon() != 0 ||
           (phieuMuon != nullptr && phieuMuon->coThamChieuDocGia(ds[i]->layMa()))){
            loi = "Khong thay rieng doc gia khi con lien ket phieu";
            return false;
        }
    }
    QuanLyDocGia tam;
    std::string loai[] = {"SinhVien", "GiangVien"};
    for(int k = 0; k < 2; k++){
        std::ifstream tep(thuMuc + "/" + loai[k] + ".txt");
        int n = 0;
        if(!tep || !docDauTep(tep, n)){
            loi = "Khong doc duoc dau tep " + loai[k];
            return false;
        }
        for(int i = 0; i < n; i++){
            DocGia* docGia = nullptr;
            if(k == 0){
                docGia = new SinhVien;
            }
            else{
                docGia = new GiangVien;
            }
            if(!docGia->nhap(tep) || !tam.them(docGia)){
                delete docGia;
                loi = "Du lieu sai hoac trung ma " + loai[k];
                return false;
            }
        }
        if(!hetTep(tep)){
            loi = "Tep du du lieu " + loai[k];
            return false;
        }
    }
    ds.doi(tam.ds);
    return true;
}

void QuanLyDocGia::doi(QuanLyDocGia& khac){
    ds.doi(khac.ds);
}
