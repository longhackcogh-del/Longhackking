cmake_minimum_required(VERSION 3.16)
project(QuanLyThuVien LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(taiLieu
    NhapXuat.cpp TaiLieu.cpp Sach.cpp TapChi.cpp Bao.cpp QuanLyTaiLieu.cpp
    Nguoi.cpp DocGia.cpp SinhVien.cpp GiangVien.cpp NhanVienThuThu.cpp ThuThuTruong.cpp
    PhieuMuon.cpp NhatKyViPham.cpp QuanLyDocGia.cpp QuanLyNhanVien.cpp
    QuanLyThuThuTruong.cpp QuanLyPhieuMuon.cpp QuanLyViPham.cpp QuanLyThuVien.cpp
    ThongKe.cpp ThucNghiem.cpp)
target_include_directories(taiLieu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(thuVien main.cpp Menu.cpp)
target_link_libraries(thuVien PRIVATE taiLieu)
add_executable(demoTaiLieu demoTaiLieu.cpp Menu.cpp)
target_link_libraries(demoTaiLieu PRIVATE taiLieu)
add_executable(kiemThuTaiLieu tests/kiemThuTaiLieu.cpp)
target_link_libraries(kiemThuTaiLieu PRIVATE taiLieu)
add_executable(kiemThuThuVien tests/kiemThuThuVien.cpp)
target_link_libraries(kiemThuThuVien PRIVATE taiLieu)
enable_testing()
add_test(NAME kiemThuTaiLieu COMMAND kiemThuTaiLieu)
add_test(NAME kiemThuThuVien COMMAND kiemThuThuVien)
if(WIN32)
    find_program(POWERSHELL_EXECUTABLE powershell)
    if(POWERSHELL_EXECUTABLE)
        add_test(NAME kiemThuMenu COMMAND "${POWERSHELL_EXECUTABLE}"
            -NoProfile -ExecutionPolicy Bypass
            -File "${CMAKE_CURRENT_SOURCE_DIR}/tests/kiemThuMenu.ps1"
            -TepChay $<TARGET_FILE:thuVien>)
    endif()
endif()
