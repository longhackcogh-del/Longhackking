#include "KiemThu.h"
#include "../PhieuMuon.h"
#include "../QuanLyPhieuMuon.h"
#include "../QuanLyViPham.h"
#include "../QuanLyDocGia.h"
#include "../QuanLyTaiLieu.h"
#include "../SinhVien.h"
#include "../GiangVien.h"
#include "../Sach.h"
#include "../TapChi.h"
#include "../Bao.h"
#include <sstream>
using namespace std;

//=====du lieu kiem thu, khong sua du lieu mau=====
SinhVien taoDocGia(string ma, bool hoatDong = true, int soMuon = 0){
    return SinhVien("N_" + ma, "Nguyen Van An", "01/01/2004", "an@dh.edu", "0901234567",
                   ma, soMuon, hoatDong, "SV_" + ma, "CT1", "CNTT", "Phan mem");
}

Sach taoSach(string ma, int tong = 10, int con = 10){
    return Sach(ma, "Lap trinh", "NXB", 2020, tong, con, 50000, "Tac gia", "Tin hoc", "ISBN", 100);
}

bool themDocGia(QuanLyDocGia& q, DocGia* nguoi){
    if(q.them(nguoi)){
        return true;
    }
    delete nguoi;
    return false;
}

bool themTaiLieu(QuanLyTaiLieu& q, TaiLieu* taiLieu){
    if(q.them(taiLieu)){
        return true;
    }
    delete taiLieu;
    return false;
}

string chupPhieu(const QuanLyPhieuMuon& q){
    ostringstream tep;
    tep << q.laySoLuong() << '\n';
    for(int i = 0; i < q.laySoLuong(); i++){
        q.lay(i)->ghi(tep);
    }
    return tep.str();
}

string chupViPham(const QuanLyViPham& q){
    ostringstream tep;
    tep << q.laySoLuong() << '\n';
    for(int i = 0; i < q.laySoLuong(); i++){
        q.lay(i)->ghi(tep);
    }
    return tep.str();
}

string chupTatCa(const QuanLyPhieuMuon& pm, const QuanLyDocGia& dg,
                      const QuanLyTaiLieu& tl, const QuanLyViPham& vp){
    ostringstream tep;
    tep << chupPhieu(pm) << chupViPham(vp);
    for(int i = 0; i < dg.laySoLuong(); i++){
        dg.layDocGia(i)->ghi(tep);
    }
    for(int i = 0; i < tl.laySoLuong(); i++){
        tl.layTaiLieu(i)->ghi(tep);
    }
    return tep.str();
}

string ghiPhieu(const PhieuMuon& p){
    ostringstream tep;
    p.ghi(tep);
    return tep.str();
}

string ghiViPham(const NhatKyViPham& p){
    ostringstream tep;
    p.ghi(tep);
    return tep.str();
}

//=====kiem tra ngay, nhap xuat va friend=====
void kiemThuPhieu(){
    PhieuMuon p("P", "D", "S", "28/02/2024", "29/02/2024", 2);
    kiemTra(p.hopLe(), "Phieu hop le ngay nhuan");
    kiemTra(p.tinhSoNgayTre("29/02/2024") == 0, "Dung han khong tre");
    kiemTra(p.tinhSoNgayTre("01/03/2024") == 1, "Qua ngay nhuan");
    kiemTra(p.tinhSoNgayTre("27/02/2024") == -1, "Ngay tra truoc ngay muon");
    kiemTra(p.tinhSoNgayTre("31/04/2024") == -1, "Ngay tra khong ton tai");
    kiemTra(!PhieuMuon("P", "D", "S", "29/02/2023", "01/03/2023", 1).hopLe(), "Nam khong nhuan");
    kiemTra(!PhieuMuon("P", "D", "S", "02/01/2024", "01/01/2024", 1).hopLe(), "Han truoc ngay muon");
    kiemTra(!PhieuMuon("P", "D", "S", "01/01/2024", "02/01/2024", 0).hopLe(), "So luong bang khong");
    kiemTra(!PhieuMuon("", "D", "S", "01/01/2024", "02/01/2024", 1).hopLe(), "Ma phieu rong");
    PhieuMuon nhap;
    istringstream duLieu("P\nD\nS\n28/02/2024\n29/02/2024\n2\n");
    kiemTra(nhap.nhap(duLieu) && ghiPhieu(nhap) == ghiPhieu(p), "Nhap phieu qua istream");
    string cu = ghiPhieu(nhap);
    istringstream sai("P\nD\nS\n28/02/2024\n29/02/2024\nabc\n");
    kiemTra(!nhap.nhap(sai) && ghiPhieu(nhap) == cu, "Nhap sai giu phieu cu");
    istringstream thieu("P\n");
    kiemTra(!nhap.nhap(thieu) && ghiPhieu(nhap) == cu, "Nhap thieu giu phieu cu");
    ostringstream xuat;
    xuat << p;
    kiemTra(xuat.str().find("Ma phieu: P") != string::npos
             && xuat.str().find("So luong: 2") != string::npos, "operator<< hien thi noi dung");
    SinhVien dg = taoDocGia("D");
    PhieuMuon quaHan("CU", "D", "S", "01/01/2000", "02/01/2000", 1);
    kiemTra(kiemTraHanMuon(dg, quaHan), "Friend phieu cu qua han thuoc doc gia");
    kiemTra(!kiemTraHanMuon(taoDocGia("KHAC"), quaHan), "Friend sai chu phieu");
    string homNay = ngayHienTai();
    PhieuMuon dungHan("NAY", "D", "S", homNay, homNay, 1);
    kiemTra(!kiemTraHanMuon(dg, dungHan), "Friend dung han hom nay");
    PhieuMuon tuongLai("SAU", "D", "S", homNay, "31/12/9999", 1);
    kiemTra(!kiemTraHanMuon(dg, tuongLai), "Friend chua den han");
    istringstream doc(ghiPhieu(p));
    PhieuMuon docLai;
    kiemTra(docLai.doc(doc) && ghiPhieu(docLai) == ghiPhieu(p), "Doc ghi phieu round trip");
    istringstream phatSai("P\nD\nS\n01/01/2024\n02/01/2024\n1\n02/01/2024\nDa tra\n2000\n");
    kiemTra(!docLai.doc(phatSai) && ghiPhieu(docLai) == ghiPhieu(p), "Tu choi phat qua han khi tra dung han");
}

