#include "Player.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"
#include "../../Map/Map1.h"

//キャラクターの初期化子
Player::Player(Collision* collision, Map1* map):
	Character({ POS_X, POS_Y, 0 },SIZE,MAX_HP,{ VELOCITY_X, VELOCITY_Y,0 }),
	m_collision(collision), m_map(map)
{

}

void Player::Update(float delta_time)
{
	m_is_ground = CheckIsGround();
	Gravity(delta_time);
	MoveRange();
	ActionHandle(delta_time);
	Invincible(delta_time);
}

void Player::Draw(float delta_time, const Camera* camera)
{
	if (!m_is_draw)
	{
		//描画しない場合はここで終了
		return;
	}

	if (m_is_draw)
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
	}
}

void Player::StampAction(float delta_time)
{	
	if (m_is_direction_right)
	{
		e_currentAction = ePlayerAction::Stamp_right;
	}
	else
	{
		e_currentAction = ePlayerAction::Stamp_left;
	}

	m_stamp_time += delta_time;

	if (m_stamp_time >= STAMP_DURATION)
	{
		m_stamp_time = 0.0f; // タイマーをリセット
		m_is_stamp = false;
		m_is_hovering = false;
	}
}

void Player::RollAction(float delta_time)
{
	if (m_is_direction_right)
	{
		e_currentAction = ePlayerAction::Roll_right;
	}
	else
	{
		e_currentAction = ePlayerAction::Roll_left;
	}
}

void Player::ActionHandle(float delta_time)
{
	// 1秒未満の場合、アクションを変更しない
	//if (m_landing_time < 1.0f) return;

	MoveHandle(delta_time);

	switch (e_currentAction)
	{
	case ePlayerAction::Move_right:

		animLoader->SetAnimation(2);  /*move_right*/

		break;
	
	case ePlayerAction::Move_left:
		
		animLoader->SetAnimation(3);  /*move_left*/
		
		break;

	case ePlayerAction::Dash_right:
	
		animLoader->SetAnimation(4);  /*dash_right*/
	
		break;
	
	case ePlayerAction::Dash_left:

		animLoader->SetAnimation(5);  /*dash_left*/

		break;

	case ePlayerAction::Idle_right:

		animLoader->SetAnimation(0);  /*idle_left*/

		break;

	case ePlayerAction::Idle_left:

		animLoader->SetAnimation(1);  /*idle_left*/

		break;

	case ePlayerAction::Hover_right:

		animLoader->SetAnimation(6);  /*jump_right*/

		break;

	case ePlayerAction::Hover_left:

		animLoader->SetAnimation(7);  /*jump_left*/

		break;

	case ePlayerAction::Hover_end_right:

		animLoader->SetAnimation(8);  /*jump_end_right*/

		break;

	case ePlayerAction::Hover_end_left:

		animLoader->SetAnimation(9);  /*jump_end_left*/

		break;

	case ePlayerAction::Stamp_right:

		animLoader->SetAnimation(10);  /*stamp_right*/

		break;

	case ePlayerAction::Stamp_left:

		animLoader->SetAnimation(11);  /*stamp_left*/

		break;

	case ePlayerAction::Roll_right:
		
		animLoader->SetAnimation(12);  /*roll_right*/

		break;

	case ePlayerAction::Roll_left:

		animLoader->SetAnimation(13);  /*roll_left*/

		break;

	case ePlayerAction::Beam_right:

		animLoader->SetAnimation(16);  /*beam_right*/

		break;

	case ePlayerAction::Beam_left:

		animLoader->SetAnimation(17);  /*beam_left*/

		break;

	default:

		break;
	}
}

void Player::MoveHandle(float delta_time)
{
	m_is_rolling = false;

	//アナログスティックの入力値を取得
	GetJoypadAnalogInput(&m_input_x, &m_input_y, DX_INPUT_PAD1);

	normalized_input_x = m_input_x / 1000.0f;

	//ジャンプボタン、または接地判定falseの場合、ジャンプ処理を行う
	if ((tnl::Input::IsKeyDown(eKeys::KB_SPACE) || tnl::Input::IsPadDown(ePad::KEY_3))|| !CheckIsGround())
	{
		m_is_hovering = true;
	}

	if (m_is_hovering && m_stamp_time == 0.0f)
	{
		Hovering(delta_time);
		HoveringDirection(delta_time);
	}

	if (m_is_stamp)
	{
		StampAction(delta_time);
	}
		//HoveringEnd();

	if (CheckIsGround())
	{
		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || normalized_input_x > 0)
		{
			m_is_direction_right = true;

			if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) || normalized_input_x > DASH_THRESHOLD)
			{
				m_pos.x += VELOCITY_X * delta_time * 2;
				e_currentAction = ePlayerAction::Dash_right;

				//ダッシュ中にCで転がる攻撃
				if (tnl::Input::IsKeyDown(eKeys::KB_Z))
				{
					m_is_rolling = true;
					RollAction(delta_time);
				}
			}
			else
			{
				m_pos.x += VELOCITY_X * delta_time;
				e_currentAction = ePlayerAction::Move_right;
			}
		}
		else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || normalized_input_x < 0)
		{
			m_is_direction_right = false;

			if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) || abs(normalized_input_x) > DASH_THRESHOLD)
			{
				m_pos.x -= VELOCITY_X * delta_time * 2;
				e_currentAction = ePlayerAction::Dash_left;

				//ダッシュ中にCで転がる攻撃
				if (tnl::Input::IsKeyDown(eKeys::KB_Z))
				{
					m_is_rolling = true;
					RollAction(delta_time);
				}
			}
			else
			{
				m_pos.x -= VELOCITY_X * delta_time;
				e_currentAction = ePlayerAction::Move_left;
			}
		}
		else if (tnl::Input::IsKeyDown(eKeys::KB_C))
		{
			if (m_is_direction_right)
			{
				e_currentAction = ePlayerAction::Beam_right;
			}
			else
			{
				e_currentAction = ePlayerAction::Beam_left;
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
	}
}

