#include "KiemThu.h"
#include "../ThongKe.h"
#include "../SinhVien.h"
#include "../Sach.h"
#include "../TapChi.h"
#include "../Bao.h"
#include "../ThuatToan.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

static bool themDocGia(QuanLyThuVien& tv, const string& ma, int soMuon){
    SinhVien* dg = new SinhVien("N_" + ma, "Nguyen Van An", "01/01/2004",
                               "an@dh.edu", "0901234567", ma, soMuon, true,
                               "SV_" + ma, "CT1", "CNTT", "Phan mem");
    // Tao dau vao don vi cho ham thong ke; khong ghi tep du lieu nghiep vu.
    if(!tv.layDocGia().them(dg)){
        delete dg;
        return false;
    }
    return true;
}

static void kiemThuDocGia(){
    QuanLyThuVien tv;
    ostringstream rong;
    thongKeDocGia(tv, rong);
    kiemTra(rong.str().find("rong") != string::npos, "Thong ke doc gia rong");
    kiemTra(themDocGia(tv, "D1", 2), "Tao mot doc gia");
    ostringstream mot;
    thongKeDocGia(tv, mot);
    kiemTra(mot.str().find("dang muon: 2") != string::npos, "Tong mot phan tu");
    kiemTra(mot.str().find("it nhat: 2") != string::npos, "Min mot phan tu");
    kiemTra(themDocGia(tv, "D2", 3), "Them doc gia thu hai");
    ostringstream chan;
    thongKeDocGia(tv, chan);
    kiemTra(chan.str().find("dang muon: 5") != string::npos, "Tong chan dung operator cong");
    kiemTra(chan.str().find("D2 -") != string::npos && chan.str().find("D1 -") == string::npos,
             "Chi liet ke nguoi muon nhieu nhat");
    kiemTra(themDocGia(tv, "D3", 3), "Them nguoi dong hang");
    ostringstream le;
    thongKeDocGia(tv, le);
    kiemTra(le.str().find("dang muon: 8") != string::npos, "Tong le cong phan tu cuoi");
    kiemTra(le.str().find("D2 -") != string::npos && le.str().find("D3 -") != string::npos,
             "Khong bo sot nguoi dong hang");
    kiemTra(le.str().find("it nhat: 2") != string::npos, "Tim min khac max");
}

static void kiemThuLichSu(){
    QuanLyThuVien tv;
    ostringstream rong;
    thongKeTaiLieuMuonNhieu(tv, rong);
    kiemTra(rong.str().find("Chua co luot muon") != string::npos, "Khong co phieu");
    kiemTra(themDocGia(tv, "D1", 0), "Tao doc gia muon");
    Sach* sach = new Sach("S1", "Lap trinh", "NXB DH", 2022, 4, 4, 100000,
                          "Nguyen Van A", "Tin hoc", "ISBN1", 100);
    bool them = tv.themTaiLieu(sach);
    if(!them){
        delete sach;
    }
    kiemTra(them, "Them sach cho lich su");
    kiemTra(tv.lapPhieu(PhieuMuon("P1", "D1", "S1", "01/01/2026", "03/01/2026", 2)),
             "Muon hai ban tren mot phieu");
    ostringstream dangMuon;
    thongKeTaiLieuMuonNhieu(tv, dangMuon);
    kiemTra(dangMuon.str().find("lich su): 2") != string::npos, "Dem so ban khong dem so phieu");
    kiemTra(tv.traTaiLieu("P1", "02/01/2026"), "Tra dung han");
    kiemTra(tv.layTaiLieu().xoa("S1"), "Xoa ho so da tra");
    ostringstream lichSu;
    thongKeTaiLieuMuonNhieu(tv, lichSu);
    kiemTra(lichSu.str().find("S1 - ho so da xoa") != string::npos, "Khong bo mat tai lieu lich su");
    kiemTra(lichSu.str().find("lich su): 2") != string::npos, "Tra khong xoa luot muon lich su");
}

