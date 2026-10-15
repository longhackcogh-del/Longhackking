#include "KiemThu.h"
#include "../SinhVien.h"
#include "../GiangVien.h"
#include "../QuanLyDocGia.h"
#include "../QuanLyNhanVien.h"
#include "../QuanLyThuThuTruong.h"
#include "../QuanLyPhieuMuon.h"
#include "../QuanLyTaiLieu.h"
#include "../QuanLyViPham.h"
#include "../Sach.h"
#include <sstream>
#include <type_traits>
#include <limits>

//=====du lieu dung rieng cho kiem thu=====
SinhVien taoSinhVien(std::string ma, int soMuon = 0, bool hoatDong = true){
    return SinhVien("N_" + ma, "Nguyen Van An", "29/02/2004", "an@dh.edu",
                   "0901234567", ma, soMuon, hoatDong, "SV_" + ma, "CT1", "CNTT", "Phan mem");
}

GiangVien taoGiangVien(std::string ma, int soMuon = 0, int soNam = 10){
    return GiangVien("N_" + ma, "Le Giang Vien", "01/01/1980", "gv@dh.edu",
                     "0901234568", ma, soMuon, true, "GV_" + ma, "CNTT", "Tien si", soNam);
}

NhanVienThuThu taoNhanVien(std::string ma, double heSo = 2, double luong = 5000000){
    return NhanVienThuThu("N_" + ma, "Le Nhan Vien", "01/01/1990", "nv@dh.edu",
                         "0901234567", ma, "Sang", "Thu thu", luong, heSo);
}

ThuThuTruong taoTruong(std::string ma, std::string maDocGia = "DG_TT",
                       int soNhanVien = 11, double phuCap = 2){
    return ThuThuTruong("N_" + ma, "Tran Thu Thu", "01/01/1980", "tt@dh.edu",
                       "0901234567", maDocGia, "GV_" + ma, "CNTT", "Tien si", 10,
                       ma, "Sang", "Truong", 5000000, 2, "Tang 1", soNhanVien, phuCap);
}

std::string noiDung(const NhanVienThuThu& nguoi){
    std::ostringstream tep;
    nguoi.ghi(tep);
    return tep.str();
}

std::string noiDungDocGia(const DocGia& nguoi){
    std::ostringstream tep;
    nguoi.ghi(tep);
    return tep.str();
}

static int soDangSong = 0;
class SinhVienDem : public SinhVien{
public:
    SinhVienDem(const SinhVien& nguoi) : Nguoi(nguoi), SinhVien(nguoi){
        soDangSong++;
    }
    ~SinhVienDem() override{
        soDangSong--;
    }
};

