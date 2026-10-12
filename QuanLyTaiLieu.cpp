#include "QuanLyTaiLieu.h"
#include "Sach.h"
#include "TapChi.h"
#include "Bao.h"
#include "ThuatToan.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

QuanLyTaiLieu::QuanLyTaiLieu()
{
    kiemTraPhieuMuon = nullptr;
}

QuanLyTaiLieu::~QuanLyTaiLieu()
{
    for (int i = 0; i < ds.laySoLuong(); i++)
    {
        delete ds[i];
    }
}

void QuanLyTaiLieu::ganKiemTraPhieuMuon(bool (*ham)(const std::string&))
{
    kiemTraPhieuMuon = ham;
}

bool QuanLyTaiLieu::dangMuon(const TaiLieu& taiLieu) const
{
    if (taiLieu.laySoLuongCon() < taiLieu.laySoLuongTong())
    {
        return true;
    }

    if (kiemTraPhieuMuon != nullptr)
    {
        return kiemTraPhieuMuon(taiLieu.layMa());
    }

    return false;
}

int QuanLyTaiLieu::timViTri(const std::string& ma) const
{
    for (int i = 0; i < ds.laySoLuong(); i++)
    {
        if (ds[i]->layMa() == ma)
        {
            return i;
        }
    }

    return -1;
}

bool QuanLyTaiLieu::them(std::unique_ptr<TaiLieu> taiLieu)
{
    if (taiLieu == nullptr)
    {
        return false;
    }

    if (timViTri(taiLieu->layMa()) != -1)
    {
        return false;
    }

    ds.them(taiLieu.get());
    // Danh sach nhan quyen so huu sau khi them thanh cong.
    taiLieu.release();

    return true;
}

bool QuanLyTaiLieu::sua(
    const std::string& ma,
    std::unique_ptr<TaiLieu> taiLieu
)
{
    int viTri = timViTri(ma);
    if (viTri < 0)
    {
        return false;
    }

    if (taiLieu == nullptr)
    {
        return false;
    }

    if (taiLieu->layMa() != ma)
    {
        return false;
    }

    if (taiLieu->layLoai() != ds[viTri]->layLoai())
    {
        return false;
    }

    int soDangMuon = ds[viTri]->laySoLuongTong() - ds[viTri]->laySoLuongCon();
    int soDangMuonMoi = taiLieu->laySoLuongTong() - taiLieu->laySoLuongCon();
    if (soDangMuonMoi != soDangMuon)
    {
        return false;
    }

    delete ds[viTri];
    ds.sua(viTri, taiLieu.release());

    return true;
}

bool QuanLyTaiLieu::xoa(const std::string& ma)
{
    int viTri = timViTri(ma);
    if (viTri < 0)
    {
        return false;
    }

    if (dangMuon(*ds[viTri]))
    {
        return false;
    }

    delete ds[viTri];
    ds.xoa(viTri);

    return true;
}

TaiLieu* QuanLyTaiLieu::timTheoMa(const std::string& ma) const
{
    int viTri = timViTri(ma);
    if (viTri < 0)
    {
        return nullptr;
    }

    return ds[viTri];
}

int QuanLyTaiLieu::timTheoTen(
    const std::string& ten,
    std::ostream& luong
) const
{
    int soKetQua = 0;
    for (int i = 0; i < ds.laySoLuong(); i++)
    {
        if (ds[i]->layTen().find(ten) != std::string::npos)
        {
            ds[i]->ghi(luong);
            soKetQua++;
        }
    }

    return soKetQua;
}

int QuanLyTaiLieu::laySoLuong() const
{
    return ds.laySoLuong();
}

const TaiLieu* QuanLyTaiLieu::layTaiLieu(int viTri) const
{
    return ds[viTri];
}

void QuanLyTaiLieu::hienThi() const
{
    if (ds.laySoLuong() == 0)
    {
        std::cout << "Danh sach rong\n";
    }

    for (int i = 0; i < ds.laySoLuong(); i++)
    {
        ds[i]->xuat();
    }
}

void QuanLyTaiLieu::sapXepTheoNam()
{
    // Selection Sort: chon nam nho nhat trong doan chua sap xep.
    for (int i = 0; i < ds.laySoLuong() - 1; i++)
    {
        int nhoNhat = i;
        for (int j = i + 1; j < ds.laySoLuong(); j++)
        {
            if (ds[j]->layNam() < ds[nhoNhat]->layNam())
            {
                nhoNhat = j;
            }
        }

        hoanDoi(ds[i], ds[nhoNhat]);
    }
}