static void kiemThuThuatToan(){
    for(int n = 0; n <= 40; n++){
        for(int loai = 0; loai < 4; loai++){
            for(int mau = 0; mau < 3; mau++){
                int a[40];
                int tam[40];
                for(int i = 0; i < n; i++){
                    a[i] = i;
                    if(mau == 1){
                        a[i] = n - 1 - i;
                    }
                    else if(mau == 2){
                        a[i] = 7;
                    }
                }
                switch(loai){
                    case 0:
                        bubbleSort(a, n);
                        break;
                    case 1:
                        selectionSort(a, n);
                        break;
                    case 2:
                        quickSort(a, 0, n - 1);
                        break;
                    case 3:
                        mergeSort(a, 0, n - 1, tam);
                        break;
                }
                bool dung = true;
                for(int i = 0; i < n; i++){
                    int mongDoi = i;
                    if(mau == 2){
                        mongDoi = 7;
                    }
                    if(a[i] != mongDoi){
                        dung = false;
                    }
                }
                kiemTra(dung, "Sap xep rong/don/tang/dao/trung n=" + to_string(n));
                for(int x = -1; x <= n; x++){
                    int tuanTu = timKiemTuanTu(a, n, x);
                    int nhiPhan = timKiemNhiPhan(a, n, x);
                    bool timDung = (tuanTu < 0 && nhiPhan < 0);
                    if(tuanTu >= 0 && nhiPhan >= 0 && nhiPhan < n){
                        timDung = a[tuanTu] == x && a[nhiPhan] == x;
                    }
                    kiemTra(timDung, "Hai tim kiem xac dinh dung khoa, ke ca trung");
                }
            }
        }
    }
    ostringstream ketQua;
    ketQua << scientific << setprecision(7);
    ios::fmtflags cu = ketQua.flags();
    streamsize chinhXac = ketQua.precision();
    kiemTra(thucNghiemThuatToan(ketQua), "Thuc nghiem xac minh moi dap an");
    kiemTra(ketQua.flags() == cu && ketQua.precision() == chinhXac,
             "Thuc nghiem khoi phuc dinh dang ostream");
    kiemTra(ketQua.str().find("2000,") != string::npos, "Du kich thuoc cuoi");
}

// Kiem tra thuat toan duoc goi tren danh sach nghiep vu, khong chi mang so.
static void kiemThuTaiLieu(){
    QuanLyThuVien tv;
    TaiLieu* moi[4];
    moi[0] = new Sach("S3", "Sach C", "NXB DH", 2022, 3, 3, 30000,
                      "Tac gia C", "Tin hoc", "ISBN3", 100);
    moi[1] = new TapChi("T1", "Tap chi", "NXB DH", 2020, 2, 2, 10000, 1, 1, "Khoa hoc");
    moi[2] = new Bao("B2", "Bao", "NXB DH", 2021, 2, 2, 20000, "01/01/2021", "Bao ngay");
    moi[3] = new Sach("S1", "Sach A", "NXB DH", 2020, 1, 1, 10000,
                      "Tac gia A", "Tin hoc", "ISBN1", 50);
    for(int i = 0; i < 4; i++){
        bool them = tv.themTaiLieu(moi[i]);
        if(!them){
            delete moi[i];
        }
        kiemTra(them, "Them tai lieu nhieu loai de sap xep");
    }
    QuanLyTaiLieu& ds = tv.layTaiLieu();
    string thuTu[4];
    for(int i = 0; i < 4; i++){
        thuTu[i] = ds.layTaiLieu(i)->layMa();
        kiemTra(ds.timNhiPhan(thuTu[i]) == ds.timTheoMa(thuTu[i]),
                 "Nhi phan dung doi tuong tren danh sach chua sap");
    }
    kiemTra(ds.timNhiPhan("KHONG_CO") == nullptr, "Nhi phan ma khong ton tai");
    for(int i = 0; i < 4; i++){
        kiemTra(ds.layTaiLieu(i)->layMa() == thuTu[i], "Tim nhi phan khong doi thu tu danh sach chinh");
    }
    ds.sapXepTheoNam();
    for(int i = 1; i < 4; i++){
        kiemTra(ds.layTaiLieu(i - 1)->layNam() <= ds.layTaiLieu(i)->layNam(),
                 "Selection Sort nam voi gia tri trung");
    }
    ds.sapXepTheoGiaTri();
    for(int i = 1; i < 4; i++){
        kiemTra(ds.layTaiLieu(i - 1)->layGiaTri() <= ds.layTaiLieu(i)->layGiaTri(),
                 "Quick Sort gia voi gia tri trung");
    }
    kiemTra(ds.laySoLuong() == 4 && ds.timTheoMa("S3") != nullptr
             && ds.timTheoMa("T1") != nullptr && ds.timTheoMa("B2") != nullptr
             && ds.timTheoMa("S1") != nullptr, "Sap xep khong lam mat doi tuong");
}

int main(){
    kiemThuDocGia();
    kiemThuLichSu();
    kiemThuThuatToan();
    kiemThuTaiLieu();
    return ketQuaKiemThu();
}
