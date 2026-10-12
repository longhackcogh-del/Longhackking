#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include <filesystem>
#include <limits>
#include <sstream>
std::unique_ptr<TaiLieu> nhapTaiLieu() {
    std::cout << "Loai (1 Sach, 2 TapChi, 3 Bao): ";
    std::string dong;
    std::getline(std::cin, dong);
    std::unique_ptr<TaiLieu> taiLieu;
    if (dong == "1") taiLieu.reset(new Sach);
    else if (dong == "2") taiLieu.reset(new TapChi);
    else if (dong == "3") taiLieu.reset(new Bao);
    else throw std::invalid_argument("Loai khong hop le");
    std::cout << "Nhap mot dong: \"ma\" \"ten\" \"nha xuat ban\" nam tong con gia\n";
    if (dong == "1") std::cout << "Them: \"tac gia\" \"the loai\" \"ISBN\" soTrang\n";
    if (dong == "2") std::cout << "Them: soPhatHanh thangPhatHanh \"linh vuc\"\n";
    if (dong == "3") std::cout << "Them: \"dd/mm/yyyy\" \"loai bao\"\n";
    if (!std::getline(std::cin, dong)) throw std::invalid_argument("Ket thuc nhap");
    std::istringstream luong(dong);
    taiLieu->nhap(luong);
    luong >> std::ws;
    if (!luong.eof()) throw std::invalid_argument("Du truong du lieu");
    return taiLieu;
}
int main() {
    QuanLyTaiLieu quanLy;
    std::string chon;
    while (true) {
        std::cout << "\n1 Them | 2 Hien thi | 3 Tim ma | 4 Tim ten | 5 Sua\n"
                  << "6 Xoa | 7 Sap xep nam | 8 Sap xep gia | 9 Thong ke\n"
                  << "10 Luu | 11 Doc | 0 Thoat\nChon: ";
        if (!std::getline(std::cin, chon) || chon == "0") break;
        try {
            if (chon == "1") {
                std::cout << (quanLy.them(nhapTaiLieu()) ? "Da them\n" : "Trung ma\n");
            } else if (chon == "2") {
                quanLy.hienThi();
            } else if (chon == "3" || chon == "5" || chon == "6") {
                std::string ma;
                std::cout << "Ma: ";
                std::getline(std::cin, ma);
                if (chon == "3") {
                    TaiLieu* taiLieu = quanLy.timTheoMa(ma);
                    if (taiLieu) taiLieu->xuat();
                    else std::cout << "Khong tim thay\n";
                } else if (chon == "5") {
                    std::cout << (quanLy.sua(ma, nhapTaiLieu()) ? "Da sua\n" : "Tu choi: ma/loai/so dang muon phai giu nguyen\n");
                } else {
                    std::cout << (quanLy.xoa(ma) ? "Da xoa\n" : "Khong ton tai hoac dang muon\n");
                }
            } else if (chon == "4") {
                std::string ten;
                std::cout << "Ten hoac mot phan ten (phan biet hoa thuong): ";
                std::getline(std::cin, ten);
                if (quanLy.timTheoTen(ten) == 0) std::cout << "Khong tim thay\n";
            } else if (chon == "7") {
                quanLy.sapXepTheoNam();
                quanLy.hienThi();
            } else if (chon == "8") {
                quanLy.sapXepTheoGiaTri();
                quanLy.hienThi();
            } else if (chon == "9") {
                quanLy.thongKe();
            } else if (chon == "10" || chon == "11") {
                std::string loi;
                bool thanhCong;
                if (chon == "10") {
                    std::filesystem::create_directories("data");
                    thanhCong = quanLy.luu("data", loi);
                } else {
                    thanhCong = quanLy.doc("data", loi);
                }
                std::cout << (thanhCong ? "Thanh cong" : loi) << '\n';
            } else {
                std::cout << "Lua chon khong hop le\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Loi: " << e.what() << '\n';
        }
    }
    return 0;
}
