#pragma once
#include "../engine/GameEngine.h"
#include "MusicBGM.h"
#include "MusicSE.h"

class MusicManager 
{
public:

    MusicManager() {}

private:

    //-----ƒƒ“ƒo•Ï”-----//
    std::unique_ptr<MusicBGM> m_bgm;
    std::map<std::string, std::unique_ptr<MusicSE>> m_se;

public:

    //-----ƒƒ“ƒoŠÖ”-----//
    void LoadBGM(const std::string& path);                          /*BGM‚Ì“Ç‚İ‚İ*/
    void LoadSE(const std::string& key, const std::string& path);  /*Œø‰Ê‰¹‚Ì“Ç‚İ‚İ*/

    void PlayBGM();
    void StopBGM(); 

    void PlaySE(const std::string& key);
    void StopSE(const std::string& key); 
};