//=====kiem tra lop va du lieu nhap=====
void kiemThuLop(){
    kiemTra(std::is_abstract<DocGia>::value, "DocGia truu tuong");
    kiemTra(std::has_virtual_destructor<Nguoi>::value, "Nguoi huy ao");
    SinhVien sv = taoSinhVien("SV", 2);
    GiangVien gv = taoGiangVien("GV", 3);
    DocGia* ds[] = {&sv, &gv};
    kiemTra(ds[0]->layGioiHanMuon() == 5 && ds[1]->layGioiHanMuon() == 10, "Da hinh gioi han");
    kiemTra(sv + gv == 5, "Cong so dang muon");
    kiemTra(!taoSinhVien("X", -1).hopLe(), "So dang muon am");
    kiemTra(!taoSinhVien("X", 6).hopLe(), "Sinh vien vuot gioi han");
    kiemTra(!taoGiangVien("X", 11).hopLe(), "Giang vien vuot gioi han");
    kiemTra(!taoGiangVien("X", 0, -1).hopLe(), "Nam cong tac am");
    kiemTra(taoGiangVien("X", 0, 0).hopLe(), "Nam cong tac bang khong");
    kiemTra(!taoSinhVien("X", 0, false).kiemTraDieuKienMuon(), "Tai khoan khoa");
    kiemTra(sv.kiemTraDieuKienMuon(3) && !sv.kiemTraDieuKienMuon(4), "Bien han muc");
    kiemTra(!sv.tangSoDangMuon(0) && !sv.giamSoDangMuon(-1), "So luong giao dich sai");
    kiemTra(sv.tangSoDangMuon(3) && !sv.tangSoDangMuon(1), "Tang den gioi han");
    kiemTra(!sv.giamSoDangMuon(6) && sv.giamSoDangMuon(5), "Giam so muon");
    kiemTra(ngayHopLe("29/02/2000") && !ngayHopLe("29/02/1900"), "Nam nhuan");
    kiemTra(!ngayHopLe("31/04/2024") && !ngayHopLe("1/1/2024"), "Dinh dang ngay");
    kiemTra(!chuoiHopLe("   "), "Chuoi rong");
    Nguoi sai("N", "Ten", "01/01/2000", "sai", "abc");
    kiemTra(!sai.hopLe(), "Email dien thoai sai");
    int so = 7;
    std::istringstream saiSo("12abc\n");
    kiemTra(!nhapSo(saiSo, "", so) && so == 7, "So lan chu giu gia tri");
    std::istringstream quaLon("999999999999999999999\n");
    kiemTra(!nhapSo(quaLon, "", so), "So vuot mien int");
    double thuc = 0;
    std::istringstream nan("nan\n");
    kiemTra(!nhapSo(nan, "", thuc), "Tu choi NaN");
    std::istringstream nhapSv(noiDungDocGia(sv));
    SinhVien docSv;
    kiemTra(docSv.nhap(nhapSv) && noiDungDocGia(docSv) == noiDungDocGia(sv), "Nhap xuat sinh vien");
    std::istringstream nhapGv(noiDungDocGia(gv));
    GiangVien docGv;
    kiemTra(docGv.nhap(nhapGv) && noiDungDocGia(docGv) == noiDungDocGia(gv), "Nhap xuat giang vien");
    std::string cu = noiDungDocGia(docSv);
    std::istringstream nhapSai("\n");
    kiemTra(!docSv.nhap(nhapSai) && noiDungDocGia(docSv) == cu, "Nhap sai giu sinh vien");
    std::istringstream eof("");
    kiemTra(!docGv.nhap(eof), "Nhap EOF");
    NhanVienThuThu nv = taoNhanVien("NV");
    kiemTra(nv.hopLe() && nv.tinhLuong() == 10000000, "Tinh luong");
    kiemTra(!taoNhanVien("NV", 0).hopLe() && !taoNhanVien("NV", -1).hopLe(), "He so luong sai");
    kiemTra(!taoNhanVien("NV", 1, 0).hopLe() && !taoNhanVien("NV", 1, -1).hopLe(), "Luong co ban sai");
    kiemTra(!taoNhanVien("NV", std::numeric_limits<double>::infinity()).hopLe(), "Luong khong huu han");
    NhanVienThuThu docNv;
    std::istringstream nhapNv(noiDung(nv));
    kiemTra(docNv.nhap(nhapNv) && noiDung(docNv) == noiDung(nv), "Nhap xuat nhan vien");
    ThuThuTruong tt = taoTruong("TT");
    kiemTra(tt.hopLe() && tt.tinhThuNhap() == 14000000, "Thu nhap truong");
    kiemTra(!taoTruong("TT", "DG", -1).hopLe(), "So nhan vien am");
    kiemTra(!taoTruong("TT", "DG", 0, -1).hopLe(), "Phu cap am");
    Nguoi* nhanhGv = static_cast<GiangVien*>(&tt);
    Nguoi* nhanhNv = static_cast<NhanVienThuThu*>(&tt);
    kiemTra(nhanhGv == nhanhNv, "Chung mot Nguoi qua ke thua ao");
    ThuThuTruong docTt;
    std::istringstream nhapTt(noiDung(tt));
    kiemTra(docTt.nhap(nhapTt) && noiDung(docTt) == noiDung(tt), "Nhap du hai nhanh truong");
    cu = noiDung(docTt);
    std::istringstream thieu("N\nTen\n01/01/1980\n");
    kiemTra(!docTt.nhap(thieu) && noiDung(docTt) == cu, "Nhap thieu giu truong");
    std::ostringstream xuat;
    std::streambuf* coutCu = std::cout.rdbuf(xuat.rdbuf());
    ds[0]->xuat();
    ds[1]->xuat();
    tt.xuat();
    std::cout.rdbuf(coutCu);
    kiemTra(xuat.str().find("Nguyen Van An") != std::string::npos
             && xuat.str().find("Le Giang Vien") != std::string::npos, "Xuat da hinh");
}

