#pragma once
#include "../engine/GameEngine.h"
#include "GameObject.h"

class Player;
class Camera;
class Collision;

class ClearBalloon : public GameObject
{
public:
	ClearBalloon(Collision *collision);

private:
	//-----ƒƒ“ƒo•Ï”-----//
	int m_balloon_hdl = 0;
	int m_balloon_clear_hdl = 0;

	float m_size_x = 300;
	float m_size_y = 544;

	float m_balloon_timer = 0.0f;
	float m_balloon_offset_y = 10.0f;
	float m_balloon_velocity_y = 5.0f;

	Collision *m_collision = nullptr;

public:
	//-----ƒƒ“ƒoŠÖ”-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;
	void Finalize() override;

private:

	void ClearPosChange();
	//bool IsPlayerAttached(const Player* player);
	//void AttachPlayer();
	//void MoveBalloon(float delta_time);

public:

	//-----Getter&Setter-----//
	void SetClearPosition(const tnl::Vector3& pos){this->SetPos(pos);}
};