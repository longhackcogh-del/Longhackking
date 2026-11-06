#include "KiemThu.h"
#include "../QuanLyThuVien.h"
#include "../TepHeThong.h"
#include <iostream>
#include <string>
#include <sstream>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif
using namespace std;
namespace fs = filesystem;

static string docChu(const fs::path& tep){
    ifstream doc(tep, ios::binary);
    ostringstream chu;
    chu << doc.rdbuf();
    return chu.str();
}

static string docCacDong(const fs::path& tep){
    istringstream doc(docChu(tep));
    string ketQua;
    string dong;
    while(getline(doc, dong)){
        if(!dong.empty() && dong.back() == '\r'){
            dong.pop_back();
        }
        ketQua += dong + '\n';
    }
    return ketQua;
}

static void chepBo(const fs::path& nguon, const fs::path& dich){
    fs::create_directory(dich);
    for(int i = 0; i < 9; i++){
        fs::copy_file(nguon / tenTepThuVien[i], dich / tenTepThuVien[i]);
    }
}

// Chup ca sau danh sach, khong chi so luong.
static string chup(const QuanLyThuVien& tv){
    ostringstream s;
    s << tv.layTaiLieu().laySoLuong() << '\n';
    for(int i = 0; i < tv.layTaiLieu().laySoLuong(); i++){
        tv.layTaiLieu().layTaiLieu(i)->ghi(s);
    }
    s << tv.layDocGia().laySoLuong() << '\n';
    for(int i = 0; i < tv.layDocGia().laySoLuong(); i++){
        tv.layDocGia().layDocGia(i)->ghi(s);
    }
    s << tv.layNhanVien().laySoLuong() << '\n';
    for(int i = 0; i < tv.layNhanVien().laySoLuong(); i++){
        tv.layNhanVien().lay(i)->ghi(s);
    }
    s << tv.layThuThuTruong().laySoLuong() << '\n';
    for(int i = 0; i < tv.layThuThuTruong().laySoLuong(); i++){
        tv.layThuThuTruong().lay(i)->ghi(s);
    }
    s << tv.layPhieuMuon().laySoLuong() << '\n';
    for(int i = 0; i < tv.layPhieuMuon().laySoLuong(); i++){
        tv.layPhieuMuon().lay(i)->ghi(s);
    }
    s << tv.layViPham().laySoLuong() << '\n';
    for(int i = 0; i < tv.layViPham().laySoLuong(); i++){
        tv.layViPham().lay(i)->ghi(s);
    }
    return s.str();
}

// Sua dung mot dong trong ban sao kiem thu, khong sua mau goc.
static void suaDong(const fs::path& tep, int viTri, const string& giaTri){
    istringstream doc(docChu(tep));
    ostringstream moi;
    string dong;
    int i = 0;
    while(getline(doc, dong)){
        if(i == viTri){
            dong = giaTri;
        }
        moi << dong << '\n';
        i++;
    }
    kiemTra(ghiTep(tep, moi.str()), "Tao du lieu loi trong thu muc kiem thu");
}

