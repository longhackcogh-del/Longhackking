#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"

#include <filesystem>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::string nhapChuoi(const std::string& loiNhac)
{
    std::cout << loiNhac;
    std::string chuoi;
    if (!std::getline(std::cin, chuoi))
    {
        throw std::runtime_error("Ket thuc nhap du lieu.");
    }
    return chuoi;
}

template<class T>
T nhapSo(const std::string& loiNhac)
{
    while (true)
    {
        std::string chuoi = nhapChuoi(loiNhac);
        std::istringstream luong(chuoi);
        T so;
        if (luong >> so)
        {
            luong >> std::ws;
            if (luong.eof())
            {
                return so;
            }
        }
        std::cout << "Nhap sai dinh dang so. Vui long nhap lai.\n";
    }
}

std::unique_ptr<TaiLieu> nhapTaiLieu(
    const std::string& loai,
    const std::string& maCu = ""
)
{
    std::string ma;
    if (maCu.empty())
    {
        ma = nhapChuoi("Nhap ma tai lieu: ");
    }
    else
    {
        ma = maCu;
        std::cout << "Ma tai lieu giu nguyen: " << ma << '\n';
    }

    std::string ten = nhapChuoi("Nhap ten tai lieu: ");
    std::string nxb = nhapChuoi("Nhap nha xuat ban: ");
    int nam = nhapSo<int>("Nhap nam xuat ban: ");
    int tong = nhapSo<int>("Nhap tong so luong: ");
    int con = nhapSo<int>("Nhap so luong con: ");
    double gia = nhapSo<double>("Nhap gia tri (dong): ");

    // Tao luong nhap dung dinh dang cu, giu nguyen kiem tra trong cac lop.
    std::ostringstream duLieu;
    duLieu << std::quoted(ma) << ' ';
    duLieu << std::quoted(ten) << ' ';
    duLieu << std::quoted(nxb) << ' ';
    duLieu << nam << ' ';
    duLieu << tong << ' ';
    duLieu << con << ' ';
    duLieu << std::setprecision(17) << gia << ' ';

    std::unique_ptr<TaiLieu> taiLieu;
    if (loai == "Sach")
    {
        std::string tacGia = nhapChuoi("Nhap tac gia: ");
        std::string theLoai = nhapChuoi("Nhap the loai: ");
        std::string isbn = nhapChuoi("Nhap ISBN: ");
        int soTrang = nhapSo<int>("Nhap so trang: ");
        duLieu << std::quoted(tacGia) << ' ';
        duLieu << std::quoted(theLoai) << ' ';
        duLieu << std::quoted(isbn) << ' ';
        duLieu << soTrang;
        taiLieu.reset(new Sach);
    }
    else if (loai == "TapChi")
    {
        int soPhatHanh = nhapSo<int>("Nhap so phat hanh: ");
        int thang = nhapSo<int>("Nhap thang phat hanh (1-12): ");
        std::string linhVuc = nhapChuoi("Nhap linh vuc: ");
        duLieu << soPhatHanh << ' ';
        duLieu << thang << ' ';
        duLieu << std::quoted(linhVuc);
        taiLieu.reset(new TapChi);
    }
    else if (loai == "Bao")
    {
        std::string ngay = nhapChuoi("Nhap ngay phat hanh (dd/mm/yyyy): ");
        std::string loaiBao = nhapChuoi("Nhap loai bao: ");
        duLieu << std::quoted(ngay) << ' ';
        duLieu << std::quoted(loaiBao);
        taiLieu.reset(new Bao);
    }
    else
    {
        throw std::invalid_argument("Loai tai lieu khong hop le.");
    }

    std::istringstream luong(duLieu.str());
    taiLieu->nhap(luong);
    return taiLieu;
}

void hienThiMenu()
{
    std::cout << "\n==================================\n";
    std::cout << "       QUAN LY TAI LIEU\n";
    std::cout << "==================================\n";
    std::cout << "1. Them sach\n";
    std::cout << "2. Them tap chi\n";
    std::cout << "3. Them bao\n";
    std::cout << "4. Hien thi danh sach\n";
    std::cout << "5. Tim kiem tai lieu\n";
    std::cout << "6. Sua thong tin\n";
    std::cout << "7. Xoa tai lieu\n";
    std::cout << "8. Sap xep tai lieu\n";
    std::cout << "9. Thong ke\n";
    std::cout << "10. Luu file\n";
    std::cout << "11. Doc file\n";
    std::cout << "0. Thoat\n";
    std::cout << "==================================\n";
    std::cout << "Nhap lua chon: ";
}

