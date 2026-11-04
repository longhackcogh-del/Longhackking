# Hệ thống Quản lý Thư viện Đại học

## Chạy ứng dụng thư viện tích hợp

Mở terminal PowerShell tại thư mục dự án trong VS Code. Cần `g++` hỗ trợ C++17 trong `PATH`:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
.\build\tich-hop\thuVien.exe
```

Chỉ chạy executable khi bước biên dịch thành công. Script dùng `-std=c++17 -Wall -Wextra -Wpedantic`, liệt kê nguồn tường minh và không đưa `main()` của kiểm thử hoặc code mẫu vào ứng dụng.

Menu 1–6 quản lý tài liệu, độc giả, nhân viên, thủ thư trưởng, mượn–trả và vi phạm trên cùng một `QuanLyThuVien`. Menu 7 gọi các hàm tìm kiếm và sắp xếp đã có. Nhập `0` để quay lại từ menu con, `11` để thoát ứng dụng. Nhập mỗi thông tin trên một dòng; ngày theo `dd/mm/yyyy`.

Menu 8 thực hiện thống kê và thực nghiệm thuật toán. Menu 9 đọc đủ chín tệp vào dữ liệu tạm, kiểm tra rồi hỏi xác nhận thay thế toàn bộ. Menu 10 lưu cả bộ dữ liệu qua thư mục chuẩn bị và bản sao phục hồi. Chương trình không tự đọc khi khởi động hoặc tự lưu khi thoát.

Khi thêm mới tài liệu, số còn phải bằng tổng số lượng. Khi thêm mới độc giả, số đang mượn phải bằng 0; sau đó lập phiếu để cập nhật các số này. Sửa hồ sơ phải giữ mã định danh và số đang mượn; sửa tài liệu phải giữ số lượng đang mượn. Dữ liệu nhập sai bị từ chối, hồ sơ cũ được giữ nguyên.

Thêm thủ thư trưởng đồng thời đăng ký vai trò độc giả giảng viên từ chính thông tin đã nhập. Nếu độc giả đã có, chỉ liên kết khi toàn bộ thông tin giảng viên trùng khớp. Hai vai trò được đồng bộ sau mượn/trả và sửa từ menu thủ thư trưởng. Hồ sơ liên kết được sửa ở menu thủ thư trưởng. Xóa vai trò thủ thư trưởng giữ lại độc giả và lịch sử; muốn xóa tiếp độc giả, dùng menu độc giả khi không còn tài liệu đang mượn.

### Liên kết nhân sự và chuyển vai trò

- Mã người xác định một người. Cùng mã người ở nhiều vai trò phải khớp họ tên, ngày sinh, email và điện thoại. Thêm hồ sơ có thông tin mâu thuẫn bị từ chối. Sửa nhân thân của một hồ sơ hợp lệ đồng bộ phần `Nguoi` sang các vai trò liên kết, giữ nguyên mã và số đang mượn.
- Một mã nhân viên chỉ thuộc danh sách nhân viên thường hoặc danh sách thủ thư trưởng. Không lưu bản sao nhân viên thường cho thủ thư trưởng. Menu nhân viên chỉ hiển thị nhân viên thường; xem thủ thư trưởng ở menu 4.
- Menu **3 → 9** chuyển nhân viên thành thủ thư trưởng. Chọn mã nhân viên, nhập đầy đủ hồ sơ trưởng; giữ nguyên mã người, mã nhân viên, nhân thân, ca/chức vụ/lương/hệ số hiện tại. Bổ sung thông tin giảng viên và quản lý. Nếu đã có độc giả giảng viên, phải nhập đúng thông tin và số đang mượn; nếu chưa có, đăng ký độc giả mới với số đang mượn bằng 0. Không tự đổi loại độc giả sinh viên thành giảng viên.
- Menu **4 → 11** chuyển thủ thư trưởng về nhân viên thường. Giữ nguyên nhân thân và thông tin nhân viên, giữ độc giả giảng viên, phiếu, tồn kho và vi phạm. Phần thông tin quản lý riêng của vai trò trưởng không nằm trong hồ sơ nhân viên thường; muốn chuyển lên trưởng lại, nhập lại phần này. Trường chức vụ là mô tả hồ sơ; quyền duyệt phụ thuộc đối tượng còn thuộc danh sách thủ thư trưởng, không phụ thuộc dòng chữ chức vụ.
- Chuyển vai trò là thao tác riêng, không tự diễn ra khi thêm trùng mã. Các điều kiện được kiểm tra trước; thao tác trả về thất bại không làm thay đổi các danh sách. Các con trỏ lấy từ danh sách nhân sự cần được tìm lại sau thao tác chuyển vai trò vì danh sách có thể cấp phát lại.
- Bỏ vai trò trưởng không xóa lịch sử người duyệt; người đã về nhân viên không được duyệt vi phạm mới. Mã đã xuất hiện trong lịch sử duyệt không được cấp lại bằng chức năng thêm mới sau khi xóa hồ sơ nhân sự. Dùng chuyển vai trò để giữ mã của người đang có hồ sơ.
- Menu **4 → 8** xóa hồ sơ nhân sự trưởng, khác với chuyển về nhân viên. Xóa nhân sự không xóa dây chuyền độc giả, phiếu hay vi phạm. Các thao tác ghi dữ liệu của ứng dụng phải đi qua `QuanLyThuVien`; các lớp quản lý riêng vẫn được giữ để kiểm thử từng module.

Trả trễ tự ghi vi phạm với mã `VP_<mã phiếu>`. Chức năng ghi nhận thủ công từ phiếu đã trả vẫn kiểm tra trùng; không tạo một vi phạm thứ hai. Duyệt vi phạm yêu cầu mã thủ thư trưởng tồn tại. Thanh toán và duyệt trùng bị từ chối.

Chạy kiểm thử riêng:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -KiemThu
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\kiemThuMenu.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\chayKiemThuDocGia.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\chayKiemThuMuonTra.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\chayKiemThuTepHeThong.ps1
```

