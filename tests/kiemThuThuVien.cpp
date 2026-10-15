#include "KiemThu.h"
#include "QuanLyThuVien.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "SinhVien.h"
#include "GiangVien.h"
#include "ThongKe.h"
#include "ThucNghiem.h"
#include <type_traits>
#include <sstream>

static SinhVien* taoSinhVien(const std::string& ma, int soMuon = 0, bool hoatDong = true){
    return new SinhVien("N_" + ma, "Nguyen Sinh Vien", "01/01/2004", "sv@dh.edu",
                        "0901234567", ma, soMuon, hoatDong, "SV_" + ma, "CT01", "CNTT", "Phan mem");
}

static GiangVien* taoGiangVien(const std::string& ma, int soMuon = 0){
    return new GiangVien("N_" + ma, "Nguyen Giang Vien", "01/01/1980", "gv@dh.edu",
                         "0901234568", ma, soMuon, true, "GV_" + ma, "CNTT", "Tien si", 10);
}

static bool themDocGia(QuanLyDocGia& quanLy, DocGia* nguoi){
    if(!quanLy.them(nguoi)){
        delete nguoi;
        return false;
    }
    return true;
}

static ThuThuTruong taoThuThu(const std::string& ma, int soNhanVien = 12, double phuCap = 2){
    return ThuThuTruong("N_" + ma, "Tran Thu Thu", "01/01/1975", "tt@dh.edu", "0901234569",
                       "DG_" + ma, "GV_" + ma, "CNTT", "Tien si", 20,
                       ma, "Sang", "Truong thu thu", 5000000, 2, "Tang 1", soNhanVien, phuCap);
}

static void taoDuLieu(QuanLyThuVien& heThong){
    kiemTra(heThong.layTaiLieu().them(new Sach("S1", "Lap trinh C++", "NXB", 2020,
                                              20, 20, 100000, "Nguyen A", "CNTT", "ISBN", 100)), "Them sach he thong");
    kiemTra(heThong.layTaiLieu().them(new TapChi("T1", "Khoa hoc", "NXB", 2019,
                                                2, 2, 30000, 1, 2, "CNTT")), "Them tap chi he thong");
    kiemTra(heThong.layTaiLieu().them(new Bao("B1", "Tin tuc", "NXB", 2024,
                                             3, 3, 10000, "29/02/2024", "Ngay")), "Them bao he thong");
    kiemTra(themDocGia(heThong.layDocGia(), taoSinhVien("D1")), "Them sinh vien");
    kiemTra(themDocGia(heThong.layDocGia(), taoGiangVien("D2")), "Them giang vien");
    kiemTra(themDocGia(heThong.layDocGia(), taoSinhVien("DX", 0, false)), "Them doc gia bi khoa");
    kiemTra(heThong.layNhanVien().them(NhanVienThuThu("N_NV1", "Le Thu Thu", "01/01/1990",
                                                     "nv@dh.edu", "0901234560", "NV1",
                                                     "Sang", "Thu thu", 4000000, 1.5)), "Them nhan vien");
    kiemTra(heThong.layThuThuTruong().them(taoThuThu("TT1")), "Them thu thu truong");
}

