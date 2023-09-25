#pragma once
#include "../engine/GameEngine.h"
#include "MusicBGM.h"
#include "MusicSE.h"

class MusicManager 
{
private:

    MusicManager() {}

    //-----メンバ変数-----//
    std::unique_ptr<MusicBGM> m_bgm;
    std::map<std::string, std::unique_ptr<MusicSE>> m_se;

public:
    // シングルトンインスタンスを取得するための関数
    static MusicManager& GetInstance()
    {
        static MusicManager instance;  // 静的変数としてシングルトンインスタンスを作成
        return instance;
    }

    //-----メンバ関数-----//
    void LoadBGM(const std::string& path);                          /*BGMの読み込み*/
    void LoadSE(const std::string& key, const std::string& path);  /*効果音の読み込み*/

    void PlayBGM();
    void StopBGM(); 

    void PlaySE(const std::string& key);
    void StopSE(const std::string& key); 
};