void timKiem(QuanLyTaiLieu& quanLy)
{
    std::cout << "\n1. Tim theo ma\n2. Tim theo ten\n0. Quay lai\n";
    std::string chon = nhapChuoi("Nhap lua chon tim kiem: ");
    if (chon == "0")
    {
        return;
    }
    if (chon == "1")
    {
        std::string ma = nhapChuoi("Nhap ma tai lieu can tim: ");
        TaiLieu* taiLieu = quanLy.timTheoMa(ma);
        if (taiLieu == nullptr)
        {
            std::cout << "Khong tim thay tai lieu.\n";
            return;
        }
        taiLieu->xuat();
        std::cout << "Tim kiem thanh cong.\n";
    }
    else if (chon == "2")
    {
        std::string ten = nhapChuoi("Nhap ten hoac mot phan ten (phan biet hoa thuong): ");
        int soKetQua = quanLy.timTheoTen(ten);
        if (soKetQua == 0)
        {
            std::cout << "Khong tim thay tai lieu.\n";
        }
        else
        {
            std::cout << "Tim thay " << soKetQua << " tai lieu.\n";
        }
    }
    else
    {
        std::cout << "Lua chon tim kiem khong hop le.\n";
    }
}

void sapXep(QuanLyTaiLieu& quanLy)
{
    std::cout << "\n1. Theo nam xuat ban tang dan\n2. Theo gia tri tang dan\n0. Quay lai\n";
    std::string chon = nhapChuoi("Nhap lua chon sap xep: ");
    if (chon == "0")
    {
        return;
    }
    if (chon == "1")
    {
        quanLy.sapXepTheoNam();
    }
    else if (chon == "2")
    {
        quanLy.sapXepTheoGiaTri();
    }
    else
    {
        std::cout << "Lua chon sap xep khong hop le.\n";
        return;
    }
    quanLy.hienThi();
    std::cout << "Sap xep thanh cong.\n";
}

void xuLyLuaChon(QuanLyTaiLieu& quanLy, const std::string& chon)
{
    if (chon == "1" || chon == "2" || chon == "3")
    {
        std::string loai;
        if (chon == "1")
        {
            loai = "Sach";
        }
        else if (chon == "2")
        {
            loai = "TapChi";
        }
        else
        {
            loai = "Bao";
        }
        std::cout << "\nTHEM " << loai << '\n';
        bool daThem = quanLy.them(nhapTaiLieu(loai));
        if (daThem)
        {
            std::cout << "Them tai lieu thanh cong.\n";
        }
        else
        {
            std::cout << "Them that bai: ma tai lieu da ton tai.\n";
        }
    }
    else if (chon == "4")
    {
        quanLy.hienThi();
        std::cout << "Da hien thi " << quanLy.laySoLuong() << " tai lieu.\n";
    }
    else if (chon == "5")
    {
        timKiem(quanLy);
    }
    else if (chon == "6")
    {
        std::string ma = nhapChuoi("Nhap ma tai lieu can sua: ");
        TaiLieu* cu = quanLy.timTheoMa(ma);
        if (cu == nullptr)
        {
            std::cout << "Sua that bai: khong tim thay tai lieu.\n";
            return;
        }
        cu->xuat();
        std::cout << "Nhap thong tin moi. Giu nguyen so ban dang muon.\n";
        bool daSua = quanLy.sua(ma, nhapTaiLieu(cu->layLoai(), ma));
        if (daSua)
        {
            std::cout << "Sua thong tin thanh cong.\n";
        }
        else
        {
            std::cout << "Sua that bai: khong duoc thay doi so ban dang muon.\n";
        }
    }
    else if (chon == "7")
    {
        std::string ma = nhapChuoi("Nhap ma tai lieu can xoa: ");
        if (quanLy.xoa(ma))
        {
            std::cout << "Xoa tai lieu thanh cong.\n";
        }
        else
        {
            std::cout << "Xoa that bai: khong tim thay hoac tai lieu dang duoc muon.\n";
        }
    }
    else if (chon == "8")
    {
        sapXep(quanLy);
    }
    else if (chon == "9")
    {
        quanLy.thongKe();
        std::cout << "Thong ke thanh cong.\n";
    }
    else if (chon == "10" || chon == "11")
    {
        std::string loi;
        bool thanhCong;
        if (chon == "10")
        {
            std::filesystem::create_directories("data");
            thanhCong = quanLy.luu("data", loi);
        }
        else
        {
            thanhCong = quanLy.doc("data", loi);
        }
        if (thanhCong)
        {
            std::cout << "Thao tac file thanh cong tai thu muc data.\n";
        }
        else
        {
            std::cout << "Thao tac file that bai: " << loi << '\n';
        }
    }
    else
    {
        std::cout << "Lua chon khong hop le. Vui long chon tu 0 den 11.\n";
    }
}

int main()
{
    QuanLyTaiLieu quanLy;
    std::string chon;
    while (true)
    {
        hienThiMenu();
        if (!std::getline(std::cin, chon))
        {
            break;
        }
        if (chon == "0")
        {
            std::cout << "Da thoat chuong trinh.\n";
            break;
        }
        try
        {
            xuLyLuaChon(quanLy, chon);
        }
        catch (const std::exception& loi)
        {
            std::cout << "Thao tac that bai: " << loi.what() << '\n';
        }
    }
    return 0;
}
