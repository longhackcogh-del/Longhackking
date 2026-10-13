# Công việc 1: Quản lý tài liệu thư viện

Nhánh `tv1-tailieu` chứa module tài liệu độc lập: `TaiLieu`, `Sach`, `TapChi`, `Bao`, `QuanLyTaiLieu`; mảng template `DanhSachQuanLy<T>`, nhập/xuất và thuật toán dùng chung. Không dùng `vector`, `std::sort`, `std::quoted` hoặc `bits/stdc++.h`.

## Biên dịch và chạy

Trên Windows cần MinGW có `g++` và `ar` trong PATH. Chạy tại thư mục gốc:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -KiemThu
.\build\demoTaiLieu.exe
```

Nếu có CMake:

```powershell
cmake -S . -B build/cmake
cmake --build build/cmake
ctest --test-dir build/cmake --output-on-failure
```

CMake chỉ biên dịch sáu file nguồn của module, demo và kiểm thử; không cần `main.cpp`, `Menu.cpp`, độc giả hoặc phiếu mượn. `main()` của demo chỉ gọi menu tài liệu. Mã tích hợp chung được giữ riêng trong workspace.

## Chức năng

1. Thêm sách, tạp chí, báo.
2. Hiển thị danh sách, tìm theo mã hoặc một phần tên (phân biệt hoa/thường).
3. Sửa giữ nguyên mã, loại và số bản đang mượn; xóa bị chặn khi đang mượn.
4. Selection Sort theo năm; Quick Sort theo giá trị, đều tăng dần.
5. Thống kê số đầu tài liệu, tổng số bản, số còn và số đang mượn.
6. Lưu/đọc `Sach.txt`, `TapChi.txt`, `Bao.txt` trong thư mục `data`.

Nhập chuỗi có khoảng trắng trực tiếp, không thêm ngoặc kép. Ngày theo `dd/mm/yyyy`. Tài liệu mới trên demo phải có số lượng còn bằng tổng số lượng. Nhập số sai định dạng được yêu cầu nhập lại; dữ liệu sai điều kiện nghiệp vụ bị từ chối. Chương trình không tự lưu khi thoát.

Để dùng mẫu trên bản clone mới, sao chép ba tệp từ `data_mau` sang `data`, rồi chọn 11 trong demo. Dữ liệu mẫu là dữ liệu minh họa, không phải hồ sơ thư viện thật.

```powershell
New-Item -ItemType Directory -Path data -Force
Copy-Item data_mau/*.txt data
```

## OOP, dữ liệu và tệp

`TaiLieu` là lớp trừu tượng, có hàm hủy ảo và hai hàm thuần ảo `xuat() const`, `tinhTienPhat(int) const`. Các lớp con ghi đè nhập, xuất, kiểm tra và phạt. `DanhSachQuanLy<TaiLieu*>` dùng mảng động cùng số lượng/sức chứa, giữ được đa hình.

Mức phạt đề xuất trong đặc tả: sách 2.000, tạp chí 3.000, báo 1.000 đồng/ngày/bản. Số ngày không dương thì phạt bằng 0. Phần phiếu mượn sau này tính số ngày trễ và nhân với số bản mượn; phần 1 không tạo phiếu hoặc độc giả.

`nhap()` trả `bool`, nhập vào đối tượng tạm để lỗi không đổi đối tượng cũ. Constructor có tham số giữ giá trị đầu vào; `hopLe()` và lớp quản lý kiểm tra trước khi tiếp nhận. Thêm/sửa thành công thì lớp quản lý nhận quyền sở hữu con trỏ; thất bại thì người gọi hủy con trỏ mới. Con trỏ tìm thấy chỉ để truy cập, không được `delete`.

Tệp mới: dòng `THUVIEN_2`, số bản ghi, sau đó mỗi trường trên một dòng. Ba tệp tài liệu cũ có chuỗi ngoặc kép vẫn đọc được. Đọc sai, thiếu hoặc trùng mã giữ danh sách cũ; đọc riêng bị chặn khi có tài liệu đang mượn. Lưu ba tệp tuần tự chưa bảo đảm khôi phục cả bộ nếu lỗi ở tệp sau, nên kiểm tra thông báo và sao lưu dữ liệu cần giữ.

`ganKiemTraPhieuMuon(bool (*ham)(const std::string&))` là điểm nối phần phiếu: callback trả true nếu mã tài liệu còn phiếu đang mượn. Kiểm tra số bản còn/tổng vẫn hoạt động khi chưa gắn callback. Các quy tắc phiếu, friend và OOP của phần tiếp theo sẽ được tích hợp sau, không kéo phụ thuộc chưa commit vào phần 1.

Tìm mã tuần tự dùng `timTheoMa`; demo dùng `timNhiPhan` trên mảng con trỏ phụ đã sắp mã. Vì dựng/sắp lại mảng bằng Selection Sort mỗi lần, toàn bộ lần gọi không chỉ có chi phí O(log n).

## Kiểm thử và tài liệu yêu cầu

`tests/kiemThuTaiLieu.cpp` kiểm tra dữ liệu, kho, đa hình, thêm/sửa/xóa, tìm/sắp, template và tệp mới/cũ. `tests/kiemThuMenuTaiLieu.ps1` chạy demo thật, gồm cả ba loại, nhập sai, mã trùng, EOF, lưu/đọc và dữ liệu mẫu. Kết quả được lấy từ thực thi, không gán trước trạng thái đạt.

Hai tài liệu giáo viên giữ ở thư mục gốc: `BaiTapLon_GiaoVien.docx.docx`, `DacTaChiTiet_Bai1.docx.docx`. Các bản code mẫu, ghi chú và phần tích hợp chưa thuộc commit này vẫn giữ trên máy. Commit phần 1 chưa tạo báo cáo hay sơ đồ lớp chính thức.

File thực thi và dữ liệu chạy không theo dõi Git; có thể tạo lại bằng các lệnh trên khi cần nộp. `.gitignore` không bỏ qua mã nguồn, tài liệu giáo viên hoặc `data_mau`.