void QuanLyTaiLieu::quickSort(int trai, int phai)
{
    if (trai >= phai)
    {
        return;
    }

    int i = trai;
    int j = phai;
    int giua = trai + (phai - trai) / 2;
    double chot = ds[giua]->layGiaTri();

    // Phan hoach: gia nho sang trai, gia lon sang phai.
    while (i <= j)
    {
        while (ds[i]->layGiaTri() < chot)
        {
            i++;
        }

        while (ds[j]->layGiaTri() > chot)
        {
            j--;
        }

        if (i <= j)
        {
            hoanDoi(ds[i], ds[j]);
            i++;
            j--;
        }
    }

    if (trai < j)
    {
        quickSort(trai, j);
    }

    if (i < phai)
    {
        quickSort(i, phai);
    }
}

void QuanLyTaiLieu::sapXepTheoGiaTri()
{
    quickSort(0, ds.laySoLuong() - 1);
}

void QuanLyTaiLieu::thongKe(std::ostream& luong) const
{
    std::string loai[] = {"Sach", "TapChi", "Bao"};

    for (int k = 0; k < 3; k++)
    {
        int soDau = 0;
        long long tong = 0;
        long long con = 0;

        for (int i = 0; i < ds.laySoLuong(); i++)
        {
            if (ds[i]->layLoai() == loai[k])
            {
                soDau++;
                tong += ds[i]->laySoLuongTong();
                con += ds[i]->laySoLuongCon();
            }
        }

        luong << loai[k] << ": dau=" << soDau;
        luong << ", tong=" << tong;
        luong << ", con=" << con;
        luong << ", dang muon=" << tong - con << '\n';
    }
}

bool QuanLyTaiLieu::luu(const std::string& thuMuc, std::string& loi) const
{
    loi.clear();
    std::string loai[] = {"Sach", "TapChi", "Bao"};

    for (int k = 0; k < 3; k++)
    {
        std::string tenTep = thuMuc + "/" + loai[k] + ".txt";
        std::ofstream tep(tenTep);
        if (!tep)
        {
            loi = "Khong mo duoc tep " + loai[k];
            return false;
        }

        for (int i = 0; i < ds.laySoLuong(); i++)
        {
            if (ds[i]->layLoai() == loai[k])
            {
                ds[i]->ghi(tep);
            }
        }

        tep.flush();
        if (!tep)
        {
            loi = "Loi ghi tep " + loai[k];
            return false;
        }
    }

    return true;
}

bool QuanLyTaiLieu::doc(const std::string& thuMuc, std::string& loi)
{
    loi.clear();

    for (int i = 0; i < ds.laySoLuong(); i++)
    {
        if (dangMuon(*ds[i]))
        {
            loi = "Khong thay danh sach khi co tai lieu dang muon";
            return false;
        }
    }

    QuanLyTaiLieu tam;
    std::string loai[] = {"Sach", "TapChi", "Bao"};

    try
    {
        for (int k = 0; k < 3; k++)
        {
            std::string tenTep = thuMuc + "/" + loai[k] + ".txt";
            std::ifstream tep(tenTep);
            if (!tep)
            {
                throw std::runtime_error("Khong mo duoc tep " + loai[k]);
            }

            std::string dong;
            int soDong = 0;

            while (std::getline(tep, dong))
            {
                soDong++;
                std::istringstream luong(dong);
                luong >> std::ws;
                if (luong.eof())
                {
                    continue;
                }

                std::unique_ptr<TaiLieu> taiLieu;
                if (k == 0)
                {
                    taiLieu.reset(new Sach);
                }
                else if (k == 1)
                {
                    taiLieu.reset(new TapChi);
                }
                else if (k == 2)
                {
                    taiLieu.reset(new Bao);
                }

                try
                {
                    taiLieu->nhap(luong);
                    luong >> std::ws;
                    if (!luong.eof())
                    {
                        throw std::runtime_error("Du truong du lieu");
                    }

                    // Chuyen quyen so huu doi tuong vao danh sach tam.
                    bool daThem = tam.them(std::move(taiLieu));
                    if (!daThem)
                    {
                        throw std::runtime_error("Trung ma");
                    }
                }
                catch (const std::exception& loiDoc)
                {
                    std::string thongBao = loai[k] + ": dong ";
                    thongBao += std::to_string(soDong);
                    thongBao += ": ";
                    thongBao += loiDoc.what();
                    throw std::runtime_error(thongBao);
                }
            }

            if (tep.bad())
            {
                throw std::runtime_error("Loi doc tep " + loai[k]);
            }
        }

        // Chi thay danh sach sau khi doc thanh cong toan bo ba tep.
        ds.doi(tam.ds);
    }
    catch (const std::exception& loiDoc)
    {
        loi = loiDoc.what();
        return false;
    }

    return true;
}