//=====ham kiem thu OOP va nhan su=====
static void kiemThuOOP(){
    ThuThuTruong thuThu = taoThuThu("TT");
    Nguoi* nhanhGiangVien = static_cast<GiangVien*>(&thuThu);
    Nguoi* nhanhNhanVien = static_cast<NhanVienThuThu*>(&thuThu);
    kiemTra(nhanhGiangVien == nhanhNhanVien, "Hai nhanh dung chung mot Nguoi");
    kiemTra(thuThu.hopLe() && thuThu.tinhThuNhap() == 14000000, "Thu nhap thu thu truong");
    kiemTra(!taoThuThu("AM", -1).hopLe(), "So nhan vien am");
    kiemTra(!taoThuThu("AM", 1, -1).hopLe(), "Phu cap am");
    Nguoi nguoiSai("N", "Ten", "31/04/2000", "a@b.c", "0901");
    kiemTra(!nguoiSai.hopLe(), "Ngay sinh sai");
    Nguoi emailSai("N", "Ten", "01/01/2000", "ab.c", "0901");
    kiemTra(!emailSai.hopLe(), "Email sai");
    NhanVienThuThu nhanVienSai("N", "Ten", "01/01/2000", "a@b.c", "0901",
                               "NV", "Sang", "Thu thu", 0, 1);
    kiemTra(!nhanVienSai.hopLe(), "Luong khong duong");
    NhanVienThuThu heSoSai("N", "Ten", "01/01/2000", "a@b.c", "0901",
                           "NV", "Sang", "Thu thu", 1, -1);
    kiemTra(!heSoSai.hopLe(), "He so khong duong");
    GiangVien namSai("N", "Ten", "01/01/2000", "a@b.c", "0901",
                     "DG", 0, true, "GV", "CNTT", "Thac si", -1);
    kiemTra(!namSai.hopLe(), "Nam cong tac am");
    SinhVien* sinhVien = taoSinhVien("S", 2);
    GiangVien* giangVien = taoGiangVien("G", 3);
    DocGia* coSo = sinhVien;
    kiemTra(coSo->layGioiHanMuon() == 5 && giangVien->layGioiHanMuon() == 10, "Han muc da hinh");
    kiemTra(*sinhVien + *giangVien == 5, "operator+ doc gia");
    std::ostringstream noiDung;
    thuThu.ghi(noiDung);
    ThuThuTruong docLai;
    std::istringstream dauVao(noiDung.str());
    kiemTra(docLai.nhap(dauVao) && docLai.tinhThuNhap() == thuThu.tinhThuNhap(), "Nhap xuat thu thu truong");
    std::istringstream sai("N\nTen\n01/01/2000\na@b.c\n0901\n");
    kiemTra(!docLai.nhap(sai) && docLai.layMa() == "TT", "Nhap sai giu thu thu truong");
    delete sinhVien;
    delete giangVien;

    QuanLyDocGia docGia;
    kiemTra(themDocGia(docGia, taoSinhVien("A")), "Them doc gia A");
    kiemTra(!themDocGia(docGia, taoSinhVien("A")), "Trung ma doc gia");
    DocGia* chen = taoGiangVien("B", 1);
    kiemTra(docGia.chen(0, chen), "Chen doc gia dau danh sach");
    kiemTra(docGia.layDocGia(0)->layMa() == "B", "Vi tri chen doc gia");
    docGia.sapXepTheoSoMuon();
    kiemTra(docGia.layDocGia(0)->layMa() == "A", "Bubble Sort doc gia");
    kiemTra(docGia.timBangBam("B") != nullptr && docGia.timBangBam("X") == nullptr, "Bang bam doc gia");
    kiemTra(docGia.timTheoTen("Nguyen") == 2, "Tim ho ten");
    kiemTra(docGia.xoa("A") && !docGia.xoa("B"), "Xoa doc gia va chan dang muon");
    DocGia* moi = taoGiangVien("B", 1);
    kiemTra(docGia.sua("B", moi), "Sua giu so dang muon");
    moi = taoGiangVien("B", 0);
    kiemTra(!docGia.sua("B", moi), "Chan sua mat luot muon");
    delete moi;

    QuanLyNhanVien nhanVien;
    NhanVienThuThu dau("N1", "Ten 1", "01/01/1990", "a@b.c", "0901",
                       "NV1", "Sang", "Thu thu", 1000, 2);
    NhanVienThuThu sau("N2", "Ten 2", "01/01/1990", "a@b.c", "0902",
                       "NV2", "Chieu", "Thu thu", 1000, 1);
    kiemTra(nhanVien.them(dau) && nhanVien.them(sau) && !nhanVien.them(dau), "Nhan vien them trung");
    kiemTra(nhanVien.timTheoMa("NV1")->tinhLuong() == 2000, "Tinh luong");
    kiemTra(nhanVien.timTheoCa("Sang") == 1 && nhanVien.timTheoCa("Dem") == 0, "Tim ca");
    nhanVien.sapXepTheoHeSoLuong();
    kiemTra(nhanVien.lay(0)->layMa() == "NV2", "Sap xep he so luong");
    kiemTra(nhanVien.sua("NV1", dau) && !nhanVien.sua("X", dau), "Sua nhan vien");
    kiemTra(nhanVien.xoa("NV1") && !nhanVien.xoa("NV1"), "Xoa nhan vien");
    QuanLyThuThuTruong quanLyThuThu;
    kiemTra(quanLyThuThu.them(taoThuThu("TT1", 12, 2))
             && quanLyThuThu.them(taoThuThu("TT2", 5, 1)), "Them thu thu truong");
    kiemTra(!quanLyThuThu.them(taoThuThu("TT1")), "Trung thu thu truong");
    kiemTra(quanLyThuThu.timTheoSoNhanVien(10) == 1, "Quan ly hon 10 nhan vien");
    quanLyThuThu.sapXepTheoPhuCap();
    kiemTra(quanLyThuThu.lay(0)->layMa() == "TT2", "Sap xep phu cap");
}