//=====kiem tra quan ly doc gia=====
void kiemThuDocGia(const std::filesystem::path& thuMuc){
    QuanLyDocGia q;
    kiemTra(q.layDocGia(-1) == nullptr && !q.xoa("X"), "Danh sach rong");
    q.sapXepTheoSoMuon();
    kiemTra(!q.them(nullptr), "Khong them con tro rong");
    kiemTra(q.them(new SinhVien(taoSinhVien("D1", 2))), "Them sinh vien");
    kiemTra(q.chen(0, new GiangVien(taoGiangVien("D2", 1))), "Chen giang vien dau");
    kiemTra(q.chen(2, new SinhVien(taoSinhVien("D3"))), "Chen cuoi");
    SinhVien* trung = new SinhVien(taoSinhVien("D1"));
    kiemTra(!q.them(trung), "Tu choi trung ma");
    delete trung;
    SinhVien* chenSai = new SinhVien(taoSinhVien("D4"));
    kiemTra(!q.chen(-1, chenSai) && !q.chen(4, chenSai), "Vi tri chen sai");
    delete chenSai;
    kiemTra(q.timBangBam("D1") == q.timTheoMa("D1") && q.timBangBam("X") == nullptr, "Tim ma va bang bam");
    kiemTra(q.timTheoTen("Nguyen Van") == 2 && q.timTheoTen("Khong co") == 0, "Tim ten");
    kiemTra(!q.xoa("D1"), "Chan xoa doc gia dang muon");
    SinhVien* suaSai = new SinhVien(taoSinhVien("D1"));
    kiemTra(!q.sua("D1", suaSai) && q.timTheoMa("D1")->laySoDangMuon() == 2, "Sua khong doi so muon");
    delete suaSai;
    kiemTra(q.sua("D1", new SinhVien(taoSinhVien("D1", 2, false))), "Sua trang thai tai khoan");
    q.sapXepTheoSoMuon();
    kiemTra(q.layDocGia(0)->layMa() == "D3" && q.layDocGia(2)->layMa() == "D1", "Bubble sort so muon");
    std::string loi;
    kiemTra(q.luu(thuMuc.string(), loi), "Luu hai loai doc gia");
    QuanLyDocGia doc;
    bool daDoc = doc.doc(thuMuc.string(), loi);
    kiemTra(daDoc && doc.laySoLuong() == 3, "Doc hai loai doc gia");
    kiemTra(doc.timTheoMa("D2") != nullptr && doc.timTheoMa("D2")->layLoai() == "GiangVien", "Khoi phuc dung loai");
    kiemTra(!doc.doc(thuMuc.string(), loi) && doc.laySoLuong() == 3, "Chan doc de khi dang muon");
    kiemTra(q.xoa("D3") && !q.xoa("D3"), "Xoa doc gia khong muon");
    QuanLyDocGia giu;
    giu.them(new SinhVien(taoSinhVien("GIU")));
    kiemTra(ghiTep(thuMuc / "SinhVien.txt", "THUVIEN_2\n1\nTHIEU\n"), "Ghi tep hong kiem thu");
    kiemTra(!giu.doc(thuMuc.string(), loi) && giu.timTheoMa("GIU") != nullptr, "Doc hong giu danh sach cu");
    kiemTra(!giu.doc((thuMuc / "khong_co").string(), loi), "Doc thieu tep");
    kiemTra(!giu.luu((thuMuc / "khong_co").string(), loi), "Ghi duong dan sai");
    QuanLyDocGia trungTep;
    SinhVien a = taoSinhVien("TRUNG");
    kiemTra(ghiTep(thuMuc / "SinhVien.txt", "THUVIEN_2\n2\n" + noiDungDocGia(a) + noiDungDocGia(a)), "Tep trung ma");
    kiemTra(ghiTep(thuMuc / "GiangVien.txt", "THUVIEN_2\n0\n"), "Tep giang vien rong");
    kiemTra(!trungTep.doc(thuMuc.string(), loi) && trungTep.laySoLuong() == 0, "Tu choi trung ma trong tep");
    {
        QuanLyDocGia boNho;
        for(int i = 0; i < 40; i++){
            SinhVienDem* nguoi = new SinhVienDem(taoSinhVien("B" + std::to_string(i)));
            bool daThem = boNho.them(nguoi);
            kiemTra(daThem, "Them khi tang suc chua");
            if(!daThem){
                delete nguoi;
            }
        }
        kiemTra(soDangSong == 40, "So doi tuong so huu");
        kiemTra(boNho.xoa("B0") && soDangSong == 39, "Xoa goi huy dan xuat");
        SinhVienDem* thay = new SinhVienDem(taoSinhVien("B1"));
        bool daSua = boNho.sua("B1", thay);
        kiemTra(daSua && soDangSong == 39, "Sua huy doi tuong cu");
        if(!daSua){
            delete thay;
        }
    }
    kiemTra(soDangSong == 0, "Huy danh sach giai phong doi tuong");
}

