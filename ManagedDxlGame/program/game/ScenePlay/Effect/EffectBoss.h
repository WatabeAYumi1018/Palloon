#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "Effect.h"

class Enemy;
class Player;

class EffectBoss : public Effect
{
public:

    EffectBoss(Enemy* enemy,Player* player);
    ~EffectBoss();

private:

    //-----定数-----//
    const int FIREBALL_SIZE = 100;  // ファイアーボールの大きさ
    const float FIREBALL_SPEED = 10.0f;  // ファイアーボールの速度

    //-----メンバ変数-----//
    tnl::Vector3 m_fireball_pos;  // ファイアーボールの位置
    tnl::Vector3 m_offset_flame = {600,-100,0};     // 火炎放射の位置
    tnl::Vector3 m_offset_fireball = { 200,0,0 };  // ファイアーボールの位置
    tnl::Vector3 m_fireball_dir; // ファイアーボールが飛ぶ方向

    std::vector<tnl::Vector3> m_collision_circles_pos;		/*5つの円の座標*/

    eEffectBossType e_effectType = eEffectBossType::None;

    //-----ポインタ変数-----//
    Enemy* m_enemy = nullptr;				
    Player* m_player = nullptr;				

    //-----メンバ関数-----//
    void FireballHandle();
    void FlameHandle();
    void EffectHandle();

public:

    void CalculateCollisionCircles();

    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;
};