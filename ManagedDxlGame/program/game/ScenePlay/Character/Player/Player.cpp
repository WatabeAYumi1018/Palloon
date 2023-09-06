#include "Player.h"
#include "../../Camera/Camera.h"

//キャラクターの初期化子
Player::Player() :
	Character
	(
		{ PLAYER_POS_X, PLAYER_POS_Y, 0 },
		PLAYER_SIZE,
		PLAYER_MAX_HP,
		{ PLAYER_VELOCITY_X, PLAYER_VELOCITY_Y,0 }
	)
{
	Initialize();
}

Player::~Player()
{
	Finalize();
}

void Player::Initialize()
{

}

void Player::Update(float delta_time)
{
	MoveHandle(delta_time);
	AnimHandle(delta_time);
}

void Player::Draw(float delta_time, const Camera* camera)
{
	tnl::Vector3 draw_pos =
		m_pos - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	//アニメーションの描画
	animLoader->Draw(delta_time, draw_pos);
	//★デバッグ用
	DrawFormatString(0, 30, 1, "Player_x: %.2f", draw_pos.x);
	DrawFormatString(0, 50, 1, "Player_y: %.2f", draw_pos.y);
	//DrawCircle(draw_pos.x, draw_pos.y, m_size, -1, TRUE);
}

void Player::MoveHandle(float delta_time)
{
	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time ;

	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT))
	{
		m_is_dirction_right = true;

		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))
		{
			m_pos.x += PLAYER_VELOCITY_X * delta_time * 2;
		}
		else
		{
			m_pos.x += PLAYER_VELOCITY_X * delta_time;
		}
		//右と上を同時に押す＋Lineの当たり判定が発生している場合は斜め上へ移動
		if (tnl::Input::IsKeyDown(eKeys::KB_UP)) 
		{
		
		}
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT))
	{
		m_is_dirction_right = false;

		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))
		{
			m_pos.x -= PLAYER_VELOCITY_X * delta_time * 2;
		}
		else
		{
			m_pos.x -= PLAYER_VELOCITY_X * delta_time;
		}
	}
	//zキーで攻撃
	if (tnl::Input::IsKeyDown(eKeys::KB_Z))
	{
		//攻撃処理
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))//&& m_jump_count < PLAYER_JUMP_MAX_COUNT
	{
			m_pos.y -= PLAYER_VELOCITY_Y * delta_time*5;
	}
	//あとで
	//	m_is_jump = true;
	//	m_is_ground = false;
	//	m_jump_count++;
	//}
	////ジャンプ中
	//if (m_is_jump)
	//{
	//	if (m_jump_time > 0)
	//	{
	//		m_pos.y -= m_jump_height.y * delta_time;
	//		m_jump_height.y -= m_gravity.y  * delta_time;
	//		m_jump_time -= delta_time;
	//	}
	//	else
	//	{
	//		//m_is_falling = true;						// ジャンプ上昇終了後、急速に落下
	//		m_is_jump = true;
	//		//m_pos.y += (m_gravity.y * delta_time) * 5;	// ここの5は急速に落下する速度の倍率
	//	}
	//}
	////着地
	//else
	//{
	//	m_is_jump = false;
	//	m_is_falling = false;
	//	m_is_ground = true;
	//	m_jump_count = 0;								//カウントリセット
	//	m_jump_height.y= 200;			//ジャンプの高さをリセット
	//	m_jump_time = 10;					//ジャンプ時間をリセット
	//}
}

//状況によってセットするアニメーションIDを変える(ID番号はcsvにて確認)
void Player::AnimHandle(float delta_time)
{
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT))
	{
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))
		{
			animLoader->SetAnimation(4);	 /*dash_right*/
		}
		else if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))
		{
			animLoader->SetAnimation(6);	 /*jump_right*/
		}
		else
		{
			animLoader->SetAnimation(2);    /*walk_right*/
		}
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT))
	{
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT))
		{
			animLoader->SetAnimation(5);	 /*dash_right*/
		}
		else if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))
		{
			animLoader->SetAnimation(7);	 /*jump_left*/
		}
		else
		{
			animLoader->SetAnimation(3);	 /*walk_left*/
		}
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))
	{
		if (m_is_dirction_right)
		{
			animLoader->SetAnimation(6);	 /*jump_right*/
		}
		else
		{
			animLoader->SetAnimation(7);	 /*jump_left*/
		}
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_Z))
	{
		if (m_is_dirction_right)
		{
			animLoader->SetAnimation(16);	 /*roll_right*/
			//再生後、フラグを立ててアイドルに戻す
			//animLoader->SetAnimation(0);	 /*idle_right*/
		}
		else
		{
			animLoader->SetAnimation(8);	 /*roll_left*/
			//animLoader->SetAnimation(1);	 /*idle_left*/
		}
	}
	else
	{
		if (m_is_dirction_right)
		{
			animLoader->SetAnimation(0);	 /*idle_right*/
		}
		else
		{
			animLoader->SetAnimation(1);	 /*idle_left*/
		}
	}
}

void Player::Finalize()
{

}

