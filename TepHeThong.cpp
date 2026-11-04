#include "TepHeThong.h"
#include "QuanLyThuVien.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;
namespace fs = std::filesystem;

const char* const tenTepThuVien[9] = {
    "Sach.txt", "TapChi.txt", "Bao.txt", "SinhVien.txt", "GiangVien.txt",
    "NhanVienThuThu.txt", "ThuThuTruong.txt", "PhieuMuon.txt", "NhatKyViPham.txt"
};

//=====ham phat hien giao dich dang do va duong dan khong an toan=====
bool kiemTraThuMucDuLieu(const string& thuMuc, bool canDuTep, string& loi){
    loi.clear();
    error_code ec;
    fs::path goc(thuMuc);
    if(thuMuc.empty() || !fs::is_directory(goc, ec) || ec || fs::is_symlink(goc, ec) || ec){
        loi = "Khong dung duoc thu muc du lieu: " + thuMuc;
        return false;
    }
    fs::path giaoDich = goc / ".giao-dich-thuvien";
    fs::file_status trangThai = fs::symlink_status(giaoDich, ec);
    if(ec && ec != errc::no_such_file_or_directory){
        loi = "Khong kiem tra duoc giao dich: " + giaoDich.string();
        return false;
    }
    if(fs::exists(trangThai)){
        loi = "Phat hien giao dich luu dang do: " + giaoDich.string()
            + ". Dung ghi; xem nhat-ky.txt va cac thu muc cu/moi. "
              "Sao chep ca thu muc ra noi an toan, phuc hoi bo cu theo nhat ky; "
              "chi doi ten thu muc giao dich sau khi da kiem tra. Khong tron hai bo du lieu.";
        return false;
    }
    for(int i = 0; i < 9; i++){
        fs::path tep = goc / tenTepThuVien[i];
        ec.clear();
        trangThai = fs::symlink_status(tep, ec);
        if(ec && ec != errc::no_such_file_or_directory){
            loi = "Khong kiem tra duoc tep: " + tep.string();
            return false;
        }
        if(!fs::exists(trangThai)){
            if(!canDuTep){
                continue;
            }
            loi = "Thieu tep: " + tep.string();
            return false;
        }
        if(!fs::is_regular_file(trangThai)){
            loi = "Duong dan du lieu khong phai tep thuong: " + tep.string();
            return false;
        }
        if(canDuTep){
            ifstream doc(tep);
            string dau;
            if(!getline(doc, dau)){
                loi = "Khong doc duoc dau tep: " + tep.string();
                return false;
            }
            if(!dau.empty() && dau.back() == '\r'){
                dau.pop_back();
            }
            if(dau != "THUVIEN_2"){
                loi = "Sai dau THUVIEN_2: " + tep.string();
                return false;
            }
        }
    }
    return true;
}

// Nhat ky ghi y dinh truoc khi doi ten, giu lai de phuc hoi khi bi dung dot ngot.
static bool ghiNhatKy(const fs::path& giaoDich, const string& dong){
    ofstream tep(giaoDich / "nhat-ky.txt", ios::app);
    tep << dong << '\n';
    tep.close();
    return static_cast<bool>(tep);
}

