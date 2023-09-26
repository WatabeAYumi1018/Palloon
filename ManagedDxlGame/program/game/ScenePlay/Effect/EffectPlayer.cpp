#include "../Character/Player/Player.h"
#include "../Camera/Camera.h"
#include "EffectPlayer.h"


EffectPlayer::EffectPlayer(Player *player, eEffectPlayerType effectType):
	Effect(tnl::Vector3(0, 0, 0), player), m_effectType(effectType)
{
	// CSVからアニメーションデータをロード
	animLoader = new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");
}

EffectPlayer::~EffectPlayer()
{
	delete animLoader;
	animLoader = nullptr;
}

void EffectPlayer::Update(float delta_time)
{
	if (m_is_active) 
	{
		EffectHandle();
		run_time += delta_time;

		if (run_time > active_time) 
		{
			m_is_active = false;
		}
	}
}

void EffectPlayer::Draw(float delta_time, const Camera* camera)
{
	if (m_is_active)
	{
		tnl::Vector3 draw_pos;

		if (m_player->GetIsDirectionRight())
		{
			draw_pos =m_pos + m_offset - camera->GetTarget() + 
				tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		}
		else
		{
			draw_pos =m_pos - m_offset - camera->GetTarget() +
				tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		}

		animLoader->Draw(delta_time * 2, draw_pos);
	}
}

//当たり判定の計算処理
void EffectPlayer::CalculateCollisionCircles()
{
	m_collision_circles_pos.clear();

	tnl::Vector3 circle_pos;

	if (m_effectType == eEffectPlayerType::Fire)
	{
		//放射状に当たり判定の円を配置
		if (m_player->GetIsDirectionRight())
		{
			//左：１つの円
			circle_pos = m_pos;
			m_collision_circles_pos.emplace_back(circle_pos);

			//中央：２つの円
			for (int i = 1; i <= 2; i++)
			{
				circle_pos = m_pos + tnl::Vector3(i * m_size, 0, 0);
				m_collision_circles_pos.emplace_back(circle_pos);
			}

			//右：３つの円
			for (int i = 1; i <= 3; i++)
			{
				circle_pos = m_pos + tnl::Vector3((i + 2) * m_size, 0, 0);
				m_collision_circles_pos.emplace_back(circle_pos);
			}
		}
		else
		{
			//：右１つの円
			circle_pos = -m_pos;
			m_collision_circles_pos.emplace_back(circle_pos);

			//中央：２つの円
			for (int i = 1; i <= 2; i++)
			{
				circle_pos = m_pos - tnl::Vector3(i * m_size, 0, 0);
				m_collision_circles_pos.emplace_back(circle_pos);
			}

			//左：３つの円
			for (int i = 1; i <= 3; i++)
			{
				circle_pos = m_pos - tnl::Vector3((i + 2) * m_size, 0, 0);
				m_collision_circles_pos.emplace_back(circle_pos);
			}
		}
	}

	else if (m_effectType == eEffectPlayerType::Beam)
	{
		//直線状に当たり判定の円を配置
		for (int i = 0; i < 10; i++)
		{
			if (m_player->GetIsDirectionRight())
			{
				circle_pos = m_pos + tnl::Vector3(i * m_size * 2, 0, 0);
				m_collision_circles_pos.emplace_back(circle_pos);
			}
			else
			{
				circle_pos = m_pos - tnl::Vector3(i * m_size * 2, 0, 0);
				m_collision_circles_pos.emplace_back(circle_pos);
			}		
		}
	}
}

//ファイアのアニメーション設定
void EffectPlayer::EffectFireHandle()
{
	if (m_player->GetIsDirectionRight())
	{
		animLoader->SetAnimation(56);  /*effect_fire_right*/
	}
	else
	{
		animLoader->SetAnimation(57);  /*effect_fire_left*/
	}
}

//ビームのアニメーション設定
void EffectPlayer::EffectBeamHandle()
{

	if (m_player->GetIsDirectionRight())
	{
		animLoader->SetAnimation(58);  /*effect_beam_right*/
	}
	else
	{
		animLoader->SetAnimation(59);  /*effect_beam_left*/
	}
}

//エフェクトのアニメーション設定
void EffectPlayer::EffectHandle()
{
	switch (m_effectType)
	{
	case eEffectPlayerType::Fire:

		EffectFireHandle();

		break;
		
	case eEffectPlayerType::Beam:
		
		EffectBeamHandle();
			
		break;
	}
}