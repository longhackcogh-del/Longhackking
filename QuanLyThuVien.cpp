#include "QuanLyThuVien.h"
#include <sstream>

//=====ham khoi tao=====
QuanLyThuVien::QuanLyThuVien(){
    taiLieu.ganQuanLyPhieuMuon(&phieuMuon);
    docGia.ganQuanLyPhieuMuon(&phieuMuon);
}

QuanLyTaiLieu& QuanLyThuVien::layTaiLieu(){
    return taiLieu;
}

QuanLyDocGia& QuanLyThuVien::layDocGia(){
    return docGia;
}

QuanLyNhanVien& QuanLyThuVien::layNhanVien(){
    return nhanVien;
}

QuanLyThuThuTruong& QuanLyThuVien::layThuThuTruong(){
    return thuThuTruong;
}

QuanLyPhieuMuon& QuanLyThuVien::layPhieuMuon(){
    return phieuMuon;
}

QuanLyViPham& QuanLyThuVien::layViPham(){
    return viPham;
}

//=====ham tim nhan su theo ma nguoi=====
const NhanVienThuThu* QuanLyThuVien::timNhanVienTheoNguoi(const std::string& ma) const{
    for(int i = 0; i < nhanVien.laySoLuong(); i++){
        if(nhanVien.lay(i)->layMaNguoi() == ma){
            return nhanVien.lay(i);
        }
    }
    return nullptr;
}

const ThuThuTruong* QuanLyThuVien::timThuThuTheoNguoi(const std::string& ma) const{
    for(int i = 0; i < thuThuTruong.laySoLuong(); i++){
        if(thuThuTruong.lay(i)->layMaNguoi() == ma){
            return thuThuTruong.lay(i);
        }
    }
    return nullptr;
}

//=====ham kiem tra va dong bo thong tin mot nguoi=====
bool QuanLyThuVien::nhanThanKhop(const Nguoi& nguoi) const{
    for(int i = 0; i < docGia.laySoLuong(); i++){
        const DocGia* cu = docGia.layDocGia(i);
        if(cu->layMaNguoi() == nguoi.layMaNguoi() && !cu->cungThongTinCaNhan(nguoi)){
            return false;
        }
    }
    const NhanVienThuThu* nv = timNhanVienTheoNguoi(nguoi.layMaNguoi());
    const ThuThuTruong* tt = timThuThuTheoNguoi(nguoi.layMaNguoi());
    if(nv != nullptr && !nv->cungThongTinCaNhan(nguoi)){
        return false;
    }
    if(tt != nullptr && !tt->cungThongTinCaNhan(nguoi)){
        return false;
    }
    return true;
}

void QuanLyThuVien::dongBoNhanThan(const Nguoi& nguoi){
    // Chi chep phan Nguoi, khong doi cac ma vai tro va so dang muon.
    Nguoi nhanThan = nguoi;
    for(int i = 0; i < docGia.laySoLuong(); i++){
        DocGia* cu = docGia.layDocGia(i);
        if(cu->layMaNguoi() == nhanThan.layMaNguoi()){
            static_cast<Nguoi&>(*cu) = nhanThan;
        }
    }
    const NhanVienThuThu* nv = timNhanVienTheoNguoi(nhanThan.layMaNguoi());
    if(nv != nullptr){
        static_cast<Nguoi&>(*nhanVien.timTheoMa(nv->layMa())) = nhanThan;
    }
    const ThuThuTruong* tt = timThuThuTheoNguoi(nhanThan.layMaNguoi());
    if(tt != nullptr){
        static_cast<Nguoi&>(*thuThuTruong.timTheoMa(tt->layMa())) = nhanThan;
    }
}

bool QuanLyThuVien::maNhanVienDaDuyet(const std::string& ma) const{
    for(int i = 0; i < viPham.laySoLuong(); i++){
        if(viPham.lay(i)->layNguoiDuyet() == ma){
            return true;
        }
    }
    return false;
}

