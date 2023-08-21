#pragma once
#include "wta_LoadAnim.h"

namespace wta {

    class DrawAnim {
    public:
        // コンストラクタでCSVからアニメーションデータをロード
        DrawAnim(const std::string& csvPath, const std::string& basePath);

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

//アニメーションの描画を行うクラス
