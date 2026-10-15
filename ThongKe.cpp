#include "ThongKe.h"

//=====ham thong ke ton kho=====
void thongKeTonKho(const QuanLyThuVien& heThong){
    heThong.layTaiLieu().thongKe();
    const QuanLyDocGia& docGia = heThong.layDocGia();
    long long tongMuon = 0;
    int i = 0;
    while(i + 1 < docGia.laySoLuong()){
        tongMuon += *docGia.layDocGia(i) + *docGia.layDocGia(i + 1);
        i += 2;
    }
    if(i < docGia.laySoLuong()){
        tongMuon += docGia.layDocGia(i)->laySoDangMuon();
    }
    std::cout << "Tong so tai lieu doc gia dang muon: " << tongMuon << '\n';
}

//=====ham tim doc gia muon nhieu nhat=====
void thongKeDocGiaMuonNhieuNhat(const QuanLyThuVien& heThong){
    const QuanLyDocGia& quanLy = heThong.layDocGia();
    if(quanLy.laySoLuong() == 0){
        std::cout << "Danh sach doc gia rong\n";
        return;
    }
    int nhieuNhat = 0;
    int itNhat = quanLy.layDocGia(0)->laySoDangMuon();
    for(int i = 0; i < quanLy.laySoLuong(); i++){
        int soMuon = quanLy.layDocGia(i)->laySoDangMuon();
        nhieuNhat = timMax(nhieuNhat, soMuon);
        itNhat = timMin(itNhat, soMuon);
    }
    std::cout << "So dang muon nhieu nhat: " << nhieuNhat << '\n';
    std::cout << "So dang muon it nhat: " << itNhat << '\n';
    for(int i = 0; i < quanLy.laySoLuong(); i++){
        if(quanLy.layDocGia(i)->laySoDangMuon() == nhieuNhat){
            quanLy.layDocGia(i)->xuat();
        }
    }
}

//=====ham tim tai lieu duoc muon nhieu nhat=====
void thongKeTaiLieuMuonNhieuNhat(const QuanLyThuVien& heThong){
    const QuanLyTaiLieu& quanLy = heThong.layTaiLieu();
    const QuanLyPhieuMuon& phieu = heThong.layPhieuMuon();
    long long nhieuNhat = 0;
    if(quanLy.laySoLuong() == 0){
        std::cout << "Danh sach tai lieu rong\n";
        return;
    }
    for(int i = 0; i < quanLy.laySoLuong(); i++){
        nhieuNhat = timMax(nhieuNhat, phieu.demLuotMuonTaiLieu(quanLy.layTaiLieu(i)->layMa()));
    }
    std::cout << "Tong so ban duoc muon nhieu nhat: " << nhieuNhat << '\n';
    for(int i = 0; i < quanLy.laySoLuong(); i++){
        const TaiLieu* sach = quanLy.layTaiLieu(i);
        if(phieu.demLuotMuonTaiLieu(sach->layMa()) == nhieuNhat){
            sach->xuat();
        }
    }
}

//=====ham thong ke tien phat=====
void thongKeTienPhat(const QuanLyThuVien& heThong){
    const QuanLyViPham& quanLy = heThong.layViPham();
    std::cout << "Tien phat da thu: " << quanLy.tinhTongTienPhatDaThanhToan() << '\n';
    std::cout << "Tien phat chua thu: " << quanLy.tinhTongTienPhatChuaThanhToan() << '\n';
    std::cout << "Tong tien phat: " << quanLy.tinhTongTienPhatDaThanhToan()
        + quanLy.tinhTongTienPhatChuaThanhToan() << '\n';
}
