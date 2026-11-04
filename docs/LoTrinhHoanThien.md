# Lộ trình hoàn thiện và bàn giao thư viện

Ưu tiên: đúng đề, chương trình chạy thật, dễ hiểu theo docs/phancode1.cpp. Tài liệu mẫu định hướng cách trình bày; không dùng bits/stdc++.h, tên biến che khuất std hoặc chức năng chỉ in thông báo trong mẫu để thay nghiệp vụ thật.

## Chặng 1. Chốt mã nguồn

1. Đối chiếu hai đề bài với bảng docs/KiemToanChucNang_HienTai.md.
2. Giữ cấu trúc .h/.cpp, không viết lại các lớp đã đúng. Dùng mảng, vòng lặp, điều kiện và thuật toán tự cài; giữ const, override, destructor ảo và cấm copy ở đối tượng sở hữu bộ nhớ.
3. main.cpp chỉ tạo một QuanLyThuVien và gọi menuChinh(thuVien). Menu dùng chung hệ thống bằng tham chiếu, do while và switch. Không đặt đọc tệp, xử lý phiếu hoặc danh sách toàn cục vào main.
4. Trình bày mỗi lựa chọn menu trên một dòng code. Các hàm quản lý và tính toán tách khỏi phần nhập lựa chọn.
5. Build và chạy sáu bộ kiểm thử trên bản sao nguồn sạch. Dữ liệu kiểm thử trong build, không sửa dữ liệu mẫu gốc.

## Chặng 2. Lưu GitHub

Chỉ stage đúng nguồn, cấu hình build, kiểm thử, mẫu tích hợp và hướng dẫn liên quan đã kiểm tra. Commit và push bình thường trên tich-hop-thuvien theo yêu cầu hiện tại; không merge main hoặc force push. Giữ nguyên .vscode/settings.json và docs/BaoCaoTienDo_Phan2_DocGia_NhanSu.docx. Báo cáo Word/PDF nháp trong BaoCao_NopBai chưa được coi là bản báo cáo cuối đã duyệt, không đưa vào commit mã nguồn này.

## Chặng 3. Bàn giao cho nhóm

Viết báo cáo ngắn theo từng phần: main/menu; cấu trúc kế thừa; quyền sở hữu con trỏ; luồng mượn/trả; đồng bộ nhân sự; đọc/lưu an toàn; thống kê và thực nghiệm. Mỗi đoạn khó có ví dụ nhỏ, lý do phải dùng và file cần đọc. Tạo bản trong docs để người dùng tự chuyển cho thành viên; không tự gửi tin nhắn hoặc email.

## Chặng 4. Hồ sơ nộp cuối

Sau khi nhóm xem chương trình, cập nhật Word/PDF theo code cuối và kết quả thật. Điền tên trường, cô, lớp và thành viên; kiểm tra từng trang, sơ đồ và bảng số đo. Thử trên máy nộp. Chỉ bổ sung phần bắt buộc còn thiếu; không thêm database, GUI hoặc đăng nhập ngoài đề.

## Điều kiện chốt

Sáu bộ kiểm thử đạt trên nguồn sẽ lưu, git diff --check không lỗi, danh sách staged đúng và không có file cá nhân/build. Báo rõ giới hạn: chưa có sanitizer hoạt động ở môi trường hiện tại, chín lần đổi tên không nguyên tử trước mất điện, mã người duyệt lịch sử không chứng minh danh tính nếu dữ liệu bị sửa ngoài. Không dùng từ hoàn hảo hoặc không còn lỗi chỉ vì kiểm thử đạt.
