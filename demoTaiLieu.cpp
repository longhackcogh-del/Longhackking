#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "NhapXuat.h"
#include <filesystem>
#include <system_error>

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

//=====ham doc ghi tep tai lieu=====
static void xuLyTep(QuanLyTaiLieu& quanLy, bool ghi){
    string loi;
    bool thanhCong = false;
    if(ghi){
        std::error_code maLoi;
        std::filesystem::create_directories("data", maLoi);
        if(maLoi){
            cout << "Khong tao duoc thu muc data: " << maLoi.message() << '\n';
            return;
        }
        thanhCong = quanLy.luu("data", loi);
    }
    else{
        thanhCong = quanLy.doc("data", loi);
    }
    if(thanhCong){
        cout << "Thao tac file thanh cong tai thu muc data.\n";
    }
    else{
        cout << "Thao tac file that bai: " << loi << '\n';
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

//=====menu tai lieu=====
void menuTaiLieu(){
    QuanLyTaiLieu quanLy;
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
                    int soKetQua = quanLy.timTheoTen(ten);
                    cout << "So ket qua: " << soKetQua << '\n';
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
                xuLyTep(quanLy, true);
                break;
            case 11:
                xuLyTep(quanLy, false);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }while(chon != 0 && !cin.eof());
}


int main(){
    menuTaiLieu();
    return 0;
}
