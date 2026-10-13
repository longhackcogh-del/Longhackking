#include "KiemThu.h"
#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "NhapXuat.h"
#include <limits>
#include <type_traits>
#include <sstream>

static Sach* taoSach(std::string ma = "S1", int tong = 3, int con = 3){
    return new Sach(ma, "Lap trinh C++", "NXB GD", 2020, tong, con,
                    125000.125, "Nguyen A", "CNTT", "ISBN-1", 200);
}

static bool themSach(QuanLyTaiLieu& quanLy, Sach* sach){
    if(!quanLy.them(sach)){
        delete sach;
        return false;
    }
    return true;
}

static bool phieuDangMuon(const std::string& ma){
    return ma == "S1";
}

//=====ham kiem thu du lieu=====
static void kiemThuDuLieu(){
    Sach maRong(" ", "T", "N", 2020, 1, 1, 1, "A", "B", "C", 1);
    Sach tongAm("S", "T", "N", 2020, -1, 0, 1, "A", "B", "C", 1);
    Sach conVuot("S", "T", "N", 2020, 1, 2, 1, "A", "B", "C", 1);
    Sach conAm("S", "T", "N", 2020, 1, -1, 1, "A", "B", "C", 1);
    Sach giaAm("S", "T", "N", 2020, 1, 1, -1, "A", "B", "C", 1);
    Sach namSai("S", "T", "N", 0, 1, 1, 1, "A", "B", "C", 1);
    Sach trangSai("S", "T", "N", 2020, 1, 1, 1, "A", "B", "C", 0);
    Sach giaVoHan("S", "T", "N", 2020, 1, 1,
                  std::numeric_limits<double>::infinity(), "A", "B", "C", 1);
    kiemTra(!maRong.hopLe(), "Ma rong");
    kiemTra(!tongAm.hopLe(), "Tong am");
    kiemTra(!conVuot.hopLe(), "Con vuot tong");
    kiemTra(!conAm.hopLe(), "Con am");
    kiemTra(!giaAm.hopLe(), "Gia am");
    kiemTra(!namSai.hopLe(), "Nam sai");
    kiemTra(!trangSai.hopLe(), "So trang sai");
    kiemTra(!giaVoHan.hopLe(), "Gia vo han");
    TapChi thangSai("T", "T", "N", 2020, 1, 1, 1, 1, 13, "Khoa hoc");
    TapChi soSai("T", "T", "N", 2020, 1, 1, 1, 0, 1, "Khoa hoc");
    Bao ngaySai("B", "B", "N", 2020, 1, 1, 1, "29/02/2023", "Ngay");
    kiemTra(!thangSai.hopLe(), "Thang sai");
    kiemTra(!soSai.hopLe(), "So phat hanh sai");
    kiemTra(!ngaySai.hopLe(), "Ngay sai");
    kiemTra(ngayHopLe("29/02/2024"), "Nam nhuan 2024");
    kiemTra(!ngayHopLe("29/02/1900"), "1900 khong nhuan");
    kiemTra(ngayHopLe("29/02/2000"), "2000 nhuan");
    kiemTra(!ngayHopLe("31/04/2024"), "Thang 4 co 30 ngay");
    kiemTra(!ngayHopLe("1/01/2024") && !ngayHopLe("aa/01/2024"), "Dinh dang ngay");
    kiemTra(doiNgay("01/03/2024") - doiNgay("28/02/2024") == 2, "Dem ngay qua nam nhuan");
    kiemTra(doiNgay("01/01/2025") - doiNgay("31/12/2024") == 1, "Dem ngay qua nam");
    Sach nhapSach;
    std::istringstream dung("S9\nTen co khoang trang\nNXB\n2020\n1\n1\n2.5\nA\nB\nC\n10\n");
    kiemTra(nhapSach.nhap(dung), "Nhap du lieu dung");
    std::istringstream sai("S0\nTen\nNXB\n2020\n1\n1\n2.5\nA\nB\nC\n0\n");
    kiemTra(!nhapSach.nhap(sai), "Nhap sai");
    kiemTra(nhapSach.layMa() == "S9", "Nhap sai giu doi tuong");
    std::istringstream saiSo("12abc\n");
    int so = 0;
    kiemTra(!nhapSo(saiSo, "", so), "Tu choi so co ky tu du");
    std::istringstream thieu("S0\nTen\n");
    kiemTra(!nhapSach.nhap(thieu) && nhapSach.layMa() == "S9", "Thieu truong giu doi tuong");
}

