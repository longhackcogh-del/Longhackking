# Hệ thống Quản lý Thư viện Đại học

Chương trình C++ dạng console, giữ các lớp và kiến thức OOP trong hai tài liệu bài tập lớn. Code mẫu `docs/phancode1.cpp` chỉ dùng làm tham khảo phong cách.

## Biên dịch và chạy trên Windows

Cần MinGW có `g++`, `ar` trong PATH. Chạy tại thư mục gốc dự án:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -KiemThu
.\build\verification\thuVien.exe
```

Script biên dịch với C++17, `-Wall -Wextra -Wpedantic -O2`. File mới được đặt trong `build/verification`, không thay các file thực thi cũ của dự án.

Nếu máy có CMake:

```powershell
cmake -S . -B build/cmake
cmake --build build/cmake
ctest --test-dir build/cmake --output-on-failure
```

Máy dùng để kiểm tra lần này không có CMake trong PATH; kết quả biên dịch và kiểm thử được lấy từ `build.ps1`.

## Sử dụng

Menu chính có bảy nhóm: tài liệu, độc giả, nhân viên, thủ thư trưởng, phiếu mượn/trả, vi phạm và báo cáo. Mỗi menu dùng `do...while` và `switch...case`. `main()` chỉ gọi `menuChinh()`.

- Nhập chuỗi có khoảng trắng trực tiếp, không thêm dấu ngoặc kép.
- Nhập ngày theo `dd/mm/yyyy`.
- Vị trí chèn bắt đầu từ 0.
- Tài liệu mới: số lượng còn bằng tổng số lượng.
- Độc giả mới: số đang mượn bằng 0. Mượn/trả sẽ cập nhật các số lượng này.
- Khi sửa, giữ nguyên mã và số đang mượn. Nhập lỗi không thay đối tượng cũ.
- Trả trễ tự ghi vi phạm `VP_<maPhieu>`; menu ghi nhận kiểm tra và từ chối ghi trùng.
- Lưu/đọc trong mỗi menu đồng bộ cả chín tệp tại `data`. Chương trình không tự lưu khi thoát.
- Đọc tệp thay toàn bộ dữ liệu bằng bản lưu nếu bản lưu hợp lệ; nên lưu các thay đổi cần giữ trước khi đọc.
- Phiếu đã trả giữ lại lịch sử. Có thể xóa tài liệu/độc giả sau khi hết mượn; mã còn trong lịch sử không được cấp cho đối tượng mới.

Dữ liệu minh họa nằm trong `data_mau`, dùng tên và giao dịch phục vụ kiểm thử, không phải hồ sơ thư viện thực tế. Muốn dùng mẫu, sao chép chín tệp sang `data`, chạy chương trình rồi chọn chức năng đọc tệp.

## Quy ước nghiệp vụ

Các thông số dưới đây lấy từ phần đề xuất trong đặc tả, không phải giá trị cố định trong đề gốc:

| Nội dung | Giá trị |
|---|---|
| Hạn mức sinh viên | 5 tài liệu |
| Hạn mức giảng viên | 10 tài liệu |
| Phạt sách / tạp chí / báo | 2.000 / 3.000 / 1.000 đồng mỗi ngày mỗi bản |
| Thu nhập thủ thư trưởng | Lương cơ bản × hệ số lương + hệ số phụ cấp × 2.000.000 |

Tính ngày theo lịch Gregory, có kiểm tra năm nhuận. Ngày trả bằng hạn trả không phạt. Tài khoản khóa không được mượn thêm nhưng vẫn được trả.

Thông tin độc giả trong hồ sơ thủ thư trưởng thể hiện nhánh kế thừa GiangVien. Danh sách mượn/trả quản lý các hồ sơ SinhVien/GiangVien tại menu độc giả; hồ sơ thủ thư trưởng trong menu nhân sự không tự tạo hồ sơ mượn.

## Định dạng tệp

Mỗi tệp mới có:

```text
THUVIEN_2
<so_ban_ghi>
<truong_1>
<truong_2>
...
```

Mỗi trường nằm trên một dòng, số thực lưu với độ chính xác 17 chữ số. Thứ tự các trường nằm trong hàm `ghi()` và `nhap()/doc()` của từng lớp.

Ba tệp tài liệu vẫn đọc được định dạng cũ dùng chuỗi trong ngoặc kép, gồm cả ký tự được escape. Đọc toàn hệ thống cần đủ chín tệp và dữ liệu mượn/trả nhất quán. Các tệp rỗng ở định dạng mới vẫn phải có hai dòng đầu.

Khi lưu, chương trình ghi vào `data/.dang_luu` trước, sau đó thay tệp. Nếu thao tác thay bị lỗi, chương trình khôi phục các tệp đã thay từ bản sao. Cơ chế này không bảo đảm giao dịch khi máy mất điện; nếu còn `.dang_luu` sau gián đoạn, cần kiểm tra các bản sao trước lần lưu tiếp theo.

## Kiểm thử và tài liệu

- `tests/kiemThuTaiLieu.cpp`: dữ liệu, đa hình, kho, thêm/sửa/xóa, tìm, sắp xếp, tệp mới/cũ, template.
- `tests/kiemThuThuVien.cpp`: kế thừa ảo, nhân sự, mượn/trả, friend, toán tử, phạt, dữ liệu liên kết, khôi phục lỗi lưu và thuật toán.
- `tests/kiemThuMenu.ps1`: chạy ứng dụng thực qua các menu, kiểm tra output và dữ liệu lưu; các tệp thử nằm riêng dưới `build/verification/kiem_thu_menu`.
- [Bảng đối chiếu yêu cầu](docs/DoiChieuYeuCau.md).
- [Báo cáo cài đặt và kiểm thử](docs/BaoCao.md).
- [Số liệu thực nghiệm chạy thật](docs/KetQuaThucNghiem.csv).

Ngoại lệ C++ chỉ còn dùng khi `operator[]` trả tham chiếu nhưng nhận chỉ số sai. Các thao tác nhập liệu và nghiệp vụ báo thành công/thất bại bằng `bool`.
