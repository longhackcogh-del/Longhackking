#include "NhapXuat.h"
#include <cctype>
#include <ctime>
#include <iomanip>

//=====ham xuat tien=====
void xuatTien(std::ostream& luong, double tien){
    std::ios::fmtflags dinhDangCu = luong.flags();
    std::streamsize doChinhXacCu = luong.precision();
    luong << std::fixed << std::setprecision(0) << tien;
    luong.flags(dinhDangCu);
    luong.precision(doChinhXacCu);
}

//=====ham kiem tra chuoi=====
bool chuoiHopLe(const std::string& chuoi){
    bool coChu = false;
    for(unsigned int i = 0; i < chuoi.size(); i++){
        unsigned char kyTu = static_cast<unsigned char>(chuoi[i]);
        if(kyTu == '\r' || kyTu == '\n'){
            return false;
        }
        if(!std::isspace(kyTu)){
            coChu = true;
        }
    }
    return coChu;
}

//=====ham kiem tra ngay=====
bool ngayHopLe(const std::string& ngay){
    if(ngay.size() != 10){
        return false;
    }
    if(ngay[2] != '/' || ngay[5] != '/'){
        return false;
    }
    for(int i = 0; i < 10; i++){
        if(i != 2 && i != 5){
            if(ngay[i] < '0' || ngay[i] > '9'){
                return false;
            }
        }
    }
    int d = (ngay[0] - '0') * 10 + ngay[1] - '0';
    int m = (ngay[3] - '0') * 10 + ngay[4] - '0';
    int y = 0;
    for(int i = 6; i < 10; i++){
        y = y * 10 + ngay[i] - '0';
    }
    if(y < 1 || m < 1 || m > 12){
        return false;
    }
    int soNgay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)){
        soNgay[1] = 29;
    }
    return d >= 1 && d <= soNgay[m - 1];
}

//=====ham doi ngay thanh so ngay=====
int doiNgay(const std::string& ngay){
    if(!ngayHopLe(ngay)){
        return -1;
    }
    int d = (ngay[0] - '0') * 10 + ngay[1] - '0';
    int m = (ngay[3] - '0') * 10 + ngay[4] - '0';
    int y = 0;
    for(int i = 6; i < 10; i++){
        y = y * 10 + ngay[i] - '0';
    }
    int namTruoc = y - 1;
    int ketQua = namTruoc * 365 + namTruoc / 4 - namTruoc / 100 + namTruoc / 400;
    int soNgay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)){
        soNgay[1] = 29;
    }
    for(int i = 0; i < m - 1; i++){
        ketQua += soNgay[i];
    }
    return ketQua + d;
}

std::string ngayHienTai(){
    std::time_t bayGio = std::time(nullptr);
    std::tm* ngay = std::localtime(&bayGio);
    if(ngay == nullptr){
        return "";
    }
    std::ostringstream ketQua;
    ketQua << std::setfill('0') << std::setw(2) << ngay->tm_mday << '/';
    ketQua << std::setw(2) << ngay->tm_mon + 1 << '/';
    ketQua << std::setw(4) << ngay->tm_year + 1900;
    return ketQua.str();
}

//=====ham nhap chuoi=====
bool nhapChuoi(std::istream& luong, const std::string& loiNhac, std::string& chuoi){
    if(&luong == &std::cin){
        std::cout << loiNhac;
    }
    if(!std::getline(luong, chuoi)){
        return false;
    }
    if(!chuoi.empty() && chuoi.back() == '\r'){
        chuoi.pop_back();
    }
    return chuoiHopLe(chuoi);
}

//=====ham doc chuoi dinh dang cu=====
bool docChuoiCu(std::istream& luong, std::string& chuoi){
    luong >> std::ws;
    chuoi.clear();
    if(luong.peek() != '"'){
        return static_cast<bool>(luong >> chuoi);
    }
    luong.get();
    char kyTu;
    while(luong.get(kyTu)){
        if(kyTu == '"'){
            return true;
        }
        if(kyTu == '\\'){
            if(!luong.get(kyTu)){
                return false;
            }
        }
        chuoi += kyTu;
    }
    return false;
}