//=====ham kiem thu quan ly=====
static void kiemThuQuanLy(){
    QuanLyTaiLieu quanLy;
    std::string loi;
    std::ostringstream ketQua;
    quanLy.hienThi();
    quanLy.sapXepTheoNam();
    quanLy.sapXepTheoGiaTri();
    quanLy.thongKe(ketQua);
    kiemTra(quanLy.laySoLuong() == 0 && quanLy.timTheoMa("X") == nullptr, "Danh sach rong");
    kiemTra(quanLy.timNhiPhan("X") == nullptr && quanLy.layTaiLieu(0) == nullptr, "Tim nhi phan rong");
    kiemTra(!quanLy.xoa("X") && quanLy.timTheoTen("X", ketQua) == 0, "Tim xoa rong");
    kiemTra(themSach(quanLy, taoSach()), "Them sach");
    kiemTra(!themSach(quanLy, taoSach()) && !quanLy.them(nullptr), "Trung ma va con tro rong");
    kiemTra(quanLy.them(new TapChi("T1", "Khoa hoc", "NXB", 2018, 2, 2, 30000, 5, 12, "Ky thuat")), "Them tap chi");
    kiemTra(quanLy.them(new Bao("B1", "Tin tuc", "NXB", 2024, 4, 4, 10000, "29/02/2024", "Ngay")), "Them bao");
    TaiLieu* sach = quanLy.timTheoMa("S1");
    kiemTra(sach->tinhTienPhat(3) == 6000, "Phat sach da hinh");
    kiemTra(quanLy.timTheoMa("T1")->tinhTienPhat(3) == 9000, "Phat tap chi da hinh");
    kiemTra(quanLy.timTheoMa("B1")->tinhTienPhat(3) == 3000, "Phat bao da hinh");
    kiemTra(sach->tinhTienPhat(-1) == 0 && sach->tinhTienPhat(0) == 0, "Khong tre");
    kiemTra(sach->tinhTienPhat(std::numeric_limits<int>::max()) == 4294967294000.0, "Khong tran int");
    quanLy.hienThi();
    kiemTra(sach->giamSoLuong(2) && sach->laySoLuongCon() == 1, "Giam kho");
    kiemTra(!sach->giamSoLuong(2) && !sach->giamSoLuong(0) && !sach->tangSoLuong(-1), "Kho sai");
    kiemTra(!quanLy.xoa("S1"), "Chan xoa dang muon");
    Sach* moi = taoSach();
    kiemTra(!quanLy.sua("S1", moi), "Chan sua mat so dang muon");
    delete moi;
    moi = taoSach("S1", 5, 3);
    kiemTra(quanLy.sua("S1", moi), "Sua giu so dang muon");
    sach = quanLy.timTheoMa("S1");
    kiemTra(!sach->tangSoLuong(3) && sach->tangSoLuong(2), "Tra kho");
    quanLy.ganKiemTraPhieuMuon(phieuDangMuon);
    kiemTra(!quanLy.xoa("S1"), "Chan theo ham kiem tra phieu");
    quanLy.ganKiemTraPhieuMuon(nullptr);
    moi = taoSach("S2");
    kiemTra(!quanLy.sua("S1", moi) && !quanLy.sua("X", moi), "Chan doi ma va sua ma khong ton tai");
    delete moi;
    kiemTra(quanLy.timTheoTen("Lap trinh", ketQua) == 1, "Tim ten mot phan");
    quanLy.sapXepTheoNam();
    kiemTra(quanLy.layTaiLieu(0)->layMa() == "T1" && quanLy.layTaiLieu(2)->layMa() == "B1", "Selection Sort");
    quanLy.sapXepTheoGiaTri();
    kiemTra(quanLy.layTaiLieu(0)->layMa() == "B1" && quanLy.layTaiLieu(2)->layMa() == "S1", "Quick Sort");
    kiemTra(quanLy.timNhiPhan("S1") == sach && quanLy.timNhiPhan("KHONG") == nullptr, "Tim nhi phan sau sap xep");
    ketQua.str("");
    quanLy.thongKe(ketQua);
    kiemTra(ketQua.str().find("Sach: dau=1, tong=5, con=5, dang muon=0") != std::string::npos, "Thong ke");

    std::filesystem::path thuMuc = std::filesystem::path("build") / "kiem_thu_tai_lieu_v2";
    std::filesystem::create_directories(thuMuc);
    kiemTra(quanLy.luu(thuMuc.string(), loi), "Luu ba tep");
    QuanLyTaiLieu docLai;
    kiemTra(docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 3, "Doc ba tep");
    kiemTra(docLai.timTheoMa("S1")->layGiaTri() == 125000.125, "Khoi phuc gia chinh xac");
    kiemTra(docLai.timTheoMa("B1")->tinhTienPhat(2) == 2000 && docLai.timTheoMa("T1")->layLoai() == "TapChi", "Khoi phuc da hinh");
    kiemTra(!docLai.doc("build/khong_ton_tai_v2", loi) && docLai.laySoLuong() == 3, "Tep thieu giu danh sach");
    kiemTra(!quanLy.luu("build/khong_ton_tai_v2", loi), "Loi mo tep ghi");
    ghiTep(thuMuc / "Bao.txt", "du lieu hong\n");
    kiemTra(!docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 3, "Tep hong giu danh sach");
    quanLy.luu(thuMuc.string(), loi);
    ghiTep(thuMuc / "Bao.txt", "THUVIEN_2\n1\nS1\nBao\nNXB\n2024\n1\n1\n10\n01/01/2024\nNgay\n");
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Trung ma giua tep");
    quanLy.luu(thuMuc.string(), loi);
    std::ofstream themDu(thuMuc / "Sach.txt", std::ios::app);
    themDu << "DU\n";
    themDu.close();
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Du truong");
    quanLy.luu(thuMuc.string(), loi);
    docLai.timTheoMa("S1")->giamSoLuong();
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Khong doc de mat luot muon");
    docLai.timTheoMa("S1")->tangSoLuong();
    kiemTra(quanLy.xoa("S1") && !quanLy.xoa("S1"), "Xoa thanh cong");
    QuanLyTaiLieu rong;
    rong.luu(thuMuc.string(), loi);
    kiemTra(docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 0, "Doc tep rong");

    ghiTep(thuMuc / "Sach.txt", "\"S1\" \"Ten co \\\"ngoac\\\"\" \"NXB GD\" 2020 3 3 125000.125 \"Nguyen A\" \"CNTT\" \"ISBN\" 200\n");
    ghiTep(thuMuc / "TapChi.txt", "");
    ghiTep(thuMuc / "Bao.txt", "");
    kiemTra(docLai.doc(thuMuc.string(), loi) && docLai.laySoLuong() == 1, "Doc tep dinh dang cu");
    kiemTra(docLai.timTheoMa("S1")->layTen() == "Ten co \"ngoac\"", "Chuoi cu co dau ngoac");
}

