#include "KiemThu.h"
#include "../QuanLyThuVien.h"
#include "../Sach.h"
#include "../TapChi.h"
#include "../Bao.h"
#include "../SinhVien.h"
#include <sstream>
#include <iomanip>
using namespace std;

//=====du lieu nhap cua ca kiem thu=====
static SinhVien taoSinhVien(const string& ma, int soMuon = 0, bool hoatDong = true){
    return SinhVien("N_" + ma, "Nguyen Van An", "01/01/2004", "an@dh.edu", "0901234567",
                    ma, soMuon, hoatDong, "SV_" + ma, "CT1", "CNTT", "Phan mem");
}

static ThuThuTruong taoThuThu(){
    return ThuThuTruong("N_TT", "Tran Thi Thu", "01/01/1980", "thu@dh.edu", "0901234568",
                        "DG_TT", "GV_TT", "CNTT", "Tien si", 10,
                        "TT01", "Sang", "Truong", 5000000, 2, "Tang 1", 12, 1);
}

static bool themSach(QuanLyThuVien& thuVien, const string& ma, int tong = 3, int con = 3){
    Sach* sach = new Sach(ma, "Lap trinh", "NXB DH", 2022, tong, con, 120000,
                          "Nguyen Van A", "Tin hoc", "ISBN01", 100);
    if(!thuVien.themTaiLieu(sach)){
        delete sach;
        return false;
    }
    return true;
}

static bool themSinhVien(QuanLyThuVien& thuVien, const string& ma,
                         int soMuon = 0, bool hoatDong = true, int viTri = 0){
    SinhVien* nguoi = new SinhVien(taoSinhVien(ma, soMuon, hoatDong));
    if(!thuVien.themDocGia(nguoi, viTri)){
        delete nguoi;
        return false;
    }
    return true;
}

//=====ham chup du lieu de kiem tra thao tac that bai=====
static string chupHeThong(QuanLyThuVien& thuVien){
    ostringstream tep;
    tep << thuVien.layTaiLieu().laySoLuong() << '\n';
    for(int i = 0; i < thuVien.layTaiLieu().laySoLuong(); i++){
        thuVien.layTaiLieu().layTaiLieu(i)->ghi(tep);
    }
    tep << thuVien.layDocGia().laySoLuong() << '\n';
    for(int i = 0; i < thuVien.layDocGia().laySoLuong(); i++){
        thuVien.layDocGia().layDocGia(i)->ghi(tep);
    }
    tep << thuVien.layNhanVien().laySoLuong() << '\n';
    for(int i = 0; i < thuVien.layNhanVien().laySoLuong(); i++){
        thuVien.layNhanVien().lay(i)->ghi(tep);
    }
    tep << thuVien.layThuThuTruong().laySoLuong() << '\n';
    for(int i = 0; i < thuVien.layThuThuTruong().laySoLuong(); i++){
        thuVien.layThuThuTruong().lay(i)->ghi(tep);
    }
    tep << thuVien.layPhieuMuon().laySoLuong() << '\n';
    for(int i = 0; i < thuVien.layPhieuMuon().laySoLuong(); i++){
        thuVien.layPhieuMuon().lay(i)->ghi(tep);
    }
    tep << thuVien.layViPham().laySoLuong() << '\n';
    for(int i = 0; i < thuVien.layViPham().laySoLuong(); i++){
        thuVien.layViPham().lay(i)->ghi(tep);
    }
    return tep.str();
}

//=====kiem thu sua vai tro thu thu khi dang muon=====
static void kiemThuSuaVaiTro(){
    QuanLyThuVien thuVien;
    kiemTra(themSach(thuVien, "S01"), "vai tro: them tai lieu");
    kiemTra(thuVien.themThuThuTruong(taoThuThu()), "vai tro: them thu thu va doc gia");
    kiemTra(thuVien.lapPhieu(PhieuMuon("P01", "DG_TT", "S01", "01/01/2026", "03/01/2026", 1)),
             "vai tro: muon truoc khi sua");
    string truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.suaThuThuTruong("TT01", taoThuThu()), "vai tro: tu choi sua sai so dang muon");
    kiemTra(chupHeThong(thuVien) == truoc, "vai tro: sua that bai giu ca sau danh sach");

    istringstream nhap(
        "N_TT\nTran Thi Thu Moi\n01/01/1980\nthu.moi@dh.edu\n0901234568\n"
        "DG_TT\n1\n0\nGV_TT\nCNTT\nTien si\n10\n"
        "TT01\nChieu\nTruong\n5000000\n3\nTang 2\n15\n2\n");
    ThuThuTruong moi;
    kiemTra(moi.nhap(nhap), "vai tro: nhap ho so moi giu cac ma va so dang muon");
    kiemTra(thuVien.suaThuThuTruong("TT01", moi), "vai tro: sua thong tin khi dang muon");
    const DocGia* docGia = thuVien.layDocGia().timTheoMa("DG_TT");
    const ThuThuTruong* thuThu = thuVien.layThuThuTruong().timTheoMa("TT01");
    kiemTra(docGia != nullptr && thuThu != nullptr, "vai tro: ca hai ho so van ton tai");
    kiemTra(docGia->layHoTen() == "Tran Thi Thu Moi" && thuThu->layHoTen() == docGia->layHoTen(),
             "vai tro: dong bo ho ten");
    kiemTra(!docGia->layHoatDong() && !thuThu->layHoatDong(), "vai tro: dong bo trang thai khoa");
    kiemTra(docGia->laySoDangMuon() == 1 && thuThu->laySoDangMuon() == 1, "vai tro: giu so dang muon");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 2, "vai tro: sua khong doi kho");
    kiemTra(thuThu->tinhThuNhap() == 19000000, "vai tro: cap nhat luong va phu cap dung cong thuc");
    ostringstream a;
    ostringstream b;
    docGia->ghi(a);
    thuThu->GiangVien::ghi(b);
    kiemTra(a.str() == b.str(), "vai tro: dong bo toan bo thong tin GiangVien");

    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.lapPhieu(PhieuMuon("P02", "DG_TT", "S01", "01/01/2026", "03/01/2026", 1)),
             "vai tro: tai khoan khoa khong muon them");
    kiemTra(chupHeThong(thuVien) == truoc, "vai tro: muon that bai khong doi du lieu");
    kiemTra(!thuVien.traTaiLieu("P01", "31/02/2026"), "vai tro: tra ngay sai bi tu choi");
    kiemTra(chupHeThong(thuVien) == truoc, "vai tro: tra sai khong doi du lieu");
    kiemTra(thuVien.traTaiLieu("P01", "03/01/2026"), "vai tro: tai khoan khoa van duoc tra");
    kiemTra(docGia->laySoDangMuon() == 0 && thuThu->laySoDangMuon() == 0, "vai tro: dong bo so muon sau tra");
    kiemTra(!docGia->layHoatDong() && !thuThu->layHoatDong(), "vai tro: tra khong tu mo khoa");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 3, "vai tro: tra khoi phuc ton kho");
}

