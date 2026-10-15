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

//=====ham selection sort=====
template<class T>
void selectionSort(T ds[], int n){
    for(int i = 0; i < n - 1; i++){
        int nhoNhat = i;
        for(int j = i + 1; j < n; j++){
            if(ds[j] < ds[nhoNhat]){
                nhoNhat = j;
            }
        }
        hoanDoi(ds[i], ds[nhoNhat]);
    }
}

//=====ham quick sort=====
template<class T>
void quickSort(T ds[], int trai, int phai){
    if(trai >= phai){
        return;
    }
    int i = trai;
    int j = phai;
    T chot = ds[trai + (phai - trai) / 2];
    while(i <= j){
        while(ds[i] < chot){
            i++;
        }
        while(chot < ds[j]){
            j--;
        }
        if(i <= j){
            hoanDoi(ds[i], ds[j]);
            i++;
            j--;
        }
    }
    if(trai < j){
        quickSort(ds, trai, j);
    }
    if(i < phai){
        quickSort(ds, i, phai);
    }
}

//=====ham merge sort=====
template<class T>
void mergeSort(T ds[], int trai, int phai, T tam[]){
    if(trai >= phai){
        return;
    }
    int giua = trai + (phai - trai) / 2;
    mergeSort(ds, trai, giua, tam);
    mergeSort(ds, giua + 1, phai, tam);
    int i = trai;
    int j = giua + 1;
    int k = trai;
    while(i <= giua && j <= phai){
        if(ds[j] < ds[i]){
            tam[k] = ds[j];
            j++;
        }
        else{
            tam[k] = ds[i];
            i++;
        }
        k++;
    }
    while(i <= giua){
        tam[k] = ds[i];
        k++;
        i++;
    }
    while(j <= phai){
        tam[k] = ds[j];
        k++;
        j++;
    }
    for(int viTri = trai; viTri <= phai; viTri++){
        ds[viTri] = tam[viTri];
    }
}

//=====bang bam tu cai dat, tham do tuyen tinh=====
class BangBamMa{
private:
    std::string* khoa;
    int* viTri;
    int sucChua;

    unsigned int tinhMaBam(const std::string& ma) const{
        unsigned int giaTri = 0;
        for(unsigned int i = 0; i < ma.size(); i++){
            giaTri = giaTri * 31 + static_cast<unsigned char>(ma[i]);
        }
        return giaTri % static_cast<unsigned int>(sucChua);
    }

public:
    explicit BangBamMa(int n){
        sucChua = timMax(3, n * 2 + 1);
        khoa = new std::string[sucChua];
        viTri = new int[sucChua];
        for(int i = 0; i < sucChua; i++){
            viTri[i] = -1;
        }
    }

    ~BangBamMa(){
        delete[] khoa;
        delete[] viTri;
    }

    BangBamMa(const BangBamMa&) = delete;
    BangBamMa& operator=(const BangBamMa&) = delete;

    bool them(const std::string& ma, int viTriMoi){
        if(viTriMoi < 0){
            return false;
        }
        int dau = static_cast<int>(tinhMaBam(ma));
        for(int i = 0; i < sucChua; i++){
            int k = (dau + i) % sucChua;
            if(viTri[k] == -1){
                khoa[k] = ma;
                viTri[k] = viTriMoi;
                return true;
            }
            if(khoa[k] == ma){
                return false;
            }
        }
        return false;
    }

    int tim(const std::string& ma) const{
        int dau = static_cast<int>(tinhMaBam(ma));
        for(int i = 0; i < sucChua; i++){
            int k = (dau + i) % sucChua;
            if(viTri[k] == -1){
                return -1;
            }
            if(khoa[k] == ma){
                return viTri[k];
            }
        }
        return -1;
    }
};
#endif
