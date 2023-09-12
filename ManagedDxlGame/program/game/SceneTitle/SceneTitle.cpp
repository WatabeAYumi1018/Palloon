#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneTitle.h"
#include "../ScenePlay/scenePlay.h"
#include "../../engine/SceneManager.h"

void SceneTitle::Update(float delta_time) 
{
	sequence_.update(delta_time);
	logoHandle(delta_time);
	bounceHandle(delta_time);

	for (auto& balloon : balloons)
	{
		balloon.Update(delta_time);
	}
	SpawnBalloon(); // 風船を生成
}

void SceneTitle::Draw(float delta_time) 
{
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, m_back_hdl, TRUE);

	//for (const auto& balloon : balloons)
	//{
	//	DrawExtendGraph(m_pos.x, m_pos.y, m_pos.x + m_size, m_pos.y + m_size, m_balloon_hdl, TRUE);
	//}

	int logoHeight; // ロゴの高さを取得
	GetGraphSize(m_logo_hdl, NULL, &logoHeight); // ロゴの高さを取得
	DrawRectExtendGraph(300, 400, 400 + m_current_width, 400 + logoHeight, 0, 0, m_current_width, logoHeight, m_logo_hdl, TRUE);
	DrawGraph(400, m_chara_pos.y, m_palloon_hdl, TRUE);
}

bool SceneTitle::SeqIdle(float delta_time) 
{
	if (sequence_.isStart())

		//balloon->Initialize();
	{
		m_back_hdl = LoadGraph("graphics/title/Titleback.jpg");
		m_logo_hdl = LoadGraph("graphics/title/TitleLogo.png");
		m_palloon_hdl= LoadGraph("graphics/title/PALLOON.png");
		
		m_current_width = 0;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) 
	{
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new ScenePlay());
	}
	return true;
}

void SceneTitle::logoHandle(float delta_time)
{
	// ロゴの幅を徐々に増やす
	m_current_width += m_display_time * delta_time * 5;

	// ロゴの幅が画面幅を超えたら画面幅に固定
	if (m_current_width > DXE_WINDOW_WIDTH) 
	{
		m_current_width = DXE_WINDOW_WIDTH;

		if (!m_is_logo_displayed) 
		{
			m_is_logo_displayed = true;  // ロゴの描画が終わったのでフラグを設定
		}
	}
}

void SceneTitle::bounceHandle(float delta_time)
{
	// ロゴが完全に表示されてからキャラをバウンドさせる
	if (!m_is_logo_displayed) return;

	if (m_bounceCount < m_maxBounce)
	{
		m_velocity.y += m_gravity.y; // 重力を速度に加える
		m_chara_pos.y += m_velocity.y; // 速度を位置に加える

		// イラストが地面に到達したらバウンドさせる
		if (m_chara_pos.y >= m_ground_y)
		{
			m_chara_pos.y = m_ground_y; // 位置を地面に設定
			m_velocity.y *= m_bounceRate; // バウンドさせるために速度を反転&減少させる
			m_bounceCount++; // バウンド回数を増やす
		}
	}
	else
	{
		// 最大バウンド回数を超えた場合、イラストを画面中央に固定する
		m_chara_pos.y = m_ground_y;
	}
}

void SceneTitle::SpawnBalloon() 
{
	
}