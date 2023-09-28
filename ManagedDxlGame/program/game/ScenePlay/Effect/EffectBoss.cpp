#include "EffectBoss.h"
#include "../Character/Player/Player.h"

EffectBoss::EffectBoss(Player* player, eEffectBossType effectType) :
    Effect(tnl::Vector3(0, 0, 0), player), m_effectType(effectType)
{

}

EffectBoss::~EffectBoss()
{

}

void EffectBoss::Update(float delta_time)
{
    if (m_is_active)
    {
        m_pos = m_player->GetPos();

        EffectHandle();
        run_time += delta_time;

        if (run_time > active_time)
        {
            m_is_active = false;
        }
    }
}

void EffectBoss::Draw(float delta_time, const Camera* camera)
{
    // EffectPlayerと同様の描画ロジックが適用可能です。
    // 必要に応じて調整してください。
}

void EffectBoss::CalculateFireballs()
{
    m_fireball_positions.clear();

    tnl::Vector3 fireball_pos;

    // 5つの火の玉の位置を計算するロジック 
    // ゲームの要件に応じて調整してください。
}

void EffectBoss::FireballHandle()
{
    if (m_is_fireball)
    {
        // 火の玉のアニメーションのロジック
    }
}

void EffectBoss::FlameHandle()
{
    if (m_is_flame)
    {
        // 放射状の火炎のアニメーションのロジック
    }
}

void EffectBoss::EffectHandle()
{
    if (m_effectType == eEffectBossType::Flame)
    {
        FlameHandle();
    }
    else if (m_effectType == eEffectBossType::FireBall)
    {
        FireballHandle();
    }
}