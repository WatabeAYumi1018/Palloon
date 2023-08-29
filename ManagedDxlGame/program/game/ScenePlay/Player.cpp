#include "Player.h"
#include "PlayCamera.h"


//キャラクターの初期化子
Player::Player() : Character({ PLAYER_POS_X, PLAYER_POS_Y, 0 }, PLAYER_SIZE, PLAYER_HP, { PLAYER_VELOCITY_X, PLAYER_VELOCITY_Y,0 })
{
	Initialize();
}

Player::~Player() { Finalize(); }

void Player::Initialize() 
{
	// CSVからアニメーションデータをロード
	animLoader =new wta::DrawAnim("csv/AnimLoad.csv","graphics/animation");
}

void Player::Update(float delta_time)
{
	Move(delta_time);
}

void Player::Draw(float delta_time, const PlayCamera* camera) {
	tnl::Vector3 draw_pos = m_pos - camera->target + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	//アニメーションの描画
	animLoader->Draw(delta_time, draw_pos);
	//★デバッグ用
	DrawFormatString(0, 30, 1, "Player_x: %.2f", draw_pos.x);
	DrawFormatString(0, 50, 1, "Player_y: %.2f", draw_pos.y);
	DrawCircle(draw_pos.x, draw_pos.y, m_size, -1, TRUE);
}

void Player::Move(float delta_time) {
	//状況によってセットするアニメーションIDを変える(ID番号はcsvにて確認)
	animLoader->SetAnimation(0); //idle_right
	//キャラクターの移動
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) { m_pos.x += PLAYER_VELOCITY_X * delta_time; }
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) { m_pos.x -= PLAYER_VELOCITY_X * delta_time; }

	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time;

	//着地中
	
	//if (m_is_Ground) {
		//スペースボタンでジャンプ
		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
 			m_is_jump = true;
			m_is_ground = false;
			m_was_ground = false;
			m_jump_velocity.y = 1000.0f;
			m_jump_time = 10.0f;
		}
	//}
	//ジャンプ中
	if (m_is_jump) {
		m_pos.y -= m_jump_velocity.y * delta_time;			//ジャンプ速度分y座標を上げる
		m_jump_velocity.y -= m_gravity.y * delta_time;		//ジャンプしたら重力適応
		m_jump_time -= delta_time;							//ジャンプ滞空時間を減らす
		//0になったらジャンプ終了
		if (m_jump_time <= 0) {
			m_is_jump = false;
			m_was_ground = false;
			m_jump_time = 0;
		}
	}
	// グラウンドに着地したらy座標を修正
	else{
		m_is_ground = true;					// 地面に接しているフラグをtrueにする
		m_was_ground = true;				// 地面に接しているフラグをfalseにする
		m_jump_velocity.y = 0;				// ジャンプ速度を0にリセット
		m_jump_time = 0;					// ジャンプ時間を0にリセット
	}
}

void Player::Finalize() 
{
	//画像の解放
	delete animLoader;
	animLoader = nullptr;
}

