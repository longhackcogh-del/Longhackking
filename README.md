# Longhackking

Module quản lý tài liệu – Bài 1, Nhóm 1, giai đoạn 1. C++17, không dùng
`vector`, `std::sort` hoặc `bits/stdc++.h`. Không có thay đổi `main.cpp` chung.

## Tài liệu đầu vào

Thư mục `docs` rỗng tại thời điểm triển khai. Đã đọc trực tiếp nội dung Word
của `BaiTapLon_GiaoVien.docx.docx` và `DacTaChiTiet_Bai1.docx.docx` ở gốc dự án.
Áp dụng phần tài liệu của Bài 1 và mức phạt đề xuất trong bản đặc tả:
sách 2.000, tạp chí 3.000, báo 1.000 đồng/ngày trễ; ngày trễ âm tính bằng 0.

## Biên dịch và chạy bằng PowerShell

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -I. TaiLieu.cpp Sach.cpp TapChi.cpp Bao.cpp QuanLyTaiLieu.cpp tests/kiemThuTaiLieu.cpp -o build/kiemThuTaiLieu.exe
.\build\kiemThuTaiLieu.exe
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -I. TaiLieu.cpp Sach.cpp TapChi.cpp Bao.cpp QuanLyTaiLieu.cpp demoTaiLieu.cpp -o build/demoTaiLieu.exe
.\build\demoTaiLieu.exe
```

Hoặc dùng CMake: `cmake -S . -B build/cmake`,
`cmake --build build/cmake`, `ctest --test-dir build/cmake --output-on-failure`.
Lệnh CMake được cung cấp để tiện tích hợp; kết quả kiểm thử thực tế bên dưới
được chạy bằng g++.

Demo có đủ 11 lựa chọn quản lý tài liệu. Chọn 11 để đọc mẫu từ `data`.
Khi thêm/sửa, nhập một dòng theo hướng dẫn; chuỗi có khoảng trắng đặt trong
dấu ngoặc kép. Nhập lỗi bị từ chối và có thể thao tác lại. Ngày dùng `dd/mm/yyyy`.
Tên được tìm theo chuỗi con, phân biệt chữ hoa/chữ thường.
Sửa giữ nguyên mã, loại tài liệu và số bản đang mượn, nhưng cho phép thay đổi
tổng số bản nếu vẫn giữ được số đang mượn.

## Mã nguồn

- `TaiLieu.h/.cpp`: lớp trừu tượng, kiểm tra dữ liệu chung, tồn kho, nhập/xuất chung.
- `Sach.h/.cpp`, `TapChi.h/.cpp`, `Bao.h/.cpp`: thông tin riêng, nhập/xuất và phạt đa hình.
- `DanhSachQuanLy.h`: template mảng động, thêm/chèn/sửa/xóa, kiểm tra chỉ số.
- `ThuatToan.h`: các hàm template; đổi chỗ dùng trong sắp xếp, max dùng tính phạt;
  min và tìm kiếm tuần tự được kiểm thử, chưa dùng trong nghiệp vụ module.
- `QuanLyTaiLieu.h/.cpp`: thêm, hiển thị, tìm mã/tên, sửa, xóa có bảo vệ,
  Selection Sort theo năm tăng dần, Quick Sort theo giá trị tăng dần, thống kê,
  lưu/đọc ba loại đối tượng.
- `demoTaiLieu.cpp`: menu độc lập; `tests/kiemThuTaiLieu.cpp`: kiểm thử độc lập.
- `data/Sach.txt`, `data/TapChi.txt`, `data/Bao.txt`: dữ liệu mẫu.

## Bộ nhớ và tích hợp

`QuanLyTaiLieu` sở hữu các đối tượng qua mảng con trỏ `TaiLieu*`. Thêm/sửa
nhận `unique_ptr<TaiLieu>` để giải phóng tự động khi bị từ chối hoặc có lỗi.
Chỉ truyền đối tượng mới, chưa thuộc danh sách nào. Không tạo `unique_ptr`
từ con trỏ lấy bởi `timTheoMa`.
Các con trỏ trả về chỉ được mượn, không được `delete`; mất hiệu lực khi sửa,
xóa, đọc thay danh sách hoặc hủy quản lý. Không gọi `nhap` trực tiếp trên tài
liệu đang thuộc danh sách; dùng `sua` để bảo vệ mã và số bản đang mượn.
Không sao chép lớp danh sách và quản lý, tránh giải phóng hai lần.

Module mượn–trả cần gọi `giamSoLuong(n)` và `tangSoLuong(n)`, kiểm tra giá trị
trả về, đồng thời cập nhật phiếu và độc giả. `tinhTienPhat` được gọi qua
`TaiLieu*`. Gắn `ganKiemTraPhieuMuon` với hàm kiểm tra phiếu chưa trả theo mã
để chặn xóa cả khi dữ liệu phiếu và kho chưa khớp; hiện đã kiểm thử bằng hàm giả lập.
Luôn chặn xóa khi `soLuongCon < soLuongTong`.

Đọc file khôi phục đúng lớp và số lượng còn; trùng mã giữa các file, thiếu
file, dư trường hay dữ liệu không hợp lệ đều bị từ chối. Danh sách hiện tại
giữ nguyên nếu đọc lỗi. Đọc thay thế bị chặn khi danh sách hiện tại đang có
tài liệu mượn. Khi tích hợp toàn hệ thống, cần nạp và đối chiếu phiếu mượn
trước khi cho phép thao tác; giai đoạn này chưa đối chiếu với file phiếu.

Lưu ghi lần lượt ba file vào thư mục đã tồn tại và báo lỗi nếu ghi thất bại.
Đây chưa phải giao dịch nguyên tử cho cả ba file: nếu lỗi giữa chừng, những
file đã ghi trước đó có thể đã thay đổi. Nên sao lưu dữ liệu trước khi lưu.

## Kiểm thử thực tế

Biên dịch cả demo và kiểm thử bằng g++ với C++17 và các cờ cảnh báo nêu trên:
thành công, không cảnh báo. Bộ kiểm thử đạt 450 phép kiểm tra, gồm dữ liệu
không hợp lệ, ngày nhuận, danh sách rỗng, trùng mã, nhập lỗi không đổi đối
tượng, tồn kho, xóa/sửa có bảo vệ, đa hình, đọc/ghi, file hỏng/thiếu/dư trường,
khôi phục loại/giá/kho, mảng động và sắp xếp 200 tài liệu có khóa trùng nhau.
Demo đã chạy đọc dữ liệu mẫu, hiển thị và thống kê đúng ba loại.
Dữ liệu kiểm thử sinh riêng trong `build/du_lieu_kiem_thu`.

Các module độc giả, nhân sự, phiếu mượn–trả, nhật ký phạt và những thuật toán,
toán tử, hàm bạn, thực nghiệm còn lại của toàn bài sẽ triển khai ở các giai
đoạn tiếp theo. Chưa commit, push hay merge.
