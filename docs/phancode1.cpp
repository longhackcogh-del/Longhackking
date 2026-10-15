#include<bits/stdc++.h>
using namespace std;
//========Lop nguoi========
class nguoi{
	protected:
		string manguoi;
		string hoten;
		string email;
		string std;
	public:
		//====ham nhap======
		virtual void nhap(){
			cin.ignore();
			cout<<"\nNhap ma nguoi: ";
			getline(cin, manguoi);
			cout<<"\nNhap ho ten: ";
			getline(cin, hoten);
			cout<<"\nNhap email: ";
			getline(cin, email);
			cout<<"\nNhap so dien thoai: ";
			getline(cin, std);
		}
		//=======ham xuat======
		virtual void xuat(){
			cout<<"\nMa nguoi: "<<manguoi<<endl;
			cout<<"\nHo ten: "<<hoten<<endl;
			cout<<"\nEmail: "<<email<<endl;
			cout<<"\nSo dien thoai: "<<std<<endl;
			if(ktremail()){
				cout<<"\nEmail hop le "<<endl;
			}
			else{
				cout<<"\nEmail khong hop le "<<endl;
			}
		}	
		bool ktremail(){
			int a = email.find('@');
			int b = email.find('.',a);
			return a!=-1 && b!=-1 && a>0 && b>a+1 && b<email.length()-1;
		}
		//=====ham huy======
		virtual ~nguoi(){
		}
};
//=======lop khach hang ke thua lop nguoi======
class khachhang : public nguoi{
	private:
		string makh;
		string diachigd;
		int diemtichluy;
	public:
		//=======ham nhap======
		void nhap(){
			nguoi::nhap();
			cin.ignore();
			cout<<"\nNhap ma khach hang: ";
			getline(cin, makh);
			cout<<"\nNhap dia chi giao dich: ";
			getline(cin, diachigd);
			cout<<"\nNhap diem tich luy: ";
			cin>>diemtichluy;
		}
		//======ham xuat======
		void xuat(){
			nguoi::xuat();
			cout<<"\nMa khach hang: "<<makh<<endl;
			cout<<"\nDia chi giao dich: "<<diachigd<<endl;
			cout<<"\nDiem tich luy: "<<diemtichluy<<endl;
		}
		void capnhatdiachi(string diachimoi){
			diachigd = diachimoi;
		}
		void capnhatdiem(int diemmoi){
			diemtichluy = diemmoi;
		}
		string laymakh() const{
			return makh;
		}
};
//========lop nhan vien ke thua lop nguoi=======
class nhanvien : virtual public nguoi{
	private:
		string manv;
		string bophan;
		double luongcoban;
		double hesoluong;
	public:
		//=====ham nhap======
		void nhap(){
			nguoi::nhap();
			cin.ignore();
			cout<<"\nNhap ma nhan vien: ";
			getline(cin, manv);
			cout<<"\nNhap bo phan: ";
			getline(cin, bophan);
			cout<<"\nNhap luong co ban: ";
			cin>>luongcoban;
			cout<<"\nNhap he so luong: ";
			cin>>hesoluong;
		}
		//======ham xuat=====
		void xuat(){
			nguoi::xuat();
			cout<<"\nMa nhan vien: "<<manv<<endl;
			cout<<"\nBo phan: "<<bophan<<endl;
			cout<<"\nLuong co ban: "<<luongcoban<<endl;
			cout<<"\nHe so luong: "<<hesoluong<<endl;
			cout<<"\nLuong: "<<tinhluong()<<endl;
		}
		//=====ham tinh luong=====
		double tinhluong(){
			return luongcoban*hesoluong;
		}
};
//=====lop nghiep vu thuong mai ke thua lop nguoi=======
class nghiepvuthuongmai : virtual public nguoi{
	private:
		string chuyenmon;
		int sonamkinhnghiem;
		double doanhso;
	public:
		//======ham nhap=======
		void nhapnghiepvurieng(){
			nguoi::nhap();
			cin.ignore();
			cout<<"\nNhap chuyen mon: ";
			getline(cin, chuyenmon);
			cout<<"\nNhap so nam kinh nghiem: ";
			cin>>sonamkinhnghiem;
			cout<<"\nNhap doanh so: ";
			cin>>doanhso;
		}
		//======ham xuat=======
		void xuatnghiepvurieng(){
			nguoi::xuat();
			cout<<"\nChuyen mon: "<<chuyenmon<<endl;
			cout<<"\nSo nam kinh nghiem: "<<sonamkinhnghiem<<endl;
			cout<<"\nDoanh so: "<<doanhso<<endl;
		}
		//======ham lay danh so
		double laydoanhso() const{
			return doanhso;
		}
};
//=====lop quan ly san pham ke thua tu lop nhan vien va lop nghiep vu thuong mai
class quanlysanpham : public nhanvien,public nghiepvuthuongmai{
	private:
		string danhmucphutrach;
		double hesothuong;
	public:
		//======ham nhap=====
		void nhapquanly(){
			nhanvien::nhap();
			nghiepvuthuongmai::nhapnghiepvurieng();
			cin.ignore();
			cout<<"\nNhap danh muc phu trach: ";
			getline(cin, danhmucphutrach);
			cout<<"\nNhap he so thuong: ";
			cin>>hesothuong;
		}
		//====ham xuat====
		void xuatquanly(){
			nhanvien::xuat();
			nghiepvuthuongmai::xuatnghiepvurieng();
			cout<<"\nDanh muc phu trach: "<<danhmucphutrach<<endl;
			cout<<"\nHe so thuong: "<<hesothuong<<endl;
		}
		//====ham tinh thu nhap=====
		float tinhthunhap(){
			return tinhluong() + laydoanhso() * hesothuong;
		}
};
//=====lop san pham======
class sanpham{
	protected:
		string masp;
		string tensp;
		double gianhap;
		int soluongton;
	public:
		//=====Ham nhap ao====
		virtual void nhap(){
			cin.ignore();
			cout<<"\nNhap ma san pham: ";
			getline(cin, masp);
			cout<<"\nNhap ten san pham: ";
			getline(cin, tensp);
			cout<<"\nNhap gia nhap: ";
			cin>>gianhap;
			cout<<"\nNhap so luong ton: ";
			cin>>soluongton;
		}
		//=====Ham xuat ao======
		virtual void xuat(){
			cout<<"\nMa san pham: "<<masp<<endl;
			cout<<"\nTen san pham: "<<tensp<<endl;
			cout<<"\nGia nhap: "<<gianhap<<endl;
			cout<<"\nSo luong ton: "<<soluongton<<endl;
		}
		string laymap() const{
			return masp;
		}
		string laytensp() const{
			return tensp;
		}
		int laytonkho() const{
			return soluongton;
		}
		virtual ~sanpham(){
		}
		virtual double tinhgiaban() const = 0;
};
//=====lop san pham vat ly ke thua lop san pham
class sanphamvatly : public sanpham{
	protected:
		double khoiluong;
		double phidonggoi;
	public:
	//======ham nhap=====
		void nhap() override{
			sanpham::nhap();
			cout<<"\nNhap khoi luong: ";
			cin>>khoiluong;
			cout<<"\nNhap phi dong goi: ";
			cin>>phidonggoi;
		}
		//=======ham xuat======
		void xuat() override{
			sanpham::xuat();
			cout<<"\nKhoi luong: "<<khoiluong<<endl;
			cout<<"\nPhi dong goi: "<<phidonggoi<<endl;
			cout<<"\nTinh gia ban: "<<tinhgiaban()<<endl;
		}
		//=====ham tinh gia ban=====
		double tinhgiaban() const override{
			return gianhap * 1.2+phidonggoi;
		}
};
//======lop san pham ke thua lop san pham
class sanphamso : public sanpham{
	protected:
		string dinhdang;
		double phibanquyen;
	public:
		//=====ham nhap=====
		void nhap() override{
			sanpham::nhap();
			cin.ignore();
			cout<<"\nNhap dinh dang: ";
			getline(cin, dinhdang);
			cout<<"\nNhap phi ban quyen: ";
			cin>>phibanquyen;
		}
		//=====ham xuat=====
		void xuat() override{
			sanpham::xuat();
			cout<<"\nDinh dang: "<<dinhdang<<endl;
			cout<<"\nPhi ban quyen: "<<phibanquyen<<endl;
			cout<<"\nTinh gia ban: "<<tinhgiaban()<<endl;
		}
		//======ham tinh gia ban=====
		double tinhgiaban() const override{
			return gianhap + phibanquyen;
		}		
};
//=====lop don hang====
class donhang{
	protected:
		string madon;
		string makh;
		string ngaydat;
		string trangthai;
		double tongtien;
	public:
		//=====ham khoi tao======
		donhang(string madonhang=" ", string makh=" ",string ngaydat=" ", string trangthai =" ",double tongtien=0.0){
			this->madon=madonhang;
			this->makh=makh;
			this->ngaydat=ngaydat;
			this->trangthai=trangthai;
			this->tongtien=tongtien;
		}
		string laymadon() const{
			return madon;
		}
		//=====ham huy=====
		virtual ~donhang(){
		}
		//=====ham nhap ao======
		virtual void nhap(){
			cin.ignore();
			cout<<"\nNhap ma don: ";
			getline(cin, madon);
			cout<<"\nNhap ma khach hang: ";
			getline(cin, makh);
			cout<<"\nNhap ngay dat: ";
			getline(cin, ngaydat);
			cout<<"\nNhap trang thai: ";
			getline(cin, trangthai);
			cout<<"\nNhap tong tien: ";
			cin>>tongtien;
		}
		//======ham xuat ao======
		virtual void xuat(){
			cout<<"\nMa don: "<<madon<<endl;
			cout<<"\nMa khach hang: "<<makh<<endl;
			cout<<"\nNgay dat: "<<ngaydat<<endl;
			cout<<"\nTrang thai: "<<trangthai<<endl;
			cout<<"\nTong tien: "<<tongtien<<endl;
			cout<<"\nKiem tra ton kho: "<<(kiemtratonkho() ? "Co" : "Khong")<<endl;
			cout<<"\nTong tien hien tai: "<<tongtien<<endl;
			cout<<"\nTao don: "<<(trangthai == "Da tao" ? "Da tao" : "Chua tao")<<endl;
			cout<<"\nHuy don: "<<(trangthai == "Da huy" ? "Da huy" : "Chua huy")<<endl;
		}
		//=====ham kiem tra ton kho======
		bool kiemtratonkho(int soluongton = 0, int soluongmua = 0){
			if(soluongmua > 0 && soluongton >= soluongmua){
				return true;
			}
			return false;
		}
		//=====Ham tinh tong tien====
		void tinhtong(double gia=0.0, int soluong=0.0){
			if(gia>=0 && soluong > 0){
				tongtien = tongtien + gia * soluong;
			}
		}
		//=====ham tao don=====
		void taodon(){
			if(trangthai == "Chua tao"){
				trangthai = "Da tao";
				cout<<"\nTao don hang thanh cong!: ";
			}
			else{
				cout<<"\nDon hang da duoc tao: ";
			}
		}
		//======ham huy don =====
		void huydon(){
			if(trangthai == "Da tao"){
				trangthai = "Da huy";
				cout<<"\nHuy don hang thanh cong!: ";
			}
			else{
				cout<<"\nKhong the huy don hang: ";
			}
		}
};
//=====Lop giao hang=====
class giaohang{
	protected:
		string magiaohang;
		string madon;
		string dvvanchuyen;
		string ngaydukien;
		string trangthai;
	public:
		//====ham khoi tao======
		giaohang(string magiaohang=" ",string madon=" ",string dcvanchuyen=" ",string ngaydukien=" ",string trangthai= " "){
			this->magiaohang=magiaohang;
			this->madon=madon;
			this->dvvanchuyen=dcvanchuyen;
			this->ngaydukien=ngaydukien;
			this->trangthai=trangthai;
		}
		//=====ham huy ao====
		virtual ~giaohang(){
		}
		//=====ham nhap ao=====
		virtual void nhap(){
			cin.ignore();
			cout<<"\nNhap ma giao hang: ";
			getline(cin, magiaohang);
			cout<<"\nNhap ma don: ";
			getline(cin, madon);
			cout<<"\nNhap dich vu van chuyen: ";
			getline(cin, dvvanchuyen);
			cout<<"\nNhap ngay du kien: ";
			getline(cin, ngaydukien);
			cout<<"\nNhap trang thai: ";
			getline(cin, trangthai);
		}
		//=====ham xuat ao=====
		virtual void xuat(){
			cout<<"\nMa giao hang: "<<magiaohang<<endl;
			cout<<"\nMa don: "<<madon<<endl;
			cout<<"\nDich vu van chuyen: "<<dvvanchuyen<<endl;
			cout<<"\nNgay du kien: "<<ngaydukien<<endl;
			cout<<"\nTrang thai: "<<trangthai<<endl;
			cout<<"\nCap nhat hanh trinh hien tai: "<<trangthai<<endl;
			cout<<"\nDuoc giao hang: "<<(duocgiaohang(trangthai) ? "Co" : "Khong")<<endl;
			cout<<"\nHuy giao hang: "<<((trangthai == "Da huy") ? "Da huy" : "Chua huy")<<endl;
		}
		//======ham cap nhat hanh trinh=====
		void capnhathanhtrinh(string trangthaimoi, string trangthaidon){
			if(trangthaidon == "Da huy"){
				cout<<"\nDon hang da huy, khong the giao! ";
				trangthai = "Da huy";
				return;
			}
			if(trangthai == "Da Huy"){
				cout<<"\nDon giao hang da huy! ";
				return;
			}
			trangthai = trangthaimoi;
			cout<<"\nCap nhat hanh trinh thanh cong! ";
		}
		//======ham ktr co duoc giao hang =====
		bool duocgiaohang(string trangthaidon){
			if(trangthaidon == "Da huy"){
				return false;
			}
			return true;
		}
		//======ham huy giao hang=====
		void huygiaohang(){
			trangthai = "Da huy";
			cout<<"\nDa huy giao hang! ";
		}
};
//======Lop Thanh toan=====
class thanhtoan{
	protected:
		string mathanhtoan;
		string madon;
		string phuongthuc;
		string trangthai;
		double sotien;
	public:
		//=====ham khoi tao====
		thanhtoan(string mathanhtoan=" ",string madon=" ",string phuongthuc=" ",string trangthai=" ",double sotien=0.0){
			this->mathanhtoan=mathanhtoan;
			this->madon=madon;
			this->phuongthuc=phuongthuc;
			this->trangthai=trangthai;
			this->sotien=sotien;
		}
		//======ham nhap ao======
		virtual void nhap(){
			cin.ignore();
			cout<<"\nNhap ma thanh toan: ";
			getline(cin, mathanhtoan);
			cout<<"\nNhap ma don: ";
			getline(cin, madon);
			cout<<"\nNhap phuong thuc: ";
			getline(cin, phuongthuc);
			cout<<"\nNhap trang thai: ";
			getline(cin, trangthai);
			cout<<"\nNhap so tien: ";
			cin>>sotien;
		}
		//========ham xuat ao======
		virtual void xuat(){
			cout<<"\nMa thanh toan: "<<mathanhtoan<<endl;
			cout<<"\nMa don: "<<madon<<endl;
			cout<<"\nPhuong thuc: "<<phuongthuc<<endl;
			cout<<"\nTrang thai: "<<trangthai<<endl;
			cout<<"\nSo tien: "<<sotien<<endl;
		}
		//======ham huy ao=======
		virtual ~thanhtoan(){
		}
		//======ham xu ly trang thai thanh toan=======
		void xulythanhtoan(){
			if(sotien <= 0){
				cout<<"\nSo tien khong hop le! ";
				return;
			}
			if(trangthai == "Da thanh toan"){
				cout<<"\nDon hang da thanh toan truoc do! ";
				return;
			}
			if(trangthai == "Da hoan tien"){
				cout<<"\nGiao dich da hoan tien! ";
				return;
			}
			trangthai == "Da thanh toan";
			cout<<"\nThanh toan thanh cong: ";
		}
		//=====ham hoan tien======
		void hoantien(){
			if(trangthai == "Da thanh toan" && sotien >0){
				trangthai ="Da hoan tien: ";
				cout<<"\nHoan tien thanh cong: ";
				cout<<"\nSo tien hoan: "<<sotien<<"VND"<<endl;
			}
			else{
				cout<<"\nKhong du dieu kien hoan tien! ";
			}
		}
};
//======lop he thong=======
class hethong{
	private:
		static const int Max = 100;
		khachhang dskh[Max];
		int nkh;
		sanpham *dssp[Max];
		int nsp;
		donhang dsdh[Max];
		int ndh;
		giaohang dsgh[Max];
		int ngh;
		thanhtoan dstt[Max];
		int ntt;
	public:
		hethong(){
			nkh = nsp = ndh = ngh = ntt = 0;
			for(int i=0;i<Max;i++){
				dssp[i] = NULL;
			}
		}
		~hethong(){
			for(int i=0; i<nsp; i++ ){
				delete dssp[i];
			}
		}
		int timkh(string ma){
			for(int i=0; i<nkh; i++){
				if(dskh[i].laymakh() == ma)
				return i;
			}
			return -1;
		}
		int timsp(string ma){
			for(int i=0; i<nsp; i++){
				if(dssp[i]->laymap()==ma)
				return i;
			}
			return -1;
		}
		int timdh(string ma){
			for(int i=0;i<ndh;i++){
				if(dsdh[i].laymadon() == ma)
				return i;
			}
			return -1;
		}
};
int timkh(string ma, khachhang dskh[], int n) {
	for (int i = 0; i < n; i++) {
		if (dskh[i].laymakh() == ma) return i;
	}
	return -1;
}
//=====menu khach hang=====

