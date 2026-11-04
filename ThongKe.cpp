#include "ThongKe.h"
#include "ThuatToan.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

//=====ham thong ke doc gia=====
void thongKeDocGia(const QuanLyThuVien& thuVien, ostream& luong){
    const QuanLyDocGia& ds = thuVien.layDocGia();
    int n = ds.laySoLuong();
    if(n == 0){
        luong << "Danh sach doc gia rong.\n";
        return;
    }
    int nhieuNhat = ds.layDocGia(0)->laySoDangMuon();
    int itNhat = nhieuNhat;
    long long tong = 0;
    // Cong theo cap bang operator+; phan le duoc cong rieng.
    for(int i = 0; i + 1 < n; i += 2){
        tong += *ds.layDocGia(i) + *ds.layDocGia(i + 1);
    }
    if(n % 2 != 0){
        tong += ds.layDocGia(n - 1)->laySoDangMuon();
    }
    for(int i = 0; i < n; i++){
        int soMuon = ds.layDocGia(i)->laySoDangMuon();
        nhieuNhat = timMax(nhieuNhat, soMuon);
        itNhat = timMin(itNhat, soMuon);
    }
    luong << "Tong so tai lieu doc gia dang muon: " << tong << '\n';
    luong << "So muon it nhat: " << itNhat << '\n';
    luong << "So muon nhieu nhat: " << nhieuNhat << '\n';
    for(int i = 0; i < n; i++){
        const DocGia* dg = ds.layDocGia(i);
        if(dg->laySoDangMuon() == nhieuNhat){
            luong << dg->layMa() << " - " << dg->layHoTen() << '\n';
        }
    }
}

// Tinh tren toan bo phieu, ke ca tai lieu da xoa ho so; dem so ban muon.
void thongKeTaiLieuMuonNhieu(const QuanLyThuVien& thuVien, ostream& luong){
    const QuanLyPhieuMuon& ds = thuVien.layPhieuMuon();
    DanhSachQuanLy<string> ma;
    for(int i = 0; i < ds.laySoLuong(); i++){
        string khoa = ds.lay(i)->layMaTaiLieu();
        if(ma.timTheoKhoa(khoa) < 0){
            ma.them(khoa);
        }
    }
    if(ma.laySoLuong() == 0){
        luong << "Chua co luot muon.\n";
        return;
    }
    long long nhieuNhat = 0;
    for(int i = 0; i < ma.laySoLuong(); i++){
        nhieuNhat = timMax(nhieuNhat, ds.demLuotMuonTaiLieu(ma[i]));
    }
    luong << "So ban muon nhieu nhat (gom lich su): " << nhieuNhat << '\n';
    for(int i = 0; i < ma.laySoLuong(); i++){
        if(ds.demLuotMuonTaiLieu(ma[i]) == nhieuNhat){
            const TaiLieu* tl = thuVien.layTaiLieu().timTheoMa(ma[i]);
            luong << ma[i];
            if(tl != nullptr){
                luong << " - " << tl->layTen();
            }
            else{
                luong << " - ho so da xoa";
            }
            luong << '\n';
        }
    }
}

//=====ham thuc nghiem, khong dung du lieu nghiep vu=====
bool thucNghiemThuatToan(ostream& luong){
    ios::fmtflags cu = luong.flags();
    streamsize chinhXac = luong.precision();
    luong << fixed << setprecision(3);
    luong << "Thoi gian micro giay; trung binh 3 lan sap xep, 1000 truy van tim.\n"
          << "Du lieu khoa nguyen duy nhat, hoan vi hat giong 2026.\n"
          << "Tim nhi phan khong gom sap xep; bam khong gom xay dung.\n"
          << "n,bubble_us,selection_us,quick_us,merge_us,tuan_tu_us,nhi_phan_us,bam_us,dung_bam_us\n";
    int kichThuoc[] = {100, 500, 1000, 2000};
    bool hopLe = true;
    volatile long long tongKiemTra = 0;
    for(int k = 0; k < 4; k++){
        int n = kichThuoc[k];
        int* goc = new int[n];
        int* a = new int[n];
        int* tam = new int[n];
        string* khoa = new string[n];
        for(int i = 0; i < n; i++){
            goc[i] = i;
            khoa[i] = to_string(i);
        }
        unsigned int hat = 2026;
        for(int i = n - 1; i > 0; i--){
            hat = hat * 1664525u + 1013904223u;
            int j = static_cast<int>(hat % static_cast<unsigned int>(i + 1));
            hoanDoi(goc[i], goc[j]);
        }
        luong << n;
        for(int loai = 0; loai < 4; loai++){
            double tong = 0;
            for(int lan = 0; lan < 3; lan++){
                for(int i = 0; i < n; i++){
                    a[i] = goc[i];
                }
                auto dau = chrono::steady_clock::now();
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
                auto cuoi = chrono::steady_clock::now();
                tong += chrono::duration<double, micro>(cuoi - dau).count();
                for(int i = 0; i < n; i++){
                    if(a[i] != i){
                        hopLe = false;
                    }
                }
            }
            luong << ',' << tong / 3;
        }
        BangBamMa bang(n);
        auto dauBam = chrono::steady_clock::now();
        for(int i = 0; i < n; i++){
            if(!bang.them(khoa[i], i)){
                hopLe = false;
            }
        }
        auto cuoiBam = chrono::steady_clock::now();
        for(int loai = 0; loai < 3; loai++){
            auto dau = chrono::steady_clock::now();
            for(int i = 0; i < 1000; i++){
                int x = (i * 37) % (n + 1);
                int viTri = -1;
                switch(loai){
                    case 0:
                        viTri = timKiemTuanTu(a, n, x);
                        break;
                    case 1:
                        viTri = timKiemNhiPhan(a, n, x);
                        break;
                    case 2:
                        viTri = bang.tim(to_string(x));
                        break;
                }
                tongKiemTra += viTri;
                int mongDoi = x;
                if(x == n){
                    mongDoi = -1;
                }
                if(viTri != mongDoi){
                    hopLe = false;
                }
            }
            auto cuoi = chrono::steady_clock::now();
            luong << ',' << chrono::duration<double, micro>(cuoi - dau).count() / 1000;
        }
        luong << ',' << chrono::duration<double, micro>(cuoiBam - dauBam).count() << '\n';
        delete[] goc;
        delete[] a;
        delete[] tam;
        delete[] khoa;
    }
    luong << "Kiem tra ket qua thuat toan: ";
    if(hopLe){
        luong << "DAT\n";
    }
    else{
        luong << "LOI\n";
    }
    luong << "Do phuc tap: tuan tu O(n), nhi phan O(log n) tren mang da sap xep.\n"
          << "Bam: tra trung binh O(1), xau nhat O(n); dung bang tinh rieng.\n"
          << "Bubble: tot nhat O(n), xau nhat O(n^2); Selection: O(n^2).\n"
          << "Quick: trung binh O(n log n), xau nhat O(n^2); Merge: O(n log n).\n"
          << "Khoa bam la chuoi, tim mang dung so nguyen; khong so sanh toc do tuyet doi.\n"
          << "Thoi gian phu thuoc may va lan chay, khong thay the chung minh do phuc tap.\n";
    luong.flags(cu);
    luong.precision(chinhXac);
    return hopLe;
}
