#include "Menu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "SinhVien.h"
#include "GiangVien.h"
#include "TepHeThong.h"
#include "ThongKe.h"
#include <iostream>
#include <string>
using namespace std;

// Doc/luu ca bo de khong lam lech lien ket khi thao tac tu menu con.
static void menuDocDuLieu(QuanLyThuVien& thuVien);
static void menuLuuDuLieu(QuanLyThuVien& thuVien);

//=====ham nhap lua chon=====
static bool nhapLuaChon(int& chon){
    return nhapSo(cin, "Nhap lua chon: ", chon);
}

static bool nhapMa(string& ma){
    return nhapChuoi(cin, "Nhap ma: ", ma);
}

static void baoKetQua(bool thanhCong){
    if(thanhCong){
        cout << "Thao tac thanh cong.\n";
    }
    else{
        cout << "Thao tac that bai. Du lieu khong hop le, trung ma, khong ton tai"
                  << " hoac khong du dieu kien nghiep vu.\n";
    }
}

//=====ham tao doi tuong nhap=====
static TaiLieu* nhapTaiLieu(int loai){
    TaiLieu* moi = nullptr;
    switch(loai){
        case 1:
            moi = new Sach;
            break;
        case 2:
            moi = new TapChi;
            break;
        case 3:
            moi = new Bao;
            break;
        default:
            return nullptr;
    }
    if(!moi->nhap()){
        delete moi;
        return nullptr;
    }
    return moi;
}

static DocGia* nhapDocGia(int loai){
    DocGia* moi = nullptr;
    switch(loai){
        case 1:
            moi = new SinhVien;
            break;
        case 2:
            moi = new GiangVien;
            break;
        default:
            return nullptr;
    }
    if(!moi->nhap()){
        delete moi;
        return nullptr;
    }
    return moi;
}

