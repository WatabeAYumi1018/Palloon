#pragma once
#include "../../wta_library/wta_LoadAnimation.h"

namespace wta {

    class AnimLoad {
    public:
        // コンストラクタでCSVからアニメーションデータをロード
        AnimLoad(const std::string& csvPath, const std::string& basePath);

    private:
        std::vector<CsvAnimData> animations;    // すべてのアニメーションデータ
        const CsvAnimData* currentAnim = nullptr;    // 現在のアニメーション
        float elapsedTime;
        int currentFrame;
        float frameDuration;		                 //1フレームの時間（アニメーション描画のスピード調整）

	public:
        // 指定IDのアニメーションをセット
        void SetAnimation(int id);

        // アニメーションを描画
        void Draw(float delta_time, tnl::Vector3 pos, float scale = 1.0f, float angle = 0.0f);
        
    };
}

//アニメーションループ画像の読み取りを行うクラス
//char*からstd::stringへの変換(何かあった時のため保持)
//AnimLoadLoop(const char* pathName);
//~AnimLoadLoop();
//
////ファイルを読み込む関数
//void loadAnimLoopFile(const char* path);