`-KiemThu` biên dịch `tests/kiemThuTichHop.cpp` thành executable riêng. `kiemThuMenu.ps1` biên dịch lại ứng dụng rồi nhập dữ liệu qua stdin của chính ứng dụng, kiểm tra đầu ra, mã thoát và trường hợp hết đầu vào. Mỗi lần chạy lưu `nhap.txt`, `xuat.txt`, `loi.txt` và kết quả trong `build/menu-kiemthu-<mã riêng>/`; không ghi vào dữ liệu mẫu hoặc thư mục cá nhân.

Đây là một chương trình quản lý thư viện chung. Nhánh `tv2-docgia` phát triển phần độc giả và nhân sự, giữ các giao diện để tích hợp với tài liệu, mượn trả và vi phạm.

## Phạm vi phần 2

- Các lớp `Nguoi`, `DocGia`, `SinhVien`, `GiangVien`, `NhanVienThuThu`, `ThuThuTruong`.
- Quản lý độc giả: thêm, xuất, tìm mã/tên, sửa, xóa khi không còn mượn, chèn tại vị trí k, Bubble Sort theo số đang mượn, kiểm tra hạn mức và đọc/ghi file.
- Quản lý nhân viên: thêm, xuất, tìm mã/ca, sửa, xóa, sắp xếp hệ số lương, tính lương và đọc/ghi file.
- Quản lý thủ thư trưởng: thêm, xuất, tìm mã, tìm người quản lý hơn 10 nhân viên, sắp xếp phụ cấp, tính thu nhập, đọc/ghi file, xem và duyệt vi phạm.
- Giữ lớp trừu tượng, hàm thuần ảo, kế thừa ảo, kế thừa nhiều, đa hình, template và toán tử theo đề.

Giới hạn sinh viên 5, giảng viên 10 và phụ cấp nhân 2.000.000 là quy ước hiện dùng theo đặc tả bổ sung. Thủ thư trưởng có thể mang trạng thái đang mượn hợp lệ; sửa thông tin không được đổi mã người, mã nhân viên, mã độc giả hoặc số đang mượn. Trạng thái tài khoản vẫn có thể được cập nhật.

## Biên dịch và kiểm thử trên Windows / VS Code

Cần Git, Windows PowerShell và g++ hỗ trợ C++17, có trong `PATH`. Có thể dùng g++ của MSYS2 UCRT64. Kiểm tra trong terminal VS Code:

```powershell
g++ --version
```

