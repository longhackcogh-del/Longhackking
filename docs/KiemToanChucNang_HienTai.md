# Rà soát chức năng thư viện sau khi hoàn thiện menu

Phạm vi: mã nguồn trên nhánh tich-hop-thuvien, commit nền a06ea0e cùng các thay đổi chưa commit. Tài liệu này đối chiếu chức năng thực tế, không thay thế kết quả chạy mới sau khi sửa code tiếp. Báo cáo Word đã tạo trước đó là bản nháp và chưa cập nhật các lựa chọn menu con trong lượt rà soát này.

## Đối chiếu chức năng đề bài

| Nhóm yêu cầu | Đường gọi thực tế | Kết luận |
|---|---|---|
| Thêm sách, tạp chí, báo | Menu 1/1 → nhapTaiLieu → QuanLyThuVien::themTaiLieu → QuanLyTaiLieu::them | Có, kiểm tra loại/mã và số còn của hồ sơ mới |
| Xuất, tìm mã, tìm tên tài liệu | Menu 1/2,3,4 → hienThi, timTheoMa, timTheoTen | Có, dùng đa hình xuất đối tượng |
| Sửa, xóa tài liệu | Menu 1/5,6 → sua, xoa | Có, giữ mã/loại/số đang mượn; chặn xóa đang mượn |
| Sắp xếp năm/giá trị; kho và loại | Menu 1/7,8,9 → sapXepTheoNam, sapXepTheoGiaTri, thongKe | Có, Selection/Quick tự cài đặt |
| Thêm/xuất/tìm/sửa/xóa độc giả | Menu 2/1–6 → QuanLyThuVien và QuanLyDocGia | Có, chặn mã/nhân thân mâu thuẫn và xóa đang mượn |
| Bubble số đang mượn, chèn k, hạn mức | Menu 2/7,8,9 | Có; vị trí từ 0; hạn mức kiểm tra thêm số lượng dự kiến |
| Thêm/xuất/tìm mã/ca/sửa/xóa nhân viên | Menu 3/1–6 | Có; thêm/sửa/xóa qua điều phối kiểm tra hai danh sách nhân sự |
| Sắp xếp hệ số, tính lương | Menu 3/7,8 | Có, công thức và định dạng tiền tách biệt |
| Thủ thư trưởng: thêm/xuất/tìm, quản lý >10, sắp phụ cấp, thu nhập | Menu 4/1–6 | Có, giữ kế thừa nhiều và ảo |
| Sửa/xóa trưởng, xem/duyệt vi phạm | Menu 4/7–10 | Có; xóa không xóa dây chuyền độc giả/lịch sử |
| Chuyển vai trò nhân sự | Menu 3/9, 4/11 | Có theo phương án nhóm đã duyệt; giữ mã, nhân thân và lịch sử |
| Lập phiếu, trả, xuất, tìm | Menu 5/1–4 → QuanLyThuVien, QuanLyPhieuMuon, PhieuMuon | Có kiểm tra tài khoản, hạn mức, tồn kho, ngày, mã; không trả hai lần |
| Liệt kê phiếu/độc giả đang mượn, quá hạn, phạt | Menu 5/5–8 | Có; quá hạn theo ngày hệ thống; phạt qua hàm ảo TaiLieu và số lượng |
| Sắp mã phiếu | Menu 5/9 → sapXepTheoMa → mergeSort | Có, sử dụng operator< |
| Ghi/xuất/tìm theo độc giả/chưa thanh toán/thanh toán/tổng/đếm | Menu 6/1–7 | Có; trả trễ đã tự ghi, ghi lại bị chặn |
| Duyệt/tìm mã vi phạm | Menu 6/8,9 | Có; duyệt và thanh toán là hai trạng thái độc lập, không thêm điều kiện ngoài đề |
| Thống kê loại và tồn kho | Menu 8/1 | Có tổng số đầu, tổng số bản, số còn và đang mượn |
| Độc giả mượn nhiều nhất | Menu 8/2 → thongKeDocGia | Có đồng hạng; tính theo số đang mượn hiện tại; tổng dùng operator+; min dùng timMin |
| Tài liệu được mượn nhiều nhất | Menu 8/3 → thongKeTaiLieuMuonNhieu | Có; tính số bản trên toàn bộ lịch sử, không bỏ mã hồ sơ đã xóa |
| Phiếu quá hạn, tổng tiền đã/chưa thu | Menu 8/4,5 | Có, tái sử dụng quản lý hiện có |
| Thực nghiệm ≥4 kích thước | Menu 8/6 → thucNghiemThuatToan | Có 100/500/1000/2000; 4 sắp xếp, tuần tự, nhị phân và băm; kiểm tra đáp án và giải thích độ phức tạp |
| Đọc/lưu trong từng nhóm | Menu 1,2,3,5,6: mục 10 lưu, 11 đọc; menu 4: mục 12 lưu, 13 đọc | Đã bổ sung lối gọi dùng chung; luôn đọc/lưu cả bộ tránh lệch liên kết |
| Đọc/lưu ở menu chính | Menu 9/10 → docToanBo/luuToanBo | Có, hệ thống tạm, xác nhận, kiểm tra nhất quán và phục hồi |

