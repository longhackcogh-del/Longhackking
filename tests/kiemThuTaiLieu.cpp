#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "ThuatToan.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <type_traits>
int soKiemTra = 0;
void kiemTra(bool dieuKien, const std::string& ten) {
    if (!dieuKien) throw std::runtime_error("THAT BAI: " + ten);
    soKiemTra++;
}
template<class Ham> void phaiBaoLoi(Ham ham, const std::string& ten) {
    bool coLoi = false;
    try { ham(); }
    catch (const std::exception&) { coLoi = true; }
    kiemTra(coLoi, ten);
}
std::unique_ptr<TaiLieu> sach(std::string ma = "S1", int tong = 3, int con = 3) {
    return std::unique_ptr<TaiLieu>(new Sach(ma, "Lap trinh C++", "NXB GD", 2020,
                                          tong, con, 125000.125, "Nguyen A", "CNTT", "ISBN-1", 200));
}
bool phieuDangMuon(const std::string& ma) { return ma == "S1"; }
void ghiTep(const std::filesystem::path& tep, const std::string& noiDung) {
    std::ofstream luong(tep);
    luong << noiDung;
    if (!luong) throw std::runtime_error("Khong ghi duoc du lieu kiem thu");
}
int main() {
    static_assert(std::is_abstract<TaiLieu>::value, "TaiLieu phai truu tuong");
    static_assert(std::has_virtual_destructor<TaiLieu>::value, "Ham huy phai ao");
    try {
        QuanLyTaiLieu q;
        std::string loi;
        std::ostringstream ketQua;
        q.hienThi();
        q.sapXepTheoNam();
        q.sapXepTheoGiaTri();
        q.thongKe(ketQua);
        kiemTra(q.laySoLuong() == 0 && q.timTheoMa("X") == nullptr, "Danh sach rong");
        kiemTra(!q.xoa("X") && q.timTheoTen("X", ketQua) == 0, "Tim xoa rong");
        phaiBaoLoi([&] { q.layTaiLieu(0); }, "Chi so rong");
        phaiBaoLoi([] { sach("   "); }, "Ma rong");
        phaiBaoLoi([] { sach("X", -1, 0); }, "Tong am");
        phaiBaoLoi([] { sach("X", 1, 2); }, "Con vuot tong");
        phaiBaoLoi([] { sach("X", 1, -1); }, "Con am");
        phaiBaoLoi([] { Sach s("S", "T", "N", 2020, 1, 1, -1, "A", "B", "C", 1); }, "Gia am");
        phaiBaoLoi([] { Sach s("S", "T", "N", 0, 1, 1, 1, "A", "B", "C", 1); }, "Nam sai");
        phaiBaoLoi([] { Sach s("S", "T", "N", 2020, 1, 1, 1, "A", "B", "C", 0); }, "So trang sai");
        phaiBaoLoi([] { Sach s("S", "T", "N", 2020, 1, 1, std::numeric_limits<double>::infinity(), "A", "B", "C", 1); }, "Gia vo han");
        phaiBaoLoi([] { TapChi t("T", "T", "N", 2020, 1, 1, 1, 1, 13, "Khoa hoc"); }, "Thang sai");
        phaiBaoLoi([] { TapChi t("T", "T", "N", 2020, 1, 1, 1, 0, 1, "Khoa hoc"); }, "So phat hanh sai");
        phaiBaoLoi([] { Bao b("B", "B", "N", 2020, 1, 1, 1, "29/02/2023", "Ngay"); }, "Ngay sai");
        kiemTra(TaiLieu::ngayHopLe("29/02/2024") && !TaiLieu::ngayHopLe("29/02/1900") && TaiLieu::ngayHopLe("29/02/2000"), "Nam nhuan");
        kiemTra(!TaiLieu::ngayHopLe("31/04/2024") && !TaiLieu::ngayHopLe("1/01/2024") && !TaiLieu::ngayHopLe("aa/01/2024"), "Dinh dang ngay");
        kiemTra(q.them(sach()), "Them sach");
        kiemTra(!q.them(sach()) && !q.them(nullptr), "Trung ma va con tro rong");
        kiemTra(q.them(std::unique_ptr<TaiLieu>(new TapChi("T1", "Khoa hoc", "NXB", 2018, 2, 2, 30000, 5, 12, "Ky thuat"))), "Them tap chi");
        kiemTra(q.them(std::unique_ptr<TaiLieu>(new Bao("B1", "Tin tuc", "NXB", 2024, 4, 4, 10000, "29/02/2024", "Ngay"))), "Them bao");
        TaiLieu* s = q.timTheoMa("S1");
        kiemTra(s->tinhTienPhat(3) == 6000 && q.timTheoMa("T1")->tinhTienPhat(3) == 9000 && q.timTheoMa("B1")->tinhTienPhat(3) == 3000, "Phat da hinh");
        kiemTra(s->tinhTienPhat(-1) == 0 && s->tinhTienPhat(0) == 0, "Khong tre");
        kiemTra(s->tinhTienPhat(std::numeric_limits<int>::max()) == 4294967294000.0, "Phat khong tran int");
        q.hienThi();
        kiemTra(s->giamSoLuong(2) && s->laySoLuongCon() == 1, "Giam kho");
        kiemTra(!s->giamSoLuong(2) && !s->giamSoLuong(0) && !s->tangSoLuong(-1), "Kho sai");
        kiemTra(!q.xoa("S1"), "Chan xoa dang muon");
        kiemTra(!q.sua("S1", sach()), "Chan sua mat so dang muon");
        kiemTra(q.sua("S1", sach("S1", 5, 3)), "Sua giu so dang muon");
        s = q.timTheoMa("S1");
        kiemTra(!s->tangSoLuong(3) && s->tangSoLuong(2), "Tra kho");
        q.ganKiemTraPhieuMuon(phieuDangMuon);
        kiemTra(!q.xoa("S1"), "Chan theo phieu muon");
        q.ganKiemTraPhieuMuon(nullptr);
        kiemTra(!q.sua("S1", sach("S2")) && !q.sua("X", sach("S2")), "Chan doi ma va sua ma khong ton tai");
        kiemTra(q.timTheoTen("Lap trinh", ketQua) == 1, "Tim ten mot phan");
        q.sapXepTheoNam();
        kiemTra(q.layTaiLieu(0)->layMa() == "T1" && q.layTaiLieu(2)->layMa() == "B1", "Selection Sort");
        q.sapXepTheoGiaTri();
        kiemTra(q.layTaiLieu(0)->layMa() == "B1" && q.layTaiLieu(2)->layMa() == "S1", "Quick Sort");
        ketQua.str("");
        q.thongKe(ketQua);
        kiemTra(ketQua.str().find("Sach: dau=1, tong=5, con=5, dang muon=0") != std::string::npos, "Thong ke");
        Sach nhapSach;
        std::istringstream dung("\"S9\" \"Ten co khoang trang\" \"NXB\" 2020 1 1 2.5 \"A\" \"B\" \"C\" 10");
        nhapSach.nhap(dung);
        std::istringstream sai("\"S0\" \"Ten\" \"NXB\" 2020 1 1 2.5 \"A\" \"B\" \"C\" 0");
        phaiBaoLoi([&] { nhapSach.nhap(sai); }, "Nhap sai");
        kiemTra(nhapSach.layMa() == "S9", "Nhap sai giu nguyen doi tuong");
        std::filesystem::path thuMuc = std::filesystem::path("build") / "du_lieu_kiem_thu";
        std::filesystem::create_directories(thuMuc);
        kiemTra(q.luu(thuMuc.string(), loi), "Luu ba tep");
        QuanLyTaiLieu docLai;
        kiemTra(docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 3, "Doc ba tep");
        kiemTra(docLai.timTheoMa("S1")->layGiaTri() == 125000.125 && docLai.timTheoMa("B1")->tinhTienPhat(2) == 2000, "Khoi phuc gia va da hinh");
        kiemTra(docLai.timTheoMa("T1")->layLoai() == "TapChi" && docLai.timTheoMa("S1")->laySoLuongCon() == 5, "Khoi phuc loai va kho");
        kiemTra(!docLai.doc("build/khong_ton_tai", loi) && docLai.laySoLuong() == 3, "Tep thieu giu danh sach");
        kiemTra(!q.luu("build/khong_ton_tai", loi), "Loi mo tep ghi");
        ghiTep(thuMuc / "Bao.txt", "du lieu hong\n");
        kiemTra(!docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 3, "Tep hong giu danh sach");
        q.luu(thuMuc.string(), loi);
        ghiTep(thuMuc / "Bao.txt", "\"S1\" \"Bao\" \"NXB\" 2024 1 1 10 \"01/01/2024\" \"Ngay\"\n");
        kiemTra(!docLai.doc(thuMuc.string(), loi), "Trung ma giua cac tep");
        q.luu(thuMuc.string(), loi);
        std::ofstream themDu(thuMuc / "Sach.txt", std::ios::app);
        themDu << "\"S2\" \"T\" \"N\" 2020 1 1 1 \"A\" \"B\" \"C\" 1 DU\n";
        themDu.close();
        kiemTra(!docLai.doc(thuMuc.string(), loi), "Du truong");
        q.luu(thuMuc.string(), loi);
        docLai.timTheoMa("S1")->giamSoLuong();
        kiemTra(!docLai.doc(thuMuc.string(), loi), "Khong doc de mat luot muon");
        docLai.timTheoMa("S1")->tangSoLuong();
        kiemTra(q.xoa("S1") && !q.xoa("S1"), "Xoa thanh cong");
        QuanLyTaiLieu rong;
        rong.luu(thuMuc.string(), loi);
        kiemTra(docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 0, "Doc tep rong");
        DanhSachQuanLy<int> mang;
        mang.them(1);
        mang.chen(0, 2);
        mang.sua(1, 3);
        mang.xoa(0);
        kiemTra(mang[0] == 3 && mang.laySoLuong() == 1, "Template danh sach");
        phaiBaoLoi([&] { mang[-1]; }, "Chi so am");
        int ds[] = {2, 3, 4};
        kiemTra(timMin(2, 3) == 2 && timMax(2, 3) == 3 && timKiemTuanTu(ds, 3, 4) == 2, "Ham template");
        QuanLyTaiLieu nhieu;
        for (int i = 0; i < 200; i++) {
            nhieu.them(std::unique_ptr<TaiLieu>(new Sach(std::to_string(i), "T", "N", 2000 + i % 7, 1, 1, i % 11, "A", "B", "C", 1)));
        }
        nhieu.sapXepTheoNam();
        for (int i = 1; i < 200; i++) kiemTra(nhieu.layTaiLieu(i - 1)->layNam() <= nhieu.layTaiLieu(i)->layNam(), "Thu tu nam");
        nhieu.sapXepTheoGiaTri();
        for (int i = 1; i < 200; i++) kiemTra(nhieu.layTaiLieu(i - 1)->layGiaTri() <= nhieu.layTaiLieu(i)->layGiaTri(), "Thu tu gia trung nhau");
        std::cout << "DAT: " << soKiemTra << " kiem tra\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