//=====kiem tra quan ly nhan su=====
void kiemThuNhanSu(const std::filesystem::path& thuMuc){
    std::string loi;
    QuanLyNhanVien nv;
    kiemTra(nv.them(taoNhanVien("NV1", 3)) && nv.them(taoNhanVien("NV2", 1)), "Them nhan vien");
    kiemTra(!nv.them(taoNhanVien("NV1")), "Nhan vien trung ma");
    kiemTra(nv.timTheoCa("Sang") == 2 && nv.timTheoCa("Dem") == 0, "Tim ca lam");
    kiemTra(nv.sua("NV1", taoNhanVien("NV1", 4)), "Sua nhan vien");
    kiemTra(!nv.sua("NV1", taoNhanVien("KHAC")), "Bao toan ma nhan vien");
    nv.sapXepTheoHeSoLuong();
    kiemTra(nv.lay(0)->layMa() == "NV2" && nv.timTheoMa("NV1")->tinhLuong() == 20000000, "Sap xep he so va luong");
    kiemTra(nv.luu(thuMuc.string(), loi), "Luu nhan vien");
    QuanLyNhanVien doc;
    kiemTra(doc.doc(thuMuc.string(), loi) && doc.laySoLuong() == 2, "Doc nhan vien");
    kiemTra(ghiTep(thuMuc / "NhanVienThuThu.txt", "SAI\n0\n"), "Ghi dau tep sai");
    kiemTra(!doc.doc(thuMuc.string(), loi) && doc.laySoLuong() == 2, "Doc nhan vien loi giu du lieu");
    kiemTra(nv.xoa("NV2") && !nv.xoa("X"), "Xoa nhan vien");
    QuanLyThuThuTruong tt;
    ThuThuTruong dangMuon = taoTruong("TT1");
    kiemTra(dangMuon.tangSoDangMuon(1), "Tao trang thai truong dang muon");
    kiemTra(tt.them(dangMuon), "Them truong co so muon hop le");
    kiemTra(tt.them(taoTruong("TT2", "DG_TT2", 10, 1)), "Them truong thu hai");
    kiemTra(!tt.them(taoTruong("TT2")), "Truong trung ma");
    ThuThuTruong doiTrangThai = taoTruong("TT2", "DG_TT2", 10, 1);
    doiTrangThai.tangSoDangMuon(1);
    kiemTra(!tt.sua("TT2", doiTrangThai), "Khong tang so muon qua sua thong tin");
    kiemTra(!tt.sua("TT2", taoTruong("TT2", "DG_DOI", 10, 1)), "Bao toan ma doc gia khi khong muon");
    kiemTra(!tt.sua("TT2", taoTruong("MA_DOI", "DG_TT2", 10, 1)), "Bao toan ma nhan vien truong");
    kiemTra(tt.timTheoSoNhanVien(10) == 1, "Truong quan ly hon 10 nguoi");
    ThuThuTruong sua = taoTruong("TT1");
    kiemTra(!tt.sua("TT1", sua), "Khong sua so dang muon");
    sua.tangSoDangMuon(1);
    kiemTra(tt.sua("TT1", sua), "Sua truong giu trang thai muon");
    ThuThuTruong doiMa = taoTruong("TT1", "DG_KHAC");
    doiMa.tangSoDangMuon(1);
    kiemTra(!tt.sua("TT1", doiMa), "Khong doi ma doc gia cua truong");
    if(tt.timTheoMa("TT1") != nullptr){
        kiemTra(tt.timTheoMa("TT1")->DocGia::layMa() == "DG_TT"
                 && tt.timTheoMa("TT1")->laySoDangMuon() == 1, "Sua that bai giu trang thai truong");
    }
    else{
        kiemTra(false, "Sua that bai giu trang thai truong");
    }
    tt.sapXepTheoPhuCap();
    kiemTra(tt.lay(0) != nullptr && tt.lay(0)->layMa() == "TT2", "Sap xep phu cap");
    kiemTra(tt.luu(thuMuc.string(), loi), "Luu truong");
    QuanLyThuThuTruong docTt;
    kiemTra(docTt.doc(thuMuc.string(), loi) && docTt.laySoLuong() == 2, "Doc lai truong dang muon");
    const ThuThuTruong* docLai = docTt.timTheoMa("TT1");
    kiemTra(docLai != nullptr && docLai->laySoDangMuon() == 1, "Bao toan so muon qua tep");
    kiemTra(ghiTep(thuMuc / "ThuThuTruong.txt", "THUVIEN_2\n1\nTHIEU\n"), "Tep truong thieu du lieu");
    int soCu = docTt.laySoLuong();
    kiemTra(!docTt.doc(thuMuc.string(), loi) && docTt.laySoLuong() == soCu, "Doc truong loi giu danh sach");
    kiemTra(tt.xoa("TT2") && !tt.xoa("KHONG_CO"), "Xoa truong khong muon");
}