//=====ham kiem thu muon tra=====
static void kiemThuMuonTra(QuanLyThuVien& heThong){
    QuanLyPhieuMuon& phieu = heThong.layPhieuMuon();
    QuanLyDocGia& docGia = heThong.layDocGia();
    QuanLyTaiLieu& taiLieu = heThong.layTaiLieu();
    QuanLyViPham& viPham = heThong.layViPham();
    PhieuMuon muon("P2", "D1", "S1", "28/02/2024", "29/02/2024", 2);
    kiemTra(phieu.lapPhieu(muon, docGia, taiLieu), "Lap phieu");
    kiemTra(docGia.timTheoMa("D1")->laySoDangMuon() == 2
             && taiLieu.timTheoMa("S1")->laySoLuongCon() == 18, "Cap nhat dong thoi");
    kiemTra(!phieu.lapPhieu(muon, docGia, taiLieu), "Chan phieu trung");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "D1", "S1", "01/03/2024", "02/03/2024", 4),
                            docGia, taiLieu), "Vuot han muc");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "DX", "S1", "01/03/2024", "02/03/2024", 1),
                            docGia, taiLieu), "Tai khoan bi khoa");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "KHONG", "S1", "01/03/2024", "02/03/2024", 1),
                            docGia, taiLieu), "Doc gia khong ton tai");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "D1", "KHONG", "01/03/2024", "02/03/2024", 1),
                            docGia, taiLieu), "Tai lieu khong ton tai");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "D2", "T1", "01/03/2024", "02/03/2024", 3),
                            docGia, taiLieu), "Khong du ton kho");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "D2", "T1", "02/03/2024", "01/03/2024", 1),
                            docGia, taiLieu), "Han tra truoc ngay muon");
    kiemTra(!phieu.lapPhieu(PhieuMuon("X", "D2", "T1", "01/03/2024", "02/03/2024", 0),
                            docGia, taiLieu), "So luong muon 0");
    kiemTra(!taiLieu.xoa("S1") && !docGia.xoa("D1"), "Chan xoa doi tuong dang muon");
    kiemTra(phieu.lapPhieu(PhieuMuon("P3", "D1", "S1", "28/02/2024", "29/02/2024", 3),
                           docGia, taiLieu), "Muon den dung han muc");
    kiemTra(docGia.timTheoMa("D1")->laySoDangMuon() == 5, "Sinh vien muon toi da 5");
    kiemTra(!phieu.traTaiLieu("P2", "27/02/2024", docGia, taiLieu, viPham), "Ngay tra truoc ngay muon");
    kiemTra(!phieu.traTaiLieu("P2", "31/02/2024", docGia, taiLieu, viPham), "Ngay tra sai");
    kiemTra(phieu.traTaiLieu("P3", "29/02/2024", docGia, taiLieu, viPham), "Tra dung han");
    kiemTra(viPham.laySoLuong() == 0 && phieu.timTheoMa("P3")->layTienPhat() == 0, "Dung han khong vi pham");
    kiemTra(phieu.traTaiLieu("P2", "02/03/2024", docGia, taiLieu, viPham), "Tra tre qua thang nhuan");
    kiemTra(phieu.timTheoMa("P2")->layTienPhat() == 8000, "Phat theo ngay va so luong");
    kiemTra(docGia.timTheoMa("D1")->laySoDangMuon() == 0
             && taiLieu.timTheoMa("S1")->laySoLuongCon() == 20, "Tra cap nhat dong thoi");
    kiemTra(!phieu.traTaiLieu("P2", "03/03/2024", docGia, taiLieu, viPham), "Chan tra hai lan");
    kiemTra(!viPham.ghiViPham(*phieu.timTheoMa("P2")) && viPham.laySoLuong() == 1, "Chan ghi vi pham trung");
    kiemTra(viPham.demViPham("D1") == 1 && viPham.tinhTongTienPhatChuaThanhToan() == 8000, "Thong ke vi pham");
    kiemTra(viPham.thanhToanPhat("VP_P2") && !viPham.thanhToanPhat("VP_P2"), "Chan thu phat hai lan");
    kiemTra(!viPham.thanhToanPhat("KHONG"), "Khong thanh toan ma la");
    kiemTra(viPham.tinhTongTienPhatDaThanhToan() == 8000, "Tong da thu");
    const ThuThuTruong* thuThu = heThong.layThuThuTruong().timTheoMa("TT1");
    kiemTra(thuThu->duyetViPham(viPham, "VP_P2"), "Duyet vi pham");
    kiemTra(!thuThu->duyetViPham(viPham, "VP_P2"), "Khong duyet trung");
    thuThu->xemNhatKyViPham(viPham);
    kiemTra(phieu.lapPhieu(PhieuMuon("P1", "D2", "T1", "01/01/2024", "01/01/2024", 1),
                           docGia, taiLieu), "Lap phieu tap chi");
    kiemTra(phieu.timTheoMa("P1")->tinhTienPhat(*taiLieu.timTheoMa("T1"), "03/01/2024") == 6000,
             "Phat tap chi qua con tro");
    kiemTra(phieu.traTaiLieu("P1", "01/01/2024", docGia, taiLieu, viPham), "Tra tap chi dung ngay");
    kiemTra(phieu.lapPhieu(PhieuMuon("P5", "D2", "B1", "30/12/2024", "31/12/2024", 2),
                           docGia, taiLieu), "Lap phieu bao");
    kiemTra(phieu.traTaiLieu("P5", "02/01/2025", docGia, taiLieu, viPham), "Tra bao qua nam");
    kiemTra(phieu.timTheoMa("P5")->layTienPhat() == 4000 && viPham.laySoLuong() == 2, "Phat bao 2 ngay 2 ban");
    kiemTra(viPham.tinhTongTienPhatChuaThanhToan() == 4000, "Tong chua thu");
    kiemTra(phieu.lapPhieu(PhieuMuon("P6", "D2", "S1", "01/01/2025", "31/12/9999", 1),
                           docGia, taiLieu), "Phieu chua den han");
    kiemTra(phieu.lapPhieu(PhieuMuon("P7", "D1", "S1", "01/01/2000", "02/01/2000", 1),
                           docGia, taiLieu), "Phieu qua han chua tra");
    kiemTra(kiemTraHanMuon(*docGia.timTheoMa("D1"), *phieu.timTheoMa("P7")), "Friend kiem tra qua han");
    kiemTra(!kiemTraHanMuon(*docGia.timTheoMa("D2"), *phieu.timTheoMa("P7")), "Friend kiem tra dung chu phieu");
    kiemTra(!kiemTraHanMuon(*docGia.timTheoMa("D2"), *phieu.timTheoMa("P6")), "Friend chua qua han");
    kiemTra(!kiemTraHanMuon(*docGia.timTheoMa("D1"), *phieu.timTheoMa("P2")), "Friend phieu da tra");
    kiemTra(kiemTraDieuKienMuon(*docGia.timTheoMa("D1"), *taiLieu.timTheoMa("S1")), "Friend dieu kien muon");
    kiemTra(!kiemTraDieuKienMuon(*docGia.timTheoMa("DX"), *taiLieu.timTheoMa("S1")), "Friend tu choi tai khoan khoa");
    phieu.sapXepTheoMa();
    kiemTra(phieu.lay(0)->layMa() == "P1" && phieu.lay(phieu.laySoLuong() - 1)->layMa() == "P7", "Merge Sort phieu");
    std::ostringstream ketQua;
    ketQua << *phieu.timTheoMa("P2");
    kiemTra(ketQua.str().find("Tien phat: 8000") != std::string::npos, "operator<< phieu");
    kiemTra(phieu.lietKeTheoDocGia("D1") == 3, "Liet ke phieu doc gia");
    kiemTra(phieu.lietKeDocGiaMuonTaiLieu("S1", docGia) == 2, "Liet ke doc gia dang muon");
    std::string loi;
    kiemTra(heThong.kiemTraNhatQuan(loi), "He thong nhat quan sau muon tra");
}

