#ifndef TEP_H
#define TEP_H
#include "NhapXuat.h"
#include <fstream>
#include <iomanip>

//=====ham ghi dau tep=====
inline void ghiDauTep(std::ostream& tep, int soLuong){
    tep << "THUVIEN_2\n" << soLuong << '\n';
    tep << std::setprecision(17);
}

//=====ham doc dau tep=====
inline bool docDauTep(std::istream& tep, int& soLuong){
    std::string dau;
    if(!std::getline(tep, dau)){
        return false;
    }
    if(!dau.empty() && dau.back() == '\r'){
        dau.pop_back();
    }
    if(dau != "THUVIEN_2"){
        return false;
    }
    if(!nhapSo(tep, "", soLuong)){
        return false;
    }
    return soLuong >= 0 && soLuong <= 1000000;
}

inline bool hetTep(std::istream& tep){
    tep >> std::ws;
    return tep.eof() && !tep.bad();
}
#endif