//=====kiem tra muon tra va tinh phat da hinh=====
void kiemThuNghiepVu(){
    QuanLyDocGia dg;
    QuanLyTaiLieu tl;
    QuanLyPhieuMuon pm;
    QuanLyViPham vp;
    dg.ganQuanLyPhieuMuon(&pm);
    tl.ganQuanLyPhieuMuon(&pm);
    kiemTra(themDocGia(dg, new SinhVien(taoDocGia("D"))), "Them doc gia de muon");
    kiemTra(themDocGia(dg, new SinhVien(taoDocGia("KHOA", false))), "Them tai khoan khoa");
    kiemTra(themTaiLieu(tl, new Sach(taoSach("S"))), "Them sach");
    kiemTra(themTaiLieu(tl, new Sach(taoSach("HET", 0, 0))), "Them tai lieu het kho");
    string cu = chupTatCa(pm, dg, tl, vp);
    kiemTra(!pm.lapPhieu(PhieuMuon("X1", "KHONG_CO", "S", "01/01/2024", "02/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Muon sai ma doc gia khong doi du lieu");
    kiemTra(!pm.lapPhieu(PhieuMuon("X2", "D", "KHONG_CO", "01/01/2024", "02/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Muon sai ma tai lieu khong doi du lieu");
    kiemTra(!pm.lapPhieu(PhieuMuon("X3", "KHOA", "S", "01/01/2024", "02/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Tai khoan khoa khong muon");
    kiemTra(!pm.lapPhieu(PhieuMuon("X4", "D", "S", "01/01/2024", "02/01/2024", 6), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Vuot han muc khong doi du lieu");
    kiemTra(!pm.lapPhieu(PhieuMuon("X5", "D", "HET", "01/01/2024", "02/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Het ton kho khong doi du lieu");
    kiemTra(themTaiLieu(tl, new Sach(taoSach("IT", 1, 1))), "Them kho it hon so muon");
    cu = chupTatCa(pm, dg, tl, vp);
    kiemTra(!pm.lapPhieu(PhieuMuon("X6", "D", "IT", "01/01/2024", "02/01/2024", 2), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Thieu ton kho khong cap nhat mot phan");
    kiemTra(pm.lapPhieu(PhieuMuon("P1", "D", "S", "01/01/2024", "02/01/2024", 2), dg, tl), "Muon thanh cong");
    kiemTra(dg.timTheoMa("D")->laySoDangMuon() == 2 && tl.timTheoMa("S")->laySoLuongCon() == 8, "Cap nhat ca hai so luong");
    cu = chupTatCa(pm, dg, tl, vp);
    kiemTra(!pm.lapPhieu(PhieuMuon("P1", "D", "S", "01/01/2024", "02/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Trung phieu khong tang muon");
    kiemTra(!pm.traTaiLieu("X", "03/01/2024", dg, tl, vp) && chupTatCa(pm, dg, tl, vp) == cu, "Tra sai ma");
    kiemTra(!pm.traTaiLieu("P1", "31/04/2024", dg, tl, vp) && chupTatCa(pm, dg, tl, vp) == cu, "Tra ngay sai");
    kiemTra(!pm.traTaiLieu("P1", "31/12/2023", dg, tl, vp) && chupTatCa(pm, dg, tl, vp) == cu, "Tra truoc ngay muon");
    kiemTra(pm.traTaiLieu("P1", "02/01/2024", dg, tl, vp), "Tra dung han");
    kiemTra(dg.timTheoMa("D")->laySoDangMuon() == 0 && tl.timTheoMa("S")->laySoLuongCon() == 10
             && vp.laySoLuong() == 0, "Tra dung han cap nhat kho khong phat");
    kiemTra(!pm.timTheoMa("P1")->dangMuon() && pm.timTheoMa("P1")->layNgayTra() == "02/01/2024", "Luu trang thai va ngay tra");
    cu = chupTatCa(pm, dg, tl, vp);
    kiemTra(!pm.traTaiLieu("P1", "03/01/2024", dg, tl, vp) && chupTatCa(pm, dg, tl, vp) == cu, "Khong tra hai lan");
    kiemTra(!kiemTraHanMuon(*dg.timTheoMa("D"), *pm.timTheoMa("P1")), "Phieu da tra khong con qua han");
    // Ba doi tuong that, tinh phat qua TaiLieu da hinh.
    kiemTra(themTaiLieu(tl, new TapChi("T", "Tap chi", "NXB", 2024, 5, 5, 50000, 1, 1, "Khoa hoc")), "Them tap chi");
    kiemTra(themTaiLieu(tl, new Bao("B", "Bao", "NXB", 2024, 5, 5, 10000, "01/01/2024", "Ngay")), "Them bao");
    string ma[] = {"S", "T", "B"};
    double mucPhat[] = {2000, 3000, 1000};
    for(int i = 0; i < 3; i++){
        string maPhieu = "TRE" + ma[i];
        kiemTra(pm.lapPhieu(PhieuMuon(maPhieu, "D", ma[i], "01/01/2024", "02/01/2024", 2), dg, tl), "Muon loai tai lieu that");
        kiemTra(pm.traTaiLieu(maPhieu, "04/01/2024", dg, tl, vp), "Tra tre loai tai lieu that");
        const PhieuMuon* p = pm.timTheoMa(maPhieu);
        kiemTra(p != nullptr && p->layTienPhat() == 2 * 2 * mucPhat[i], "Phat dung loai x so ngay x so luong");
        const NhatKyViPham* v = vp.timTheoPhieu(maPhieu);
        kiemTra(v != nullptr && v->laySoNgayTre() == 2 && v->layTienPhat() == 4 * mucPhat[i], "Ghi nhat ky dung tien va ngay");
        kiemTra(!vp.ghiViPham(*p), "Khong ghi trung vi pham");
    }
    kiemTra(vp.tinhTongTienPhatChuaThanhToan() == 24000 && vp.tinhTongTienPhatDaThanhToan() == 0, "Tong tien phat chua thu");
    kiemTra(vp.thanhToanPhat("VP_TRES"), "Thanh toan lan dau");
    string vpCu = chupViPham(vp);
    kiemTra(!vp.thanhToanPhat("VP_TRES") && chupViPham(vp) == vpCu, "Khong thu hai lan");
    kiemTra(vp.tinhTongTienPhatChuaThanhToan() == 16000 && vp.tinhTongTienPhatDaThanhToan() == 8000, "Tong tien sau thanh toan");
    kiemTra(!vp.thanhToanPhat("KHONG_CO"), "Thanh toan sai ma");
    kiemTra(vp.duyet("VP_TRES", "TT1") && !vp.duyet("VP_TRES", "TT2"), "Duyet mot lan");
    kiemTra(vp.timTheoMa("VP_TRES")->layNguoiDuyet() == "TT1", "Giu nguoi duyet dau tien");
    kiemTra(!vp.duyet("VP_TRET", "-") && !vp.duyet("VP_TRET", " "), "Ma nguoi duyet sai");
    kiemTra(vp.demViPham("D") == 3 && vp.demViPham("KHONG_CO") == 0, "Dem vi pham");
    const QuanLyPhieuMuon& pmConst = pm;
    const QuanLyViPham& vpConst = vp;
    kiemTra(pmConst.timTheoMa("P1") != nullptr && pmConst.timTheoMa("X") == nullptr, "Tim phieu const");
    kiemTra(vpConst.timTheoMa("VP_TRES") != nullptr && vpConst.timTheoMa("X") == nullptr, "Tim vi pham const");
    kiemTra(pm.lay(-1) == nullptr && pm.lay(99) == nullptr && vp.lay(-1) == nullptr, "Chi so ngoai pham vi");
    kiemTra(pm.coThamChieuDocGia("D") && pm.coThamChieuTaiLieu("S"), "Tra cuu lien ket");
    kiemTra(pm.demDangMuonDocGia("D") == 0 && pm.demDangMuonTaiLieu("S") == 0
             && pm.demLuotMuonTaiLieu("S") == 4, "Thong ke luong muon tra");
    kiemTra(pm.lapPhieu(PhieuMuon("DAY", "D", "S", "01/01/2024", "02/01/2024", 5), dg, tl), "Muon dung gioi han sinh vien");
    cu = chupTatCa(pm, dg, tl, vp);
    kiemTra(!pm.lapPhieu(PhieuMuon("VUOT", "D", "S", "01/01/2024", "02/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == cu, "Khong vuot han muc cong don");
    kiemTra(pm.traTaiLieu("DAY", "02/01/2024", dg, tl, vp), "Tra sau khi muon du han muc");
    ostringstream hienThi;
    streambuf* coutCu = cout.rdbuf(hienThi.rdbuf());
    int soLan = vp.timTheoDocGia("D");
    vp.lietKeChuaThanhToan();
    vp.hienThi();
    cout.rdbuf(coutCu);
    kiemTra(soLan == 3 && hienThi.str().find("So vi pham chua thanh toan: 2") != string::npos,
             "Tim va liet ke nhat ky chua thanh toan");
    // Tai khoan khoa van duoc tra tai lieu da muon.
    kiemTra(pm.lapPhieu(PhieuMuon("K", "D", "S", "01/01/2024", "02/01/2024", 1), dg, tl), "Muon truoc khi khoa");
    kiemTra(themDocGia(dg, new SinhVien(taoDocGia("D2"))), "Them doc gia thu hai");
    SinhVien* khoa = new SinhVien(taoDocGia("D", false, 1));
    bool daKhoa = dg.sua("D", khoa);
    kiemTra(daKhoa, "Khoa tai khoan dang muon");
    if(!daKhoa){
        delete khoa;
    }
    kiemTra(pm.traTaiLieu("K", "02/01/2024", dg, tl, vp), "Cho tra khi tai khoan khoa");
}

//=====kiem tra doi tuong sai khong bi cap nhat=====
void kiemThuDuLieuSai(){
    NhatKyViPham rong;
    string cu = ghiViPham(rong);
    kiemTra(!rong.duyet("TT") && ghiViPham(rong) == cu, "Khong duyet nhat ky chua hop le");
    kiemTra(!rong.thanhToanPhat(), "Khong thu nhat ky chua hop le");
    NhatKyViPham v("V", "P", "D", 2, 4000);
    istringstream nhap(ghiViPham(v));
    NhatKyViPham doc;
    kiemTra(doc.nhap(nhap) && ghiViPham(doc) == ghiViPham(v), "Nhap xuat nhat ky");
    cu = ghiViPham(doc);
    istringstream sai("V\nP\nD\nQua han\n2\n4000\n2\n-\n");
    kiemTra(!doc.nhap(sai) && ghiViPham(doc) == cu, "Trang thai thanh toan sai giu nhat ky");
    SinhVien dg = taoDocGia("D", true, 1);
    Sach sach = taoSach("S", 10, 9);
    Sach sachSai("S", "Lap trinh", "NXB", 2020, 10, 9, 1000, "Tac gia", "Tin hoc", "ISBN", -1);
    PhieuMuon p("P", "D", "S", "01/01/2024", "02/01/2024", 1);
    cu = ghiPhieu(p);
    kiemTra(!p.traTaiLieu(dg, sachSai, "03/01/2024") && ghiPhieu(p) == cu
             && dg.laySoDangMuon() == 1 && sachSai.laySoLuongCon() == 9, "Tra tai lieu sai giu moi trang thai");
    SinhVien dgSai("N", "An", "31/02/2004", "an@dh.edu", "0901234567", "D", 1, true, "SV", "CT1", "CNTT", "PM");
    PhieuMuon p2("P2", "D", "S", "01/01/2024", "02/01/2024", 1);
    cu = ghiPhieu(p2);
    kiemTra(!p2.traTaiLieu(dgSai, sach, "03/01/2024") && ghiPhieu(p2) == cu
             && dgSai.laySoDangMuon() == 1 && sach.laySoLuongCon() == 9, "Tra doc gia sai giu moi trang thai");
    SinhVien khongMuon = taoDocGia("D");
    kiemTra(!p2.traTaiLieu(khongMuon, sach, "03/01/2024"), "Khong tra qua so dang muon");
    Sach duKho = taoSach("S");
    kiemTra(!p2.traTaiLieu(dg, duKho, "03/01/2024"), "Khong tra vuot tong kho");
}

//=====kiem tra merge sort, liet ke va cac template trong nghiep vu=====
void kiemThuSapXep(){
    QuanLyDocGia dg;
    QuanLyTaiLieu tl;
    QuanLyPhieuMuon pm;
    kiemTra(themTaiLieu(tl, new Sach(taoSach("S", 100, 100))), "Kho cho nhieu phieu");
    pm.sapXepTheoMa();
    kiemTra(pm.laySoLuong() == 0, "Merge sort rong");
    for(int i = 40; i >= 0; i--){
        string so = to_string(i);
        kiemTra(themDocGia(dg, new SinhVien(taoDocGia("D" + so))), "Them nguoi khi tang suc chua");
        kiemTra(pm.lapPhieu(PhieuMuon("P" + so, "D" + so, "S", "01/01/2000", "02/01/2000", 1), dg, tl), "Them phieu dao thu tu");
        if(i == 40){
            pm.sapXepTheoMa();
            kiemTra(pm.lay(0)->layMa() == "P40", "Merge sort mot phan tu");
        }
    }
    pm.sapXepTheoMa();
    for(int i = 1; i < pm.laySoLuong(); i++){
        kiemTra(!( *pm.lay(i) < *pm.lay(i - 1)), "Merge sort tang theo ma chuoi");
    }
    kiemTra(pm.laySoLuong() == 41 && pm.demDangMuonTaiLieu("S") == 41, "Sort khong mat phieu va so luong");
    kiemTra(pm.lapPhieu(PhieuMuon("PHU", "D0", "S", "01/01/2000", "02/01/2000", 1), dg, tl), "Them phieu cung doc gia");
    ostringstream xuat;
    streambuf* cu = cout.rdbuf(xuat.rdbuf());
    int soPhieu = pm.lietKeTheoDocGia("D0");
    int soNguoi = pm.lietKeDocGiaMuonTaiLieu("S", dg);
    pm.lietKeQuaHan(dg);
    pm.hienThi();
    cout.rdbuf(cu);
    kiemTra(soPhieu == 2, "Liet ke phieu theo doc gia");
    kiemTra(soNguoi == 41, "Template tim tuan tu loai trung nguoi");
    kiemTra(xuat.str().find("So phieu qua han: 42") != string::npos, "Liet ke qua han dung friend");
    kiemTra(xuat.str().find("Ma phieu: PHU") != string::npos, "Hien thi dung operator<<");
}

//=====kiem tra doc ghi tep va du lieu hong=====
void kiemThuTep(const filesystem::path& thuMuc){
    QuanLyDocGia dg;
    QuanLyTaiLieu tl;
    QuanLyPhieuMuon pm;
    QuanLyViPham vp;
    themDocGia(dg, new SinhVien(taoDocGia("D")));
    themTaiLieu(tl, new Sach(taoSach("S")));
    kiemTra(pm.lapPhieu(PhieuMuon("P", "D", "S", "01/01/2024", "02/01/2024", 2), dg, tl), "Tao phieu cho tep");
    kiemTra(pm.traTaiLieu("P", "04/01/2024", dg, tl, vp), "Tao vi pham cho tep");
    kiemTra(vp.thanhToanPhat("VP_P") && vp.duyet("VP_P", "TT"), "Tao trang thai da thu da duyet");
    string loi;
    kiemTra(pm.lapPhieu(PhieuMuon("DANG", "D", "S", "01/01/2024", "02/01/2024", 1), dg, tl), "Phieu dang muon trong tep");
    kiemTra(pm.luu(thuMuc.string(), loi) && vp.luu(thuMuc.string(), loi), "Luu hai tep dung ten");
    QuanLyPhieuMuon docPm;
    QuanLyViPham docVp;
    kiemTra(docPm.doc(thuMuc.string(), loi) && chupPhieu(docPm) == chupPhieu(pm), "Doc phieu dung trang thai ngay tra tien phat");
    kiemTra(docVp.doc(thuMuc.string(), loi) && chupViPham(docVp) == chupViPham(vp), "Doc vi pham giu thanh toan va nguoi duyet");
    kiemTra(!docVp.thanhToanPhat("VP_P") && !docVp.duyet("VP_P", "TT2"), "Doc lai khong thu hoac duyet trung");
    ostringstream motPhieu;
    pm.lay(0)->ghi(motPhieu);
    string banGhi = motPhieu.str();
    string tepSai[] = {
        "SAI\n0\n", "THUVIEN_2\n-1\n", "THUVIEN_2\n1000001\n", "THUVIEN_2\n1\nTHIEU\n",
        "THUVIEN_2\n2\n" + banGhi + banGhi,
        "THUVIEN_2\n0\nDU\n",
        "THUVIEN_2\n1\nP\nD\nS\n01/01/2024\n02/01/2024\n1\n-\nSAI\n0\n",
        "THUVIEN_2\n1\nP\nD\nS\n01/01/2024\n02/01/2024\n1\n-\nDang muon\nnan\n"
    };
    string cu = chupPhieu(docPm);
    for(unsigned int i = 0; i < sizeof(tepSai) / sizeof(tepSai[0]); i++){
        kiemTra(ghiTep(thuMuc / "PhieuMuon.txt", tepSai[i]), "Ghi dau vao phieu sai");
        kiemTra(!docPm.doc(thuMuc.string(), loi) && chupPhieu(docPm) == cu && !loi.empty(), "Doc phieu sai giu danh sach");
    }
    string v = ghiViPham(*vp.lay(0));
    string cungPhieu = "MA_KHAC" + v.substr(v.find('\n'));
    string vpSai[] = {
        "SAI\n0\n", "THUVIEN_2\n1\nTHIEU\n", "THUVIEN_2\n2\n" + v + v,
        "THUVIEN_2\n2\n" + v + cungPhieu,
        "THUVIEN_2\n0\nDU\n",
        "THUVIEN_2\n1\nV\nP\nD\nQua han\n0\n4000\n0\n-\n",
        "THUVIEN_2\n1\nV\nP\nD\nQua han\n2\n-1\n0\n-\n",
        "THUVIEN_2\n1\nV\nP\nD\nQua han\n2\n4000\n2\n-\n",
        "THUVIEN_2\n1\nV\nP\nD\nQua han\n2\n4000\n0\n \n"
    };
    cu = chupViPham(docVp);
    for(unsigned int i = 0; i < sizeof(vpSai) / sizeof(vpSai[0]); i++){
        kiemTra(ghiTep(thuMuc / "NhatKyViPham.txt", vpSai[i]), "Ghi dau vao vi pham sai");
        kiemTra(!docVp.doc(thuMuc.string(), loi) && chupViPham(docVp) == cu && !loi.empty(), "Doc vi pham sai giu danh sach");
    }
    kiemTra(!docPm.doc((thuMuc / "KHONG_CO").string(), loi), "Thieu tep phieu");
    kiemTra(!docVp.doc((thuMuc / "KHONG_CO").string(), loi), "Thieu tep vi pham");
    kiemTra(!pm.luu((thuMuc / "KHONG_CO").string(), loi), "Ghi phieu sai duong dan");
    kiemTra(!vp.luu((thuMuc / "KHONG_CO").string(), loi), "Ghi vi pham sai duong dan");
    // Mo phong du lieu lien ket mau thuan: da co vi pham cho ma phieu nay.
    QuanLyPhieuMuon xungDot;
    kiemTra(xungDot.lapPhieu(PhieuMuon("P", "D", "S", "01/01/2024", "02/01/2024", 1), dg, tl), "Tao phieu kiem tra xung dot nhat ky");
    string truocTra = chupTatCa(xungDot, dg, tl, vp);
    kiemTra(!xungDot.traTaiLieu("P", "04/01/2024", dg, tl, vp)
             && chupTatCa(xungDot, dg, tl, vp) == truocTra, "Xung dot nhat ky khong lam tra do dang");
    QuanLyPhieuMuon rongPm;
    QuanLyViPham rongVp;
    kiemTra(rongPm.luu(thuMuc.string(), loi) && rongVp.luu(thuMuc.string(), loi), "Luu danh sach rong");
    kiemTra(docPm.doc(thuMuc.string(), loi) && docPm.laySoLuong() == 0
             && docVp.doc(thuMuc.string(), loi) && docVp.laySoLuong() == 0, "Doc danh sach rong");
}

//=====cac chuc nang va truong hop bien chua duoc bo cu kiem tra=====
string docNoiDungTep(const filesystem::path& ten){
    ifstream tep(ten, ios::binary);
    ostringstream noiDung;
    noiDung << tep.rdbuf();
    return noiDung.str();
}

void kiemThuBoSung(const filesystem::path& thuMuc){
    QuanLyPhieuMuon pm;
    QuanLyViPham vp;
    QuanLyDocGia dg;
    QuanLyTaiLieu tl;
    string truoc = chupTatCa(pm, dg, tl, vp);
    kiemTra(pm.timTheoMa("X") == nullptr && vp.timTheoPhieu("X") == nullptr, "Tim trong danh sach rong");
    kiemTra(!pm.coThamChieuDocGia("X") && !pm.coThamChieuTaiLieu("X"), "Tham chieu trong danh sach rong");
    kiemTra(pm.demDangMuonDocGia("X") == 0 && pm.demDangMuonTaiLieu("X") == 0
             && pm.demLuotMuonTaiLieu("X") == 0, "Dem trong danh sach rong");
    kiemTra(vp.tinhTongTienPhatChuaThanhToan() == 0 && vp.tinhTongTienPhatDaThanhToan() == 0, "Tong tien danh sach rong");
    kiemTra(!pm.traTaiLieu("X", "01/01/2024", dg, tl, vp)
             && chupTatCa(pm, dg, tl, vp) == truoc, "Tra trong danh sach rong");
    kiemTra(!vp.duyet("X", "TT") && !vp.thanhToanPhat("X"), "Duyet va thu trong danh sach rong");
    ostringstream hienThi;
    streambuf* cu = cout.rdbuf(hienThi.rdbuf());
    pm.hienThi();
    vp.hienThi();
    pm.lietKeQuaHan(dg);
    vp.lietKeChuaThanhToan();
    int soPhieu = pm.lietKeTheoDocGia("X");
    int soNguoi = pm.lietKeDocGiaMuonTaiLieu("X", dg);
    int soViPham = vp.timTheoDocGia("X");
    cout.rdbuf(cu);
    kiemTra(soPhieu == 0 && soNguoi == 0 && soViPham == 0, "Liet ke rong tra dung so luong");
    kiemTra(hienThi.str().find("Danh sach rong") != string::npos, "Thong bao danh sach rong");
    PhieuMuon phieu("P", "D", "S", "28/02/2000", "28/02/2000", 1);
    kiemTra(phieu.tinhSoNgayTre("01/03/2000") == 2, "The ky chia het 400 co ngay nhuan");
    PhieuMuon theKy("P", "D", "S", "28/02/1900", "28/02/1900", 1);
    kiemTra(theKy.tinhSoNgayTre("01/03/1900") == 1, "The ky khong chia het 400 khong nhuan");
    PhieuMuon namMoi("P", "D", "S", "31/12/2023", "31/12/2023", 1);
    kiemTra(namMoi.tinhSoNgayTre("01/01/2024") == 1, "Tinh ngay qua nam");
    Sach sai("S", "Sach", "NXB", 2020, 10, 10, 1000, "Tac gia", "Tin hoc", "ISBN", -1);
    kiemTra(phieu.tinhTienPhat(sai, "01/03/2000") == -1, "Tinh phat tu choi tai lieu khong hop le");
    Sach khac = taoSach("KHAC");
    kiemTra(phieu.tinhTienPhat(khac, "01/03/2000") == -1, "Tinh phat tu choi sai ma tai lieu");
    NhatKyViPham nhatKy("V", "P", "D", 2, 4000);
    ostringstream boolChu;
    boolChu << boolalpha;
    nhatKy.ghi(boolChu);
    NhatKyViPham doc;
    istringstream docBool(boolChu.str());
    kiemTra(doc.nhap(docBool) && !doc.layDaThanhToan(), "Ghi trang thai 0 du luong bat boolalpha");
    nhatKy.thanhToanPhat();
    boolChu.str("");
    nhatKy.ghi(boolChu);
    istringstream docDaThu(boolChu.str());
    kiemTra(doc.nhap(docDaThu) && doc.layDaThanhToan(), "Ghi trang thai 1 du luong bat boolalpha");
    // Han muc giang vien phai duoc goi da hinh, khong gan cung 5.
    kiemTra(themDocGia(dg, new GiangVien("NG", "Giang Vien", "01/01/1980", "gv@dh.edu", "0901234567",
                                       "G", 0, true, "GV", "CNTT", "Tien si", 10)), "Them giang vien de muon");
    kiemTra(themTaiLieu(tl, new Sach(taoSach("S", 20, 20))), "Kho cho giang vien");
    kiemTra(pm.lapPhieu(PhieuMuon("G10", "G", "S", "01/01/2024", "10/01/2024", 10), dg, tl), "Giang vien muon du 10");
    truoc = chupTatCa(pm, dg, tl, vp);
    kiemTra(!pm.lapPhieu(PhieuMuon("G11", "G", "S", "01/01/2024", "10/01/2024", 1), dg, tl)
             && chupTatCa(pm, dg, tl, vp) == truoc, "Giang vien khong vuot 10");
    kiemTra(pm.traTaiLieu("G10", "05/01/2024", dg, tl, vp), "Tra truoc han");
    kiemTra(vp.laySoLuong() == 0 && tl.timTheoMa("S")->laySoLuongCon() == 20
             && dg.timTheoMa("G")->laySoDangMuon() == 0, "Tra som khong phat va khoi phuc so luong");
    // Doc rieng chi phan tich ledger; tra van phai kiem tra ma lien quan.
    string loi;
    kiemTra(ghiTep(thuMuc / "PhieuMuon.txt", "THUVIEN_2\n1\n" + ghiPhieu(phieu)), "Tao phieu thieu doc gia lien ket");
    QuanLyPhieuMuon moCoi;
    kiemTra(moCoi.doc(thuMuc.string(), loi), "Doc phieu dung dinh dang de doi chieu khi tich hop");
    truoc = chupTatCa(moCoi, dg, tl, vp);
    kiemTra(!moCoi.traTaiLieu("P", "01/03/2000", dg, tl, vp)
             && chupTatCa(moCoi, dg, tl, vp) == truoc, "Tra phieu thieu doc gia khong doi du lieu");
}

//=====kiem tra luu khong lam hong file da co=====
void kiemThuLuuAnToan(const filesystem::path& thuMuc){
    string loi;
    PhieuMuon p1("P1", "D", "S", "01/01/2024", "02/01/2024", 1);
    PhieuMuon p2("P2", "D", "S", "01/01/2024", "02/01/2024", 1);
    string phieuGoc = "THUVIEN_2\n2\n" + ghiPhieu(p1) + ghiPhieu(p2);
    kiemTra(ghiTep(thuMuc / "PhieuMuon.txt", phieuGoc), "Tao file phieu goc cho kiem thu luu");
    string byteGoc = docNoiDungTep(thuMuc / "PhieuMuon.txt");
    QuanLyPhieuMuon pm;
    kiemTra(pm.doc(thuMuc.string(), loi), "Nap phieu goc");
    *pm.timTheoMa("P2") = PhieuMuon();
    kiemTra(!pm.luu(thuMuc.string(), loi) && docNoiDungTep(thuMuc / "PhieuMuon.txt") == byteGoc,
             "Luu phieu khong hop le giu file cu");
    kiemTra(ghiTep(thuMuc / "PhieuMuon.txt", phieuGoc) && pm.doc(thuMuc.string(), loi), "Khoi tao lai phieu hop le");
    *pm.timTheoMa("P2") = *pm.timTheoMa("P1");
    kiemTra(!pm.luu(thuMuc.string(), loi) && docNoiDungTep(thuMuc / "PhieuMuon.txt") == byteGoc,
             "Luu phieu trung ma giu file cu");
    NhatKyViPham v1("V1", "P1", "D", 1, 2000);
    NhatKyViPham v2("V2", "P2", "D", 1, 2000);
    string vpGoc = "THUVIEN_2\n2\n" + ghiViPham(v1) + ghiViPham(v2);
    kiemTra(ghiTep(thuMuc / "NhatKyViPham.txt", vpGoc), "Tao file vi pham goc");
    byteGoc = docNoiDungTep(thuMuc / "NhatKyViPham.txt");
    QuanLyViPham vp;
    kiemTra(vp.doc(thuMuc.string(), loi), "Nap vi pham goc");
    *vp.timTheoMa("V2") = NhatKyViPham();
    kiemTra(!vp.luu(thuMuc.string(), loi) && docNoiDungTep(thuMuc / "NhatKyViPham.txt") == byteGoc,
             "Luu vi pham sai giu file cu");
    kiemTra(ghiTep(thuMuc / "NhatKyViPham.txt", vpGoc) && vp.doc(thuMuc.string(), loi), "Khoi tao lai vi pham hop le");
    *vp.timTheoMa("V2") = NhatKyViPham("V2", "P1", "D", 1, 2000);
    kiemTra(!vp.luu(thuMuc.string(), loi) && docNoiDungTep(thuMuc / "NhatKyViPham.txt") == byteGoc,
             "Luu vi pham trung su kien giu file cu");
    *vp.timTheoMa("V2") = v1;
    kiemTra(!vp.luu(thuMuc.string(), loi) && docNoiDungTep(thuMuc / "NhatKyViPham.txt") == byteGoc,
             "Luu vi pham trung ma giu file cu");
    // File tam co san phai duoc giu, khong dung lai hoac xoa.
    filesystem::create_directory(thuMuc / "xung_dot_phieu");
    filesystem::path a = thuMuc / "xung_dot_phieu";
    QuanLyPhieuMuon rongPm;
    kiemTra(ghiTep(a / "PhieuMuon.txt", "DU LIEU CU") && ghiTep(a / "PhieuMuon.txt.tam", "FILE CA NHAN"), "Tao xung dot file tam phieu");
    kiemTra(!rongPm.luu(a.string(), loi) && docNoiDungTep(a / "PhieuMuon.txt") == "DU LIEU CU"
             && docNoiDungTep(a / "PhieuMuon.txt.tam") == "FILE CA NHAN", "Khong ghi de file tam co san");
    filesystem::create_directory(thuMuc / "xung_dot_vp");
    a = thuMuc / "xung_dot_vp";
    QuanLyViPham rongVp;
    kiemTra(ghiTep(a / "NhatKyViPham.txt", "DU LIEU CU") && ghiTep(a / "NhatKyViPham.txt.saoLuu", "BAN SAO CA NHAN"), "Tao xung dot ban sao vi pham");
    kiemTra(!rongVp.luu(a.string(), loi) && docNoiDungTep(a / "NhatKyViPham.txt") == "DU LIEU CU"
             && docNoiDungTep(a / "NhatKyViPham.txt.saoLuu") == "BAN SAO CA NHAN", "Khong ghi de ban sao co san");
    filesystem::create_directory(thuMuc / "thanh_cong");
    a = thuMuc / "thanh_cong";
    kiemTra(rongPm.luu(a.string(), loi) && rongVp.luu(a.string(), loi), "Tao moi hai file an toan");
    kiemTra(rongPm.luu(a.string(), loi) && rongVp.luu(a.string(), loi), "Luu lap lai hai file an toan");
    kiemTra(docNoiDungTep(a / "PhieuMuon.txt").find("THUVIEN_2") == 0
             && !filesystem::exists(a / "PhieuMuon.txt.tam")
             && !filesystem::exists(a / "PhieuMuon.txt.saoLuu"), "Hoan tat luu khong de lai file lam viec");
}

int main(int argc, char* argv[]){
    if(argc != 2 || !filesystem::is_directory(argv[1]) || !filesystem::is_empty(argv[1])){
        cerr << "Can thu muc kiem thu rieng, rong\n";
        return 2;
    }
    kiemThuPhieu();
    kiemThuNghiepVu();
    kiemThuDuLieuSai();
    kiemThuSapXep();
    kiemThuTep(argv[1]);
    filesystem::path goc(argv[1]);
    filesystem::create_directory(goc / "bo_sung");
    filesystem::create_directory(goc / "luu_an_toan");
    kiemThuBoSung(goc / "bo_sung");
    kiemThuLuuAnToan(goc / "luu_an_toan");
    cout << "Dat: " << soKiemTra - soLoi << ", khong dat: " << soLoi << '\n';
    return ketQuaKiemThu();
}
