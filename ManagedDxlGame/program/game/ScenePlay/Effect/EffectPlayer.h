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

	std::vector<tnl::Vector3> m_collision_circles_pos;  // 5つの円の座標

	eEffectPlayerType m_effectType = eEffectPlayerType::None;
	
public:

	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;

	void CalculateCollisionCircles();	//円の座標を計算する関数(ビームの場合

private:

	void EffectBeamHandle();
	void EffectFireHandle();
	void EffectHandle();


public:
	//-----Getter,Setter-----//
	std::vector<tnl::Vector3> GetCollisionCirclesPos() const { return m_collision_circles_pos; }
};