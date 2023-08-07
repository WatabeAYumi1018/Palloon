#pragma once
#include "../../engine/GameEngine.h"

//別々のpngファイルを読み込んで、それぞれの画像をループ表示してアニメーションを再生するクラス
class Anim {

public:
    Anim(const char* pathName);
    ~Anim();

    //ファイルを読み込む関数
    void loadAnimLoopFile(const char* path);                                                    
    //アニメーションを描画する関数
    void drawAnimLoopFile(float delta_time, tnl::Vector3 pos, const char* path, float angle=0, float scale=1.0f);

private:
    std::vector<int> Imgs;      //読み込んだpng画像のハンドルを格納する配列
    int NumImgs;				//読み込んだpng画像の数  
    bool LoopFlag; 			    //ループするかどうか
    int currentFrame;			//現在のフレーム
    float elapsedTime;			//経過時間
    float frameDuration;		//1フレームの時間（あsにメーション描画のスピード調整）
};