int main(int argc, char* argv[]){
    if(argc != 3 || !fs::is_directory(argv[1]) || !fs::is_empty(argv[1])){
        cerr << "Can thu muc kiem thu rong va duong dan mau\n";
        return 2;
    }
    fs::path goc(argv[1]);
    fs::path mau(argv[2]);
    QuanLyThuVien tv;
    string loi;
    kiemTra(tv.docToanBo(mau.string(), loi), "Doc du chin tep mau");
    kiemTra(tv.kiemTraNhatQuan(loi), "Mau nhat quan");
    kiemTra(tv.layTaiLieu().laySoLuong() == 3, "Dung ba loai tai lieu");
    kiemTra(tv.layDocGia().laySoLuong() == 3, "Sinh vien va hai giang vien");
    kiemTra(tv.layViPham().tinhTongTienPhatDaThanhToan() == 6000, "Giu so tien da thu");
    kiemTra(tv.layViPham().tinhTongTienPhatChuaThanhToan() == 3000, "Giu so tien chua thu");
    string banDau = chup(tv);

    fs::path luu = goc / "luu moi co khoang trang";
    fs::create_directory(luu);
    kiemTra(tv.luuToanBo(luu.string(), loi), "Luu du chin tep");
    kiemTra(!fs::exists(luu / ".giao-dich-thuvien"), "Ket thuc giao dich thanh cong");
    for(int i = 0; i < 9; i++){
        kiemTra(docCacDong(luu / tenTepThuVien[i]) == docCacDong(mau / tenTepThuVien[i]),
                 string("Round trip tung truong: ") + tenTepThuVien[i]);
    }
    kiemTra(tv.luuToanBo(luu.string(), loi), "Luu de bo cu co ban sao");
    kiemTra(fs::exists(luu / ".sao-luu-thuvien-2/cu/Sach.txt"), "Giu tep cu sau luu");
    QuanLyThuVien docLai;
    kiemTra(docLai.docToanBo(luu.string(), loi) && chup(docLai) == banDau,
             "Doc lai khoi phuc ca sau danh sach");
    kiemTra(docLai.traTaiLieu("P01", "05/01/2026"), "Tra sau khi doc lai");
    kiemTra(docLai.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 3, "Kho sau tra");
    kiemTra(docLai.layDocGia().timTheoMa("DG_SV01")->laySoDangMuon() == 0, "So muon sau tra");
    kiemTra(!docLai.traTaiLieu("P01", "05/01/2026"), "Khong tra hai lan sau doc");
    kiemTra(docLai.chuyenThanhNhanVien("NV_TT01"), "Chuyen vai tro sau doc");
    kiemTra(!docLai.duyetViPham("VP_P03", "NV_TT01"), "Nguoi da chuyen vai tro khong duyet moi");
    kiemTra(docLai.layViPham().timTheoMa("VP_P02")->layNguoiDuyet() == "NV_TT01", "Giu lich su duyet");
    kiemTra(docLai.kiemTraNhatQuan(loi), "Lich su duyet khong can vai tro truong hien tai");
    kiemTra(docLai.xoaNhanVien("NV_TT01"), "Xoa nhan su co lich su duyet");
    kiemTra(docLai.xoaDocGia("DG_TT01"), "Xoa doc gia da tra");
    kiemTra(docLai.layTaiLieu().xoa("B01"), "Xoa tai lieu da tra");
    kiemTra(docLai.luuToanBo(luu.string(), loi), "Luu lich su co ho so da xoa");
    QuanLyThuVien lichSu;
    kiemTra(lichSu.docToanBo(luu.string(), loi), "Doc lai lich su thieu ho so da xoa");
    kiemTra(lichSu.layDocGia().timTheoMa("DG_TT01") == nullptr
             && lichSu.layTaiLieu().timTheoMa("B01") == nullptr, "Khong tao lai ho so da xoa");
    kiemTra(lichSu.layViPham().timTheoMa("VP_P02")->layNguoiDuyet() == "NV_TT01", "Khong gan lai nguoi duyet");

    // Moi ca sai bat dau tu bo mau rieng, doi chieu ca he thong truoc/sau.
    const char* tepSai[] = {"Sach.txt", "SinhVien.txt", "NhanVienThuThu.txt", "NhanVienThuThu.txt",
        "ThuThuTruong.txt", "PhieuMuon.txt", "PhieuMuon.txt", "PhieuMuon.txt",
        "NhatKyViPham.txt", "NhatKyViPham.txt", "NhatKyViPham.txt", "Sach.txt",
        "SinhVien.txt", "Bao.txt", "NhatKyViPham.txt", "PhieuMuon.txt"};
    int dongSai[] = {7, 8, 7, 2, 3, 3, 4, 5, 3, 6, 7, 1, 9, 9, 8, 19};
    const char* giaTriSai[] = {"3", "0", "NV_TT01", "N_SV01", "Ten mau thuan",
        "DG_KHONG_CO", "TL_KHONG_CO", "29/02/2023", "P_KHONG_CO", "99", "7000",
        "1000001", "2", "31/04/2026", "2", "0"};
    for(int i = 0; i < 16; i++){
        fs::path ca = goc / ("sai-" + to_string(i));
        chepBo(mau, ca);
        suaDong(ca / tepSai[i], dongSai[i], giaTriSai[i]);
        kiemTra(!tv.docToanBo(ca.string(), loi), "Tu choi du lieu sai " + to_string(i));
        kiemTra(!loi.empty() && chup(tv) == banDau, "Doc sai giu ca sau danh sach " + to_string(i));
    }
    for(int i = 0; i < 9; i++){
        fs::path ca = goc / ("thieu-" + to_string(i));
        fs::create_directory(ca);
        for(int j = 0; j < 9; j++){
            if(i != j){
                fs::copy_file(mau / tenTepThuVien[j], ca / tenTepThuVien[j]);
            }
        }
        kiemTra(!tv.docToanBo(ca.string(), loi) && chup(tv) == banDau,
                 "Thieu tep khong thay du lieu " + to_string(i));
    }
    // Dau tep, du dong, cat cut va trung ban ghi tren tung loai tep.
    int soDongBanGhi[] = {11, 10, 9, 12, 12, 10, 20, 9, 8};
    for(int i = 0; i < 9; i++){
        for(int k = 0; k < 4; k++){
            fs::path ca = goc / ("dinh-dang-" + to_string(i) + "-" + to_string(k));
            chepBo(mau, ca);
            fs::path tep = ca / tenTepThuVien[i];
            string chu = docChu(tep);
            if(k == 0){
                suaDong(tep, 0, "SAI_PHIEN_BAN");
            }
            else if(k == 1){
                kiemTra(ghiTep(tep, chu + "du lieu du\n"), "Tao tep du dong");
            }
            else if(k == 2){
                chu.pop_back();
                chu = chu.substr(0, chu.rfind('\n') + 1);
                kiemTra(ghiTep(tep, chu), "Tao tep thieu truong cuoi");
            }
            else{
                istringstream doc(chu);
                string dong;
                getline(doc, dong);
                getline(doc, dong);
                int n = stoi(dong);
                string dauBanGhi;
                for(int j = 0; j < soDongBanGhi[i]; j++){
                    getline(doc, dong);
                    dauBanGhi += dong + '\n';
                }
                string noiDung = chu.substr(chu.find('\n', chu.find('\n') + 1) + 1);
                kiemTra(ghiTep(tep, "THUVIEN_2\n" + to_string(n + 1) + "\n" + noiDung + dauBanGhi),
                         "Tao tep trung ban ghi");
            }
            kiemTra(!tv.docToanBo(ca.string(), loi), "Tu choi dinh dang sai " + ca.filename().string());
            kiemTra(chup(tv) == banDau, "Loi dinh dang giu nguyen he thong");
        }
    }
    fs::path doDang = goc / "giao dich dang do";
    chepBo(mau, doDang);
    fs::create_directory(doDang / ".giao-dich-thuvien");
    kiemTra(!tv.docToanBo(doDang.string(), loi) && loi.find("dang do") != string::npos, "Chan doc khi giao dich dang do");
    kiemTra(!tv.luuToanBo(doDang.string(), loi), "Chan ghi khi giao dich dang do");
    kiemTra(chup(tv) == banDau, "Giao dich dang do giu bo nho");
    kiemTra(docChu(doDang / "Sach.txt") == docChu(mau / "Sach.txt"), "Giao dich dang do giu tep");

    fs::path rong = goc / "rong";
    fs::create_directory(rong);
    QuanLyThuVien heThongRong;
    kiemTra(heThongRong.luuToanBo(rong.string(), loi), "Luu he thong rong van du chin tep");
    kiemTra(tv.docToanBo(rong.string(), loi) && tv.layTaiLieu().laySoLuong() == 0, "Doc rong thay he thong cu");
    kiemTra(tv.docToanBo(mau.string(), loi), "Doc lai mau khi dang rong");
    kiemTra(!tv.luuToanBo((goc / "khong-ton-tai").string(), loi), "Khong tu tao thu muc dich");
    string tepRongTruoc = docChu(rong / "Sach.txt");
    tv.layTaiLieu().timTheoMa("S01")->tangSoLuong(1);
    kiemTra(!tv.luuToanBo(rong.string(), loi), "Khong luu khi bo nho lech ton kho");
    kiemTra(docChu(rong / "Sach.txt") == tepRongTruoc, "Luu bi tu choi khong doi tep cu");
    kiemTra(tv.layTaiLieu().timTheoMa("S01")->laySoLuongCon() == 3, "Khong tu sua kho sai");
    kiemTra(tv.docToanBo(mau.string(), loi), "Doc thay he thong cu dang khong nhat quan");

    fs::path chan = goc / "duong dan la thu muc";
    fs::create_directory(chan);
    fs::create_directory(chan / "PhieuMuon.txt");
    kiemTra(!tv.luuToanBo(chan.string(), loi), "Khong ghi de thu muc gia tep");
    kiemTra(!fs::exists(chan / ".giao-dich-thuvien"), "Kiem tra duong dan truoc khi tao giao dich");

#ifdef _WIN32
    // Khoa tep thu tam: bay tep truoc da thay, buoc thu tam se loi doi ten.
    fs::path khoa = goc / "tep bi khoa";
    chepBo(mau, khoa);
    HANDLE tepKhoa = CreateFileW((khoa / "PhieuMuon.txt").c_str(), GENERIC_READ,
                                FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    kiemTra(tepKhoa != INVALID_HANDLE_VALUE, "Mo khoa Windows chan doi ten");
    if(tepKhoa != INVALID_HANDLE_VALUE){
        kiemTra(!heThongRong.luuToanBo(khoa.string(), loi), "Loi giua qua trinh thay chin tep");
        kiemTra(loi.find("phuc hoi day du") != string::npos, "Thong bao phuc hoi thanh cong");
        CloseHandle(tepKhoa);
        for(int i = 0; i < 9; i++){
            kiemTra(docChu(khoa / tenTepThuVien[i]) == docChu(mau / tenTepThuVien[i]),
                     string("Phuc hoi nguyen tep cu: ") + tenTepThuVien[i]);
        }
        kiemTra(!fs::exists(khoa / ".giao-dich-thuvien"), "Phuc hoi xong khong chan doc tiep");
        kiemTra(lichSu.docToanBo(khoa.string(), loi), "Doc duoc bo cu sau phuc hoi");
    }
#endif
    return ketQuaKiemThu();
}
