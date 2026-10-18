# Hệ thống Quản lý Thư viện Đại học

## Chạy ứng dụng tích hợp — giai đoạn 1

Mở terminal PowerShell tại thư mục dự án trong VS Code. Cần `g++` hỗ trợ C++17 trong `PATH`:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
.\build\tich-hop\thuVien.exe
```

Chỉ chạy executable khi bước biên dịch thành công. Script dùng `-std=c++17 -Wall -Wextra -Wpedantic`, liệt kê nguồn tường minh và không đưa `main()` của kiểm thử hoặc code mẫu vào ứng dụng.

Menu 1–6 quản lý tài liệu, độc giả, nhân viên, thủ thư trưởng, mượn–trả và vi phạm trên cùng một `QuanLyThuVien`. Menu 7 gọi các hàm tìm kiếm và sắp xếp đã có. Nhập `0` để quay lại từ menu con, `11` để thoát ứng dụng. Nhập mỗi thông tin trên một dòng; ngày theo `dd/mm/yyyy`.

Mục 8 (thống kê nâng cao/thực nghiệm) và 9–10 (đọc/ghi toàn hệ thống) được đánh dấu **chưa triển khai**. Dữ liệu hiện chỉ ở bộ nhớ và mất khi thoát; chương trình không tự đọc hay lưu dữ liệu. Không dùng phiên bản này để lưu công việc thực tế.

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
