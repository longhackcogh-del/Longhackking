#ifndef DANHSACHQUANLY_H
#define DANHSACHQUANLY_H
#include "ThuatToan.h"
#include <iostream>
#include <stdexcept>

// Danh sach giai phong mang; lop quan ly giai phong doi tuong con tro.
template<class T>
class DanhSachQuanLy{
private:
    T* ds;
    int soLuong;
    int sucChua;

public:
    DanhSachQuanLy(){
        ds = nullptr;
        soLuong = 0;
        sucChua = 0;
    }

    ~DanhSachQuanLy(){
        delete[] ds;
    }

    DanhSachQuanLy(const DanhSachQuanLy&) = delete;
    DanhSachQuanLy& operator=(const DanhSachQuanLy&) = delete;

    int laySoLuong() const{
        return soLuong;
    }

    bool viTriHopLe(int k) const{
        return k >= 0 && k < soLuong;
    }

    // T& khong the tra nullptr; loi chi so phai duoc bao ro.
    T& operator[](int k){
        if(!viTriHopLe(k)){
            throw std::out_of_range("Chi so khong hop le");
        }
        return ds[k];
    }

    const T& operator[](int k) const{
        if(!viTriHopLe(k)){
            throw std::out_of_range("Chi so khong hop le");
        }
        return ds[k];
    }

    //=====ham chen=====
    bool chen(int k, T giaTri){
        if(k < 0 || k > soLuong){
            return false;
        }
        if(soLuong == sucChua){
            int sucChuaMoi = 4;
            if(sucChua > 0){
                sucChuaMoi = sucChua * 2;
            }
            T* moi = new T[sucChuaMoi];
            for(int i = 0; i < soLuong; i++){
                moi[i] = ds[i];
            }
            delete[] ds;
            ds = moi;
            sucChua = sucChuaMoi;
        }
        for(int i = soLuong; i > k; i--){
            ds[i] = ds[i - 1];
        }
        ds[k] = giaTri;
        soLuong++;
        return true;
    }

    bool them(T giaTri){
        return chen(soLuong, giaTri);
    }

    //=====ham sua=====
    bool sua(int k, T giaTri){
        if(!viTriHopLe(k)){
            return false;
        }
        ds[k] = giaTri;
        return true;
    }

    //=====ham xoa=====
    bool xoa(int k){
        if(!viTriHopLe(k)){
            return false;
        }
        for(int i = k; i < soLuong - 1; i++){
            ds[i] = ds[i + 1];
        }
        soLuong--;
        ds[soLuong] = T();
        return true;
    }

    //=====ham tim kiem=====
    int timTheoKhoa(T khoa) const{
        return timKiemTuanTu(ds, soLuong, khoa);
    }

    //=====ham sap xep=====
    void sapXep(){
        bubbleSort(ds, soLuong);
    }

    //=====ham xuat=====
    void xuat(std::ostream& luong = std::cout) const{
        for(int i = 0; i < soLuong; i++){
            luong << ds[i] << '\n';
        }
    }

    void doi(DanhSachQuanLy& khac){
        hoanDoi(ds, khac.ds);
        hoanDoi(soLuong, khac.soLuong);
        hoanDoi(sucChua, khac.sucChua);
    }
};
#endif