//=====menu tai lieu=====
static void menuTaiLieu(QuanLyThuVien& thuVien){
    QuanLyTaiLieu& quanLy = thuVien.layTaiLieu();
    int chon = 0;
    do{
        cout << "\n===== QUAN LY TAI LIEU =====\n"
                  << "1. Them tai lieu\n"
                  << "2. Xuat danh sach\n"
                  << "3. Tim theo ma\n"
                  << "4. Tim theo ten\n"
                  << "5. Sua thong tin\n"
                  << "6. Xoa\n"
                  << "7. Sap xep theo nam\n"
                  << "8. Sap xep theo gia tri\n"
                  << "9. Thong ke loai va ton kho\n"
                  << "10. Luu toan he thong\n"
                  << "11. Doc toan he thong\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1: {
                int loai = 0;
                cout << "Loai: 1. Sach, 2. Tap chi, 3. Bao\n"
                          << "Tai lieu moi: nhap so con bang tong so luong.\n";
                if(!nhapLuaChon(loai)){
                    return;
                }
                TaiLieu* moi = nhapTaiLieu(loai);
                bool dung = thuVien.themTaiLieu(moi);
                if(!dung){
                    delete moi;
                }
                baoKetQua(dung);
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3: {
                if(!nhapMa(ma)){
                    return;
                }
                const TaiLieu* nguoi = quanLy.timTheoMa(ma);
                if(nguoi != nullptr){
                    nguoi->xuat();
                }
                else{
                    cout << "Khong tim thay tai lieu.\n";
                }
                break;
            }
            case 4:
                if(!nhapChuoi(cin, "Nhap ten can tim: ", ma)){
                    return;
                }
                cout << "So ket qua: " << quanLy.timTheoTen(ma) << '\n';
                break;
            case 5: {
                if(!nhapMa(ma)){
                    return;
                }
                const TaiLieu* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay tai lieu.\n";
                    break;
                }
                cu->xuat();
                cout << "Nhap lai day du, giu ma, loai va so luong dang muon.\n";
                int loai = 3;
                if(cu->layLoai() == "Sach"){
                    loai = 1;
                }
                else if(cu->layLoai() == "TapChi"){
                    loai = 2;
                }
                TaiLieu* moi = nhapTaiLieu(loai);
                bool dung = quanLy.sua(ma, moi);
                if(!dung){
                    delete moi;
                }
                baoKetQua(dung);
                break;
            }
            case 6:
                if(!nhapMa(ma)){
                    return;
                }
                baoKetQua(quanLy.xoa(ma));
                break;
            case 7:
                quanLy.sapXepTheoNam();
                quanLy.hienThi();
                break;
            case 8:
                quanLy.sapXepTheoGiaTri();
                quanLy.hienThi();
                break;
            case 9:
                quanLy.thongKe();
                break;
            case 10:
                menuLuuDuLieu(thuVien);
                break;
            case 11:
                menuDocDuLieu(thuVien);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu doc gia=====
static void menuDocGia(QuanLyThuVien& thuVien){
    QuanLyDocGia& quanLy = thuVien.layDocGia();
    int chon = 0;
    do{
        cout << "\n===== QUAN LY DOC GIA =====\n"
                  << "1. Them doc gia\n"
                  << "2. Xuat danh sach\n"
                  << "3. Tim theo ma\n"
                  << "4. Tim theo ten\n"
                  << "5. Sua thong tin\n"
                  << "6. Xoa\n"
                  << "7. Sap xep so dang muon\n"
                  << "8. Chen tai vi tri k (tu 0)\n"
                  << "9. Kiem tra han muc\n"
                  << "10. Luu toan he thong\n"
                  << "11. Doc toan he thong\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:
            case 8: {
                int viTri = quanLy.laySoLuong();
                if(chon == 8 && !nhapSo(cin, "Nhap vi tri k: ", viTri)){
                    return;
                }
                if(viTri < 0 || viTri > quanLy.laySoLuong()){
                    cout << "Vi tri khong hop le.\n";
                    break;
                }
                int loai = 0;
                cout << "Loai: 1. Sinh vien, 2. Giang vien\n"
                          << "Doc gia moi: so dang muon phai bang 0.\n";
                if(!nhapLuaChon(loai)){
                    return;
                }
                DocGia* moi = nhapDocGia(loai);
                bool dung = thuVien.themDocGia(moi, viTri);
                if(!dung){
                    delete moi;
                }
                baoKetQua(dung);
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3: {
                if(!nhapMa(ma)){
                    return;
                }
                const DocGia* nguoi = quanLy.timTheoMa(ma);
                if(nguoi != nullptr){
                    nguoi->xuat();
                }
                else{
                    cout << "Khong tim thay doc gia.\n";
                }
                break;
            }
            case 4:
                if(!nhapChuoi(cin, "Nhap ten can tim: ", ma)){
                    return;
                }
                cout << "So ket qua: " << quanLy.timTheoTen(ma) << '\n';
                break;
            case 5: {
                if(!nhapMa(ma)){
                    return;
                }
                const DocGia* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay doc gia.\n";
                    break;
                }
                cu->xuat();
                cout << "Giu ma nguoi, ma doc gia, loai, so dang muon.\n"
                          << "Ho so thu thu truong: sua o menu thu thu truong.\n";
                int loai = 2;
                if(cu->layLoai() == "SinhVien"){
                    loai = 1;
                }
                DocGia* moi = nhapDocGia(loai);
                bool dung = thuVien.suaDocGia(ma, moi);
                if(!dung){
                    delete moi;
                }
                baoKetQua(dung);
                break;
            }
            case 6:
                if(!nhapMa(ma)){
                    return;
                }
                cout << "Ho so lien ket thu thu truong: bo vai tro thu thu truong truoc.\n";
                baoKetQua(thuVien.xoaDocGia(ma));
                break;
            case 7:
                quanLy.sapXepTheoSoMuon();
                quanLy.hienThi();
                break;
            case 9: {
                int soLuong = 0;
                if(!nhapMa(ma) || !nhapSo(cin, "So luong muon du kien: ", soLuong)){
                    return;
                }
                const DocGia* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    cout << "Khong tim thay doc gia.\n";
                }
                else{
                    cout << "Gioi han: " << nguoi->layGioiHanMuon() << '\n';
                    cout << "So dang muon: " << nguoi->laySoDangMuon() << '\n';
                    if(nguoi->kiemTraDieuKienMuon(soLuong)){
                        cout << "Du dieu kien han muc va tai khoan.\n";
                    }
                    else{
                        cout << "Khong du dieu kien han muc hoac tai khoan.\n";
                    }
                }
                break;
            }
            case 10:
                menuLuuDuLieu(thuVien);
                break;
            case 11:
                menuDocDuLieu(thuVien);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu nhan vien=====
static void menuNhanVien(QuanLyThuVien& thuVien){
    QuanLyNhanVien& quanLy = thuVien.layNhanVien();
    int chon = 0;
    do{
        cout << "\n===== QUAN LY NHAN VIEN =====\n"
                  << "Danh sach nhan vien thuong; thu thu truong quan ly o menu 4.\n"
                  << "1. Them\n"
                  << "2. Xuat danh sach\n"
                  << "3. Tim theo ma\n"
                  << "4. Tim theo ca\n"
                  << "5. Sua\n"
                  << "6. Xoa\n"
                  << "7. Sap xep he so luong\n"
                  << "8. Tinh luong\n"
                  << "9. Chuyen thanh thu thu truong\n"
                  << "10. Luu toan he thong\n"
                  << "11. Doc toan he thong\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1: {
                NhanVienThuThu moi;
                baoKetQua(moi.nhap() && thuVien.themNhanVien(moi));
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:
            case 8: {
                if(!nhapMa(ma)){
                    return;
                }
                const NhanVienThuThu* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    cout << "Khong tim thay nhan vien.\n";
                }
                else if(chon == 3){
                    nguoi->xuat();
                }
                else{
                    cout << "Luong: ";
                    xuatTien(cout, nguoi->tinhLuong());
                    cout << '\n';
                }
                break;
            }
            case 4:
                if(!nhapChuoi(cin, "Nhap ca lam viec: ", ma)){
                    return;
                }
                cout << "So ket qua: " << quanLy.timTheoCa(ma) << '\n';
                break;
            case 5: {
                if(!nhapMa(ma)){
                    return;
                }
                const NhanVienThuThu* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay nhan vien.\n";
                    break;
                }
                cu->xuat();
                cout << "Nhap lai day du; giu ma nguoi va ma nhan vien.\n";
                NhanVienThuThu moi;
                baoKetQua(moi.nhap() && thuVien.suaNhanVien(ma, moi));
                break;
            }
            case 6:
                if(!nhapMa(ma)){
                    return;
                }
                baoKetQua(thuVien.xoaNhanVien(ma));
                break;
            case 7:
                quanLy.sapXepTheoHeSoLuong();
                quanLy.hienThi();
                break;
            case 9: {
                if(!nhapMa(ma)){
                    return;
                }
                const NhanVienThuThu* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay nhan vien.\n";
                    break;
                }
                cu->xuat();
                cout << "Nhap ho so thu thu truong, giu nguyen nhan than va thong tin nhan vien.\n"
                          << "Neu da la doc gia, nhap dung ho so giang vien va so dang muon hien tai.\n";
                ThuThuTruong moi;
                baoKetQua(moi.nhap() && thuVien.chuyenThanhThuThuTruong(ma, moi));
                break;
            }
            case 10:
                menuLuuDuLieu(thuVien);
                break;
            case 11:
                menuDocDuLieu(thuVien);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu thu thu truong=====
static void menuThuThuTruong(QuanLyThuVien& thuVien){
    QuanLyThuThuTruong& quanLy = thuVien.layThuThuTruong();
    int chon = 0;
    do{
        cout << "\n===== QUAN LY THU THU TRUONG =====\n"
                  << "1. Them\n"
                  << "2. Xuat danh sach\n"
                  << "3. Tim theo ma\n"
                  << "4. Tim nguoi quan ly hon 10 nhan vien\n"
                  << "5. Sap xep phu cap\n"
                  << "6. Tinh thu nhap\n"
                  << "7. Sua\n"
                  << "8. Xoa ho so nhan su truong (giu doc gia)\n"
                  << "9. Xem nhat ky vi pham\n"
                  << "10. Duyet vi pham\n"
                  << "11. Chuyen ve nhan vien thuong\n"
                  << "12. Luu toan he thong\n"
                  << "13. Doc toan he thong\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1: {
                cout << "Tu dong dang ky vai tro doc gia GiangVien.\n"
                          << "Ho so moi: so dang muon = 0. Ho so da co: thong tin phai trung khop.\n";
                ThuThuTruong moi;
                baoKetQua(moi.nhap() && thuVien.themThuThuTruong(moi));
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:
            case 6:
            case 9: {
                if(!nhapMa(ma)){
                    return;
                }
                const ThuThuTruong* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    cout << "Khong tim thay thu thu truong.\n";
                }
                else if(chon == 3){
                    nguoi->xuat();
                }
                else if(chon == 6){
                    cout << "Thu nhap: ";
                    xuatTien(cout, nguoi->tinhThuNhap());
                    cout << '\n';
                }
                else{
                    nguoi->xemNhatKyViPham(thuVien.layViPham());
                }
                break;
            }
            case 4:
                cout << "So ket qua: " << quanLy.timTheoSoNhanVien(10) << '\n';
                break;
            case 5:
                quanLy.sapXepTheoPhuCap();
                quanLy.hienThi();
                break;
            case 7: {
                if(!nhapMa(ma)){
                    return;
                }
                const ThuThuTruong* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay thu thu truong.\n";
                    break;
                }
                cu->xuat();
                cout << "Nhap lai day du; giu cac ma va so dang muon.\n";
                ThuThuTruong moi;
                baoKetQua(moi.nhap() && thuVien.suaThuThuTruong(ma, moi));
                break;
            }
            case 8:
                if(!nhapMa(ma)){
                    return;
                }
                baoKetQua(thuVien.xoaThuThuTruong(ma));
                cout << "Ho so doc gia va lich su duoc giu lai.\n";
                break;
            case 10: {
                string maViPham;
                if(!nhapChuoi(cin, "Nhap ma thu thu truong: ", ma)
                   || !nhapChuoi(cin, "Nhap ma vi pham: ", maViPham)){
                    return;
                }
                baoKetQua(thuVien.duyetViPham(maViPham, ma));
                break;
            }
            case 11:
                if(!nhapMa(ma)){
                    return;
                }
                baoKetQua(thuVien.chuyenThanhNhanVien(ma));
                break;
            case 12:
                menuLuuDuLieu(thuVien);
                break;
            case 13:
                menuDocDuLieu(thuVien);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu muon tra=====
static void menuMuonTra(QuanLyThuVien& thuVien){
    QuanLyPhieuMuon& quanLy = thuVien.layPhieuMuon();
    int chon = 0;
    do{
        cout << "\n===== QUAN LY MUON - TRA =====\n"
                  << "1. Lap phieu muon\n"
                  << "2. Tra tai lieu\n"
                  << "3. Xuat danh sach\n"
                  << "4. Tim theo ma phieu\n"
                  << "5. Liet ke theo doc gia\n"
                  << "6. Doc gia dang muon mot tai lieu\n"
                  << "7. Phieu qua han hom nay\n"
                  << "8. Tinh tien phat tai ngay du kien\n"
                  << "9. Sap xep ma phieu (Merge Sort)\n"
                  << "10. Luu toan he thong\n"
                  << "11. Doc toan he thong\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1: {
                PhieuMuon phieu;
                baoKetQua(phieu.nhap() && thuVien.lapPhieu(phieu));
                break;
            }
            case 2: {
                string ngay;
                if(!nhapMa(ma) || !nhapChuoi(cin, "Nhap ngay tra (dd/mm/yyyy): ", ngay)){
                    return;
                }
                bool dung = thuVien.traTaiLieu(ma, ngay);
                baoKetQua(dung);
                if(dung){
                    cout << *quanLy.timTheoMa(ma);
                    if(thuVien.layViPham().timTheoPhieu(ma) != nullptr){
                        cout << "Da tu dong ghi vi pham VP_" << ma << ".\n";
                    }
                }
                break;
            }
            case 3:
                quanLy.hienThi();
                break;
            case 4: {
                if(!nhapMa(ma)){
                    return;
                }
                const PhieuMuon* phieu = quanLy.timTheoMa(ma);
                if(phieu == nullptr){
                    cout << "Khong tim thay phieu.\n";
                }
                else{
                    cout << *phieu;
                }
                break;
            }
            case 5:
                if(!nhapMa(ma)){
                    return;
                }
                cout << "So ket qua: " << quanLy.lietKeTheoDocGia(ma) << '\n';
                break;
            case 6:
                if(!nhapMa(ma)){
                    return;
                }
                cout << "So ket qua: " << quanLy.lietKeDocGiaMuonTaiLieu(ma, thuVien.layDocGia()) << '\n';
                break;
            case 7:
                quanLy.lietKeQuaHan(thuVien.layDocGia());
                break;
            case 8: {
                string ngay;
                if(!nhapMa(ma)){
                    return;
                }
                const PhieuMuon* phieu = quanLy.timTheoMa(ma);
                if(phieu == nullptr){
                    cout << "Khong tim thay phieu.\n";
                    break;
                }
                if(!phieu->dangMuon()){
                    cout << "Tien phat da chot: ";
                    xuatTien(cout, phieu->layTienPhat());
                    cout << '\n';
                    break;
                }
                if(!nhapChuoi(cin, "Nhap ngay du kien tra: ", ngay)){
                    return;
                }
                const TaiLieu* taiLieu = thuVien.layTaiLieu().timTheoMa(phieu->layMaTaiLieu());
                double tien = -1;
                if(taiLieu != nullptr){
                    tien = phieu->tinhTienPhat(*taiLieu, ngay);
                }
                if(tien < 0){
                    baoKetQua(false);
                }
                else{
                    cout << "Tien phat du kien: ";
                    xuatTien(cout, tien);
                    cout << '\n';
                }
                break;
            }
            case 9:
                quanLy.sapXepTheoMa();
                quanLy.hienThi();
                break;
            case 10:
                menuLuuDuLieu(thuVien);
                break;
            case 11:
                menuDocDuLieu(thuVien);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu vi pham=====
static void menuViPham(QuanLyThuVien& thuVien){
    QuanLyViPham& quanLy = thuVien.layViPham();
    int chon = 0;
    do{
        cout << "\n===== QUAN LY VI PHAM =====\n"
                  << "1. Ghi nhan tu phieu da tra\n"
                  << "2. Xuat nhat ky\n"
                  << "3. Tim theo doc gia\n"
                  << "4. Liet ke chua thanh toan\n"
                  << "5. Thanh toan\n"
                  << "6. Tong tien phat\n"
                  << "7. Dem vi pham cua doc gia\n"
                  << "8. Duyet vi pham\n"
                  << "9. Tim ma vi pham\n"
                  << "10. Luu toan he thong\n"
                  << "11. Doc toan he thong\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:
                cout << "Tra tre da tu dong ghi vi pham; khong ghi lai su kien da co.\n";
                if(!nhapChuoi(cin, "Nhap ma phieu da tra: ", ma)){
                    return;
                }
                baoKetQua(thuVien.ghiViPham(ma));
                break;
            case 2:
                quanLy.hienThi();
                break;
            case 3:
                if(!nhapMa(ma)){
                    return;
                }
                cout << "So ket qua: " << quanLy.timTheoDocGia(ma) << '\n';
                break;
            case 4:
                quanLy.lietKeChuaThanhToan();
                break;
            case 5:
                if(!nhapChuoi(cin, "Nhap ma vi pham: ", ma)){
                    return;
                }
                baoKetQua(quanLy.thanhToanPhat(ma));
                break;
            case 6:
                cout << "Da thu: ";
                xuatTien(cout, quanLy.tinhTongTienPhatDaThanhToan());
                cout << '\n';
                cout << "Chua thu: ";
                xuatTien(cout, quanLy.tinhTongTienPhatChuaThanhToan());
                cout << '\n';
                break;
            case 7:
                if(!nhapMa(ma)){
                    return;
                }
                cout << "So lan vi pham: " << quanLy.demViPham(ma) << '\n';
                break;
            case 8: {
                string maThuThu;
                if(!nhapChuoi(cin, "Nhap ma vi pham: ", ma)
                   || !nhapChuoi(cin, "Nhap ma thu thu truong: ", maThuThu)){
                    return;
                }
                baoKetQua(thuVien.duyetViPham(ma, maThuThu));
                break;
            }
            case 9: {
                if(!nhapMa(ma)){
                    return;
                }
                const NhatKyViPham* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    cout << "Khong tim thay vi pham.\n";
                }
                else{
                    nguoi->xuat();
                }
                break;
            }
            case 10:
                menuLuuDuLieu(thuVien);
                break;
            case 11:
                menuDocDuLieu(thuVien);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu tim kiem va sap xep=====
static void menuTimKiem(QuanLyThuVien& thuVien){
    int chon = 0;
    do{
        cout << "\n===== TIM KIEM VA SAP XEP =====\n"
                  << "1. Tim nhi phan ma tai lieu\n"
                  << "2. Tim bang bam ma doc gia\n"
                  << "3. Selection Sort nam xuat ban\n"
                  << "4. Quick Sort gia tri\n"
                  << "5. Bubble Sort so dang muon\n"
                  << "6. Merge Sort ma phieu\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1: {
                if(!nhapMa(ma)){
                    return;
                }
                const TaiLieu* nguoi = thuVien.layTaiLieu().timNhiPhan(ma);
                if(nguoi != nullptr){
                    nguoi->xuat();
                }
                else{
                    cout << "Khong tim thay tai lieu.\n";
                }
                break;
            }
            case 2: {
                if(!nhapMa(ma)){
                    return;
                }
                const DocGia* nguoi = thuVien.layDocGia().timBangBam(ma);
                if(nguoi != nullptr){
                    nguoi->xuat();
                }
                else{
                    cout << "Khong tim thay doc gia.\n";
                }
                break;
            }
            case 3:
                thuVien.layTaiLieu().sapXepTheoNam();
                thuVien.layTaiLieu().hienThi();
                break;
            case 4:
                thuVien.layTaiLieu().sapXepTheoGiaTri();
                thuVien.layTaiLieu().hienThi();
                break;
            case 5:
                thuVien.layDocGia().sapXepTheoSoMuon();
                thuVien.layDocGia().hienThi();
                break;
            case 6:
                thuVien.layPhieuMuon().sapXepTheoMa();
                thuVien.layPhieuMuon().hienThi();
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu doc va luu ca he thong=====
static void menuDocDuLieu(QuanLyThuVien& thuVien){
    string thuMuc;
    string loi;
    if(!nhapChuoi(cin, "Nhap thu muc chua du chin tep: ", thuMuc)){
        return;
    }
    QuanLyThuVien tam;
    if(!tam.docToanBo(thuMuc, loi)){
        cout << "Doc that bai: " << loi << "\nDu lieu hien tai duoc giu nguyen.\n";
        return;
    }
    int xacNhan = 0;
    if(!nhapSo(cin, "Du lieu hop le. Thay THE TOAN BO du lieu hien tai? (1: Dong y, 0: Huy): ", xacNhan)){
        return;
    }
    if(xacNhan != 1){
        cout << "Da huy doc. Du lieu hien tai duoc giu nguyen.\n";
        return;
    }
    thuVien.doiDuLieu(tam);
    cout << "Da doc du chin tep va thay du lieu thanh cong.\n";
}

static void menuLuuDuLieu(QuanLyThuVien& thuVien){
    string thuMuc;
    string loi;
    if(!nhapChuoi(cin, "Nhap thu muc dich da ton tai: ", thuMuc)){
        return;
    }
    if(!kiemTraThuMucDuLieu(thuMuc, false, loi)){
        cout << "Luu that bai: " << loi << '\n';
        return;
    }
    int xacNhan = 0;
    if(!nhapSo(cin, "Luu chin tep (thay tep cung ten neu co)? (1: Dong y, 0: Huy): ", xacNhan)){
        return;
    }
    if(xacNhan != 1){
        cout << "Da huy luu. Khong thay doi tep du lieu.\n";
        return;
    }
    if(thuVien.luuToanBo(thuMuc, loi)){
        cout << loi << '\n';
    }
    else{
        cout << "Luu that bai: " << loi << '\n';
    }
}

//=====menu thong ke va thuc nghiem=====
static void menuThongKe(QuanLyThuVien& thuVien){
    int chon = 0;
    do{
        cout << "\n===== THONG KE VA THUC NGHIEM =====\n"
             << "1. Tai lieu theo loai va ton kho\n"
             << "2. Doc gia muon nhieu nhat va tong so dang muon\n"
             << "3. Tai lieu duoc muon nhieu nhat\n"
             << "4. Phieu qua han hom nay\n"
             << "5. Tong tien phat da thu va chua thu\n"
             << "6. Thuc nghiem 4 kich thuoc du lieu\n"
                  << "0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        switch(chon){
            case 1:
                thuVien.layTaiLieu().thongKe();
                break;
            case 2:
                thongKeDocGia(thuVien, cout);
                break;
            case 3:
                thongKeTaiLieuMuonNhieu(thuVien, cout);
                break;
            case 4:
                thuVien.layPhieuMuon().lietKeQuaHan(thuVien.layDocGia());
                break;
            case 5:
                cout << "Da thu: ";
                xuatTien(cout, thuVien.layViPham().tinhTongTienPhatDaThanhToan());
                cout << "\nChua thu: ";
                xuatTien(cout, thuVien.layViPham().tinhTongTienPhatChuaThanhToan());
                cout << '\n';
                break;
            case 6:
                thucNghiemThuatToan(cout);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && cin);
}

//=====menu chinh=====
void menuChinh(QuanLyThuVien& thuVien){
    int chon = 0;
    do{
        cout << "\n========================================\n"
                  << "       HE THONG QUAN LY THU VIEN\n"
                  << "========================================\n"
                  << "1. Quan ly tai lieu\n"
                  << "2. Quan ly doc gia\n"
                  << "3. Quan ly nhan vien\n"
                  << "4. Quan ly thu thu truong\n"
                  << "5. Quan ly muon - tra\n"
                  << "6. Quan ly vi pham\n"
                  << "7. Tim kiem va sap xep\n"
                  << "8. Thong ke va thuc nghiem\n"
                  << "9. Doc du lieu tu file\n"
                  << "10. Luu du lieu vao file\n"
                  << "11. Thoat\n========================================\n";
        if(!nhapLuaChon(chon)){
            cout << "\nKet thuc dau vao. Khong tu dong luu du lieu.\n";
            return;
        }
        switch(chon){
            case 1:
                menuTaiLieu(thuVien);
                break;
            case 2:
                menuDocGia(thuVien);
                break;
            case 3:
                menuNhanVien(thuVien);
                break;
            case 4:
                menuThuThuTruong(thuVien);
                break;
            case 5:
                menuMuonTra(thuVien);
                break;
            case 6:
                menuViPham(thuVien);
                break;
            case 7:
                menuTimKiem(thuVien);
                break;
            case 8:
                menuThongKe(thuVien);
                break;
            case 9:
                menuDocDuLieu(thuVien);
                break;
            case 10:
                menuLuuDuLieu(thuVien);
                break;
            case 11:
                cout << "Thoat chuong trinh. Khong tu dong luu du lieu.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 11 && cin);
    if(!cin){
        cout << "\nKet thuc dau vao. Khong tu dong luu du lieu.\n";
    }
}
