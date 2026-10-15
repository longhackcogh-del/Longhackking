# Đối chiếu yêu cầu bài tập lớn

Nguồn: `BaiTapLon_GiaoVien.docx.docx`, `DacTaChiTiet_Bai1.docx.docx` ở thư mục gốc.

Thứ tự áp dụng: đúng đề giáo viên, đúng thuật toán và chạy được, sau đó chọn cách viết đơn giản theo `docs/phancode1.cpp`.

## Lớp và chức năng

| Yêu cầu | File, hàm thực hiện |
|---|---|
| Người: thông tin bắt buộc, hàm tạo/hủy ảo, nhập/xuất | Nguoi.h/.cpp: nhap, xuat, hopLe |
| Độc giả trừu tượng, kế thừa ảo Nguoi | DocGia.h/.cpp: layGioiHanMuon thuần ảo, kiemTraDieuKienMuon |
| Sinh viên, thông tin học tập, hạn mức | SinhVien.h/.cpp: nhap, xuat, layGioiHanMuon |
| Giảng viên, học vị, công tác không âm | GiangVien.h/.cpp: nhap, xuat, hopLe, layGioiHanMuon |
| Nhân viên kế thừa ảo Nguoi, lương và hệ số dương | NhanVienThuThu.h/.cpp: nhap, xuat, hopLe, tinhLuong |
| Thủ thư trưởng kế thừa hai nhánh, chung một Nguoi | ThuThuTruong.h/.cpp: nhap, xuat, tinhThuNhap |
| Xem/duyệt vi phạm | ThuThuTruong.cpp: xemNhatKyViPham, duyetViPham; QuanLyViPham.cpp: duyet |
| Tài liệu trừu tượng, kho và giá hợp lệ | TaiLieu.h/.cpp: xuat và tinhTienPhat thuần ảo, hopLe, giamSoLuong, tangSoLuong |
| Sách, tạp chí, báo có nhập/xuất và tiền phạt riêng | Sach.h/.cpp, TapChi.h/.cpp, Bao.h/.cpp |
| Phiếu: mã liên quan, mã phiếu trùng, tồn kho, hạn mức | QuanLyPhieuMuon.cpp: lapPhieu; PhieuMuon.cpp: lapPhieu |
| Mượn: giảm kho, tăng số đang mượn | PhieuMuon.cpp: lapPhieu |
| Trả: kiểm tra ngày, chặn trả hai lần, cập nhật hai danh sách | PhieuMuon.cpp và QuanLyPhieuMuon.cpp: traTaiLieu |
| Ngày trễ đúng lịch và tiền phạt đa hình | NhapXuat.cpp: doiNgay; PhieuMuon.cpp: tinhSoNgayTre, tinhTienPhat |
| Vi phạm ghi một lần, thanh toán không trùng | QuanLyViPham.cpp: ghiViPham; NhatKyViPham.cpp: thanhToanPhat |
| Tổng phạt chưa trả, đã trả, số lần vi phạm | QuanLyViPham.cpp: tinhTongTienPhatChuaThanhToan, tinhTongTienPhatDaThanhToan, demViPham |

## Kiến thức và thuật toán

| Yêu cầu | Triển khai và nơi sử dụng |
|---|---|
| Đóng gói, constructor/destructor | Tất cả lớp dữ liệu; destructor ảo của Nguoi, DocGia, TaiLieu |
| Kế thừa đơn | SinhVien/GiangVien từ DocGia; Sach/TapChi/Bao từ TaiLieu |
| Kế thừa nhiều, lớp cơ sở ảo | ThuThuTruong từ GiangVien và NhanVienThuThu; DocGia và NhanVienThuThu kế thừa ảo Nguoi |
| Đa hình, hàm ảo, thuần ảo | Danh sách TaiLieu* và DocGia*; gọi xuat, tinhTienPhat, layGioiHanMuon |
| Mảng đối tượng | DanhSachQuanLy<NhanVienThuThu>, DanhSachQuanLy<ThuThuTruong>, DanhSachQuanLy<PhieuMuon>, DanhSachQuanLy<NhatKyViPham> |
| Mảng con trỏ đối tượng | DanhSachQuanLy<TaiLieu*>, DanhSachQuanLy<DocGia*> |
| Class template | DanhSachQuanLy.h: T* ds, soLuong, sucChua; them, chen, sua, xoa, xuat, timTheoKhoa, sapXep, operator[] |
| Tránh sao chép sở hữu | Cấm sao chép DanhSachQuanLy và hai lớp quản lý danh sách con trỏ; chỉ chuyển quyền khi thêm/sửa thành công |
| Template hoanDoi | Các thuật toán và đổi danh sách |
| Template timMax | Tính phạt, báo cáo, bảng băm |
| Template timMin | Báo cáo độc giả có số mượn thấp nhất |
| Template timKiemTuanTu | DanhSachQuanLy::timTheoKhoa, loại trùng độc giả khi liệt kê người mượn tài liệu |
| operator+ | DocGia.cpp; sử dụng ở ThongKe.cpp để cộng số đang mượn |
| operator<< | PhieuMuon.cpp; menu hiển thị và DanhSachQuanLy::xuat |
| operator< | PhieuMuon.cpp; Merge Sort theo mã phiếu |
| Friend kiemTraHanMuon | DocGia.h, PhieuMuon.h/.cpp; liệt kê quá hạn |
| Friend operator<< | PhieuMuon.h/.cpp; xuất phiếu |
| Friend kiemTraDieuKienMuon | DocGia.h, TaiLieu.h, DocGia.cpp; lập phiếu |
| Tìm tuần tự | Theo mã/tên/ca và các tiêu chí quản lý |
| Tìm nhị phân | QuanLyTaiLieu::timNhiPhan trên mảng con trỏ phụ sắp theo mã; trả đúng con trỏ tìm thấy |
| Bảng băm tự cài | ThuatToan.h: BangBamMa, thăm dò tuyến tính; QuanLyDocGia::timBangBam khi lập phiếu |
| Bubble Sort | QuanLyDocGia::sapXepTheoSoMuon |
| Selection Sort | QuanLyTaiLieu::sapXepTheoNam |
| Quick Sort | QuanLyTaiLieu::sapXepTheoGiaTri |
| Merge Sort | QuanLyPhieuMuon::sapXepTheoMa |
| Thực nghiệm ít nhất bốn kích thước | ThucNghiem.cpp: 100, 500, 1000, 2000; bốn sắp xếp và ba tìm kiếm |