// Giu nguyen tep da tao va ban sao; khong xoa du lieu nguoi dung.
static bool luuVet(const fs::path& giaoDich, const string& loai, string& loi){
    error_code ec;
    for(int i = 1; i <= 1000000; i++){
        fs::path dich = giaoDich.parent_path() / (loai + to_string(i));
        if(fs::exists(dich, ec)){
            continue;
        }
        if(ec){
            break;
        }
        // Windows/OneDrive co the giu thu muc rat ngan sau khi dong tep.
        // Chi thu lai viec doi ten, khong ghi lai hay thay noi dung du lieu.
        for(int lan = 0; lan < 10; lan++){
            fs::rename(giaoDich, dich, ec);
            if(!ec){
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        if(!ec){
            loi += " Ban sao va nhat ky: " + dich.string();
            return true;
        }
        break;
    }
    loi += " Khong doi ten duoc thu muc giao dich; lan doc/ghi sau se bi chan. Kiem tra "
        + giaoDich.string() + ": " + ec.message();
    return false;
}

bool luuBoDuLieu(const QuanLyThuVien& thuVien, const string& thuMuc, string& loi){
    if(!kiemTraThuMucDuLieu(thuMuc, false, loi)){
        return false;
    }
    fs::path goc(thuMuc);
    fs::path giaoDich = goc / ".giao-dich-thuvien";
    fs::path moi = giaoDich / "moi";
    fs::path cu = giaoDich / "cu";
    error_code ec;
    // Tao thu muc danh dau doc quyen; khong dung lai giao dich co san.
    if(!fs::create_directory(giaoDich, ec) || ec){
        loi = "Khong tao duoc giao dich luu: " + giaoDich.string();
        return false;
    }
    bool coCu[9] = {};
    bool daCatCu[9] = {};
    bool daDatMoi[9] = {};
    bool dung = fs::create_directory(moi, ec) && !ec;
    if(dung){
        dung = fs::create_directory(cu, ec) && !ec;
    }
    if(dung){
        dung = ghiNhatKy(giaoDich, "CHUAN_BI: du lieu dich chua thay doi");
    }
    for(int i = 0; i < 9 && dung; i++){
        coCu[i] = fs::exists(goc / tenTepThuVien[i], ec);
        dung = !ec && ghiNhatKy(giaoDich, string(tenTepThuVien[i])
                               + " CO_CU " + to_string(coCu[i]));
    }
    if(dung){
        dung = thuVien.layTaiLieu().luu(moi.string(), loi)
            && thuVien.layDocGia().luu(moi.string(), loi)
            && thuVien.layNhanVien().luu(moi.string(), loi)
            && thuVien.layThuThuTruong().luu(moi.string(), loi)
            && thuVien.layPhieuMuon().luu(moi.string(), loi)
            && thuVien.layViPham().luu(moi.string(), loi);
    }
    if(dung){
        QuanLyThuVien docLai;
        dung = docLai.docToanBo(moi.string(), loi);
    }
    //=====chi thay tep dich sau khi ca bo moi da doc lai hop le=====
    for(int i = 0; i < 9 && dung; i++){
        fs::path ten(tenTepThuVien[i]);
        if(coCu[i]){
            dung = ghiNhatKy(giaoDich, "CAT_CU " + ten.string());
            if(dung){
                fs::rename(goc / ten, cu / ten, ec);
                dung = !ec;
                daCatCu[i] = dung;
            }
        }
        if(dung){
            dung = ghiNhatKy(giaoDich, "DAT_MOI " + ten.string());
            if(dung){
                fs::rename(moi / ten, goc / ten, ec);
                dung = !ec;
                daDatMoi[i] = dung;
            }
        }
        if(!dung){
            loi = "Loi thay tep " + ten.string() + ": " + ec.message();
        }
    }
    if(!dung){
        if(loi.empty()){
            loi = "Loi chuan bi bo du lieu";
        }
        //=====phuc hoi nguoc, giu ca tep moi de kiem tra=====
        bool phucHoi = true;
        for(int i = 8; i >= 0; i--){
            fs::path ten(tenTepThuVien[i]);
            if(daDatMoi[i]){
                fs::rename(goc / ten, moi / ten, ec);
                if(ec){
                    phucHoi = false;
                    continue;
                }
            }
            if(daCatCu[i]){
                fs::rename(cu / ten, goc / ten, ec);
                if(ec){
                    phucHoi = false;
                }
            }
        }
        if(phucHoi){
            loi += "; da giu/phuc hoi day du bo cu.";
            luuVet(giaoDich, ".luu-that-bai-", loi);
        }
        else{
            loi += "; PHUC HOI CHUA DAY DU. Giu nguyen " + giaoDich.string()
                + ", xem cu/moi va nhat-ky.txt de phuc hoi thu cong.";
        }
        return false;
    }
    loi = "Da luu du chin tep.";
    ghiNhatKy(giaoDich, "HOAN_TAT: chin tep dich la bo moi");
    luuVet(giaoDich, ".sao-luu-thuvien-", loi);
    return true;
}
