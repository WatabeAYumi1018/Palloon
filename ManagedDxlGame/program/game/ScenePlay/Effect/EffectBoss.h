#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "Effect.h"

class Player;

class EffectBoss : public Effect
{
public:

    EffectBoss(Player* player, eEffectBossType effectType);
    ~EffectBoss();

private:
    std::vector<tnl::Vector3> m_fireball_positions;     /*‰Î‚Ì‹Ê‚ÌˆÊ’u*/
    eEffectBossType m_effectType = eEffectBossType::None;

    wta::DrawAnim* animLoader = nullptr;

    bool m_is_fireball = false;  /*‰Î‰Šƒ{[ƒ‹*/
    bool m_is_flame = false;     /*‰Î‰Š•úË*/

    void FireballHandle();
    void FlameHandle();
    void EffectHandle();

public:

    void CalculateFireballs();
   
    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;
};