Các hàm sắp xếp template trong ThuatToan.h còn được chạy trực tiếp trong thực nghiệm và kiểm thử. Không dùng vector, std::sort, bits/stdc++.h, lambda hoặc std::quoted trong mã ứng dụng/kiểm thử mới.

## Menu và tệp

| Nhóm | Chức năng thực hiện |
|---|---|
| Tài liệu | Thêm ba loại, xuất, tìm mã/tên, sửa, xóa, sắp năm/giá, thống kê, lưu/đọc |
| Độc giả | Thêm hai loại, xuất, tìm mã/tên, sửa, xóa, Bubble Sort, chèn k, hạn mức, lưu/đọc |
| Nhân viên | Thêm, xuất, tìm mã/ca, sửa, xóa, sắp hệ số, tính lương, lưu/đọc |
| Thủ thư trưởng | Thêm, xuất, tìm mã, quản lý hơn 10 nhân viên, sắp phụ cấp, thu nhập, lưu/đọc, xem/duyệt vi phạm |
| Phiếu | Lập, trả, xuất, tìm mã, theo độc giả, người đang mượn tài liệu, quá hạn, phạt, lưu/đọc, Merge Sort |
| Vi phạm | Ghi nhận từ phiếu, xuất, tìm độc giả, chưa thanh toán, thanh toán, tổng tiền, số lần, lưu/đọc |
| Báo cáo | Theo loại, kho, độc giả mượn nhiều nhất, tài liệu được mượn nhiều nhất, quá hạn, tiền phạt, thực nghiệm |

Menu.cpp chứa các menu do...while và switch...case. main.cpp và demoTaiLieu.cpp chỉ gọi menuChinh.

QuanLyThuVien.cpp điều phối chín tệp Sach, TapChi, Bao, SinhVien, GiangVien, NhanVienThuThu, ThuThuTruong, PhieuMuon, NhatKyViPham. Khi đọc, kiểm tra đúng kiểu, trùng mã, số lượng, các tham chiếu đang mượn, tiền phạt, nhật ký và người duyệt trước khi đổi dữ liệu.

Phiếu đã trả không buộc đối tượng gốc còn tồn tại sau khi xóa. Nhật ký vẫn phải khớp mã độc giả, mã phiếu, ngày trễ và tiền phạt đã ghi. Mã đối tượng đã có lịch sử không được dùng lại.

## Thay đổi trình bày và logic

- Trình bày: ngoặc, xuống dòng, chú thích chức năng, tên tiếng Việt không dấu, main tối giản.
- Giao diện kỹ thuật: nhap trả bool, bỏ unique_ptr/quoted, dùng con trỏ với quyền sở hữu rõ; định dạng tệp mới có bộ đọc tương thích cũ.
- Bảo toàn nghiệp vụ cũ: kiểm tra kho, mã trùng, giữ số đang mượn khi sửa, giữ đối tượng khi nhập lỗi, giữ danh sách khi đọc lỗi.
- Bổ sung bắt buộc: các lớp người/nhân sự, phiếu/vi phạm, friend/toán tử, các menu còn thiếu, thuật toán thứ ba, Bubble/Merge Sort, báo cáo và thực nghiệm.
