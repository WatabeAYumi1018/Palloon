#include "AnimLoad.h"

namespace wta {

    AnimLoad::AnimLoad(const std::string& csvPath, const std::string& basePath):
       currentFrame(0), elapsedTime(0.0f), frameDuration(0.2f)
    {
        animations = LoadAnimationData(csvPath, basePath);
    }
    
    void AnimLoad::SetAnimation(int id) {
        for (const auto& anim : animations) {
            if (anim.id == id) {
                //アニメーションの種類が変わった場合は初期化
                if (currentAnim != &anim) {
                    elapsedTime = 0.0f;
                    currentFrame = 0;
                }
                currentAnim = &anim;
                return;
            }
        }
        currentAnim = nullptr;  // 見つからなかった場合はnullptrを設定
    }

    // アニメーションを描画
    void AnimLoad::Draw(float delta_time, tnl::Vector3 pos, float scale, float angle) {
        if (!currentAnim || currentAnim->animImage.empty()) return; //現在のアニメーションがない、空の場合何もしない
        elapsedTime += delta_time;
        if (elapsedTime >= frameDuration) {
            elapsedTime -= frameDuration;
            ++currentFrame;
            if (currentAnim->loop) {
                currentFrame %= currentAnim->animImage.size();
            }
            else if (currentFrame >= currentAnim->animImage.size()) {
                currentFrame = currentAnim->animImage.size() - 1;
            }
        }
        DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), scale, tnl::ToRadian(angle), currentAnim->animImage[currentFrame], TRUE);
    }
}
