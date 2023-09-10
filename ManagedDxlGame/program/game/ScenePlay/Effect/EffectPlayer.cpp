#include "../Character/Player/Player.h"
#include "../Camera/Camera.h"
#include "EffectPlayer.h"

EffectPlayer::EffectPlayer(Player *player):Effect(tnl::Vector3(0,0,0),player)
{
	// CSVからアニメーションデータをロード
	animLoader = new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");

}

EffectPlayer::~EffectPlayer()
{

}

void EffectPlayer::Update(float delta_time)
{
	//プレイヤー座標に追従
	//if (m_player)
	//{
	//	m_pos = m_player->GetPos();
	//}
	if (m_is_moved) 
	{
		elapsed_time += delta_time;
	
		if (elapsed_time > duration) 
		{
			m_is_moved = false;
		}
	}
	EffectHandle();
}

void EffectPlayer::Draw(float delta_time, const Camera* camera)
{
	if (m_player->GetIsDirectionRight())
	{
		tnl::Vector3 draw_pos =
			m_pos + m_offset - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		
		animLoader->Draw(delta_time * 2, draw_pos);
	}
	else
	{
		tnl::Vector3 draw_pos =
			m_pos - m_offset - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

		animLoader->Draw(delta_time * 2, draw_pos);
	}
}

void EffectPlayer::EffectHandle()
{
	if (m_is_moved)
	{
		if (m_player->GetIsDirectionRight())
		{
			animLoader->SetAnimation(42);  /*effect_beam_right*/
		}
		else
		{
			animLoader->SetAnimation(43);  /*effect_beam_left*/
		}
	}
}