bool Player::CheckIsGround()
{
	if (m_is_dead)
	{
		return false;
	}

	tnl::Vector3 foot_pos = m_pos + tnl::Vector3(0, SIZE, 0);
	tnl::Vector3 chip_pos = m_collision->GetCharacterMapChipPos(foot_pos, m_map);
	sCollisionInfo foot_collision = m_map->GetCollisionInfo()[chip_pos.y][chip_pos.x];

	return (foot_collision.s_type == eMapCollisionType::Box ||
		foot_collision.s_type == eMapCollisionType::Line);
}


void Player::MoveRange()
{
	//プレイヤーの移動範囲を制限
	if (m_pos.x < SIZE)
	{
		m_pos.x = SIZE;
	}
	if (m_pos.x > (m_map -> GetMapChipX() * m_map->MAP_CHIP_SIZE - SIZE))
	{
		m_pos.x = m_map->GetMapChipX()* m_map->MAP_CHIP_SIZE - SIZE;
	}
	if (m_pos.y < SIZE)
	{
		m_pos.y = SIZE;
	}
	if (m_pos.y >= (m_map->GetMapChipY() * m_map->MAP_CHIP_SIZE - SIZE))
	{
		m_is_dead=true;
	}
}

void Player::Gravity(float delta_time)
{
	//重力で下に落ちる
	if (m_is_hovered)
	{
		m_pos.y += 2 * m_gravity.y * delta_time;    // 空気が抜けた場合、重力の影響を2倍にする
	}
	else
	{
		m_pos.y += m_gravity.y * delta_time;
	}
}

void Player::Hovering(float delta_time)
{
	if (m_is_ground)
	{
		m_hovering_force = HOVER_FIRST_FORCE; // 地面にいるときは浮遊力をリセット
	}
	if (m_hovering_force > 0)
	{
		m_pos.y -= m_hovering_force * VELOCITY_Y * delta_time; // 浮遊力に基づいて位置を更新
		m_hovering_force -= HOVER_DECAY_RATE * delta_time; // 浮遊力を減少させる
		m_hovering_force = max(m_hovering_force, 0.0f); // 0以下にはならないようにする
	}
	else
	{
		m_hovering_force = 0.0f; // キーが離されたら浮遊力を0にリセット
		m_is_hovering = false;
		m_is_hovered = false;
	}
}

void Player::HoveringDirection(float delta_time)
{
	// ホバリング中
	if (m_hovering_force > 0)
	{
		if (m_is_direction_right)
		{
			HoveringStartRight(delta_time);
		}
		else
		{
			HoveringStartLeft(delta_time);
		}
	}
	//下降中
	else
	{
		if (m_is_direction_right)
		{
			HoveringStartRight(delta_time);
		}
		else
		{
			HoveringStartLeft(delta_time);
		}
	}
}

void Player::HoveringStartRight(float delta_time)
{
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || normalized_input_x > 0)
	{
		m_is_direction_right = true;
		e_currentAction = ePlayerAction::Hover_right;
		m_pos.x += VELOCITY_X * delta_time;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || normalized_input_x < 0)
	{
		m_is_direction_right = false;
		e_currentAction = ePlayerAction::Hover_left;
		m_pos.x -= VELOCITY_X * delta_time;
	}
	else
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Hover_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Hover_left;
		}
	}
}

void Player::HoveringStartLeft(float delta_time)
{
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || normalized_input_x < 0)
	{
		m_is_direction_right = false;
		e_currentAction = ePlayerAction::Hover_left;
		m_pos.x -= VELOCITY_X * delta_time;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || normalized_input_x > 0)
	{
		m_is_direction_right = true;
		e_currentAction = ePlayerAction::Hover_right;
		m_pos.x += VELOCITY_X * delta_time;
	}
	else
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Hover_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Hover_left;
		}
	}
}

void Player::HoveringEnd()
{
	if (CheckIsGround())
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Hover_end_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Hover_end_left;
		}
		m_is_hovering = false;
	}
	else
	{
		m_is_hovering = false;
	}
}

void Player::Invincible(float delta_time)
{
	// 無敵時間を更新
	if (m_is_invincible)
	{
		m_invincible_time += delta_time;

		if (m_invincible_time >= 5.0f)
		{
			m_is_invincible = false;
		}
	}
}