//=====kiem thu phuc hoi khi them ho so lien ket that bai=====
static void kiemThuPhucHoiLienKet(){
    QuanLyThuVien thuVien;
    kiemTra(themSinhVien(thuVien, "DG01"), "phuc hoi: doc gia co san");
    kiemTra(themSach(thuVien, "S01"), "phuc hoi: tai lieu co san");
    kiemTra(thuVien.lapPhieu(PhieuMuon("P01", "DG01", "S01", "01/01/2026", "03/01/2026", 1)),
             "phuc hoi: phieu lien ket co san");
    string truoc = chupHeThong(thuVien);
    // Khac ma doc gia nhung trung maNguoi: them vai tro doc gia se that bai.
    ThuThuTruong trungNguoi("N_DG01", "Tran Thi Thu", "01/01/1980", "thu@dh.edu", "0901234568",
                            "DG_TT", "GV_TT", "CNTT", "Tien si", 10,
                            "TT01", "Sang", "Truong", 5000000, 2, "Tang 1", 12, 1);
    kiemTra(!thuVien.themThuThuTruong(trungNguoi), "phuc hoi: tu choi trung ma nguoi doc gia");
    kiemTra(chupHeThong(thuVien) == truoc, "phuc hoi: khoi phuc ca sau danh sach");
    kiemTra(thuVien.layThuThuTruong().timTheoMa("TT01") == nullptr, "phuc hoi: khong sot ho so thu thu");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT") == nullptr, "phuc hoi: khong sot ho so doc gia moi");
    kiemTra(thuVien.themThuThuTruong(taoThuThu()), "phuc hoi: van them duoc ho so dung sau loi");
    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.themThuThuTruong(taoThuThu()), "phuc hoi: them trung ho so da lien ket");
    kiemTra(chupHeThong(thuVien) == truoc, "phuc hoi: trung ho so khong thay doi du lieu");

    QuanLyThuVien khac;
    GiangVien* gv = new GiangVien(static_cast<const GiangVien&>(trungNguoi));
    bool daThem = khac.themDocGia(gv, 0);
    kiemTra(daThem, "phuc hoi: tao giang vien co thong tin khac thu thu");
    if(!daThem){
        delete gv;
    }
    truoc = chupHeThong(khac);
    kiemTra(!khac.themThuThuTruong(taoThuThu()), "phuc hoi: khong ghi de giang vien khong khop");
    kiemTra(chupHeThong(khac) == truoc, "phuc hoi: giu ho so giang vien khi lien ket sai");
}

