#ifndef THONGKE_H
#define THONGKE_H
#include "QuanLyThuVien.h"
#include <ostream>

void thongKeDocGia(const QuanLyThuVien& thuVien, std::ostream& luong);
void thongKeTaiLieuMuonNhieu(const QuanLyThuVien& thuVien, std::ostream& luong);
bool thucNghiemThuatToan(std::ostream& luong);
#endif