void menukhachhang() {
    const int MAX = 100;
    static khachhang dskh[MAX];
    static int nkh = 0;
    int chon;
    do {
        cout << "\n===== QUAN LY KHACH HANG =====";
        cout << "\n1. Them khach hang";
        cout << "\n2. Xem danh sach khach hang";
        cout << "\n3. Cap nhat dia chi";
        cout << "\n4. Cap nhat diem tich luy";
        cout << "\n5. Tim khach hang theo ma";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: {
                if (nkh < MAX) {
                    dskh[nkh].nhap();
                    nkh++;
                    cout << "\nThem khach hang thanh cong!";
                } else {
                    cout << "\nDanh sach da day!";
                }
                break;
            }
            case 2: {
                if (nkh == 0) {
                    cout << "\nDanh sach rong!";
                } else {
                    for (int i = 0; i < nkh; i++) {
                        cout << "\n--- Khach hang " << i + 1 << " ---";
                        dskh[i].xuat();
                    }
                }
                break;
            }
            case 3: {
                string ma, dc;
                cout << "\nNhap ma khach hang: ";
                cin >> ma;
                int k = -1;
                for (int i = 0; i < nkh; i++) {
                    if (dskh[i].laymakh() == ma) {
                        k = i;
                        break;
                    }
                }
                if (k == -1) {
                    cout << "\nKhong tim thay khach hang!";
                } else {
                    cout << "\nNhap dia chi moi: ";
                    getline(cin >> ws, dc);
                    dskh[k].capnhatdiachi(dc);
                    cout << "\nCap nhat dia chi thanh cong!";
                }
                break;
            }
            case 4: {
                string ma;
                int diem;
                cout << "\nNhap ma khach hang: ";
                cin >> ma;
                int k = -1;
                for (int i = 0; i < nkh; i++) {
                    if (dskh[i].laymakh() == ma) {
                        k = i;
                        break;
                    }
                }
                if (k == -1) {
                    cout << "\nKhong tim thay khach hang!";
                } else {
                    cout << "\nNhap diem moi: ";
                    cin >> diem;

                    if (diem < 0) {
                        cout << "\nDiem khong hop le!";
                    } else {
                        dskh[k].capnhatdiem(diem);
                        cout << "\nCap nhat diem thanh cong!";
                    }
                }
                break;
            }
            case 5: {
                string ma;
                cout << "\nNhap ma khach hang can tim: ";
                cin >> ma;
                int k = -1;
                for (int i = 0; i < nkh; i++) {
                    if (dskh[i].laymakh() == ma) {
                        k = i;
                        break;
                    }
                }
                if (k == -1) {
                    cout << "\nKhong tim thay khach hang!";
                } else {
                    dskh[k].xuat();
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "\nLua chon khong hop le!";
        }

    } while (chon != 0);
}
//=====menu san pham=======
void menusanpham() {
    const int MAX = 100;
    static sanpham* dssp[MAX] = {};
    static int nsp = 0;
    int chon;
    do {
        cout << "\n===== QUAN LY SAN PHAM =====";
        cout << "\n1. Them san pham vat ly";
        cout << "\n2. Them san pham so";
        cout << "\n3. Xem danh sach san pham";
        cout << "\n4. Tim san pham theo ma";
        cout << "\n5. Tim san pham theo ten";
        cout << "\n6. Sap xep theo gia tang dan";
        cout << "\n7. Sap xep theo ton kho giam dan";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: {
                if (nsp >= MAX) {
                    cout << "\nDanh sach da day!";
                    break;
                }
                dssp[nsp] = new sanphamvatly;
                dssp[nsp]->nhap();
                nsp++;
                cout << "\nThem san pham vat ly thanh cong!";
                break;
            }
            case 2: {
                if (nsp >= MAX) {
                    cout << "\nDanh sach da day!";
                    break;
                }
                dssp[nsp] = new sanphamso;
                dssp[nsp]->nhap();
                nsp++;
                cout << "\nThem san pham so thanh cong!";
                break;
            }
            case 3: {
                if (nsp == 0) {
                    cout << "\nDanh sach san pham rong!";
                }
                for (int i = 0; i < nsp; i++) {
                    cout << "\n--- San pham " << i + 1 << " ---";
                    dssp[i]->xuat();
                }
                break;
            }
            case 4: {
                string ma;
                cout << "\nNhap ma san pham: ";
                cin >> ma;

                int k = -1;
                for (int i = 0; i < nsp; i++) {
                    if (dssp[i]->laymap() == ma) {
                        k = i;
                        break;
                    }
                }
                if (k == -1) {
                    cout << "\nKhong tim thay san pham!";
                } else {
                    dssp[k]->xuat();
                }
                break;
            }
            case 5: {
    			string ten;
    			cout << "\nNhap ten san pham: ";
    			getline(cin >> ws, ten);
    			bool timthay = false;
    			for (int i = 0; i < nsp; i++){
        			if (dssp[i]->laytensp().find(ten) != string::npos){
            			dssp[i]->xuat();
            			timthay = true;
       				}
    			}
    			if (!timthay){
					cout << "\nKhong tim thay san pham!";
				}
				break;
}
            case 6: {
                // Sap xep theo gia ban tang dan
                for (int i = 0; i < nsp - 1; i++) {
                    for (int j = i + 1; j < nsp; j++) {
                        if (dssp[i]->tinhgiaban() >
                            dssp[j]->tinhgiaban()) {
                            sanpham* tam = dssp[i];
                            dssp[i] = dssp[j];
                            dssp[j] = tam;
                        }
                    }
                }
                cout << "\nDa sap xep san pham theo gia tang dan!";
                break;
            }
            case 7: {
                // Can bo sung ham lay soluongton() trong lop sanpham
                cout << "\nCan bo sung ham lay soluongton()";
                cout << " de sap xep theo ton kho.";
                break;
            }
            case 0:
                break;

            default:
                cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//=====menu kho=====
void menukho() {
    int chon;
    do {
        cout << "\n===== QUAN LY KHO =====";
        cout << "\n1. Xem ton kho";
        cout << "\n2. Cap nhat so luong ton";
        cout << "\n3. Tim san pham ton thap";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1:
                cout << "\nChuc nang xem ton kho";
                break;
            case 2:
                cout << "\nChuc nang cap nhat ton kho";
                break;
            case 3:
                cout << "\nChuc nang tim ton kho thap";
                break;
            case 0:
                break;
            default:
                cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//=====menu don hang=====
void menudonhang() {
    int chon;
    do {
        cout << "\n===== QUAN LY DON HANG =====";
        cout << "\n1. Tao don hang";
        cout << "\n2. Xem danh sach don hang";
        cout << "\n3. Tim don theo ma khach hang";
        cout << "\n4. Tim don theo trang thai";
        cout << "\n5. Sap xep theo tong tien";
        cout << "\n6. Huy don hang";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: cout << "\nTao don hang"; break;
            case 2: cout << "\nXem danh sach don"; break;
            case 3: cout << "\nTim don theo khach hang"; break;
            case 4: cout << "\nTim don theo trang thai"; break;
            case 5: cout << "\nSap xep don hang"; break;
            case 6: cout << "\nHuy don hang"; break;
            case 0: break;
            default: cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//=====menu giao hang=====
void menugiaohang() {
    int chon;
    do {
        cout << "\n===== GIAO HANG =====";
        cout << "\n1. Them thong tin giao hang";
        cout << "\n2. Xem danh sach giao hang";
        cout << "\n3. Cap nhat hanh trinh";
        cout << "\n4. Huy giao hang";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: cout << "\nThem giao hang"; break;
            case 2: cout << "\nXem danh sach giao hang"; break;
            case 3: cout << "\nCap nhat hanh trinh"; break;
            case 4: cout << "\nHuy giao hang"; break;
            case 0: break;
            default: cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//=====menu thanh toan
void menuthanhtoan() {
    int chon;
    do {
        cout << "\n===== THANH TOAN =====";
        cout << "\n1. Them thanh toan";
        cout << "\n2. Xem danh sach thanh toan";
        cout << "\n3. Xu ly thanh toan";
        cout << "\n4. Hoan tien";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: cout << "\nThem thanh toan"; break;
            case 2: cout << "\nXem danh sach thanh toan"; break;
            case 3: cout << "\nXu ly thanh toan"; break;
            case 4: cout << "\nHoan tien"; break;
            case 0: break;
            default: cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//=====menu khuyen mai
void menukhuyenmai() {
    int chon;
    do {
        cout << "\n===== KHUYEN MAI =====";
        cout << "\n1. Them khuyen mai";
        cout << "\n2. Xem danh sach khuyen mai";
        cout << "\n3. Ap dung khuyen mai";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon){
            case 1: cout << "\nThem khuyen mai"; break;
            case 2: cout << "\nXem khuyen mai"; break;
            case 3: cout << "\nAp dung khuyen mai"; break;
            case 0: break;
            default: cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//======menu thong ke=====
void menuthongke() {
    int chon;
    do {
        cout << "\n===== THONG KE BAN HANG =====";
        cout << "\n1. Thong ke doanh thu";
        cout << "\n2. Thong ke san pham ban chay";
        cout << "\n3. Thong ke san pham ton thap";
        cout << "\n4. Thong ke ty le huy don";
        cout << "\n0. Quay lai";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon) {
            case 1: cout << "\nThong ke doanh thu"; break;
            case 2: cout << "\nThong ke san pham ban chay"; break;
            case 3: cout << "\nThong ke ton kho thap"; break;
            case 4: cout << "\nThong ke ty le huy don"; break;
            case 0: break;
            default: cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
//=====menu chinh======
void menuChinh() {
    int chon;
    do {
        cout << "\n========== HE THONG QUAN LY THUONG MAI DIEN TU ==========";
        cout << "\n1. Quan ly khach hang";
        cout << "\n2. Quan ly san pham";
        cout << "\n3. Quan ly kho";
        cout << "\n4. Quan ly don hang";
        cout << "\n5. Giao hang";
        cout << "\n6. Thanh toan";
        cout << "\n7. Khuyen mai";
        cout << "\n8. Thong ke ban hang";
        cout << "\n0. Thoat";
        cout << "\n==========================================================";
        cout << "\nNhap lua chon: ";
        cin >> chon;
        switch (chon) {
            case 1:
                menukhachhang();
                break;
            case 2:
                menusanpham();
                break;
            case 3:
                menukho();
                break;
            case 4:
                menudonhang();
                break;
            case 5:
                menugiaohang();
                break;
            case 6:
                menuthanhtoan();
                break;
            case 7:
                menukhuyenmai();
                break;
            case 8:
                menuthongke();
                break;
            case 0:
                cout << "\nThoat chuong trinh!";
                break;
            default:
                cout << "\nLua chon khong hop le!";
        }
    } while (chon != 0);
}
int main(){
    menuChinh();
    return 0;
}