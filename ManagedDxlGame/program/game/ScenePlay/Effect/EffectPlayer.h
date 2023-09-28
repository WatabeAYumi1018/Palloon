#pragma once
#include "../engine/GameEngine.h"
#include "Effect.h"

class Player;

class EffectPlayer : public Effect
{
public:

	EffectPlayer(Player *player, eEffectPlayerType effectType);
	~EffectPlayer();

private:

	//-----メンバ変数-----//
	std::vector<tnl::Vector3> m_collision_circles_pos;			/*5つの円の座標*/

	eEffectPlayerType m_effectType = eEffectPlayerType::None;	/*エフェクトの種類*/
	
	//-----メンバ関数-----//
	void EffectBeamHandle();
	void EffectFireHandle();
	void EffectHandle();

	Player* m_player = nullptr;				/*プレイヤー*/

public:

	void CalculateCollisionCircles();							/*円の座標を計算する関数*/

	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;

public:
	//-----Getter,Setter-----//
	std::vector<tnl::Vector3> GetCollisionCirclesPos() const { return m_collision_circles_pos; }
};