#include "QuanLyThuVien.h"
#include <filesystem>
#include <system_error>
QuanLyTaiLieu& QuanLyThuVien::layTaiLieu(){
    return taiLieu;
}

const QuanLyTaiLieu& QuanLyThuVien::layTaiLieu() const{
    return taiLieu;
}

QuanLyDocGia& QuanLyThuVien::layDocGia(){
    return docGia;
}

const QuanLyDocGia& QuanLyThuVien::layDocGia() const{
    return docGia;
}

QuanLyNhanVien& QuanLyThuVien::layNhanVien(){
    return nhanVien;
}

const QuanLyNhanVien& QuanLyThuVien::layNhanVien() const{
    return nhanVien;
}

QuanLyThuThuTruong& QuanLyThuVien::layThuThuTruong(){
    return thuThuTruong;
}

const QuanLyThuThuTruong& QuanLyThuVien::layThuThuTruong() const{
    return thuThuTruong;
}

QuanLyPhieuMuon& QuanLyThuVien::layPhieuMuon(){
    return phieuMuon;
}

const QuanLyPhieuMuon& QuanLyThuVien::layPhieuMuon() const{
    return phieuMuon;
}

QuanLyViPham& QuanLyThuVien::layViPham(){
    return viPham;
}

const QuanLyViPham& QuanLyThuVien::layViPham() const{
    return viPham;
}

//=====ham khoi tao=====
QuanLyThuVien::QuanLyThuVien(){
    taiLieu.ganQuanLyPhieuMuon(&phieuMuon);
    docGia.ganQuanLyPhieuMuon(&phieuMuon);
}

//=====ham kiem tra nhat quan=====
bool QuanLyThuVien::kiemTraNhatQuan(std::string& loi) const{
    loi.clear();
    for(int i = 0; i < taiLieu.laySoLuong(); i++){
        const TaiLieu* sach = taiLieu.layTaiLieu(i);
        if(!sach->hopLe() || phieuMuon.demDangMuonTaiLieu(sach->layMa())
           != static_cast<long long>(sach->laySoLuongTong()) - sach->laySoLuongCon()){
            loi = "Ton kho khong khop phieu: " + sach->layMa();
            return false;
        }
    }
    for(int i = 0; i < docGia.laySoLuong(); i++){
        const DocGia* nguoi = docGia.layDocGia(i);
        if(!nguoi->hopLe() || phieuMuon.demDangMuonDocGia(nguoi->layMa()) != nguoi->laySoDangMuon()){
            loi = "So dang muon khong khop phieu: " + nguoi->layMa();
            return false;
        }
    }
    for(int i = 0; i < phieuMuon.laySoLuong(); i++){
        const PhieuMuon* phieu = phieuMuon.lay(i);
        const TaiLieu* sach = taiLieu.timTheoMa(phieu->layMaTaiLieu());
        const DocGia* nguoi = docGia.timTheoMa(phieu->layMaDocGia());
        if(!phieu->hopLe() || (phieu->dangMuon() && (sach == nullptr || nguoi == nullptr))){
            loi = "Phieu thieu ma lien quan: " + phieu->layMa();
            return false;
        }
        const NhatKyViPham* nhatKy = viPham.timTheoPhieu(phieu->layMa());
        if(!phieu->dangMuon()){
            int soNgayTre = phieu->tinhSoNgayTre(phieu->layNgayTra());
            if((soNgayTre == 0 && phieu->layTienPhat() != 0)
               || (soNgayTre > 0 && phieu->layTienPhat() <= 0)){
                loi = "Tien phat khong khop ngay tra: " + phieu->layMa();
                return false;
            }
            if(sach != nullptr && phieu->layTienPhat() != phieu->tinhTienPhat(*sach, phieu->layNgayTra())){
                loi = "Tien phat khong khop loai tai lieu: " + phieu->layMa();
                return false;
            }
        }
        if(phieu->layTienPhat() > 0 && nhatKy == nullptr){
            loi = "Thieu nhat ky vi pham: " + phieu->layMa();
            return false;
        }
        if(nhatKy != nullptr){
            if(phieu->dangMuon() || nhatKy->layMaDocGia() != phieu->layMaDocGia()
               || nhatKy->layTienPhat() != phieu->layTienPhat()
               || nhatKy->laySoNgayTre() != phieu->tinhSoNgayTre(phieu->layNgayTra())){
                loi = "Vi pham khong khop phieu: " + phieu->layMa();
                return false;
            }
        }
    }
    for(int i = 0; i < viPham.laySoLuong(); i++){
        const NhatKyViPham* nhatKy = viPham.lay(i);
        if(!nhatKy->hopLe() || phieuMuon.timTheoMa(nhatKy->layMaPhieu()) == nullptr){
            loi = "Vi pham thieu phieu: " + nhatKy->layMa();
            return false;
        }
        if(nhatKy->layNguoiDuyet() != "-" && thuThuTruong.timTheoMa(nhatKy->layNguoiDuyet()) == nullptr){
            loi = "Vi pham thieu nguoi duyet: " + nhatKy->layMa();
            return false;
        }
    }
    return true;
}