//=====kiem thu dinh dang tien khong anh huong luong=====
static void kiemThuXuatTien(){
    Sach sach("S", "Sach", "NXB", 2026, 1, 1, 5000000.25, "Tac gia", "Tin hoc", "ISBN", 100);
    NhatKyViPham viPham("V", "P", "D", 1, 12000000);
    const NhanVienThuThu nhanVien("N", "Ten", "01/01/1980", "a@dh.edu", "0901234567",
                                "NV", "Sang", "Thu thu", 5000000.25, 3.25);
    ios::fmtflags dinhDangBanDau = cout.flags();
    streamsize doChinhXacBanDau = cout.precision();
    ostringstream ghiTruoc;
    sach.ghi(ghiTruoc);
    nhanVien.ghi(ghiTruoc);
    viPham.ghi(ghiTruoc);
    for(int cheDo = 0; cheDo < 3; cheDo++){
        ostringstream tep;
        if(cheDo == 1){
            tep << scientific << setprecision(3);
        }
        else if(cheDo == 2){
            tep << fixed << setprecision(2);
        }
        ios::fmtflags dinhDangCu = tep.flags();
        streamsize doChinhXacCu = tep.precision();
        xuatTien(tep, 12000000.25);
        kiemTra(tep.str() == "12000000", "tien: xuat so tien khong dung ky hieu khoa hoc");
        kiemTra(tep.flags() == dinhDangCu && tep.precision() == doChinhXacCu,
                 "tien: khoi phuc dinh dang luong bat ky");
        PhieuMuon phieu("P", "D", "S", "01/01/2026", "03/01/2026", 1);
        ostringstream xuatPhieu;
        xuatPhieu.flags(dinhDangCu);
        xuatPhieu.precision(doChinhXacCu);
        xuatPhieu << phieu;
        kiemTra(xuatPhieu.str().find("Tien phat: 0\n") != string::npos, "tien: operator xuat phieu dung dinh dang tien");
        kiemTra(xuatPhieu.flags() == dinhDangCu && xuatPhieu.precision() == doChinhXacCu,
                 "tien: operator xuat phieu khong doi dinh dang");

        cout.flags(dinhDangCu);
        cout.precision(doChinhXacCu);
        ostringstream xuat;
        streambuf* luongCu = cout.rdbuf(xuat.rdbuf());
        sach.xuat();
        nhanVien.xuat();
        viPham.xuat();
        cout.rdbuf(luongCu);
        kiemTra(xuat.str().find("Gia tri: 5000000\n") != string::npos, "tien: gia tri tai lieu du chu so");
        kiemTra(xuat.str().find("Luong co ban: 5000000\n") != string::npos, "tien: luong co ban du chu so");
        kiemTra(xuat.str().find("Tien phat: 12000000\n") != string::npos, "tien: tien phat lon du chu so");
        kiemTra(cout.flags() == dinhDangCu && cout.precision() == doChinhXacCu,
                 "tien: xuat tai lieu nhan vien vi pham giu dinh dang cout");
    }
    cout.flags(dinhDangBanDau);
    cout.precision(doChinhXacBanDau);
    ostringstream ghiSau;
    sach.ghi(ghiSau);
    nhanVien.ghi(ghiSau);
    viPham.ghi(ghiSau);
    kiemTra(ghiSau.str() == ghiTruoc.str(), "tien: hien thi khong doi du lieu ghi tep");
    kiemTra(sach.layGiaTri() == 5000000.25 && nhanVien.tinhLuong() == 16250000.8125,
             "tien: hien thi khong doi gia tri va cong thuc");
}

//=====kiem thu ma nguoi va thong tin ca nhan=====
static void kiemThuNhanThan(){
    Nguoi goc("N", "Ten", "01/01/1980", "a@dh.edu", "0901234567");
    Nguoi doi[] = {
        Nguoi("KHAC", "Ten", "01/01/1980", "a@dh.edu", "0901234567"),
        Nguoi("N", "Ten khac", "01/01/1980", "a@dh.edu", "0901234567"),
        Nguoi("N", "Ten", "02/01/1980", "a@dh.edu", "0901234567"),
        Nguoi("N", "Ten", "01/01/1980", "b@dh.edu", "0901234567"),
        Nguoi("N", "Ten", "01/01/1980", "a@dh.edu", "0901234568")
    };
    kiemTra(goc.cungThongTinCaNhan(goc), "nhan than: cung du nam truong");
    for(int i = 0; i < 5; i++){
        kiemTra(!goc.cungThongTinCaNhan(doi[i]), "nhan than: khac tung truong phai bi phat hien");
    }

    QuanLyThuVien thuVien;
    ThuThuTruong tt = taoThuThu();
    NhanVienThuThu nv = static_cast<const NhanVienThuThu&>(tt);
    kiemTra(thuVien.themNhanVien(nv), "nhan su: them nhan vien qua dieu phoi");
    string truoc = chupHeThong(thuVien);
    NhanVienThuThu trungMa("N_KHAC", "Nguoi khac", "01/01/1980", "khac@dh.edu", "0901234567",
                           "TT01", "Sang", "Thu thu", 5000000, 2);
    kiemTra(!thuVien.themNhanVien(trungMa), "nhan su: trung ma nhan vien");
    kiemTra(!thuVien.themThuThuTruong(tt), "nhan su: khong them trung ma giua hai danh sach");
    kiemTra(chupHeThong(thuVien) == truoc, "nhan su: them trung giu du lieu");
    NhanVienThuThu doiMa("N_TT", "Tran Thi Thu", "01/01/1980", "thu@dh.edu", "0901234568",
                         "TT02", "Sang", "Truong", 5000000, 2);
    kiemTra(!thuVien.themNhanVien(doiMa), "nhan su: mot nguoi khong co hai ho so nhan vien");
    kiemTra(!thuVien.suaNhanVien("TT01", doiMa), "nhan su: khong sua ma nhan vien");
    kiemTra(!thuVien.suaNhanVien("TT01", trungMa), "nhan su: khong sua ma nguoi");
    kiemTra(chupHeThong(thuVien) == truoc, "nhan su: sua ma sai khong doi du lieu");

    GiangVien* sai = new GiangVien(static_cast<const GiangVien&>(tt));
    static_cast<Nguoi&>(*sai) = Nguoi("N_TT", "Nguoi khac", "01/01/1980", "thu@dh.edu", "0901234568");
    kiemTra(!thuVien.themDocGia(sai, 0), "nhan su: trung ma nguoi khac nhan than");
    delete sai;
    kiemTra(chupHeThong(thuVien) == truoc, "nhan su: nhan than sai giu du lieu");
    GiangVien* gv = new GiangVien(static_cast<const GiangVien&>(tt));
    bool daThem = thuVien.themDocGia(gv, 0);
    kiemTra(daThem, "nhan su: cung nguoi co vai tro doc gia va nhan vien hop le");
    if(!daThem){
        delete gv;
    }
    kiemTra(thuVien.layDocGia().laySoLuong() == 1 && thuVien.layNhanVien().laySoLuong() == 1,
             "nhan su: moi vai tro chi mot ho so");
    static_cast<Nguoi&>(nv) = Nguoi("N_TT", "Ten moi", "02/01/1980", "moi@dh.edu", "0901234569");
    kiemTra(thuVien.suaNhanVien("TT01", nv), "nhan su: sua nhan than nhan vien");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT")->cungThongTinCaNhan(nv), "nhan su: sua nhan vien dong bo sang doc gia");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT")->laySoDangMuon() == 0, "nhan su: dong bo khong doi so muon");
    GiangVien* sua = new GiangVien(*dynamic_cast<GiangVien*>(thuVien.layDocGia().timTheoMa("DG_TT")));
    static_cast<Nguoi&>(*sua) = Nguoi("N_TT", "Ten tu doc gia", "02/01/1980", "moi@dh.edu", "0901234569");
    bool daSua = thuVien.suaDocGia("DG_TT", sua);
    kiemTra(daSua, "nhan su: sua nhan than tu vai tro doc gia");
    if(!daSua){
        delete sua;
    }
    kiemTra(thuVien.layNhanVien().timTheoMa("TT01")->layHoTen() == "Ten tu doc gia", "nhan su: dong bo nguoc sang nhan vien");
    kiemTra(thuVien.xoaNhanVien("TT01"), "nhan su: xoa ho so nhan vien");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT") != nullptr, "nhan su: xoa nhan vien khong xoa doc gia");
    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.xoaNhanVien("KHONGCO") && !thuVien.suaNhanVien("KHONGCO", nv), "nhan su: sua xoa ma khong co");
    kiemTra(chupHeThong(thuVien) == truoc, "nhan su: sua xoa sai giu du lieu");
}

