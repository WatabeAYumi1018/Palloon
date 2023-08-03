#pragma once
#include "../../engine/GameEngine.h"

//別々のpngファイルを読み込んで、それぞれの画像をループ表示してアニメーションを再生するクラス
class AnimLoop{

public:
    AnimLoop();
    AnimLoop(const char* pathName);
    ~AnimLoop();

    void loadAnimLoopFile(const char* path);
    void drawAnimLoopFile(float delta_time,Vector3 pos, float angle=0, float scale=1.0f);

private:
    std::vector<int> Imgs;
    int NumImgs;
    bool LoopFlag; 
    int currentFrame;
    float elapsedTime;
    float frameDuration;
};