//=====ham luu toan he thong=====
bool QuanLyThuVien::luu(const std::string& thuMuc, std::string& loi) const{
    if(!kiemTraNhatQuan(loi)){
        return false;
    }
    std::error_code maLoi;
    std::filesystem::create_directories(thuMuc, maLoi);
    if(maLoi){
        loi = "Khong tao duoc thu muc du lieu: " + maLoi.message();
        return false;
    }
    std::filesystem::path goc(thuMuc);
    std::filesystem::path tam = goc / ".dang_luu";
    if(!std::filesystem::create_directory(tam, maLoi) || maLoi){
        loi = "Khong tao duoc thu muc tam .dang_luu; kiem tra lan luu truoc";
        return false;
    }
    std::string ten[] = {"Sach", "TapChi", "Bao", "SinhVien", "GiangVien",
                        "NhanVienThuThu", "ThuThuTruong", "PhieuMuon", "NhatKyViPham"};
    bool ghiDuoc = taiLieu.luu(tam.string(), loi)
        && docGia.luu(tam.string(), loi) && nhanVien.luu(tam.string(), loi)
        && thuThuTruong.luu(tam.string(), loi) && phieuMuon.luu(tam.string(), loi)
        && viPham.luu(tam.string(), loi);
    bool coBanCu[9] = {};
    int soDaChuyen = 0;
    if(ghiDuoc){
        for(int i = 0; i < 9; i++){
            std::filesystem::path dich = goc / (ten[i] + ".txt");
            bool tonTai = std::filesystem::exists(dich, maLoi);
            if(maLoi || (tonTai && !std::filesystem::is_regular_file(dich, maLoi))){
                loi = "Duong dan tep khong hop le: " + ten[i];
                ghiDuoc = false;
                break;
            }
            if(tonTai){
                std::filesystem::rename(dich, tam / (ten[i] + ".bak"), maLoi);
                if(maLoi){
                    loi = "Khong sao luu tep cu: " + ten[i];
                    ghiDuoc = false;
                    break;
                }
                coBanCu[i] = true;
            }
            std::filesystem::rename(tam / (ten[i] + ".txt"), dich, maLoi);
            if(maLoi){
                loi = "Khong thay duoc tep: " + ten[i];
                ghiDuoc = false;
                break;
            }
            soDaChuyen++;
        }
    }
    if(!ghiDuoc){
        for(int i = 0; i < 9; i++){
            if(i < soDaChuyen){
                std::filesystem::remove(goc / (ten[i] + ".txt"), maLoi);
                if(maLoi){
                    loi += "; khong go duoc tep moi, giu ban cu tai .dang_luu";
                    return false;
                }
            }
            if(coBanCu[i]){
                std::filesystem::rename(tam / (ten[i] + ".bak"), goc / (ten[i] + ".txt"), maLoi);
                if(maLoi){
                    loi += "; khong khoi phuc duoc ban cu, giu tai .dang_luu";
                    return false;
                }
            }
        }
    }
    for(int i = 0; i < 9; i++){
        std::filesystem::remove(tam / (ten[i] + ".txt"), maLoi);
        if(maLoi){
            loi += "; khong don duoc tep tam";
            return false;
        }
        std::filesystem::remove(tam / (ten[i] + ".bak"), maLoi);
        if(maLoi){
            loi += "; khong don duoc ban sao";
            return false;
        }
    }
    std::filesystem::remove(tam, maLoi);
    if(maLoi){
        loi += "; khong don duoc thu muc tam";
        return false;
    }
    return ghiDuoc;
}

//=====ham doc toan he thong=====
bool QuanLyThuVien::doc(const std::string& thuMuc, std::string& loi){
    QuanLyThuVien tam;
    if(!tam.taiLieu.doc(thuMuc, loi) || !tam.docGia.doc(thuMuc, loi)
       || !tam.nhanVien.doc(thuMuc, loi) || !tam.thuThuTruong.doc(thuMuc, loi)
       || !tam.phieuMuon.doc(thuMuc, loi) || !tam.viPham.doc(thuMuc, loi)){
        return false;
    }
    if(!tam.kiemTraNhatQuan(loi)){
        return false;
    }
    taiLieu.doi(tam.taiLieu);
    docGia.doi(tam.docGia);
    nhanVien.doi(tam.nhanVien);
    thuThuTruong.doi(tam.thuThuTruong);
    phieuMuon.doi(tam.phieuMuon);
    viPham.doi(tam.viPham);
    return true;
}