//=====ham quan ly nhan vien=====
bool QuanLyThuVien::themNhanVien(const NhanVienThuThu& moi){
    if(!moi.hopLe() || !nhanThanKhop(moi) || thuThuTruong.timTheoMa(moi.layMa()) != nullptr
       || timThuThuTheoNguoi(moi.layMaNguoi()) != nullptr || maNhanVienDaDuyet(moi.layMa())){
        return false;
    }
    return nhanVien.them(moi);
}

bool QuanLyThuVien::suaNhanVien(const std::string& ma, const NhanVienThuThu& moi){
    const NhanVienThuThu* cu = nhanVien.timTheoMa(ma);
    if(cu == nullptr || !moi.hopLe() || moi.layMa() != ma || moi.layMaNguoi() != cu->layMaNguoi()
       || !nhanThanKhop(*cu) || thuThuTruong.timTheoMa(ma) != nullptr
       || timThuThuTheoNguoi(cu->layMaNguoi()) != nullptr){
        return false;
    }
    if(!nhanVien.sua(ma, moi)){
        return false;
    }
    dongBoNhanThan(moi);
    return true;
}

bool QuanLyThuVien::xoaNhanVien(const std::string& ma){
    const NhanVienThuThu* cu = nhanVien.timTheoMa(ma);
    if(cu == nullptr || !nhanThanKhop(*cu) || thuThuTruong.timTheoMa(ma) != nullptr
       || timThuThuTheoNguoi(cu->layMaNguoi()) != nullptr){
        return false;
    }
    // Doc gia va cac ledger khong bi xoa theo ho so nhan su.
    return nhanVien.xoa(ma);
}

//=====ham them=====
bool QuanLyThuVien::themTaiLieu(TaiLieu* moi){
    // Nhap moi khong duoc tao so dang muon thieu phieu.
    if(moi == nullptr || moi->laySoLuongCon() != moi->laySoLuongTong()){
        return false;
    }
    return taiLieu.them(moi);
}

bool QuanLyThuVien::themDocGia(DocGia* moi, int viTri){
    if(moi == nullptr || moi->laySoDangMuon() != 0 || !nhanThanKhop(*moi)){
        return false;
    }
    return docGia.chen(viTri, moi);
}

//=====ham tim vai tro doc gia=====
ThuThuTruong* QuanLyThuVien::timThuThuTheoDocGia(const std::string& ma){
    for(int i = 0; i < thuThuTruong.laySoLuong(); i++){
        const ThuThuTruong* nguoi = thuThuTruong.lay(i);
        if(nguoi->DocGia::layMa() == ma){
            return thuThuTruong.timTheoMa(nguoi->layMa());
        }
    }
    return nullptr;
}

//=====ham sua va xoa doc gia=====
bool QuanLyThuVien::suaDocGia(const std::string& ma, DocGia* moi){
    // Ho so lien ket duoc sua tu menu thu thu truong de dong bo hai vai tro.
    const DocGia* cu = docGia.timTheoMa(ma);
    if(cu == nullptr || !nhanThanKhop(*cu) || timThuThuTheoDocGia(ma) != nullptr){
        return false;
    }
    if(!docGia.sua(ma, moi)){
        return false;
    }
    dongBoNhanThan(*moi);
    return true;
}

bool QuanLyThuVien::xoaDocGia(const std::string& ma){
    if(timThuThuTheoDocGia(ma) != nullptr){
        return false;
    }
    return docGia.xoa(ma);
}

