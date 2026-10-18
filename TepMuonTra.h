#ifndef TEPMUONTRA_H
#define TEPMUONTRA_H
#include <filesystem>
#include <fstream>
#include <string>

// Chi dung cho hai tep cua module muon tra va vi pham.
// Chuong trinh ghi tuan tu; khong cho nhieu tien trinh cung ghi mot tep.
inline bool ghiTepMuonTra(const std::string& ten, const std::string& noiDung, std::string& loi){
    std::string tenTam = ten + ".tam";
    std::string tenSaoLuu = ten + ".saoLuu";
    std::error_code maLoi;
    loi.clear();
    bool coTepCu = std::filesystem::exists(ten, maLoi);
    if(maLoi){
        loi = "Khong kiem tra duoc tep " + ten;
        return false;
    }
    if(coTepCu){
        if(!std::filesystem::is_regular_file(ten, maLoi) || maLoi){
            loi = "Duong dan khong phai tep du lieu " + ten;
            return false;
        }
    }
    // Khong ghi de file lam viec co san cua lan chay khac.
    bool coTepTam = std::filesystem::exists(tenTam, maLoi);
    if(maLoi || coTepTam){
        loi = "Khong dung duoc tep tam " + tenTam;
        return false;
    }
    bool coSaoLuu = std::filesystem::exists(tenSaoLuu, maLoi);
    if(maLoi || coSaoLuu){
        loi = "Khong dung duoc tep sao luu " + tenSaoLuu;
        return false;
    }

    //=====ghi xong tep tam truoc khi thay tep cu=====
    std::ofstream tep(tenTam);
    if(!tep){
        loi = "Khong mo duoc tep tam " + tenTam;
        return false;
    }
    tep << noiDung;
    tep.close();
    if(!tep){
        loi = "Loi ghi tep tam " + tenTam;
        std::filesystem::remove(tenTam, maLoi);
        return false;
    }
    if(coTepCu){
        std::filesystem::rename(ten, tenSaoLuu, maLoi);
        if(maLoi){
            loi = "Khong tao duoc ban sao tep cu " + ten;
            std::filesystem::remove(tenTam, maLoi);
            return false;
        }
    }

    //=====thay tep dich va khoi phuc neu that bai=====
    std::filesystem::rename(tenTam, ten, maLoi);
    if(maLoi){
        loi = "Khong thay duoc tep " + ten;
        if(coTepCu){
            std::filesystem::rename(tenSaoLuu, ten, maLoi);
            if(maLoi){
                // Giu ca ban sao va tep tam de phuc hoi thu cong.
                loi += "; du lieu cu con tai " + tenSaoLuu;
                return false;
            }
        }
        std::filesystem::remove(tenTam, maLoi);
        return false;
    }
    if(coTepCu){
        std::filesystem::remove(tenSaoLuu, maLoi);
        if(maLoi){
            // Tep moi da luu thanh cong; chi viec don ban sao bi loi.
            loi = "Da luu; con ban sao can kiem tra " + tenSaoLuu;
        }
    }
    return true;
}
#endif
