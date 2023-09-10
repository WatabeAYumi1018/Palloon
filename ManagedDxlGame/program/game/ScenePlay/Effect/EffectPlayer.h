#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "../../SceneAll/Effect.h"

class Player;

class EffectPlayer : public Effect
{
public:

	EffectPlayer(Player *player);
	~EffectPlayer();

	wta::DrawAnim* animLoader = nullptr;		//アニメーションデータをロード

	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;

private:

	void EffectHandle();
};