//=====ham kiem thu doc ghi lien ket=====
static void kiemThuTep(QuanLyThuVien& heThong){
    std::filesystem::path thuMuc = std::filesystem::path("build") / "kiem_thu_thu_vien_v2";
    std::string loi;
    kiemTra(heThong.luu(thuMuc.string(), loi), "Luu 9 tep");
    QuanLyThuVien docLai;
    kiemTra(docLai.doc(thuMuc.string(), loi), "Doc 9 tep");
    kiemTra(docLai.kiemTraNhatQuan(loi), "Doc giu nhat quan");
    kiemTra(docLai.layDocGia().timTheoMa("D1")->laySoDangMuon() == 1
             && docLai.layTaiLieu().timTheoMa("S1")->laySoLuongCon() == 18, "Khoi phuc ton kho va so muon");
    kiemTra(docLai.layViPham().tinhTongTienPhatDaThanhToan() == 8000
             && docLai.layViPham().tinhTongTienPhatChuaThanhToan() == 4000, "Khoi phuc thanh toan");
    kiemTra(docLai.layViPham().timTheoMa("VP_P2")->layNguoiDuyet() == "TT1", "Khoi phuc nguoi duyet");
    kiemTra(docLai.layThuThuTruong().timTheoMa("TT1")->tinhThuNhap() == 14000000, "Khoi phuc nhan su");
    kiemTra(!docLai.doc("build/khong_ton_tai_he_thong", loi), "Doc thieu tep");
    kiemTra(docLai.layPhieuMuon().laySoLuong() == heThong.layPhieuMuon().laySoLuong(), "Doc loi giu danh sach");
    ghiTep(thuMuc / "Sach.txt", "THUVIEN_2\n0\n");
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Chan phieu dang muon thieu tai lieu");
    kiemTra(docLai.layTaiLieu().laySoLuong() == 3, "Doc loi giu tai lieu");
    heThong.luu(thuMuc.string(), loi);
    ghiTep(thuMuc / "SinhVien.txt", "THUVIEN_2\n0\n");
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Chan phieu dang muon thieu doc gia");
    heThong.luu(thuMuc.string(), loi);
    ghiTep(thuMuc / "NhatKyViPham.txt", "THUVIEN_2\n0\n");
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Chan phieu phat thieu vi pham");
    heThong.luu(thuMuc.string(), loi);
    ghiTep(thuMuc / "ThuThuTruong.txt", "THUVIEN_2\n0\n");
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Chan vi pham thieu nguoi duyet");
    heThong.luu(thuMuc.string(), loi);
    std::ofstream du(thuMuc / "PhieuMuon.txt", std::ios::app);
    du << "DU\n";
    du.close();
    kiemTra(!docLai.doc(thuMuc.string(), loi), "Chan tep du truong");
    heThong.luu(thuMuc.string(), loi);

    QuanLyThuVien sai;
    taoDuLieu(sai);
    sai.layTaiLieu().timTheoMa("S1")->giamSoLuong();
    kiemTra(!sai.kiemTraNhatQuan(loi), "Chan ton kho khong khop phieu");
    kiemTra(!sai.luu(thuMuc.string(), loi), "Khong luu du lieu lech");
    kiemTra(docLai.doc(thuMuc.string(), loi), "Du lieu tren dia con nguyen sau luu bi tu choi");

    std::filesystem::path tepChan = thuMuc / "tep_chan";
    ghiTep(tepChan, "chan");
    kiemTra(!heThong.luu(tepChan.string(), loi), "Luu vao duong dan tep bi tu choi");
    kiemTra(heThong.luu(thuMuc.string(), loi), "Luu lai sau loi");

    std::filesystem::path thuMucLoi = std::filesystem::path("build") / "kiem_thu_khoi_phuc_v2";
    kiemTra(heThong.luu(thuMucLoi.string(), loi), "Tao du lieu kiem tra khoi phuc khi loi ghi");
    std::ifstream tepCu(thuMucLoi / "NhanVienThuThu.txt");
    std::ostringstream noiDungCu;
    noiDungCu << tepCu.rdbuf();
    tepCu.close();
    QuanLyThuVien thayDoi;
    kiemTra(thayDoi.doc(thuMucLoi.string(), loi), "Doc du lieu truoc kiem tra loi ghi");
    thayDoi.layNhanVien().xoa("NV1");
    std::filesystem::remove(thuMucLoi / "PhieuMuon.txt");
    std::filesystem::create_directory(thuMucLoi / "PhieuMuon.txt");
    kiemTra(!thayDoi.luu(thuMucLoi.string(), loi), "Loi thay tep thu tam");
    std::ifstream tepSau(thuMucLoi / "NhanVienThuThu.txt");
    std::ostringstream noiDungSau;
    noiDungSau << tepSau.rdbuf();
    tepSau.close();
    kiemTra(noiDungCu.str() == noiDungSau.str(), "Khoi phuc cac tep da thay khi tep sau bi loi");
    kiemTra(!std::filesystem::exists(thuMucLoi / ".dang_luu"), "Don thu muc tam sau khoi phuc");
    std::filesystem::remove(thuMucLoi / "PhieuMuon.txt");
    kiemTra(heThong.luu(thuMucLoi.string(), loi), "Luu lai sau khi bo tep chan");

    kiemTra(docLai.doc(thuMuc.string(), loi), "Doc thay dong bo ca khi dang muon");
    kiemTra(docLai.layPhieuMuon().traTaiLieu("P6", "01/01/2025",
                                            docLai.layDocGia(), docLai.layTaiLieu(), docLai.layViPham()), "Tra sau khoi phuc");
    kiemTra(docLai.layTaiLieu().xoa("T1"), "Xoa tai lieu khi chi con phieu da tra");
    kiemTra(docLai.layDocGia().xoa("D2"), "Xoa doc gia khi khong con dang muon");
    kiemTra(docLai.kiemTraNhatQuan(loi), "Lich su da tra van hop le khi xoa doi tuong");
    kiemTra(!themDocGia(docLai.layDocGia(), taoGiangVien("D2")), "Khong tai su dung ma cua lich su");
    std::filesystem::path lichSu = std::filesystem::path("build") / "kiem_thu_lich_su_v2";
    kiemTra(docLai.luu(lichSu.string(), loi), "Luu lich su doi tuong da xoa");
    QuanLyThuVien khoiPhuc;
    kiemTra(khoiPhuc.doc(lichSu.string(), loi), "Doc lich su doi tuong da xoa");

    QuanLyThuVien rong;
    std::filesystem::path thuMucRong = std::filesystem::path("build") / "kiem_thu_rong_v2";
    kiemTra(rong.luu(thuMucRong.string(), loi) && khoiPhuc.doc(thuMucRong.string(), loi), "Doc ghi he thong rong");
    kiemTra(khoiPhuc.layPhieuMuon().laySoLuong() == 0 && khoiPhuc.layTaiLieu().laySoLuong() == 0, "Danh sach rong sau doc");
}