//=====kiem thu chuyen vai tro khi dang co muon tra va vi pham=====
static void kiemThuChuyenVaiTro(){
    QuanLyThuVien thuVien;
    ThuThuTruong tt = taoThuThu();
    NhanVienThuThu nv = static_cast<const NhanVienThuThu&>(tt);
    kiemTra(thuVien.themNhanVien(nv), "chuyen: tao nhan vien");
    GiangVien* gv = new GiangVien(static_cast<const GiangVien&>(tt));
    bool them = thuVien.themDocGia(gv, 0);
    kiemTra(them, "chuyen: doc gia giang vien co san");
    if(!them){
        delete gv;
    }
    kiemTra(themSach(thuVien, "S01"), "chuyen: kho co san");
    kiemTra(thuVien.lapPhieu(PhieuMuon("P01", "DG_TT", "S01", "01/01/2026", "03/01/2026", 1)), "chuyen: nhan vien dang muon");
    string truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.chuyenThanhThuThuTruong("TT01", tt), "chuyen: sai so dang muon bi tu choi");
    kiemTra(!thuVien.chuyenThanhThuThuTruong("KHONGCO", tt), "chuyen: ma nguon khong ton tai");
    kiemTra(chupHeThong(thuVien) == truoc, "chuyen: sai dau vao giu ca sau danh sach");
    kiemTra(tt.tangSoDangMuon(1), "chuyen: nhap dung so dang muon hien tai");
    ThuThuTruong sai = tt;
    static_cast<Nguoi&>(sai) = Nguoi("N_TT", "Ten sai", "01/01/1980", "thu@dh.edu", "0901234568");
    kiemTra(!thuVien.chuyenThanhThuThuTruong("TT01", sai), "chuyen: khong doi nhan than");
    sai = tt;
    NhanVienThuThu doiMa("N_TT", "Tran Thi Thu", "01/01/1980", "thu@dh.edu", "0901234568",
                         "TT02", "Sang", "Truong", 5000000, 2);
    static_cast<NhanVienThuThu&>(sai) = doiMa;
    kiemTra(!thuVien.chuyenThanhThuThuTruong("TT01", sai), "chuyen: khong doi ma nhan vien");
    sai = tt;
    NhanVienThuThu doiLuong("N_TT", "Tran Thi Thu", "01/01/1980", "thu@dh.edu", "0901234568",
                            "TT01", "Sang", "Truong", 7000000, 2);
    static_cast<NhanVienThuThu&>(sai) = doiLuong;
    kiemTra(!thuVien.chuyenThanhThuThuTruong("TT01", sai), "chuyen: giu thong tin nhan vien khi chuyen");
    kiemTra(chupHeThong(thuVien) == truoc, "chuyen: that bai khong doi du lieu");
    kiemTra(thuVien.chuyenThanhThuThuTruong("TT01", tt), "chuyen: nhan vien thanh truong khi dang muon");
    kiemTra(thuVien.layNhanVien().laySoLuong() == 0 && thuVien.layThuThuTruong().laySoLuong() == 1,
             "chuyen: chi mot ho so nhan su chinh");
    kiemTra(thuVien.layDocGia().laySoLuong() == 1 && thuVien.layDocGia().timTheoMa("DG_TT")->laySoDangMuon() == 1,
             "chuyen: khong nhan doi doc gia hay so muon");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 2
             && thuVien.layPhieuMuon().timTheoMa("P01")->dangMuon(), "chuyen: giu kho va phieu dang muon");
    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.themNhanVien(nv), "chuyen: khong tao ban sao nhan vien cua truong");
    NhanVienThuThu cungMaKhacNguoi("N_KHAC", "Nguoi khac", "01/01/1980", "khac@dh.edu", "0901234567",
                                  "TT01", "Sang", "Thu thu", 5000000, 2);
    kiemTra(!thuVien.themNhanVien(cungMaKhacNguoi), "chuyen: trung ma giua hai danh sach du ma nguoi khac nhau");
    kiemTra(!thuVien.themNhanVien(doiMa), "chuyen: khong lap ho so nhan vien khac ma cho cung thu thu");
    kiemTra(!thuVien.xoaNhanVien("TT01"), "chuyen: khong xoa truong tu danh sach nhan vien");
    kiemTra(chupHeThong(thuVien) == truoc, "chuyen: thao tac sai danh sach khong doi du lieu");
    kiemTra(thuVien.traTaiLieu("P01", "05/01/2026"), "chuyen: tra tre sau khi len truong");
    kiemTra(thuVien.duyetViPham("VP_P01", "TT01"), "chuyen: duyet khi dang la truong");
    kiemTra(thuVien.lapPhieu(PhieuMuon("P02", "DG_TT", "S01", "01/01/2026", "03/01/2026", 1)), "chuyen: muon tiep truoc khi ve nhan vien");
    ostringstream lichSu;
    thuVien.layPhieuMuon().timTheoMa("P01")->ghi(lichSu);
    thuVien.layPhieuMuon().timTheoMa("P02")->ghi(lichSu);
    thuVien.layViPham().timTheoMa("VP_P01")->ghi(lichSu);
    kiemTra(thuVien.chuyenThanhNhanVien("TT01"), "chuyen: truong ve nhan vien khi dang muon");
    kiemTra(thuVien.layNhanVien().laySoLuong() == 1 && thuVien.layThuThuTruong().laySoLuong() == 0,
             "chuyen: ve nhan vien khong giu ban sao truong");
    kiemTra(thuVien.layNhanVien().timTheoMa("TT01")->cungThongTinCaNhan(nv), "chuyen: ve nhan vien giu nhan than");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT")->laySoDangMuon() == 1, "chuyen: giu so muon khi bo vai tro truong");
    ostringstream sau;
    thuVien.layPhieuMuon().timTheoMa("P01")->ghi(sau);
    thuVien.layPhieuMuon().timTheoMa("P02")->ghi(sau);
    thuVien.layViPham().timTheoMa("VP_P01")->ghi(sau);
    kiemTra(sau.str() == lichSu.str(), "chuyen: bao toan phieu va nhat ky da duyet");
    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.chuyenThanhNhanVien("TT01"), "chuyen: khong chuyen ve nhan vien hai lan");
    kiemTra(chupHeThong(thuVien) == truoc, "chuyen: lap thao tac giu du lieu");
    kiemTra(thuVien.traTaiLieu("P02", "05/01/2026"), "chuyen: tra tre sau khi ve nhan vien");
    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.duyetViPham("VP_P02", "TT01"), "chuyen: mat quyen duyet moi khi khong con la truong");
    kiemTra(chupHeThong(thuVien) == truoc, "chuyen: tu choi duyet khong sua nhat ky");
    kiemTra(thuVien.layViPham().timTheoMa("VP_P01")->layNguoiDuyet() == "TT01", "chuyen: lich su duyet cu khong mat");
    kiemTra(tt.giamSoDangMuon(1), "chuyen: ho so chuyen lai khop doc gia da tra");
    kiemTra(thuVien.chuyenThanhThuThuTruong("TT01", tt), "chuyen: len truong lai cung nguoi cung ma");
    kiemTra(thuVien.duyetViPham("VP_P02", "TT01"), "chuyen: duyet moi sau khi duoc gan lai vai tro");
    kiemTra(thuVien.layViPham().timTheoMa("VP_P01")->layNguoiDuyet() == "TT01", "chuyen: gan lai vai tro giu lich su cu");
    kiemTra(thuVien.xoaThuThuTruong("TT01"), "chuyen: xoa ho so nhan su sau chuyen");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT") != nullptr, "chuyen: xoa nhan su giu doc gia");
    truoc = chupHeThong(thuVien);
    kiemTra(!thuVien.themNhanVien(nv) && !thuVien.themThuThuTruong(tt), "chuyen: khong cap lai ma nhan vien da nam trong lich su duyet");
    kiemTra(chupHeThong(thuVien) == truoc, "chuyen: tu choi cap lai ma giu lich su");

    QuanLyThuVien moi;
    kiemTra(moi.themNhanVien(nv), "chuyen moi: tao nhan vien chua la doc gia");
    kiemTra(moi.chuyenThanhThuThuTruong("TT01", tt), "chuyen moi: tao vai tro giang vien tu thong tin da nhap");
    kiemTra(moi.layDocGia().laySoLuong() == 1 && moi.layNhanVien().laySoLuong() == 0, "chuyen moi: khong sot ban sao nhan vien");
    kiemTra(moi.chuyenThanhNhanVien("TT01"), "chuyen moi: chuyen nguoc");
    kiemTra(moi.xoaNhanVien("TT01") && moi.layDocGia().laySoLuong() == 1, "chuyen moi: xoa nhan vien giu vai tro doc gia");

    // Mo phong ho so cu mau thuan de kiem tra khong am tham ghi de khi sua.
    QuanLyThuVien mauThuan;
    kiemTra(mauThuan.themNhanVien(nv), "mau thuan: tao nhan vien goc");
    GiangVien* docGiaSai = new GiangVien(static_cast<const GiangVien&>(tt));
    static_cast<Nguoi&>(*docGiaSai) = Nguoi("N_TT", "Ho so sai", "01/01/1980", "thu@dh.edu", "0901234568");
    bool daChen = mauThuan.layDocGia().them(docGiaSai);
    kiemTra(daChen, "mau thuan: nap ho so cap thap de kiem tra phong ve");
    if(!daChen){
        delete docGiaSai;
    }
    truoc = chupHeThong(mauThuan);
    kiemTra(!mauThuan.suaNhanVien("TT01", nv), "mau thuan: khong sua ghi de nhan than sai");
    kiemTra(!mauThuan.xoaNhanVien("TT01"), "mau thuan: khong xoa am tham ho so dang mau thuan");
    kiemTra(!mauThuan.chuyenThanhThuThuTruong("TT01", tt), "mau thuan: khong chuyen vai tro");
    kiemTra(chupHeThong(mauThuan) == truoc, "mau thuan: tat ca thao tac that bai giu nguyen du lieu");

    QuanLyThuVien sinhVien;
    kiemTra(sinhVien.themNhanVien(nv), "chuyen sai loai: nhan vien co san");
    SinhVien* sv = new SinhVien("N_TT", "Tran Thi Thu", "01/01/1980", "thu@dh.edu", "0901234568",
                               "DG_TT", 0, true, "SV", "Lop", "Khoa", "Nganh");
    bool daThemSv = sinhVien.themDocGia(sv, 0);
    kiemTra(daThemSv, "chuyen sai loai: cung nguoi co vai tro sinh vien hop le");
    if(!daThemSv){
        delete sv;
    }
    truoc = chupHeThong(sinhVien);
    kiemTra(!sinhVien.chuyenThanhThuThuTruong("TT01", tt), "chuyen sai loai: khong doi am tham sinh vien thanh giang vien");
    kiemTra(chupHeThong(sinhVien) == truoc, "chuyen sai loai: bao toan ho so cu");

    QuanLyThuVien thieuLienKet;
    kiemTra(thieuLienKet.layThuThuTruong().them(tt), "thieu lien ket: mo phong ho so cap thap thieu doc gia");
    truoc = chupHeThong(thieuLienKet);
    kiemTra(!thieuLienKet.chuyenThanhNhanVien("TT01"), "thieu lien ket: khong chuyen tu du lieu chua nhat quan");
    kiemTra(chupHeThong(thieuLienKet) == truoc, "thieu lien ket: tu choi giu ho so truong");

    QuanLyThuVien xoaDangMuon;
    kiemTra(xoaDangMuon.themNhanVien(nv), "xoa lien ket: tao nhan vien");
    GiangVien* nguoiMuon = new GiangVien(static_cast<const GiangVien&>(tt));
    bool daThemNguoi = xoaDangMuon.themDocGia(nguoiMuon, 0);
    kiemTra(daThemNguoi, "xoa lien ket: tao doc gia cung nguoi");
    if(!daThemNguoi){
        delete nguoiMuon;
    }
    kiemTra(themSach(xoaDangMuon, "S01"), "xoa lien ket: tao kho");
    kiemTra(xoaDangMuon.lapPhieu(PhieuMuon("P01", "DG_TT", "S01", "01/01/2026", "03/01/2026", 1)), "xoa lien ket: dang co phieu muon");
    kiemTra(xoaDangMuon.xoaNhanVien("TT01"), "xoa lien ket: chi bo vai tro nhan vien");
    kiemTra(xoaDangMuon.layDocGia().timTheoMa("DG_TT")->laySoDangMuon() == 1
             && xoaDangMuon.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 2,
             "xoa lien ket: khong doi doc gia va ton kho");
    kiemTra(xoaDangMuon.layPhieuMuon().timTheoMa("P01")->dangMuon(), "xoa lien ket: giu phieu dang muon");
    kiemTra(xoaDangMuon.traTaiLieu("P01", "05/01/2026"), "xoa lien ket: van tra duoc sau khi xoa nhan vien");
    kiemTra(xoaDangMuon.layViPham().timTheoMa("VP_P01") != nullptr, "xoa lien ket: van ghi dung vi pham");
}

