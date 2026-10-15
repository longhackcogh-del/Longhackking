#include "ThucNghiem.h"
#include "ThuatToan.h"
#include <chrono>

//=====ham kiem tra thu tu=====
static bool daSapXep(const int ds[], int n){
    for(int i = 0; i < n; i++){
        if(ds[i] != i){
            return false;
        }
    }
    return true;
}

//=====ham thuc nghiem=====
bool thucNghiem(std::ostream& ketQua){
    int kichThuoc[] = {100, 500, 1000, 2000};
    std::string tenSapXep[] = {"Bubble Sort", "Selection Sort", "Quick Sort", "Merge Sort"};
    std::string tenTim[] = {"Tuan tu", "Nhi phan", "Bang bam"};
    ketQua << "kich_thuoc,thuat_toan,so_lan,thoi_gian_micro_giay,ket_qua\n";
    bool tatCaDung = true;
    for(int k = 0; k < 4; k++){
        int n = kichThuoc[k];
        int* goc = new int[n];
        int* ds = new int[n];
        int* tam = new int[n];
        for(int i = 0; i < n; i++){
            goc[i] = n - 1 - i;
        }
        for(int loai = 0; loai < 4; loai++){
            for(int i = 0; i < n; i++){
                ds[i] = goc[i];
            }
            std::chrono::steady_clock::time_point batDau = std::chrono::steady_clock::now();
            switch(loai){
                case 0:
                    bubbleSort(ds, n);
                    break;
                case 1:
                    selectionSort(ds, n);
                    break;
                case 2:
                    quickSort(ds, 0, n - 1);
                    break;
                case 3:
                    mergeSort(ds, 0, n - 1, tam);
                    break;
            }
            double thoiGian = std::chrono::duration<double, std::micro>(
                std::chrono::steady_clock::now() - batDau).count();
            bool dung = daSapXep(ds, n);
            tatCaDung = tatCaDung && dung;
            ketQua << n << ',' << tenSapXep[loai] << ",1," << thoiGian << ',';
            if(dung){
                ketQua << "DAT\n";
            }
            else{
                ketQua << "SAI\n";
            }
        }
        BangBamMa bang(n);
        for(int i = 0; i < n; i++){
            bang.them(std::to_string(ds[i]), i);
        }
        // Thoi gian tim khong bao gom sap xep va xay dung bang bam.
        for(int loai = 0; loai < 3; loai++){
            bool dung = true;
            volatile long long tongViTri = 0;
            std::chrono::steady_clock::time_point batDau = std::chrono::steady_clock::now();
            for(int i = 0; i < 1000; i++){
                int x = i % (n + 5);
                int viTri = -1;
                switch(loai){
                    case 0:
                        viTri = timKiemTuanTu(ds, n, x);
                        break;
                    case 1:
                        viTri = timKiemNhiPhan(ds, n, x);
                        break;
                    case 2:
                        viTri = bang.tim(std::to_string(x));
                        break;
                }
                int mongDoi = -1;
                if(x < n){
                    mongDoi = x;
                }
                if(viTri != mongDoi){
                    dung = false;
                }
                tongViTri += viTri;
            }
            double thoiGian = std::chrono::duration<double, std::micro>(
                std::chrono::steady_clock::now() - batDau).count();
            tatCaDung = tatCaDung && dung;
            ketQua << n << ',' << tenTim[loai] << ",1000," << thoiGian << ',';
            if(dung){
                ketQua << "DAT\n";
            }
            else{
                ketQua << "SAI\n";
            }
        }
        delete[] goc;
        delete[] ds;
        delete[] tam;
    }
    return tatCaDung && static_cast<bool>(ketQua);
}
