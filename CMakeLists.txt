cmake_minimum_required(VERSION 3.16)
project(QuanLyTaiLieu LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(taiLieu NhapXuat.cpp TaiLieu.cpp Sach.cpp TapChi.cpp Bao.cpp QuanLyTaiLieu.cpp)
target_include_directories(taiLieu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(demoTaiLieu demoTaiLieu.cpp)
target_link_libraries(demoTaiLieu PRIVATE taiLieu)
add_executable(kiemThuTaiLieu tests/kiemThuTaiLieu.cpp)
target_link_libraries(kiemThuTaiLieu PRIVATE taiLieu)
enable_testing()
add_test(NAME kiemThuTaiLieu COMMAND kiemThuTaiLieu)
if(WIN32)
    find_program(POWERSHELL_EXECUTABLE powershell)
    if(POWERSHELL_EXECUTABLE)
        add_test(NAME kiemThuMenuTaiLieu COMMAND "${POWERSHELL_EXECUTABLE}"
            -NoProfile -ExecutionPolicy Bypass
            -File "${CMAKE_CURRENT_SOURCE_DIR}/tests/kiemThuMenuTaiLieu.ps1"
            -TepChay $<TARGET_FILE:demoTaiLieu>)
    endif()
endif()