//=====ham kiem tra vai tro doc gia truoc khi chuyen=====
bool QuanLyThuVien::kiemTraDocGiaThuThu(const ThuThuTruong& moi) const{
    if(!moi.hopLe() || !nhanThanKhop(moi)){
        return false;
    }
    const DocGia* cu = docGia.timTheoMa(moi.DocGia::layMa());
    if(cu != nullptr){
        const GiangVien* vaiTro = dynamic_cast<const GiangVien*>(cu);
        if(vaiTro == nullptr){
            return false;
        }
        // Chi lien ket ho so co cung day du thong tin, khong ghi de ho so cu.
        std::ostringstream a;
        std::ostringstream b;
        vaiTro->GiangVien::ghi(a);
        moi.GiangVien::ghi(b);
        if(a.str() != b.str()){
            return false;
        }
        return phieuMuon.demDangMuonDocGia(moi.DocGia::layMa()) == moi.laySoDangMuon();
    }
    if(moi.laySoDangMuon() != 0 || phieuMuon.coThamChieuDocGia(moi.DocGia::layMa())){
        return false;
    }
    for(int i = 0; i < docGia.laySoLuong(); i++){
        if(docGia.layDocGia(i)->layMaNguoi() == moi.layMaNguoi()){
            return false;
        }
    }
    return true;
}

//=====ham them ho so va vai tro doc gia=====
bool QuanLyThuVien::themHoSoThuThu(const ThuThuTruong& moi){
    if(!kiemTraDocGiaThuThu(moi) || thuThuTruong.timTheoMa(moi.layMa()) != nullptr
       || timThuThuTheoNguoi(moi.layMaNguoi()) != nullptr){
        return false;
    }
    if(docGia.timTheoMa(moi.DocGia::layMa()) != nullptr){
        return thuThuTruong.them(moi);
    }
    // Sao chep dung phan GiangVien, khong dua ThuThuTruong* vao tep GiangVien.
    GiangVien* vaiTro = new GiangVien(static_cast<const GiangVien&>(moi));
    if(!thuThuTruong.them(moi)){
        delete vaiTro;
        return false;
    }
    if(!docGia.them(vaiTro)){
        thuThuTruong.xoa(moi.layMa());
        delete vaiTro;
        return false;
    }
    return true;
}

//=====ham them thu thu truong=====
bool QuanLyThuVien::themThuThuTruong(const ThuThuTruong& moi){
    if(nhanVien.timTheoMa(moi.layMa()) != nullptr || timNhanVienTheoNguoi(moi.layMaNguoi()) != nullptr
       || maNhanVienDaDuyet(moi.layMa())){
        return false;
    }
    return themHoSoThuThu(moi);
}

//=====ham chuyen nhan vien thanh thu thu truong=====
bool QuanLyThuVien::chuyenThanhThuThuTruong(const std::string& ma, const ThuThuTruong& moi){
    const NhanVienThuThu* cu = nhanVien.timTheoMa(ma);
    if(cu == nullptr || moi.layMa() != ma || !cu->cungThongTinCaNhan(moi)){
        return false;
    }
    // Giu ca thong tin nhan vien; chi bo sung phan GiangVien va quan ly.
    std::ostringstream a;
    std::ostringstream b;
    cu->NhanVienThuThu::ghi(a);
    moi.NhanVienThuThu::ghi(b);
    if(a.str() != b.str() || !kiemTraDocGiaThuThu(moi)){
        return false;
    }
    bool daCoDocGia = docGia.timTheoMa(moi.DocGia::layMa()) != nullptr;
    if(!themHoSoThuThu(moi)){
        return false;
    }
    if(!nhanVien.xoa(ma)){
        thuThuTruong.xoa(ma);
        if(!daCoDocGia){
            docGia.xoa(moi.DocGia::layMa());
        }
        return false;
    }
    return true;
}

//=====ham chuyen thu thu truong ve nhan vien=====
bool QuanLyThuVien::chuyenThanhNhanVien(const std::string& ma){
    const ThuThuTruong* cu = thuThuTruong.timTheoMa(ma);
    if(cu == nullptr || nhanVien.timTheoMa(ma) != nullptr
       || timNhanVienTheoNguoi(cu->layMaNguoi()) != nullptr
       || docGia.timTheoMa(cu->DocGia::layMa()) == nullptr || !kiemTraDocGiaThuThu(*cu)){
        return false;
    }
    NhanVienThuThu moi = static_cast<const NhanVienThuThu&>(*cu);
    if(!nhanVien.them(moi)){
        return false;
    }
    if(!thuThuTruong.xoa(ma)){
        nhanVien.xoa(ma);
        return false;
    }
    return true;
}

