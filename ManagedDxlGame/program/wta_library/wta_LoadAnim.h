#pragma once
#include <string>
#include "../dxlib_ext/dxlib_ext.h"

//csvファイルからアニメーションデータを読み込み、ファイル操作にて画像ロードを行う

namespace wta {
    //csv記入のデータを格納する構造体
    struct CsvAnimData {

        //-----変数-----//
        int id;
        std::string characterName;
        std::string action;
        int direction;
        std::string fileName;
        bool loop;
        std::vector<int> animImage;	//画像ハンドルIDを格納する
        
        //-----関数-----//
        //画像をロードする
        void LoadImages(const std::string& basePath);
    };
    //csvからアニメーションデータを読み込む
    std::vector<CsvAnimData> LoadAnimationData(const std::string& csvPath, const std::string& basePath);
}