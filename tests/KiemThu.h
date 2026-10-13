#ifndef KIEMTHU_H
#define KIEMTHU_H
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

static int soKiemTra = 0;
static int soLoi = 0;

//=====ham kiem tra=====
inline void kiemTra(bool dieuKien, const std::string& ten){
    soKiemTra++;
    if(!dieuKien){
        soLoi++;
        std::cerr << "THAT BAI: " << ten << '\n';
    }
}

inline bool ghiTep(const std::filesystem::path& tep, const std::string& noiDung){
    std::ofstream luong(tep);
    luong << noiDung;
    luong.close();
    return static_cast<bool>(luong);
}

inline int ketQuaKiemThu(){
    std::cout << "Kiem tra: " << soKiemTra << ", loi: " << soLoi << '\n';
    if(soLoi > 0){
        return 1;
    }
    return 0;
}
#endif