Sau khi clone và mở thư mục repository, chạy:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\chayKiemThuDocGia.ps1
```

Script có thể được gọi bằng đường dẫn tuyệt đối từ thư mục khác. Script biên dịch trực tiếp các file nguồn trong repository bằng `-std=c++17 -Wall -Wextra -Wpedantic`, bật thêm `-D_GLIBCXX_ASSERTIONS`, rồi chạy `tests/kiemThuDocGia.cpp`. Không cần CMake hoặc file có sẵn trong `build/`.

Mỗi lần chạy tạo một thư mục mới `build/tv2-kiemthu-<mã riêng>/` gồm:

- `kiemThuDocGia.exe`: chương trình kiểm thử, không phải demo/menu thư viện.
- `bien_dich.log`: thông báo biên dịch.
- `ket_qua.txt` và `loi_kiem_thu.log`: kết quả và lỗi kiểm thử.
- `ma_nguon.csv`: SHA256 của các nguồn/header và script tại thời điểm chạy.
- `du_lieu/`: dữ liệu đầu vào do bộ kiểm thử tạo để kiểm tra cả trường hợp đúng và sai.

Mã thoát `0` nghĩa là mọi kiểm tra đạt. Mã khác `0` nghĩa là có lỗi biên dịch, kiểm thử hoặc mã nguồn thay đổi trong lúc chạy. Không dùng kết quả từ executable cũ để thay cho chạy lại script. Thư mục build được bỏ qua bởi `.gitignore`.

## File phải có khi lưu Git

Ngoài mã nguồn phần 2, cần các file dùng chung `NhapXuat.h/.cpp`, `DanhSachQuanLy.h`, `ThuatToan.h`, `Tep.h`, cùng `tests/KiemThu.h` và hai file kiểm thử/script trên.

Các phụ thuộc được dùng để biên dịch và kiểm tra kết nối thật:

- Phần tài liệu: `.h/.cpp` của `TaiLieu`, `Sach`, `TapChi`, `Bao`, `QuanLyTaiLieu`.
- Phần mượn trả và vi phạm: `.h/.cpp` của `PhieuMuon`, `QuanLyPhieuMuon`, `NhatKyViPham`, `QuanLyViPham`.

Script liệt kê tường minh toàn bộ nguồn cần biên dịch. Các phụ thuộc không bị thay đổi logic trong quá trình hoàn thiện phần 2. Không cần chép menu hoặc `main.cpp` để chạy kiểm thử này.

## Dữ liệu mẫu và tài liệu

Giữ `data_mau/SinhVien.txt`, `GiangVien.txt`, `NhanVienThuThu.txt`, `ThuThuTruong.txt`. Định dạng hiện tại bắt đầu bằng `THUVIEN_2`, sau đó là số bản ghi và từng trường trên dòng riêng. Độc giả được lưu theo đúng loại sinh viên/giảng viên.

Một số dữ liệu mẫu đang có số tài liệu đang mượn; khi tích hợp phải đọc cùng phiếu mượn tương ứng để đối chiếu nhất quán. Không tự đổi số đang mượn về 0. Bộ kiểm thử dùng thư mục riêng, không ghi đè dữ liệu mẫu.

Tài liệu yêu cầu hiện ở thư mục gốc: `BaiTapLon_GiaoVien.docx.docx`, `DacTaChiTiet_Bai1.docx.docx`. Code mẫu phong cách ở `docs/phancode1.cpp`.

## Phạm vi kiểm chứng

Bộ kiểm thử kiểm tra nhập/xuất qua luồng, dữ liệu không hợp lệ, quản lý danh sách, tìm kiếm, sắp xếp, cập nhật, lưu/đọc, bảo toàn dữ liệu khi lỗi, đa hình, một lớp cơ sở `Nguoi`, gọi hàm hủy đối tượng và liên kết mượn–trả–duyệt vi phạm thật.

Chưa thay thế kiểm thử menu chính, kiểm thử toàn hệ thống sau tích hợp, kiểm tra rò rỉ bộ nhớ bằng công cụ chuyên dụng hoặc thực nghiệm thuật toán với bốn kích thước dữ liệu. Việc sử dụng đầy đủ các hàm template/friend/toán tử trong luồng ứng dụng chung cần đối chiếu tiếp khi tích hợp. Chưa tạo báo cáo hoặc sơ đồ lớp trong giai đoạn này.

## Menu 8: Thong ke va thuc nghiem

Kiểm thử riêng thống kê và thuật toán (không tạo dữ liệu hồ sơ ra tệp):

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\chayKiemThuThongKe.ps1
```

Các menu quản lý 1, 2, 3, 5, 6 có mục 10 lưu và 11 đọc; menu thủ thư trưởng có mục 12 lưu và 13 đọc để giữ nguyên số lựa chọn chuyển vai trò đã có. Đây là lối gọi tới đọc/lưu **toàn hệ thống**, không đọc riêng một danh sách làm lệch dữ liệu liên kết. Menu chính 9/10 vẫn hoạt động như trước.

1. Tai lieu theo loai, tong so ban, so con va so dang muon.
2. Doc gia dang muon nhieu nhat (hien thi ca dong hang), tong so dang muon, muc it nhat.
3. Tai lieu duoc muon nhieu nhat theo tong so ban tren tat ca phieu; giu ca ma tai lieu da xoa.
4. Phieu dang muon qua han theo ngay he thong.
5. Tong tien phat da thu va chua thu.
6. Thuc nghiem 100, 500, 1000, 2000 phan tu; chi dung mang rieng, khong sua du lieu thu vien.

