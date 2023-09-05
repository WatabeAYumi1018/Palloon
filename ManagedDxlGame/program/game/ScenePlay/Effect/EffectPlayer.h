#pragma once
#include "../engine/GameEngine.h"
#include "../../SceneAll/Effect.h"

class Player;

class EffectPlayer : public Effect
{
public:
	EffectPlayer();
	~EffectPlayer();

	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;
};