//=====kiem tra lien ket muon tra va vi pham that=====
void kiemThuTichHop(){
    QuanLyDocGia dg;
    QuanLyTaiLieu tl;
    QuanLyPhieuMuon pm;
    QuanLyViPham vp;
    dg.ganQuanLyPhieuMuon(&pm);
    tl.ganQuanLyPhieuMuon(&pm);
    kiemTra(dg.them(new SinhVien(taoSinhVien("D1"))), "Tich hop them doc gia");
    kiemTra(tl.them(new Sach("S1", "Lap trinh", "NXB", 2020, 3, 3, 50000,
                           "Tac gia", "Tin hoc", "ISBN1", 100)), "Tich hop them sach");
    PhieuMuon phieu("P1", "D1", "S1", "01/01/2024", "02/01/2024", 1);
    kiemTra(pm.lapPhieu(phieu, dg, tl), "Lap phieu that");
    kiemTra(dg.timTheoMa("D1")->laySoDangMuon() == 1 && !dg.xoa("D1"), "So muon va chan xoa");
    SinhVien* suaSai = new SinhVien(taoSinhVien("D1"));
    kiemTra(!dg.sua("D1", suaSai), "Khong sua lech so phieu");
    delete suaSai;
    kiemTra(dg.sua("D1", new SinhVien(taoSinhVien("D1", 1))), "Sua giu lien ket phieu");
    kiemTra(pm.traTaiLieu("P1", "04/01/2024", dg, tl, vp), "Tra tre va ghi vi pham");
    kiemTra(dg.timTheoMa("D1")->laySoDangMuon() == 0 && vp.laySoLuong() == 1, "Cap nhat so muon khi tra");
    ThuThuTruong tt = taoTruong("TT");
    tt.xemNhatKyViPham(vp);
    kiemTra(tt.duyetViPham(vp, "VP_P1"), "Duyet vi pham that");
    kiemTra(vp.timTheoMa("VP_P1") != nullptr
             && vp.timTheoMa("VP_P1")->layNguoiDuyet() == "TT", "Luu ma nguoi duyet");
    kiemTra(!tt.duyetViPham(vp, "KHONG_CO"), "Duyet ma khong ton tai");
    kiemTra(!pm.traTaiLieu("P1", "04/01/2024", dg, tl, vp), "Khong tra hai lan");
}

int main(int argc, char* argv[]){
    if(argc != 2 || !std::filesystem::is_directory(argv[1]) || !std::filesystem::is_empty(argv[1])){
        std::cerr << "Can thu muc kiem thu rieng, rong va da ton tai\n";
        return 2;
    }
    std::filesystem::path goc(argv[1]);
    std::filesystem::create_directory(goc / "docgia");
    std::filesystem::create_directory(goc / "nhansu");
    kiemThuLop();
    kiemThuDocGia(goc / "docgia");
    kiemThuNhanSu(goc / "nhansu");
    kiemThuTichHop();
    std::cout << "Dat: " << soKiemTra - soLoi << ", khong dat: " << soLoi << '\n';
    return ketQuaKiemThu();
}
