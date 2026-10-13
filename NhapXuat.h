#ifndef NHAPXUAT_H
#define NHAPXUAT_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

bool chuoiHopLe(const std::string& chuoi);
bool ngayHopLe(const std::string& ngay);
int doiNgay(const std::string& ngay);
std::string ngayHienTai();
bool nhapChuoi(std::istream& luong, const std::string& loiNhac, std::string& chuoi);
bool docChuoiCu(std::istream& luong, std::string& chuoi);

//=====ham nhap so=====
template<class T>
bool nhapSo(std::istream& luong, const std::string& loiNhac, T& so){
    while(true){
        std::string dong;
        if(&luong == &std::cin){
            std::cout << loiNhac;
        }
        if(!std::getline(luong, dong)){
            return false;
        }
        std::istringstream doc(dong);
        T tam;
        if(doc >> tam){
            doc >> std::ws;
            if(doc.eof() && std::isfinite(static_cast<double>(tam))){
                so = tam;
                return true;
            }
        }
        if(&luong != &std::cin){
            return false;
        }
        std::cout << "Nhap sai dinh dang so. Vui long nhap lai.\n";
    }
}

#endif
