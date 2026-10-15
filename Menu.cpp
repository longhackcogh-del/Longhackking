#include "Menu.h"
#include "QuanLyThuVien.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "SinhVien.h"
#include "GiangVien.h"
#include "ThongKe.h"
#include "ThucNghiem.h"
#include <fstream>

using namespace std;

//=====ham bao ket qua=====
static void baoKetQua(bool thanhCong){
    if(thanhCong){
        cout << "Thao tac thanh cong.\n";
    }
    else{
        cout << "Thao tac that bai: du lieu sai, trung ma, vuot han muc hoac con lien ket.\n";
    }
}

//=====ham doc ghi dong bo=====
static void xuLyTep(QuanLyThuVien& heThong, bool ghi){
    string loi;
    bool thanhCong = false;
    if(ghi){
        thanhCong = heThong.luu("data", loi);
    }
    else{
        thanhCong = heThong.doc("data", loi);
    }
    if(thanhCong){
        cout << "Da ";
        if(ghi){
            cout << "luu";
        }
        else{
            cout << "doc";
        }
        cout << " dong bo 9 tep tai thu muc data.\n";
    }
    else{
        cout << "Thao tac tep that bai: " << loi << '\n';
    }
}

//=====ham tao tai lieu=====
static TaiLieu* nhapTaiLieu(const string& loai = ""){
    string tenLoai = loai;
    if(tenLoai.empty()){
        int chon = 0;
        cout << "1. Sach\n2. Tap chi\n3. Bao\n";
        if(!nhapSo(cin, "Chon loai: ", chon)){
            return nullptr;
        }
        switch(chon){
            case 1:
                tenLoai = "Sach";
                break;
            case 2:
                tenLoai = "TapChi";
                break;
            case 3:
                tenLoai = "Bao";
                break;
            default:
                return nullptr;
        }
    }
    TaiLieu* taiLieu = nullptr;
    if(tenLoai == "Sach"){
        taiLieu = new Sach;
    }
    else if(tenLoai == "TapChi"){
        taiLieu = new TapChi;
    }
    else if(tenLoai == "Bao"){
        taiLieu = new Bao;
    }
    if(taiLieu != nullptr && !taiLieu->nhap()){
        delete taiLieu;
        return nullptr;
    }
    return taiLieu;
}

//=====ham tao doc gia=====
static DocGia* nhapDocGia(const string& loai = ""){
    string tenLoai = loai;
    if(tenLoai.empty()){
        int chon = 0;
        cout << "1. Sinh vien\n2. Giang vien\n";
        if(!nhapSo(cin, "Chon loai: ", chon)){
            return nullptr;
        }
        switch(chon){
            case 1:
                tenLoai = "SinhVien";
                break;
            case 2:
                tenLoai = "GiangVien";
                break;
            default:
                return nullptr;
        }
    }
    DocGia* docGia = nullptr;
    if(tenLoai == "SinhVien"){
        docGia = new SinhVien;
    }
    else if(tenLoai == "GiangVien"){
        docGia = new GiangVien;
    }
    if(docGia != nullptr && !docGia->nhap()){
        delete docGia;
        return nullptr;
    }
    return docGia;
}

