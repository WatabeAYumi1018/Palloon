#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "../../SceneAll/Effect.h"

class Player;

class EffectPlayer : public Effect
{
public:

	EffectPlayer(Player *player, eEffectPlayerType effectType);
	~EffectPlayer();

	wta::DrawAnim* animLoader = nullptr;		//アニメーションデータをロード

private:

	eEffectPlayerType m_effectType = eEffectPlayerType::None;
	
public:

	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;

private:

	void EffectBeamHandle();
	void EffectFireHandle();
	void EffectHandle();
};