//=====ham kiem thu luong nghiep vu chung=====
int main(){
    QuanLyThuVien thuVien;
    kiemTra(thuVien.layTaiLieu().laySoLuong() == 0, "khoi tao tai lieu rong");
    kiemTra(thuVien.layDocGia().laySoLuong() == 0, "khoi tao doc gia rong");
    kiemTra(!thuVien.traTaiLieu("KhongCo", "03/01/2026"), "tra ma khong ton tai");
    kiemTra(!thuVien.ghiViPham("KhongCo"), "ghi vi pham khong co phieu");
    kiemTra(!thuVien.duyetViPham("VP_X", "KhongCo"), "duyet khong co thu thu");
    kiemTra(!thuVien.themTaiLieu(nullptr), "tu choi tai lieu null");
    kiemTra(!thuVien.themDocGia(nullptr, 0), "tu choi doc gia null");
    kiemTra(!themSach(thuVien, "LechKho", 3, 2), "khong them ton kho thieu phieu");
    kiemTra(!themSinhVien(thuVien, "LechMuon", 1), "khong them so dang muon thieu phieu");
    kiemTra(themSach(thuVien, "S01"), "them sach");
    kiemTra(!themSach(thuVien, "S01"), "tu choi trung tai lieu");
    kiemTra(themSinhVien(thuVien, "DG01"), "them sinh vien");
    kiemTra(!themSinhVien(thuVien, "DG01"), "tu choi trung doc gia");
    kiemTra(!themSinhVien(thuVien, "DG02", 0, true, 3), "chen sai vi tri");
    kiemTra(themSinhVien(thuVien, "DG_KHOA", 0, false, 1), "them tai khoan khoa");

    kiemTra(!thuVien.lapPhieu(PhieuMuon("P_X", "KhongCo", "S01", "01/01/2026", "03/01/2026", 1)), "muon doc gia khong co");
    kiemTra(!thuVien.lapPhieu(PhieuMuon("P_X", "DG01", "KhongCo", "01/01/2026", "03/01/2026", 1)), "muon tai lieu khong co");
    kiemTra(!thuVien.lapPhieu(PhieuMuon("P_X", "DG_KHOA", "S01", "01/01/2026", "03/01/2026", 1)), "khoa khong duoc muon");
    kiemTra(!thuVien.lapPhieu(PhieuMuon("P_X", "DG01", "S01", "30/02/2026", "03/03/2026", 1)), "ngay muon sai");
    kiemTra(!thuVien.lapPhieu(PhieuMuon("P_X", "DG01", "S01", "01/01/2026", "03/01/2026", 6)), "muon vuot han muc");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 3, "loi muon khong doi kho");
    kiemTra(thuVien.layDocGia().timTheoMa("DG01")->laySoDangMuon() == 0, "loi muon khong doi so muon");
    PhieuMuon p1("P01", "DG01", "S01", "01/01/2026", "03/01/2026", 2);
    kiemTra(thuVien.lapPhieu(p1), "lap phieu dung");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 1, "muon giam kho dung");
    kiemTra(thuVien.layDocGia().timTheoMa("DG01")->laySoDangMuon() == 2, "muon tang so muon dung");
    kiemTra(!thuVien.lapPhieu(p1), "khong lap trung phieu");
    kiemTra(!thuVien.lapPhieu(PhieuMuon("P02", "DG01", "S01", "01/01/2026", "03/01/2026", 2)), "khong vuot ton kho");
    kiemTra(!thuVien.layTaiLieu().xoa("S01"), "khong xoa tai lieu dang muon");
    kiemTra(!thuVien.xoaDocGia("DG01"), "khong xoa doc gia dang muon");
    kiemTra(!thuVien.traTaiLieu("P01", "31/02/2026"), "tra ngay sai");
    kiemTra(!thuVien.traTaiLieu("P01", "31/12/2025"), "tra truoc ngay muon");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 1, "loi tra giu kho");
    kiemTra(thuVien.traTaiLieu("P01", "03/01/2026"), "tra dung han");
    kiemTra(thuVien.layPhieuMuon().timTheoMa("P01")->layTienPhat() == 0, "dung han khong phat");
    kiemTra(thuVien.layViPham().laySoLuong() == 0, "dung han khong vi pham");
    kiemTra(!thuVien.traTaiLieu("P01", "04/01/2026"), "khong tra hai lan");
    kiemTra(thuVien.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 3, "tra phuc hoi kho");
    kiemTra(thuVien.layDocGia().timTheoMa("DG01")->laySoDangMuon() == 0, "tra giam so muon");

    kiemTra(thuVien.lapPhieu(PhieuMuon("P02", "DG01", "S01", "01/01/2026", "03/01/2026", 1)), "muon lai");
    kiemTra(thuVien.traTaiLieu("P02", "05/01/2026"), "tra sach tre hai ngay");
    const NhatKyViPham* vp = thuVien.layViPham().timTheoMa("VP_P02");
    kiemTra(vp != nullptr && vp->layTienPhat() == 4000, "tu dong ghi phat sach 4000");
    kiemTra(!thuVien.ghiViPham("P02"), "khong ghi vi pham trung");
    kiemTra(thuVien.layViPham().laySoLuong() == 1, "giu mot su kien vi pham");
    kiemTra(!thuVien.duyetViPham("VP_P02", "KhongCo"), "khong duyet bang ma gia");
    ThuThuTruong tt = taoThuThu();
    kiemTra(thuVien.themThuThuTruong(tt), "them thu thu va vai tro doc gia");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT") != nullptr, "doc gia thu thu co that");
    kiemTra(!thuVien.themThuThuTruong(tt), "trung thu thu khong them");
    kiemTra(thuVien.layDocGia().laySoLuong() == 3, "khong nhan doi vai tro doc gia");
    kiemTra(thuVien.duyetViPham("VP_P02", "TT01"), "thu thu that duyet");
    kiemTra(!thuVien.duyetViPham("VP_P02", "TT01"), "khong duyet hai lan");
    kiemTra(thuVien.layViPham().timTheoMa("VP_P02")->layNguoiDuyet() == "TT01", "luu nguoi duyet");
    kiemTra(thuVien.layViPham().thanhToanPhat("VP_P02"), "thanh toan");
    kiemTra(!thuVien.layViPham().thanhToanPhat("VP_P02"), "khong thanh toan trung");
    kiemTra(thuVien.layViPham().tinhTongTienPhatDaThanhToan() == 4000, "tong da thu");
    kiemTra(thuVien.layViPham().tinhTongTienPhatChuaThanhToan() == 0, "tong chua thu");

    kiemTra(thuVien.lapPhieu(PhieuMuon("P_TT", "DG_TT", "S01", "01/01/2026", "03/01/2026", 1)), "thu thu muon nhu giang vien");
    kiemTra(thuVien.layThuThuTruong().timTheoMa("TT01")->laySoDangMuon() == 1, "dong bo thu thu sau muon");
    kiemTra(!thuVien.xoaDocGia("DG_TT"), "giu vai tro doc gia lien ket");
    GiangVien* gvMoi = new GiangVien(static_cast<const GiangVien&>(tt));
    kiemTra(!thuVien.suaDocGia("DG_TT", gvMoi), "sua ho so lien ket qua menu thu thu");
    delete gvMoi;
    ThuThuTruong ttMoi = *thuVien.layThuThuTruong().timTheoMa("TT01");
    kiemTra(thuVien.suaThuThuTruong("TT01", ttMoi), "sua thu thu bao toan so muon");
    kiemTra(!thuVien.suaThuThuTruong("TT01", tt), "tu choi sua sai so muon");
    kiemTra(thuVien.traTaiLieu("P_TT", "03/01/2026"), "thu thu tra");
    kiemTra(thuVien.layThuThuTruong().timTheoMa("TT01")->laySoDangMuon() == 0, "dong bo thu thu sau tra");
    ostringstream hoSo;
    thuVien.layDocGia().timTheoMa("DG_TT")->ghi(hoSo);
    istringstream dauVao(hoSo.str());
    GiangVien gvDocLai;
    kiemTra(gvDocLai.nhap(dauVao), "vai tro doc gia ghi dung dinh dang giang vien");
    dauVao >> ws;
    kiemTra(dauVao.eof(), "khong ghi them truong nhan vien vao ho so giang vien");
    kiemTra(thuVien.chuyenThanhNhanVien("TT01"), "bo vai tro truong va giu nhan vien");
    kiemTra(thuVien.layDocGia().timTheoMa("DG_TT") != nullptr, "giu ho so doc gia sau bo vai tro");
    kiemTra(thuVien.layViPham().timTheoMa("VP_P02")->layNguoiDuyet() == "TT01", "giu lich su nguoi duyet");
    kiemTra(thuVien.chuyenThanhThuThuTruong("TT01", tt), "gan lai vai tro voi giang vien trung thong tin");

    QuanLyThuVien khac;
    SinhVien* trungVaiTro = new SinhVien(taoSinhVien("DG_TT"));
    kiemTra(khac.themDocGia(trungVaiTro, 0), "tao truong hop trung ma doc gia sinh vien");
    kiemTra(!khac.themThuThuTruong(tt), "khong gan thu thu vao sinh vien trung ma");
    kiemTra(khac.layThuThuTruong().laySoLuong() == 0, "loi lien ket khong them thu thu");
    kiemTra(khac.layDocGia().laySoLuong() == 1, "loi lien ket giu doc gia");
    kiemTra(thuVien.layTaiLieu().xoa("S01"), "xoa tai lieu khi da tra het");
    kiemTra(thuVien.xoaDocGia("DG01"), "xoa doc gia khi da tra het");
    kiemTra(thuVien.layPhieuMuon().timTheoMa("P02") != nullptr, "giu phieu lich su");
    kiemTra(!themSach(thuVien, "S01"), "khong tai su dung ma tai lieu lich su");
    kiemTra(!themSinhVien(thuVien, "DG01"), "khong tai su dung ma doc gia lich su");
    kiemTra(khac.layPhieuMuon().laySoLuong() == 0, "hai he thong khong dung chung danh sach tinh");
    kiemThuSuaVaiTro();
    kiemThuPhucHoiLienKet();
    kiemThuXuatTien();
    kiemThuNhanThan();
    kiemThuChuyenVaiTro();
    return ketQuaKiemThu();
}
