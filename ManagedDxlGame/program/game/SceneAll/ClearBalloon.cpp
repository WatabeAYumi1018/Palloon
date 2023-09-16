#include "ClearBalloon.h"
#include "../ScenePlay/Character/Player/Player.h"
#include "../ScenePlay/Collision/Collision.h"
#include "../ScenePlay/Camera/Camera.h"

ClearBalloon::ClearBalloon(Collision *collision) : 
	GameObject(tnl::Vector3 {0,0,0}), m_collision(collision)
{
	Initialize();
}

void ClearBalloon::Initialize()
{
	m_balloon_hdl = LoadGraph("graphics/balloon/clear_balloon.png");
	m_balloon_clear_hdl = LoadGraph("graphics/balloon/clear_palloon.png");
}

void ClearBalloon::Update(float delta_time)
{
	if (m_pos.x != 0 && m_pos.y != 0)
	{
		//if ()
		//{
		//	//まっすぐ上昇させる
		//	m_pos.y += delta_time * m_balloon_velocity_y;
		//}
		//else
		//{
		//	//その場で少々ふわふわさせる
		//	m_balloon_timer += delta_time * m_balloon_velocity_y;

		//	// sin関数を使用して風船の上下のオフセットを計算
		//	m_balloon_offset_y = sin(m_balloon_timer) * 5.0f;
		//}
	}
}

void ClearBalloon::Draw(float delta_time, const Camera* camera)
{
	ClearPosChange();

	tnl::Vector3 draw_pos =
		m_pos - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);


	if (m_pos.x != 0 && m_pos.y != 0)
	{
		if (m_collision->GetIsClear() && tnl::Input::IsKeyDown(eKeys::KB_UP))
		{
			DrawExtendGraph(draw_pos.x - m_size_x, draw_pos.y + m_size_y, draw_pos.x + m_size_x, draw_pos.y - m_size_y, m_balloon_clear_hdl, true);
		}
		else
		{
			DrawExtendGraph(draw_pos.x - m_size_x, draw_pos.y - m_size_y,
				draw_pos.x + m_size_x, draw_pos.y,
				m_balloon_hdl, true);

			//DrawGraph(draw_pos.x, draw_pos.y, m_balloon_hdl, true);
		}
	}
}

void ClearBalloon::ClearPosChange()
{
	tnl::Vector3 clear_pos = m_collision->GetClearPos();
	tnl::Vector3 default_pos = {0,0,0};

	if (clear_pos.x != default_pos.x && clear_pos.y != default_pos.y)
	{
		SetClearPosition(clear_pos);
	}
}

void ClearBalloon::Finalize()
{
	DeleteGraph(m_balloon_hdl);
	DeleteGraph(m_balloon_clear_hdl);
}