//=====ham kiem thu mang va sap xep=====
static void kiemThuMang(){
    DanhSachQuanLy<int> mang;
    kiemTra(mang.them(1) && mang.chen(0, 2) && mang.sua(1, 3) && mang.xoa(0), "Template them chen sua xoa");
    kiemTra(mang[0] == 3 && mang.laySoLuong() == 1, "Template so luong");
    kiemTra(!mang.chen(-1, 4) && !mang.sua(1, 4) && !mang.xoa(1), "Vi tri sai");
    bool baoLoi = false;
    try{
        mang[-1];
    }
    catch(const std::out_of_range&){
        baoLoi = true;
    }
    kiemTra(baoLoi, "operator[] bao chi so sai");
    mang.them(1);
    mang.sapXep();
    kiemTra(mang[0] == 1 && mang.timTheoKhoa(3) == 1, "Template tim sap xep");
    std::ostringstream luong;
    mang.xuat(luong);
    kiemTra(luong.str() == "1\n3\n", "Template xuat");
    int ds[] = {2, 3, 4};
    kiemTra(timMin(2, 3) == 2 && timMax(2, 3) == 3 && timKiemTuanTu(ds, 3, 4) == 2, "Ham template");
    QuanLyTaiLieu nhieu;
    for(int i = 0; i < 200; i++){
        themSach(nhieu, new Sach(std::to_string(i), "T", "N", 2000 + i % 7,
                                1, 1, i % 11, "A", "B", "C", 1));
    }
    nhieu.sapXepTheoNam();
    for(int i = 1; i < 200; i++){
        kiemTra(nhieu.layTaiLieu(i - 1)->layNam() <= nhieu.layTaiLieu(i)->layNam(), "Thu tu nam");
    }
    nhieu.sapXepTheoGiaTri();
    for(int i = 1; i < 200; i++){
        kiemTra(nhieu.layTaiLieu(i - 1)->layGiaTri() <= nhieu.layTaiLieu(i)->layGiaTri(), "Thu tu gia trung nhau");
    }
}

int main(){
    static_assert(std::is_abstract<TaiLieu>::value, "TaiLieu phai truu tuong");
    static_assert(std::has_virtual_destructor<TaiLieu>::value, "Ham huy phai ao");
    kiemThuDuLieu();
    kiemThuQuanLy();
    kiemThuMang();
    return ketQuaKiemThu();
}
