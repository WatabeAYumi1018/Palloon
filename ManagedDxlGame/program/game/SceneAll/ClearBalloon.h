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

	//-----’è”-----//
	const float BLINK_INTERVAL = 2.0f; /*“_–Å*/

	//-----ƒƒ“ƒo•Ï”-----//
	int m_balloon_hdl = 0;
	int m_balloon_clear_hdl = 0;
	int m_clear_up_hdl = 0;

	float m_size_x = 300;
	float m_size_y = 500;

	float m_float_time = 0.0f;
	float m_offset_y = 10.0f;
	float m_velocity_y = 100.0f;

	float m_blink_time = 0.0f;

	tnl::Vector3 m_target_pos;

	bool m_is_change_grahic = false;
	bool m_is_scene_change = false;
	bool m_is_draw = false;

	eBalloonState e_balloon_state = eBalloonState::Hidden;

	Collision *m_collision = nullptr;

public:
	//-----ƒƒ“ƒoŠÖ”-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;
	void Finalize() override;

private:

	void ClearPosChange();
	void MoveBalloon(float delta_time);

public:
	//-----Getter&Setter-----//
	bool GetIsChangeGraphic() const { return m_is_change_grahic; }
	void SteIsDraw(bool is_draw) { m_is_draw = is_draw; }
};