//=====ham kiem thu thuat toan=====
static void kiemThuThuatToan(){
    int cacMang[5][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 3, 4, 5, 6},
        {6, 5, 4, 3, 2, 1},
        {0, -2, 1, -2, 0, 4},
        {5, 1, 5, 1, 5, 1}
    };
    for(int k = 0; k < 5; k++){
        for(int loai = 0; loai < 4; loai++){
            int ds[6];
            int tam[6];
            for(int i = 0; i < 6; i++){
                ds[i] = cacMang[k][i];
            }
            switch(loai){
                case 0:
                    bubbleSort(ds, 6);
                    break;
                case 1:
                    selectionSort(ds, 6);
                    break;
                case 2:
                    quickSort(ds, 0, 5);
                    break;
                case 3:
                    mergeSort(ds, 0, 5, tam);
                    break;
            }
            for(int i = 1; i < 6; i++){
                kiemTra(ds[i - 1] <= ds[i], "Thu tu cac thuat toan");
            }
            for(int i = 0; i < 6; i++){
                int demGoc = 0;
                int demMoi = 0;
                for(int j = 0; j < 6; j++){
                    if(cacMang[k][j] == cacMang[k][i]){
                        demGoc++;
                    }
                    if(ds[j] == cacMang[k][i]){
                        demMoi++;
                    }
                }
                kiemTra(demGoc == demMoi, "Sap xep khong mat phan tu");
            }
        }
    }
    int ds[] = {1, 2, 3};
    kiemTra(timKiemNhiPhan(ds, 3, 1) == 0 && timKiemNhiPhan(ds, 3, 3) == 2, "Nhi phan bien dau cuoi");
    kiemTra(timKiemNhiPhan(ds, 3, 0) == -1 && timKiemNhiPhan(ds, 0, 1) == -1, "Nhi phan khong tim thay va rong");
    BangBamMa bang(0);
    kiemTra(bang.them("A", 0) && bang.them("D", 1), "Bam co va cham");
    kiemTra(bang.tim("A") == 0 && bang.tim("D") == 1 && bang.tim("X") == -1, "Tim bam va cham");
    kiemTra(!bang.them("A", 2), "Bam tu choi khoa trung");
    std::ofstream ketQua("build/ket_qua_thuc_nghiem.csv");
    kiemTra(thucNghiem(ketQua), "Thuc nghiem 4 kich thuoc");
    ketQua.close();
    kiemTra(static_cast<bool>(ketQua), "Ghi ket qua thuc nghiem");
}

int main(){
    static_assert(std::is_abstract<DocGia>::value, "DocGia phai truu tuong");
    static_assert(std::has_virtual_destructor<Nguoi>::value, "Nguoi phai co ham huy ao");
    kiemThuOOP();
    QuanLyThuVien heThong;
    taoDuLieu(heThong);
    kiemThuMuonTra(heThong);
    kiemThuTep(heThong);
    thongKeTonKho(heThong);
    thongKeDocGiaMuonNhieuNhat(heThong);
    thongKeTaiLieuMuonNhieuNhat(heThong);
    thongKeTienPhat(heThong);
    kiemThuThuatToan();
    return ketQuaKiemThu();
}
