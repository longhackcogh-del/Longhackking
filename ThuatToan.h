#ifndef THUATTOAN_H
#define THUATTOAN_H
#include <string>

//=====ham hoan doi=====
template<class T>
void hoanDoi(T& a, T& b){
    T tam = a;
    a = b;
    b = tam;
}

//=====ham tim max=====
template<class T>
T timMax(T a, T b){
    if(a > b){
        return a;
    }
    return b;
}

//=====ham tim min=====
template<class T>
T timMin(T a, T b){
    if(a < b){
        return a;
    }
    return b;
}

//=====ham tim kiem tuan tu=====
template<class T>
int timKiemTuanTu(T ds[], int n, T x){
    for(int i = 0; i < n; i++){
        if(ds[i] == x){
            return i;
        }
    }
    return -1;
}

//=====ham tim kiem nhi phan=====
template<class T>
int timKiemNhiPhan(T ds[], int n, T x){
    int trai = 0;
    int phai = n - 1;
    while(trai <= phai){
        int giua = trai + (phai - trai) / 2;
        if(ds[giua] == x){
            return giua;
        }
        if(ds[giua] < x){
            trai = giua + 1;
        }
        else{
            phai = giua - 1;
        }
    }
    return -1;
}

//=====ham bubble sort=====
template<class T>
void bubbleSort(T ds[], int n){
    for(int i = 0; i < n - 1; i++){
        bool daDoi = false;
        for(int j = 0; j < n - i - 1; j++){
            if(ds[j + 1] < ds[j]){
                hoanDoi(ds[j], ds[j + 1]);
                daDoi = true;
            }
        }
        if(!daDoi){
            break;
        }
    }
}

#endif
