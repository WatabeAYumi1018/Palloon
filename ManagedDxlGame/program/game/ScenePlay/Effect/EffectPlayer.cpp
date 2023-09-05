#include "../Character/Player/Player.h"
#include "../Camera/Camera.h"
#include "EffectPlayer.h"

EffectPlayer::EffectPlayer():Effect(tnl::Vector3(0,0,0),m_player)
{

}

EffectPlayer::~EffectPlayer()
{
	delete m_player;
	m_player = nullptr;
}

void EffectPlayer::Update(float delta_time)
{
	//プレイヤー座標に追従
	//if (m_player)
	//{
	//	m_pos = m_player->GetPos();
	//}
	m_pos.x += m_velocity.x * delta_time;
}

void EffectPlayer::Draw(float delta_time, const Camera* camera)
{
	tnl::Vector3 draw_pos =
		m_pos - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

		DrawCircle(draw_pos.x, draw_pos.y, m_size, -1, TRUE);
		
		//draw_pos += m_velocity * delta_time;

	//if (m_type == eEffectType::Circle)
	//{
	//}
}