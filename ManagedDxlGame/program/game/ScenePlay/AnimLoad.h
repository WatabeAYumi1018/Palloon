#pragma once
#include "../../engine/GameEngine.h"

//別々のpngファイルを読み込んで、それぞれの画像をループ表示してアニメーションを再生するクラス
class AnimLoad {

public:
    AnimLoad(const std::string pathName,bool isLoop);
    ~AnimLoad();

private:
    //-----メンバ変数-----//
    std::vector<int> Imgs;      //読み込んだpng画像のハンドルを格納する配列
    int numImgs;				//読み込んだpng画像の数  
    bool loopFlag; 			    //ループするかどうか
    bool animFinished;			//アニメーションが終了したかどうか
    int currentFrame;			//現在のフレーム
    float elapsedTime;			//経過時間
    float frameDuration;		//1フレームの時間（アニメーション描画のスピード調整）

public:
    //-----メンバ関数-----//
    //ファイルを読み込む関数
    void loadAnimFile(const std::string folderPath);
    //アニメーションを描画する関数
    void drawAnimFile(float delta_time, tnl::Vector3 pos, float angle=0, float scale=1.0f);
    //アニメーションが終了したかどうかを返す関数
    bool isAnimFinished() const { return animFinished; }
    //アニメーションをリセットする関数
    void resetAnim();
};

//アニメーションループ画像の読み取りを行うクラス

//char*からstd::stringへの変換(何かあった時のため保持)
//AnimLoadLoop(const char* pathName);
//~AnimLoadLoop();
//
////ファイルを読み込む関数
//void loadAnimLoopFile(const char* path);