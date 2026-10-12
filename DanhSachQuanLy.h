#ifndef DANHSACHQUANLY_H
#define DANHSACHQUANLY_H

#include <stdexcept>

// Lop nay chi giai phong mang. QuanLyTaiLieu giai phong cac doi tuong.
template<class T>
class DanhSachQuanLy
{
private:
    T* ds;
    int soLuong;
    int sucChua;

public:
    DanhSachQuanLy()
    {
        ds = nullptr;
        soLuong = 0;
        sucChua = 0;
    }

    ~DanhSachQuanLy()
    {
        delete[] ds;
    }

    DanhSachQuanLy(const DanhSachQuanLy&) = delete;
    DanhSachQuanLy& operator=(const DanhSachQuanLy&) = delete;

    int laySoLuong() const
    {
        return soLuong;
    }

    // Doi quyen so huu mang, khong sao chep hoac cap phat them.
    void doi(DanhSachQuanLy& khac) noexcept
    {
        T* tam = ds;
        ds = khac.ds;
        khac.ds = tam;

        int soTam = soLuong;
        soLuong = khac.soLuong;
        khac.soLuong = soTam;

        soTam = sucChua;
        sucChua = khac.sucChua;
        khac.sucChua = soTam;
    }

    T& operator[](int i)
    {
        if (i < 0 || i >= soLuong)
        {
            throw std::out_of_range("Chi so khong hop le");
        }

        return ds[i];
    }

    const T& operator[](int i) const
    {
        if (i < 0 || i >= soLuong)
        {
            throw std::out_of_range("Chi so khong hop le");
        }

        return ds[i];
    }

    void chen(int k, T giaTri)
    {
        if (k < 0 || k > soLuong)
        {
            throw std::out_of_range("Vi tri khong hop le");
        }

        if (soLuong == sucChua)
        {
            int sucChuaMoi;
            if (sucChua == 0)
            {
                sucChuaMoi = 4;
            }
            else
            {
                sucChuaMoi = sucChua * 2;
            }

            T* moi = new T[sucChuaMoi];
            for (int i = 0; i < soLuong; i++)
            {
                moi[i] = ds[i];
            }

            delete[] ds;
            ds = moi;
            sucChua = sucChuaMoi;
        }

        // Dich cac phan tu sang phai de tao cho trong tai vi tri k.
        for (int i = soLuong; i > k; i--)
        {
            ds[i] = ds[i - 1];
        }

        ds[k] = giaTri;
        soLuong++;
    }

    void them(T giaTri)
    {
        chen(soLuong, giaTri);
    }

    void sua(int k, T giaTri)
    {
        (*this)[k] = giaTri;
    }

    void xoa(int k)
    {
        // Goi operator[] de kiem tra chi so truoc khi dich mang.
        (*this)[k];

        for (int i = k; i < soLuong - 1; i++)
        {
            ds[i] = ds[i + 1];
        }

        soLuong--;
    }
};

#endif
