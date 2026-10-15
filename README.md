# Hệ thống Quản lý Thư viện Đại học

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