//=====menu tai lieu=====
static void menuTaiLieu(QuanLyThuVien& heThong){
    QuanLyTaiLieu& quanLy = heThong.layTaiLieu();
    int chon = -1;
    do{
        cout << "\n=====QUAN LY TAI LIEU=====\n";
        cout << "1. Them sach, tap chi, bao\n2. Hien thi\n3. Tim theo ma\n4. Tim theo ten\n";
        cout << "5. Sua\n6. Xoa\n7. Sap xep nam\n8. Sap xep gia tri\n9. Thong ke\n";
        cout << "10. Luu tep\n11. Doc tep\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:{
                cout << "Tai lieu moi co so luong con bang tong so luong.\n";
                TaiLieu* taiLieu = nhapTaiLieu();
                bool thanhCong = false;
                if(taiLieu != nullptr && taiLieu->laySoLuongCon() == taiLieu->laySoLuongTong()){
                    thanhCong = quanLy.them(taiLieu);
                }
                if(!thanhCong){
                    delete taiLieu;
                }
                baoKetQua(thanhCong);
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:{
                if(!nhapChuoi(cin, "Nhap ma: ", ma)){
                    break;
                }
                TaiLieu* taiLieu = quanLy.timNhiPhan(ma);
                if(taiLieu != nullptr){
                    taiLieu->xuat();
                }
                else{
                    cout << "Khong tim thay.\n";
                }
                break;
            }
            case 4:{
                string ten;
                if(nhapChuoi(cin, "Nhap ten hoac mot phan ten: ", ten)){
                    cout << "So ket qua: " << quanLy.timTheoTen(ten) << '\n';
                }
                break;
            }
            case 5:{
                if(!nhapChuoi(cin, "Nhap ma can sua: ", ma)){
                    break;
                }
                TaiLieu* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay.\n";
                    break;
                }
                cu->xuat();
                cout << "Nhap lai thong tin; giu nguyen ma va so ban dang muon.\n";
                TaiLieu* moi = nhapTaiLieu(cu->layLoai());
                bool thanhCong = quanLy.sua(ma, moi);
                if(!thanhCong){
                    delete moi;
                }
                baoKetQua(thanhCong);
                break;
            }
            case 6:
                if(nhapChuoi(cin, "Nhap ma can xoa: ", ma)){
                    baoKetQua(quanLy.xoa(ma));
                }
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
                xuLyTep(heThong, true);
                break;
            case 11:
                xuLyTep(heThong, false);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu doc gia=====
static void menuDocGia(QuanLyThuVien& heThong){
    QuanLyDocGia& quanLy = heThong.layDocGia();
    int chon = -1;
    do{
        cout << "\n=====QUAN LY DOC GIA=====\n";
        cout << "1. Them\n2. Hien thi\n3. Tim theo ma\n4. Tim theo ho ten\n5. Sua\n6. Xoa\n";
        cout << "7. Sap xep so dang muon\n8. Chen tai vi tri k\n9. Kiem tra han muc\n";
        cout << "10. Luu tep\n11. Doc tep\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:
            case 8:{
                int k = quanLy.laySoLuong();
                if(chon == 8 && !nhapSo(cin, "Nhap vi tri k (bat dau tu 0): ", k)){
                    break;
                }
                cout << "Doc gia moi co so tai lieu dang muon bang 0.\n";
                DocGia* docGia = nhapDocGia();
                bool thanhCong = false;
                if(docGia != nullptr && docGia->laySoDangMuon() == 0){
                    thanhCong = quanLy.chen(k, docGia);
                }
                if(!thanhCong){
                    delete docGia;
                }
                baoKetQua(thanhCong);
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:{
                if(!nhapChuoi(cin, "Nhap ma doc gia: ", ma)){
                    break;
                }
                DocGia* nguoi = quanLy.timTheoMa(ma);
                if(nguoi != nullptr){
                    nguoi->xuat();
                }
                else{
                    cout << "Khong tim thay.\n";
                }
                break;
            }
            case 4:{
                string ten;
                if(nhapChuoi(cin, "Nhap ho ten hoac mot phan: ", ten)){
                    cout << "So ket qua: " << quanLy.timTheoTen(ten) << '\n';
                }
                break;
            }
            case 5:{
                if(!nhapChuoi(cin, "Nhap ma can sua: ", ma)){
                    break;
                }
                DocGia* cu = quanLy.timTheoMa(ma);
                if(cu == nullptr){
                    cout << "Khong tim thay.\n";
                    break;
                }
                cu->xuat();
                cout << "Giu nguyen ma nguoi, ma doc gia va so dang muon.\n";
                DocGia* moi = nhapDocGia(cu->layLoai());
                bool thanhCong = quanLy.sua(ma, moi);
                if(!thanhCong){
                    delete moi;
                }
                baoKetQua(thanhCong);
                break;
            }
            case 6:
                if(nhapChuoi(cin, "Nhap ma can xoa: ", ma)){
                    baoKetQua(quanLy.xoa(ma));
                }
                break;
            case 7:
                quanLy.sapXepTheoSoMuon();
                quanLy.hienThi();
                break;
            case 9:{
                int soLuong = 0;
                if(!nhapChuoi(cin, "Nhap ma doc gia: ", ma)
                   || !nhapSo(cin, "Nhap so luong muon: ", soLuong)){
                    break;
                }
                DocGia* nguoi = quanLy.timTheoMa(ma);
                baoKetQua(nguoi != nullptr && nguoi->kiemTraDieuKienMuon(soLuong));
                break;
            }
            case 10:
                xuLyTep(heThong, true);
                break;
            case 11:
                xuLyTep(heThong, false);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu nhan vien=====
static void menuNhanVien(QuanLyThuVien& heThong){
    QuanLyNhanVien& quanLy = heThong.layNhanVien();
    int chon = -1;
    do{
        cout << "\n=====QUAN LY NHAN VIEN=====\n";
        cout << "1. Them\n2. Hien thi\n3. Tim ma\n4. Tim ca lam\n5. Sua\n6. Xoa\n";
        cout << "7. Sap xep he so luong\n8. Tinh luong\n9. Luu tep\n10. Doc tep\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:{
                NhanVienThuThu nguoi;
                baoKetQua(nguoi.nhap() && quanLy.them(nguoi));
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:
            case 8:{
                if(!nhapChuoi(cin, "Nhap ma nhan vien: ", ma)){
                    break;
                }
                const NhanVienThuThu* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    cout << "Khong tim thay.\n";
                    break;
                }
                if(chon == 3){
                    nguoi->xuat();
                }
                else{
                    cout << "Luong: " << nguoi->tinhLuong() << '\n';
                }
                break;
            }
            case 4:{
                string ca;
                if(nhapChuoi(cin, "Nhap ca lam: ", ca)){
                    cout << "So ket qua: " << quanLy.timTheoCa(ca) << '\n';
                }
                break;
            }
            case 5:{
                if(!nhapChuoi(cin, "Nhap ma can sua: ", ma)){
                    break;
                }
                if(quanLy.timTheoMa(ma) == nullptr){
                    cout << "Khong tim thay.\n";
                    break;
                }
                cout << "Giu nguyen ma nguoi va ma nhan vien.\n";
                NhanVienThuThu moi;
                baoKetQua(moi.nhap() && quanLy.sua(ma, moi));
                break;
            }
            case 6:
                if(nhapChuoi(cin, "Nhap ma can xoa: ", ma)){
                    baoKetQua(quanLy.xoa(ma));
                }
                break;
            case 7:
                quanLy.sapXepTheoHeSoLuong();
                quanLy.hienThi();
                break;
            case 9:
                xuLyTep(heThong, true);
                break;
            case 10:
                xuLyTep(heThong, false);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu thu thu truong=====
static void menuThuThuTruong(QuanLyThuVien& heThong){
    QuanLyThuThuTruong& quanLy = heThong.layThuThuTruong();
    int chon = -1;
    do{
        cout << "\n=====QUAN LY THU THU TRUONG=====\n";
        cout << "1. Them\n2. Hien thi\n3. Tim ma\n4. Quan ly hon 10 nhan vien\n";
        cout << "5. Sap xep phu cap\n6. Tinh thu nhap\n7. Luu tep\n8. Doc tep\n";
        cout << "9. Xem nhat ky vi pham\n10. Duyet vi pham\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:{
                cout << "Thong tin vai tro doc gia tai day co so dang muon bang 0.\n";
                ThuThuTruong nguoi;
                baoKetQua(nguoi.nhap() && quanLy.them(nguoi));
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:
            case 6:
            case 9:
            case 10:{
                if(!nhapChuoi(cin, "Nhap ma thu thu truong: ", ma)){
                    break;
                }
                const ThuThuTruong* nguoi = quanLy.timTheoMa(ma);
                if(nguoi == nullptr){
                    cout << "Khong tim thay.\n";
                    break;
                }
                switch(chon){
                    case 3:
                        nguoi->xuat();
                        break;
                    case 6:
                        cout << "Thu nhap: " << nguoi->tinhThuNhap() << '\n';
                        break;
                    case 9:
                        nguoi->xemNhatKyViPham(heThong.layViPham());
                        break;
                    case 10:{
                        string maViPham;
                        if(nhapChuoi(cin, "Nhap ma vi pham: ", maViPham)){
                            baoKetQua(nguoi->duyetViPham(heThong.layViPham(), maViPham));
                        }
                        break;
                    }
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
            case 7:
                xuLyTep(heThong, true);
                break;
            case 8:
                xuLyTep(heThong, false);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu phieu muon tra=====
static void menuPhieuMuon(QuanLyThuVien& heThong){
    QuanLyPhieuMuon& quanLy = heThong.layPhieuMuon();
    int chon = -1;
    do{
        cout << "\n=====QUAN LY PHIEU MUON TRA=====\n";
        cout << "1. Lap phieu\n2. Tra tai lieu\n3. Hien thi\n4. Tim ma phieu\n";
        cout << "5. Phieu cua doc gia\n6. Doc gia dang muon tai lieu\n7. Phieu qua han\n";
        cout << "8. Tinh tien phat\n9. Luu tep\n10. Doc tep\n11. Sap xep ma phieu (Merge Sort)\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:{
                PhieuMuon phieu;
                baoKetQua(phieu.nhap() && quanLy.lapPhieu(phieu, heThong.layDocGia(), heThong.layTaiLieu()));
                break;
            }
            case 2:{
                string ngay;
                if(nhapChuoi(cin, "Nhap ma phieu: ", ma)
                   && nhapChuoi(cin, "Nhap ngay tra (dd/mm/yyyy): ", ngay)){
                    baoKetQua(quanLy.traTaiLieu(ma, ngay, heThong.layDocGia(),
                                               heThong.layTaiLieu(), heThong.layViPham()));
                }
                break;
            }
            case 3:
                quanLy.hienThi();
                break;
            case 4:{
                if(!nhapChuoi(cin, "Nhap ma phieu: ", ma)){
                    break;
                }
                const PhieuMuon* phieu = quanLy.timTheoMa(ma);
                if(phieu != nullptr){
                    cout << *phieu;
                }
                else{
                    cout << "Khong tim thay.\n";
                }
                break;
            }
            case 5:
                if(nhapChuoi(cin, "Nhap ma doc gia: ", ma)){
                    cout << "So phieu: " << quanLy.lietKeTheoDocGia(ma) << '\n';
                }
                break;
            case 6:
                if(nhapChuoi(cin, "Nhap ma tai lieu: ", ma)){
                    cout << "So doc gia: " << quanLy.lietKeDocGiaMuonTaiLieu(ma, heThong.layDocGia()) << '\n';
                }
                break;
            case 7:
                cout << "Ngay kiem tra: " << ngayHienTai() << '\n';
                quanLy.lietKeQuaHan(heThong.layDocGia());
                break;
            case 8:{
                string ngay;
                if(!nhapChuoi(cin, "Nhap ma phieu: ", ma)){
                    break;
                }
                const PhieuMuon* phieu = quanLy.timTheoMa(ma);
                if(phieu == nullptr){
                    cout << "Khong tim thay.\n";
                    break;
                }
                if(!phieu->dangMuon()){
                    cout << "Tien phat da ghi nhan: " << phieu->layTienPhat() << '\n';
                    break;
                }
                if(!nhapChuoi(cin, "Nhap ngay tinh phat (dd/mm/yyyy): ", ngay)){
                    break;
                }
                const TaiLieu* sach = heThong.layTaiLieu().timTheoMa(phieu->layMaTaiLieu());
                double phat = -1;
                if(sach != nullptr){
                    phat = phieu->tinhTienPhat(*sach, ngay);
                }
                if(phat < 0){
                    cout << "Ngay tinh phat hoac tai lieu khong hop le.\n";
                }
                else{
                    cout << "Tien phat du kien: " << phat << '\n';
                }
                break;
            }
            case 9:
                xuLyTep(heThong, true);
                break;
            case 10:
                xuLyTep(heThong, false);
                break;
            case 11:
                quanLy.sapXepTheoMa();
                quanLy.hienThi();
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu vi pham=====
static void menuViPham(QuanLyThuVien& heThong){
    QuanLyViPham& quanLy = heThong.layViPham();
    int chon = -1;
    do{
        cout << "\n=====QUAN LY VI PHAM=====\n";
        cout << "1. Ghi nhan tu phieu da tra qua han\n2. Hien thi\n3. Tim theo doc gia\n";
        cout << "4. Chua thanh toan\n5. Thanh toan\n6. Tong tien phat\n7. So lan vi pham\n";
        cout << "8. Luu tep\n9. Doc tep\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        string ma;
        switch(chon){
            case 1:{
                if(!nhapChuoi(cin, "Nhap ma phieu: ", ma)){
                    break;
                }
                const PhieuMuon* phieu = heThong.layPhieuMuon().timTheoMa(ma);
                if(quanLy.timTheoPhieu(ma) != nullptr){
                    cout << "Vi pham da duoc ghi khi tra tai lieu; khong ghi trung.\n";
                }
                else{
                    baoKetQua(phieu != nullptr && quanLy.ghiViPham(*phieu));
                }
                break;
            }
            case 2:
                quanLy.hienThi();
                break;
            case 3:
                if(nhapChuoi(cin, "Nhap ma doc gia: ", ma)){
                    cout << "So ket qua: " << quanLy.timTheoDocGia(ma) << '\n';
                }
                break;
            case 4:
                quanLy.lietKeChuaThanhToan();
                break;
            case 5:
                if(nhapChuoi(cin, "Nhap ma vi pham: ", ma)){
                    baoKetQua(quanLy.thanhToanPhat(ma));
                }
                break;
            case 6:
                thongKeTienPhat(heThong);
                break;
            case 7:
                if(nhapChuoi(cin, "Nhap ma doc gia: ", ma)){
                    cout << "So lan vi pham: " << quanLy.demViPham(ma) << '\n';
                }
                break;
            case 8:
                xuLyTep(heThong, true);
                break;
            case 9:
                xuLyTep(heThong, false);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu thong ke=====
static void menuThongKe(QuanLyThuVien& heThong){
    int chon = -1;
    do{
        cout << "\n=====THONG KE VA BAO CAO=====\n";
        cout << "1. Tai lieu theo loai\n2. So dang muon va con kho\n3. Doc gia muon nhieu nhat\n";
        cout << "4. Tai lieu duoc muon nhieu nhat\n5. Phieu qua han\n6. Tien phat\n";
        cout << "7. Thuc nghiem 4 kich thuoc\n0. Quay lai\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        switch(chon){
            case 1:
                heThong.layTaiLieu().thongKe();
                break;
            case 2:
                thongKeTonKho(heThong);
                break;
            case 3:
                thongKeDocGiaMuonNhieuNhat(heThong);
                break;
            case 4:
                thongKeTaiLieuMuonNhieuNhat(heThong);
                break;
            case 5:
                heThong.layPhieuMuon().lietKeQuaHan(heThong.layDocGia());
                break;
            case 6:
                thongKeTienPhat(heThong);
                break;
            case 7:{
                ofstream tep("ket_qua_thuc_nghiem.csv");
                bool thanhCong = false;
                if(tep){
                    thanhCong = thucNghiem(tep);
                    tep.close();
                    thanhCong = thanhCong && static_cast<bool>(tep);
                }
                baoKetQua(thanhCong);
                if(thanhCong){
                    cout << "Ket qua tai ket_qua_thuc_nghiem.csv; don vi micro giay.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}

//=====menu chinh=====
void menuChinh(){
    QuanLyThuVien heThong;
    int chon = -1;
    cout << "Luu/doc trong cac menu se dong bo toan he thong tai thu muc data.\n";
    do{
        cout << "\n=====QUAN LY THU VIEN DAI HOC=====\n";
        cout << "1. Quan ly tai lieu\n2. Quan ly doc gia\n3. Quan ly nhan vien\n";
        cout << "4. Quan ly thu thu truong\n5. Quan ly phieu muon tra\n";
        cout << "6. Quan ly vi pham va tien phat\n7. Thong ke va bao cao\n0. Thoat\n";
        if(!nhapSo(cin, "Chon: ", chon)){
            return;
        }
        switch(chon){
            case 1:
                menuTaiLieu(heThong);
                break;
            case 2:
                menuDocGia(heThong);
                break;
            case 3:
                menuNhanVien(heThong);
                break;
            case 4:
                menuThuThuTruong(heThong);
                break;
            case 5:
                menuPhieuMuon(heThong);
                break;
            case 6:
                menuViPham(heThong);
                break;
            case 7:
                menuThongKe(heThong);
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}