Thuc nghiem sap xep dung cung mang khoa nguyen duy nhat duoc hoan vi co hat giong 2026. Moi thuat toan sap xep chay 3 lan, sao chep dau vao ngoai khoang do, kiem tra moi phan tu dau ra. Tim kiem chay 1000 truy van co ca khoa khong ton tai. Don vi micro giay; cac cot tim kiem la trung binh moi truy van. Bang bam dung khoa chuoi bieu dien cung so nguyen, nen co chi phi chuyen so sang chuoi; khong xem day la so sanh toc do tuyet doi giua cung mot kieu khoa. Cot dung_bam_us tach rieng chi phi xay dung. Nhi phan do tren mang da sap xep, khong gom thoi gian sap xep. Khong chon thuat toan chi dua vao mot lan do tren mot may.

Do phuc tap: tuan tu O(n); nhi phan O(log n) khi da sap xep; bam trung binh O(1) cho tra cuu, xau nhat O(n); Bubble Sort O(n^2), tot nhat O(n); Selection Sort O(n^2); Quick Sort trung binh O(n log n), xau nhat O(n^2); Merge Sort O(n log n), mang phu O(n). Ham timNhiPhan cua quan ly tai lieu con tao va sap xep mang phu O(n^2), khac phep do rieng buoc tim nhi phan.

## Menu 9 va 10: Doc va luu toan he thong

Du chin tep THUVIEN_2: Sach.txt, TapChi.txt, Bao.txt, SinhVien.txt, GiangVien.txt, NhanVienThuThu.txt, ThuThuTruong.txt, PhieuMuon.txt, NhatKyViPham.txt. Dong 2 la so ban ghi; moi truong mot dong.

Menu 9: nhap thu muc, doc vao he thong tam va kiem tra lien ket; nhap 1 de thay toan bo, 0 de huy. Loi/huy giu nguyen du lieu hien tai. Phieu dang muon bat buoc co tai lieu/doc gia. Phieu da tra duoc tham chieu ho so da xoa; ma nguoi duyet lich su khong bi thay doi.

Menu 10: nhap thu muc dich da ton tai, nhap 1 de xac nhan. Ghi vao .giao-dich-thuvien/moi, doc lai kiem tra, cat tep cu vao cu/, thay chin tep. Thanh cong giu .sao-luu-thuvien-N; that bai thu phuc hoi va bao ket qua. Khong tu xoa ban sao.

Neu con .giao-dich-thuvien, ca doc va ghi se bi chan. Dong ung dung, sao chep ca thu muc ra noi an toan truoc khi phuc hoi. Xem nhat-ky.txt: CO_CU ghi tep von ton tai hay khong; CAT_CU/DAT_MOI la y dinh truoc doi ten, khong phai xac nhan da xong. Doi chieu dich/cu/moi, giu rieng tep moi truoc khi phuc hoi tep cu. Voi CO_CU 0, phuc hoi trang thai khong co tep bang cach chuyen tep moi ra rieng. Chi doi ten dau giao dich khi da xac dinh bo nhat quan. Khong tron cac the he du lieu, khong tao ban ghi de hop thuc hoa.

Windows/OneDrive co the khoa tep. Chin lan doi ten khong phai giao dich nguyen tu; khong bao dam tuyet doi khi mat dien/hong o dia. Chi mot tien trinh doc/ghi bo du lieu tai mot thoi diem.

## Chay thu an toan

### Kiểm tra bản sao sạch trước khi bàn giao

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tests\kiemTraBanBanGiao.ps1
```

Script tạo bản sao nguồn riêng trong `build/ban-giao-<mã>/ThuVien`, không lấy `.git`, executable cũ, log hoặc hai file cá nhân. Script đối chiếu SHA256, nén nguồn trước khi build, rồi biên dịch/chạy sáu bộ kiểm thử từ bản sao đó. Nếu bất kỳ bước nào lỗi, script dừng và không công nhận ZIP đã được kiểm chứng. Báo cáo Word/PDF đang là bản nháp nên không tự đưa vào ZIP mã nguồn này. Kiểm tra trên cùng máy không thay thế thử nghiệm trên một máy Windows khác.

Neu executable cu dang mo, khong can dong bang lenh cuong buc. Build vao thu muc rieng:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -ThuMucBuild build/chay-thu-moi
.\build\chay-thu-moi\thuVien.exe
```

Chon 9, nhap duong dan tuyet doi toi data_tich_hop_mau, nhap 1. S01 con/tong 2/3, DG_SV01 dang muon 1. Chon 8 de xem thong ke va thuc nghiem. Tra P01 ngay 05/01/2026 se phat 4000, kho ve 3/3, doc gia ve 0. Chon 10 de luu vao thu muc rieng da tao trong build; thoat va doc lai bang menu 9 de tiep tuc.

Bo data_mau cu duoc giu nguyen; dung data_tich_hop_mau de kiem tra du chin tep. Khong luu de vao mau goc. Chay cac script kiem thu lan luot neu muon tiet kiem tai nguyen. tests/kiemThuMenu.ps1 build executable moi trong thu muc rieng, kiem tra ca menu 8, luu, thoat, mo lai va tiep tuc tra/duyet/thanh toan.
