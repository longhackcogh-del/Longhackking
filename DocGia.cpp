#include "DocGia.h"
#include "TaiLieu.h"
using namespace std;

//=====ham khoi tao=====
DocGia::DocGia(){
    soTaiLieuDangMuon = 0;
    gioiHanMuon = 0;
    dangHoatDong = true;
}

DocGia::DocGia(string ma, int soMuon, int gioiHan, bool hoatDong){
    maDocGia = ma;
    soTaiLieuDangMuon = soMuon;
    gioiHanMuon = gioiHan;
    dangHoatDong = hoatDong;
}

DocGia::~DocGia(){
}

bool DocGia::hopLe() const{
    if(!Nguoi::hopLe() || !chuoiHopLe(maDocGia)){
        return false;
    }
    return gioiHanMuon == layGioiHanMuon() && soTaiLieuDangMuon >= 0
        && soTaiLieuDangMuon <= gioiHanMuon;
}

//=====ham nhap=====
bool DocGia::nhapDocGiaRieng(istream& luong){
    int hoatDong = 0;
    if(!nhapChuoi(luong, "Nhap ma doc gia: ", maDocGia)){
        return false;
    }
    if(!nhapSo(luong, "Nhap so tai lieu dang muon: ", soTaiLieuDangMuon)){
        return false;
    }
    if(!nhapSo(luong, "Tai khoan hoat dong (0/1): ", hoatDong)){
        return false;
    }
    if(hoatDong != 0 && hoatDong != 1){
        return false;
    }
    dangHoatDong = hoatDong == 1;
    gioiHanMuon = layGioiHanMuon();
    return soTaiLieuDangMuon >= 0 && soTaiLieuDangMuon <= gioiHanMuon;
}

bool DocGia::nhap(istream& luong){
    if(!Nguoi::nhap(luong)){
        return false;
    }
    return nhapDocGiaRieng(luong);
}

//=====ham xuat=====
void DocGia::xuatDocGiaRieng() const{
    cout << "Ma doc gia: " << maDocGia << '\n';
    cout << "So dang muon: " << soTaiLieuDangMuon << '\n';
    cout << "Gioi han: " << layGioiHanMuon() << '\n';
    if(dangHoatDong){
        cout << "Tai khoan: hoat dong\n";
    }
    else{
        cout << "Tai khoan: bi khoa\n";
    }
}

void DocGia::xuat() const{
    Nguoi::xuat();
    xuatDocGiaRieng();
}

void DocGia::ghiDocGiaRieng(ostream& tep) const{
    tep << maDocGia << '\n';
    tep << soTaiLieuDangMuon << '\n';
    tep << dangHoatDong << '\n';
}

string DocGia::layMa() const{
    return maDocGia;
}

int DocGia::laySoDangMuon() const{
    return soTaiLieuDangMuon;
}

bool DocGia::layHoatDong() const{
    return dangHoatDong;
}

//=====ham kiem tra dieu kien muon=====
bool DocGia::kiemTraDieuKienMuon(int soLuong) const{
    return hopLe() && dangHoatDong && soLuong > 0
        && soLuong <= layGioiHanMuon() - soTaiLieuDangMuon;
}

bool DocGia::tangSoDangMuon(int soLuong){
    if(!kiemTraDieuKienMuon(soLuong)){
        return false;
    }
    soTaiLieuDangMuon += soLuong;
    return true;
}

bool DocGia::giamSoDangMuon(int soLuong){
    if(soLuong <= 0 || soLuong > soTaiLieuDangMuon){
        return false;
    }
    soTaiLieuDangMuon -= soLuong;
    return true;
}

//=====ham nap chong toan tu=====
long long DocGia::operator+(const DocGia& khac) const{
    return static_cast<long long>(soTaiLieuDangMuon) + khac.soTaiLieuDangMuon;
}

//=====ham ban=====
bool kiemTraDieuKienMuon(const DocGia& docGia, const TaiLieu& taiLieu){
    return docGia.dangHoatDong && docGia.kiemTraDieuKienMuon()
        && taiLieu.hopLe() && taiLieu.soLuongCon > 0;
}