Các lựa chọn đọc/lưu trong menu con gọi cùng chức năng toàn hệ thống đã duyệt, không gọi doc() riêng một quản lý. Số lựa chọn khác bản gợi ý của đề ở một số nhóm để giữ chức năng chuyển vai trò đã có; ý nghĩa được ghi rõ trên màn hình.

## Đối chiếu kiến thức kỹ thuật

| Yêu cầu | Bằng chứng |
|---|---|
| Class Template có ds/soLuong/sucChua, đủ thao tác và [] | DanhSachQuanLy.h; được dùng trong cả sáu quản lý |
| hoanDoi, timMax, timMin, timKiemTuanTu dùng thật | Sắp xếp/doi, ngày trễ/thống kê, thống kê min, tìm khóa/liệt kê và thực nghiệm |
| Tối thiểu 3 friend | kiemTraHanMuon, kiemTraDieuKienMuon, operator<< của PhieuMuon |
| Toán tử bắt buộc và sử dụng | DocGia::operator+ tính tổng thống kê; PhieuMuon << xuất, < Merge Sort; template [] |
| Kế thừa đơn/nhiều/ảo | Các lớp dẫn xuất; ThuThuTruong từ GiangVien và NhanVienThuThu dùng chung Nguoi |
| Lớp trừu tượng và đa hình | TaiLieu, DocGia; xuất và tính phạt qua lớp cơ sở |
| Ba tìm kiếm tự cài | Tuần tự, nhị phân trên mảng phụ đã sắp, BangBamMa thăm dò tuyến tính |
| Bốn sắp xếp tự cài | Bubble độc giả, Selection năm tài liệu, Quick giá trị tài liệu, Merge phiếu |
| Tách .h/.cpp, một main ứng dụng | main.cpp chỉ tạo hệ thống và gọi menu; tests và mẫu không liên kết vào app |
| Đọc ghi đúng chín tên | Sach, TapChi, Bao, SinhVien, GiangVien, NhanVienThuThu, ThuThuTruong, PhieuMuon, NhatKyViPham .txt |
| Không vector/std::sort/lambda | Không dùng trong phần cài đặt nghiệp vụ và bổ sung hiện tại |

## Giới hạn phải nói đúng

### Kết quả chạy trong lượt rà soát này

| Bộ | Đạt | Lỗi | Bằng chứng |
|---|---:|---:|---|
| Menu ứng dụng thật | 213 | 0 | build/menu-kiemthu-d5f0ac13fd0a4a78bc7b5861bcfb5fb6/ket_qua.txt |
| Thống kê, thuật toán và tìm/sắp tài liệu | 11359 | 0 | build/thongke-kiemthu-3a52f85c162a4df3903b336909fc5cb7/ket_qua.txt |
| Tích hợp | 237 | 0 | Terminal build.ps1 -KiemThu -ThuMucBuild build/ra-soat-tich-hop |
| Module 2 | 177 | 0 | build/tv2-kiemthu-3b61b623bc484bd9a1eb765a3ec84d48/ket_qua.txt |
| Module 3 | 311 | 0 | build/tv3-kiemthu-9cfa79d30f0e40cb8a20ff164b009ea4/ket_qua.txt |
| Đọc ghi toàn hệ thống | 228 | 0 | build/tep-he-thong-kiemthu-92862ce8c36642e8832828dcb7cfb3b4/ket_qua.txt |

Các log biên dịch cuối không có cảnh báo C++. Thử biên dịch chương trình nhỏ với -fsanitize=address,undefined thất bại vì linker không tìm được -lasan/-lubsan; xem build/ra-soat-bo-nho/sanitizer.log. Không báo kiểm tra bộ nhớ chuyên dụng đã đạt.

Đã đối chiếu SHA256: main.cpp, hai đề bài, docs/phancode1.cpp, bốn tệp data_mau cũ và hai file cá nhân không đổi. Không stage/commit/push.

Thực nghiệm dùng dữ liệu tạo riêng phục vụ đo, không phải hồ sơ giả bổ sung vào hệ thống. Mỗi sắp xếp đo ba lần; tìm kiếm 1000 truy vấn. Thời gian không bao gồm mọi tiền xử lý: dựng băm ghi riêng, nhị phân không gồm sắp xếp. Băm dùng chuỗi còn mảng dùng số, có khác chi phí kiểu khóa. Không suy ra băm luôn nhanh nhất từ một bảng đo.

Tệp lưu có cơ chế thử hoàn tác và phát hiện giao dịch dang dở, nhưng chín lần đổi tên không nguyên tử và không bảo đảm mất điện/hỏng ổ. Không hỗ trợ nhiều tiến trình ghi. Mã duyệt lịch sử được giữ nguyên; không thể chứng minh danh tính từ tệp đã sửa ngoài. Không tự tạo lại hồ sơ đã xóa.

Kiểm thử không chứng minh mọi đầu vào đều không có lỗi. Bản kiểm thử thống kê gồm nhiều phép kiểm tra trong vòng lặp nhỏ; số lượng lớn không đồng nghĩa từng ấy chức năng độc lập. Cần ghi đúng giới hạn kiểm tra bộ nhớ khi công cụ sanitizer không khả dụng.
