#include "Menu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "SinhVien.h"
#include "GiangVien.h"

//=====ham nhap lua chon=====
static bool nhapLuaChon(int& chon){
    return nhapSo(std::cin, "Nhap lua chon: ", chon);
}

static bool nhapMa(std::string& ma){
    return nhapChuoi(std::cin, "Nhap ma: ", ma);
}

static void baoKetQua(bool thanhCong){
    if(thanhCong){
        std::cout << "Thao tac thanh cong.\n";
    }
    else{
        std::cout << "Thao tac that bai. Du lieu khong hop le, trung ma, khong ton tai"
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
        std::cout << "\n===== QUAN LY TAI LIEU =====\n"
                  << "1. Them tai lieu\n2. Xuat danh sach\n3. Tim theo ma\n"
                  << "4. Tim theo ten\n5. Sua thong tin\n6. Xoa\n"
                  << "7. Sap xep theo nam\n8. Sap xep theo gia tri\n"
                  << "9. Thong ke loai va ton kho\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
        switch(chon){
            case 1: {
                int loai = 0;
                std::cout << "Loai: 1. Sach, 2. Tap chi, 3. Bao\n"
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
                    std::cout << "Khong tim thay tai lieu.\n";
                }
                break;
            }
            case 4:
                if(!nhapChuoi(std::cin, "Nhap ten can tim: ", ma)){
                    return;
                }
                std::cout << "So ket qua: " << quanLy.timTheoTen(ma) << '\n';
                break;
            case 5: {
                if(!nhapMa(ma)){
                    return;
                }
                const TaiLieu* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    std::cout << "Khong tim thay tai lieu.\n";
                    break;
                }
                cu->xuat();
                std::cout << "Nhap lai day du, giu ma, loai va so luong dang muon.\n";
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
            case 0:
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu doc gia=====
static void menuDocGia(QuanLyThuVien& thuVien){
    QuanLyDocGia& quanLy = thuVien.layDocGia();
    int chon = 0;
    do{
        std::cout << "\n===== QUAN LY DOC GIA =====\n"
                  << "1. Them doc gia\n2. Xuat danh sach\n3. Tim theo ma\n"
                  << "4. Tim theo ten\n5. Sua thong tin\n6. Xoa\n"
                  << "7. Sap xep so dang muon\n8. Chen tai vi tri k (tu 0)\n"
                  << "9. Kiem tra han muc\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
        switch(chon){
            case 1:
            case 8: {
                int viTri = quanLy.laySoLuong();
                if(chon == 8 && !nhapSo(std::cin, "Nhap vi tri k: ", viTri)){
                    return;
                }
                if(viTri < 0 || viTri > quanLy.laySoLuong()){
                    std::cout << "Vi tri khong hop le.\n";
                    break;
                }
                int loai = 0;
                std::cout << "Loai: 1. Sinh vien, 2. Giang vien\n"
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
                    std::cout << "Khong tim thay doc gia.\n";
                }
                break;
            }
            case 4:
                if(!nhapChuoi(std::cin, "Nhap ten can tim: ", ma)){
                    return;
                }
                std::cout << "So ket qua: " << quanLy.timTheoTen(ma) << '\n';
                break;
            case 5: {
                if(!nhapMa(ma)){
                    return;
                }
                const DocGia* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    std::cout << "Khong tim thay doc gia.\n";
                    break;
                }
                cu->xuat();
                std::cout << "Giu ma nguoi, ma doc gia, loai, so dang muon.\n"
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
                std::cout << "Ho so lien ket thu thu truong: bo vai tro thu thu truong truoc.\n";
                baoKetQua(thuVien.xoaDocGia(ma));
                break;
            case 7:
                quanLy.sapXepTheoSoMuon();
                quanLy.hienThi();
                break;
            case 9: {
                int soLuong = 0;
                if(!nhapMa(ma) || !nhapSo(std::cin, "So luong muon du kien: ", soLuong)){
                    return;
                }
                const DocGia* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    std::cout << "Khong tim thay doc gia.\n";
                }
                else{
                    std::cout << "Gioi han: " << nguoi->layGioiHanMuon() << '\n';
                    std::cout << "So dang muon: " << nguoi->laySoDangMuon() << '\n';
                    if(nguoi->kiemTraDieuKienMuon(soLuong)){
                        std::cout << "Du dieu kien han muc va tai khoan.\n";
                    }
                    else{
                        std::cout << "Khong du dieu kien han muc hoac tai khoan.\n";
                    }
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu nhan vien=====
static void menuNhanVien(QuanLyThuVien& thuVien){
    QuanLyNhanVien& quanLy = thuVien.layNhanVien();
    int chon = 0;
    do{
        std::cout << "\n===== QUAN LY NHAN VIEN =====\n"
                  << "Danh sach nhan vien thuong; thu thu truong quan ly o menu 4.\n"
                  << "1. Them\n2. Xuat danh sach\n3. Tim theo ma\n4. Tim theo ca\n"
                  << "5. Sua\n6. Xoa\n7. Sap xep he so luong\n8. Tinh luong\n"
                  << "9. Chuyen thanh thu thu truong\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
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
                    std::cout << "Khong tim thay nhan vien.\n";
                }
                else if(chon == 3){
                    nguoi->xuat();
                }
                else{
                    std::cout << "Luong: ";
                    xuatTien(std::cout, nguoi->tinhLuong());
                    std::cout << '\n';
                }
                break;
            }
            case 4:
                if(!nhapChuoi(std::cin, "Nhap ca lam viec: ", ma)){
                    return;
                }
                std::cout << "So ket qua: " << quanLy.timTheoCa(ma) << '\n';
                break;
            case 5: {
                if(!nhapMa(ma)){
                    return;
                }
                const NhanVienThuThu* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    std::cout << "Khong tim thay nhan vien.\n";
                    break;
                }
                cu->xuat();
                std::cout << "Nhap lai day du; giu ma nguoi va ma nhan vien.\n";
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
                    std::cout << "Khong tim thay nhan vien.\n";
                    break;
                }
                cu->xuat();
                std::cout << "Nhap ho so thu thu truong, giu nguyen nhan than va thong tin nhan vien.\n"
                          << "Neu da la doc gia, nhap dung ho so giang vien va so dang muon hien tai.\n";
                ThuThuTruong moi;
                baoKetQua(moi.nhap() && thuVien.chuyenThanhThuThuTruong(ma, moi));
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu thu thu truong=====
static void menuThuThuTruong(QuanLyThuVien& thuVien){
    QuanLyThuThuTruong& quanLy = thuVien.layThuThuTruong();
    int chon = 0;
    do{
        std::cout << "\n===== QUAN LY THU THU TRUONG =====\n"
                  << "1. Them\n2. Xuat danh sach\n3. Tim theo ma\n"
                  << "4. Tim nguoi quan ly hon 10 nhan vien\n5. Sap xep phu cap\n"
                  << "6. Tinh thu nhap\n7. Sua\n8. Xoa ho so nhan su truong (giu doc gia)\n"
                  << "9. Xem nhat ky vi pham\n10. Duyet vi pham\n"
                  << "11. Chuyen ve nhan vien thuong\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
        switch(chon){
            case 1: {
                std::cout << "Tu dong dang ky vai tro doc gia GiangVien.\n"
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
                    std::cout << "Khong tim thay thu thu truong.\n";
                }
                else if(chon == 3){
                    nguoi->xuat();
                }
                else if(chon == 6){
                    std::cout << "Thu nhap: ";
                    xuatTien(std::cout, nguoi->tinhThuNhap());
                    std::cout << '\n';
                }
                else{
                    nguoi->xemNhatKyViPham(thuVien.layViPham());
                }
                break;
            }
            case 4:
                std::cout << "So ket qua: " << quanLy.timTheoSoNhanVien(10) << '\n';
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
                    std::cout << "Khong tim thay thu thu truong.\n";
                    break;
                }
                cu->xuat();
                std::cout << "Nhap lai day du; giu cac ma va so dang muon.\n";
                ThuThuTruong moi;
                baoKetQua(moi.nhap() && thuVien.suaThuThuTruong(ma, moi));
                break;
            }
            case 8:
                if(!nhapMa(ma)){
                    return;
                }
                baoKetQua(thuVien.xoaThuThuTruong(ma));
                std::cout << "Ho so doc gia va lich su duoc giu lai.\n";
                break;
            case 10: {
                std::string maViPham;
                if(!nhapChuoi(std::cin, "Nhap ma thu thu truong: ", ma)
                   || !nhapChuoi(std::cin, "Nhap ma vi pham: ", maViPham)){
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
            case 0:
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu muon tra=====
static void menuMuonTra(QuanLyThuVien& thuVien){
    QuanLyPhieuMuon& quanLy = thuVien.layPhieuMuon();
    int chon = 0;
    do{
        std::cout << "\n===== QUAN LY MUON - TRA =====\n"
                  << "1. Lap phieu muon\n2. Tra tai lieu\n3. Xuat danh sach\n"
                  << "4. Tim theo ma phieu\n5. Liet ke theo doc gia\n"
                  << "6. Doc gia dang muon mot tai lieu\n7. Phieu qua han hom nay\n"
                  << "8. Tinh tien phat tai ngay du kien\n9. Sap xep ma phieu (Merge Sort)\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
        switch(chon){
            case 1: {
                PhieuMuon phieu;
                baoKetQua(phieu.nhap() && thuVien.lapPhieu(phieu));
                break;
            }
            case 2: {
                std::string ngay;
                if(!nhapMa(ma) || !nhapChuoi(std::cin, "Nhap ngay tra (dd/mm/yyyy): ", ngay)){
                    return;
                }
                bool dung = thuVien.traTaiLieu(ma, ngay);
                baoKetQua(dung);
                if(dung){
                    std::cout << *quanLy.timTheoMa(ma);
                    if(thuVien.layViPham().timTheoPhieu(ma) != nullptr){
                        std::cout << "Da tu dong ghi vi pham VP_" << ma << ".\n";
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
                    std::cout << "Khong tim thay phieu.\n";
                }
                else{
                    std::cout << *phieu;
                }
                break;
            }
            case 5:
                if(!nhapMa(ma)){
                    return;
                }
                std::cout << "So ket qua: " << quanLy.lietKeTheoDocGia(ma) << '\n';
                break;
            case 6:
                if(!nhapMa(ma)){
                    return;
                }
                std::cout << "So ket qua: " << quanLy.lietKeDocGiaMuonTaiLieu(ma, thuVien.layDocGia()) << '\n';
                break;
            case 7:
                quanLy.lietKeQuaHan(thuVien.layDocGia());
                break;
            case 8: {
                std::string ngay;
                if(!nhapMa(ma)){
                    return;
                }
                const PhieuMuon* phieu = quanLy.timTheoMa(ma);
                if(phieu == nullptr){
                    std::cout << "Khong tim thay phieu.\n";
                    break;
                }
                if(!phieu->dangMuon()){
                    std::cout << "Tien phat da chot: ";
                    xuatTien(std::cout, phieu->layTienPhat());
                    std::cout << '\n';
                    break;
                }
                if(!nhapChuoi(std::cin, "Nhap ngay du kien tra: ", ngay)){
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
                    std::cout << "Tien phat du kien: ";
                    xuatTien(std::cout, tien);
                    std::cout << '\n';
                }
                break;
            }
            case 9:
                quanLy.sapXepTheoMa();
                quanLy.hienThi();
                break;
            case 0:
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu vi pham=====
static void menuViPham(QuanLyThuVien& thuVien){
    QuanLyViPham& quanLy = thuVien.layViPham();
    int chon = 0;
    do{
        std::cout << "\n===== QUAN LY VI PHAM =====\n"
                  << "1. Ghi nhan tu phieu da tra\n2. Xuat nhat ky\n3. Tim theo doc gia\n"
                  << "4. Liet ke chua thanh toan\n5. Thanh toan\n6. Tong tien phat\n"
                  << "7. Dem vi pham cua doc gia\n8. Duyet vi pham\n9. Tim ma vi pham\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
        switch(chon){
            case 1:
                std::cout << "Tra tre da tu dong ghi vi pham; khong ghi lai su kien da co.\n";
                if(!nhapChuoi(std::cin, "Nhap ma phieu da tra: ", ma)){
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
                std::cout << "So ket qua: " << quanLy.timTheoDocGia(ma) << '\n';
                break;
            case 4:
                quanLy.lietKeChuaThanhToan();
                break;
            case 5:
                if(!nhapChuoi(std::cin, "Nhap ma vi pham: ", ma)){
                    return;
                }
                baoKetQua(quanLy.thanhToanPhat(ma));
                break;
            case 6:
                std::cout << "Da thu: ";
                xuatTien(std::cout, quanLy.tinhTongTienPhatDaThanhToan());
                std::cout << '\n';
                std::cout << "Chua thu: ";
                xuatTien(std::cout, quanLy.tinhTongTienPhatChuaThanhToan());
                std::cout << '\n';
                break;
            case 7:
                if(!nhapMa(ma)){
                    return;
                }
                std::cout << "So lan vi pham: " << quanLy.demViPham(ma) << '\n';
                break;
            case 8: {
                std::string maThuThu;
                if(!nhapChuoi(std::cin, "Nhap ma vi pham: ", ma)
                   || !nhapChuoi(std::cin, "Nhap ma thu thu truong: ", maThuThu)){
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
                    std::cout << "Khong tim thay vi pham.\n";
                }
                else{
                    nguoi->xuat();
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu tim kiem va sap xep=====
static void menuTimKiem(QuanLyThuVien& thuVien){
    int chon = 0;
    do{
        std::cout << "\n===== TIM KIEM VA SAP XEP =====\n"
                  << "1. Tim nhi phan ma tai lieu\n2. Tim bang bam ma doc gia\n"
                  << "3. Selection Sort nam xuat ban\n4. Quick Sort gia tri\n"
                  << "5. Bubble Sort so dang muon\n6. Merge Sort ma phieu\n0. Quay lai\n";
        if(!nhapLuaChon(chon)){
            return;
        }
        std::string ma;
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
                    std::cout << "Khong tim thay tai lieu.\n";
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
                    std::cout << "Khong tim thay doc gia.\n";
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
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 0 && std::cin);
}

//=====menu chinh=====
void menuChinh(QuanLyThuVien& thuVien){
    int chon = 0;
    do{
        std::cout << "\n========================================\n"
                  << "       HE THONG QUAN LY THU VIEN\n"
                  << "========================================\n"
                  << "1. Quan ly tai lieu\n2. Quan ly doc gia\n3. Quan ly nhan vien\n"
                  << "4. Quan ly thu thu truong\n5. Quan ly muon - tra\n6. Quan ly vi pham\n"
                  << "7. Tim kiem va sap xep\n"
                  << "8. Thong ke va thuc nghiem [CHUA TRIEN KHAI]\n"
                  << "9. Doc du lieu tu file [CHUA TRIEN KHAI]\n"
                  << "10. Luu du lieu vao file [CHUA TRIEN KHAI]\n"
                  << "11. Thoat\n========================================\n";
        if(!nhapLuaChon(chon)){
            std::cout << "\nKet thuc dau vao. Khong tu dong luu du lieu.\n";
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
            case 9:
            case 10:
                std::cout << "Chua trien khai trong giai doan 1. Khong thay doi du lieu.\n";
                break;
            case 11:
                std::cout << "Thoat chuong trinh. Khong tu dong luu du lieu.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    }while(chon != 11 && std::cin);
}
