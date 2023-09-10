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
	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time;

	ActionHandle(delta_time);
	Invincible(delta_time);
}

void Player::Draw(float delta_time, const Camera* camera)
{
	tnl::Vector3 draw_pos =
		m_pos - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

	//アニメーションの描画
	if (m_is_invincible)
	{
		// 0.1秒ごとに表示・非表示を切り替えることで点滅を実現
		if (static_cast<int>(m_invincible_time * 10) % 2 == 0)
		{
			animLoader->Draw(delta_time, draw_pos);
		}
	}
	else
	{
		animLoader->Draw(delta_time, draw_pos);
	}
	
	//★デバッグ用
	DrawFormatString(0, 30, 1, "Player_x: %.2f", draw_pos.x);
	DrawFormatString(0, 50, 1, "Player_y: %.2f", draw_pos.y);
	//DrawCircle(draw_pos.x, draw_pos.y, m_size, -1, TRUE);
}

void Player::ActionHandle(float delta_time)
{
	MoveHandle(delta_time);

	switch (e_currentAction)
	{
	case ePlayerAction::Move_right:

		m_pos.x += PLAYER_VELOCITY_X * delta_time;
		animLoader->SetAnimation(2);  /*move_right*/

		break;
	
	case ePlayerAction::Move_left:
		
		m_pos.x -= PLAYER_VELOCITY_X * delta_time;
		animLoader->SetAnimation(3);  /*move_left*/
		
		break;

	case ePlayerAction::Dash_right:
	
		m_pos.x += PLAYER_VELOCITY_X * delta_time * 2;
		animLoader->SetAnimation(4);  /*dash_right*/
	
		break;
	
	case ePlayerAction::Dash_left:

		m_pos.x -= PLAYER_VELOCITY_X * delta_time * 2;
		animLoader->SetAnimation(5);  /*dash_left*/

		break;

	case ePlayerAction::Idle_right:

		animLoader->SetAnimation(0);  /*idle_left*/

		break;

	case ePlayerAction::Idle_left:

		animLoader->SetAnimation(1);  /*idle_left*/

		break;

	case ePlayerAction::Jump_right:

		m_pos.y -= PLAYER_VELOCITY_Y * delta_time;
		animLoader->SetAnimation(6);  /*jump_right*/

		break;

	case ePlayerAction::Jump_left:

		m_pos.y -= PLAYER_VELOCITY_Y * delta_time;
		animLoader->SetAnimation(7);  /*jump_left*/

		break;

	default:
		break;
	}
}

void Player::MoveHandle(float delta_time)
{
	//アナログスティックの入力値を取得
	GetJoypadAnalogInput(&m_input_x, &m_input_y, DX_INPUT_PAD1);

	normalizedInputX = m_input_x / 1000.0f;

	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || normalizedInputX > 0)
	{
		m_is_direction_right = true;

		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) || normalizedInputX > DASH_THRESHOLD)
		{
			e_currentAction = ePlayerAction::Dash_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Move_right;
		}
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || normalizedInputX < 0)
	{
		m_is_direction_right = false;

		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) || abs(normalizedInputX) > DASH_THRESHOLD)
		{
			e_currentAction = ePlayerAction::Dash_left;
		}
		else
		{
			e_currentAction = ePlayerAction::Move_left;
		}	
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) || tnl::Input::IsPadDown(ePad::KEY_3))
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Jump_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Jump_left;
		}
	}
	else
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Idle_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Idle_left;
		}
	}

	float speedMultiplier = abs(normalizedInputX) > DASH_THRESHOLD ? 2.0f : 1.0f;
}

void Player::Invincible(float delta_time)
{
	if (m_is_invincible)
	{
		m_invincible_time += delta_time;

		if (m_invincible_time >= 5.0f)
		{
			m_is_invincible = false;
		}
	}
}

void Player::flashing(float delta_time)
{
	// 0.1秒ごとに表示・非表示を切り替えることで点滅を実現
	if (static_cast<int>(m_invincible_time * 10) % 2 == 0)
	{
		animLoader->Draw(delta_time, m_pos);
	}
	else
	{
		return; // 描画をスキップ
	}
}

void Player::Finalize()
{

}

