#pragma once
#include <string>
#include "../engine/GameEngine.h"

//csvファイルからアニメーションデータを読み込み、ファイル操作にて画像ロードを行う

namespace wta 
{
    //csv記入のデータを格納する構造体
    struct CsvAnimData 
    {
        //-----メンバ変数-----//
        int s_id;
        std::string s_characterName;
        std::string s_action;
        int s_direction;
        std::string s_fileName;
        bool s_loop;
        std::vector<int> s_animImage;	//画像ハンドルIDを格納する
        
        //-----メンバ関数-----//
        //画像をロードする
        void LoadImages(const std::string& basePath);
        
        int GetAnimID(std::string action, int direction);
    };
    //csvからアニメーションデータを読み込む
    std::vector<CsvAnimData> LoadAnimationData(const std::string& csvPath, const std::string& basePath);

}