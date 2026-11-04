#ifndef TEPHETHONG_H
#define TEPHETHONG_H
#include <string>

class QuanLyThuVien;

extern const char* const tenTepThuVien[9];
bool kiemTraThuMucDuLieu(const std::string& thuMuc, bool canDuTep, std::string& loi);
bool luuBoDuLieu(const QuanLyThuVien& thuVien, const std::string& thuMuc, std::string& loi);

#endif
