#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "Effect.h"

class Enemy;

class EffectBoss : public Effect
{
public:

    EffectBoss(Enemy* enemy, eEffectBossType effectType);
    ~EffectBoss();

private:

    //-----定数-----//
    const int FIREBALL_SIZE = 100;  // ファイアーボールの大きさ
    const float FIREBALL_SPEED = 10.0f;  // ファイアーボールの速度

    //-----メンバ変数-----//
    tnl::Vector3 m_fireball_pos;  // ファイアーボールの位置
    tnl::Vector3 m_fireball_direction; // ファイアーボールが飛ぶ方向

    std::vector<tnl::Vector3> m_collision_circles_pos;		/*5つの円の座標*/

    
    eEffectBossType e_effectType = eEffectBossType::None;

    Enemy* m_enemy = nullptr;				/*プレイヤー*/


    bool m_is_fireball = false;  /*火炎ボール*/
    bool m_is_flame = false;     /*火炎放射*/

    void FireballHandle();
    void FlameHandle();
    void EffectHandle();

public:

    void CalculateCollisionCircles();

    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;
};