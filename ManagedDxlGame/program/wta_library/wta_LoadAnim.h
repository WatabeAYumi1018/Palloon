#pragma once
#include <string>
#include "../dxlib_ext/dxlib_ext.h"


namespace wta {
    //csv記入のデータを格納する構造体
    struct CsvAnimData {
        int id;
        std::string characterName;
        std::string action;
        int direction;
        std::string fileName;
        bool loop;
        std::vector<int> animImage;	//画像ハンドルIDを格納する

        void LoadImages(const std::string& basePath);
    };

    std::vector<CsvAnimData> LoadAnimationData(const std::string& csvPath, const std::string& basePath);
}