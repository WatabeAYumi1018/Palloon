#pragma once
#include "wta_LoadAnim.h"

//LoadAnimクラスを基に、アニメーションの描画を行うクラス

namespace wta
{
    class DrawAnim 
    {
    public:
        // コンストラクタでCSVからアニメーションデータをロード
        DrawAnim(const std::string& csvPath, const std::string& basePath);

    private:
        std::vector<CsvAnimData> animations;         //すべてのアニメーションデータ
        const CsvAnimData* currentAnim = nullptr;    //現在のアニメーション
        float elapsedTime;							 //経過時間
        int currentFrame;							 //現在のフレーム
        float frameDuration;		                 //1フレームの時間（アニメーション描画のスピード調整）

        float lastFrameElapsedTime = 0.0f;
        const float LAST_FRAME_DURATION = 2.0f; // 最後のフレームを表示する時間


    public:
        // 指定IDのアニメーションをセット
        void SetAnimation(int id);

        // アニメーション描画
        void Draw(float delta_time, tnl::Vector3 pos, float scale = 1.0f, float angle = 0.0f);
    };
}
