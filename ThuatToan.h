#ifndef THUATTOAN_H
#define THUATTOAN_H

template<class T>
void hoanDoi(T& a, T& b)
{
    T tam = a;
    a = b;
    b = tam;
}

template<class T>
T timMax(T a, T b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

template<class T>
T timMin(T a, T b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

template<class T>
int timKiemTuanTu(T ds[], int n, T x)
{
    for (int i = 0; i < n; i++)
    {
        if (ds[i] == x)
        {
            return i;
        }
    }

    return -1;
}

#endif