//=====ham sua va xoa thu thu truong=====
bool QuanLyThuVien::suaThuThuTruong(const std::string& ma, const ThuThuTruong& moi){
    const ThuThuTruong* cu = thuThuTruong.timTheoMa(ma);
    if(cu == nullptr || docGia.timTheoMa(cu->DocGia::layMa()) == nullptr
       || !kiemTraDocGiaThuThu(*cu) || nhanVien.timTheoMa(ma) != nullptr
       || timNhanVienTheoNguoi(cu->layMaNguoi()) != nullptr){
        return false;
    }
    GiangVien* vaiTro = dynamic_cast<GiangVien*>(docGia.timTheoMa(cu->DocGia::layMa()));
    if(vaiTro == nullptr || !thuThuTruong.sua(ma, moi)){
        return false;
    }
    *vaiTro = static_cast<const GiangVien&>(moi);
    dongBoNhanThan(moi);
    return true;
}

bool QuanLyThuVien::xoaThuThuTruong(const std::string& ma){
    const ThuThuTruong* cu = thuThuTruong.timTheoMa(ma);
    if(cu == nullptr || docGia.timTheoMa(cu->DocGia::layMa()) == nullptr
       || !kiemTraDocGiaThuThu(*cu) || nhanVien.timTheoMa(ma) != nullptr
       || timNhanVienTheoNguoi(cu->layMaNguoi()) != nullptr){
        return false;
    }
    // Chi bo vai tro nhan su; giu doc gia va lich su muon, duyet vi pham.
    return thuThuTruong.xoa(ma);
}

//=====ham dong bo so dang muon=====
void QuanLyThuVien::dongBoSoMuon(const std::string& ma){
    ThuThuTruong* nguoi = timThuThuTheoDocGia(ma);
    if(nguoi != nullptr){
        const GiangVien* vaiTro = dynamic_cast<const GiangVien*>(docGia.timTheoMa(ma));
        if(vaiTro != nullptr){
            static_cast<GiangVien&>(*nguoi) = *vaiTro;
        }
    }
}

//=====ham muon tra=====
bool QuanLyThuVien::lapPhieu(const PhieuMuon& phieu){
    if(!phieuMuon.lapPhieu(phieu, docGia, taiLieu)){
        return false;
    }
    dongBoSoMuon(phieu.layMaDocGia());
    return true;
}

bool QuanLyThuVien::traTaiLieu(const std::string& ma, const std::string& ngay){
    const PhieuMuon* phieu = phieuMuon.timTheoMa(ma);
    if(phieu == nullptr){
        return false;
    }
    std::string maDocGia = phieu->layMaDocGia();
    if(!phieuMuon.traTaiLieu(ma, ngay, docGia, taiLieu, viPham)){
        return false;
    }
    dongBoSoMuon(maDocGia);
    return true;
}

//=====ham ghi va duyet vi pham=====
bool QuanLyThuVien::ghiViPham(const std::string& maPhieu){
    const PhieuMuon* phieu = phieuMuon.timTheoMa(maPhieu);
    if(phieu == nullptr){
        return false;
    }
    return viPham.ghiViPham(*phieu);
}

bool QuanLyThuVien::duyetViPham(const std::string& ma, const std::string& maThuThu){
    const ThuThuTruong* nguoi = thuThuTruong.timTheoMa(maThuThu);
    if(nguoi == nullptr || docGia.timTheoMa(nguoi->DocGia::layMa()) == nullptr
       || !kiemTraDocGiaThuThu(*nguoi)
       || nhanVien.timTheoMa(maThuThu) != nullptr
       || timNhanVienTheoNguoi(nguoi->layMaNguoi()) != nullptr){
        return false;
    }
    return nguoi->duyetViPham(viPham, ma);
}
