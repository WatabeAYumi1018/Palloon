#include "Player.h"

//キャラクターの初期化子
Player::Player(Vector3 pos) :
	Character(m_pos, PLAYER_HP,m_attack, m_jump_velocity)
{
	Initialize();
}

Player::~Player() { Finalize(); }

void Player::Initialize() 
{
	//円形の当たり判定をもつ
	//m_collision = new Collision(m_pos, 50);


	m_graph_hdl = LoadGraph("graphics/slimeA_idle00.png");
}
void Player::Update(float delta_time) 
{
	Draw();
	Move(delta_time);

}

void Player::Draw() {

	////画像をY軸回転
	//if (Input::IsKeyDown(eKeys::KB_RIGHT)) {
	//	// Y軸回転を適用した画像を描画
	//	Matrix mat = m_rotation.getMatrix();

	//	DrawGraph(m_pos.x, m_pos.y, m_graph_hdl, TRUE);}
	//else if (Input::IsKeyDown(eKeys::KB_LEFT)) {DrawGraph(m_pos.x, m_pos.y, m_graph_hdl, TRUE);}
	//else {
		DrawGraph(m_pos.x, m_pos.y, m_graph_hdl, TRUE);
//}
}

void Player::Move(float delta_time) {

	//キャラクターの移動
	if (Input::IsKeyDown(eKeys::KB_RIGHT)) { m_pos.x += PLAYER_SPEED_WALK * delta_time; }
	if (Input::IsKeyDown(eKeys::KB_LEFT)) { m_pos.x -= PLAYER_SPEED_WALK * delta_time; }

	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time;

	if (m_is_Ground) {
		//スペースボタンでジャンプ
		if (Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
 			m_is_Jump = true;
			m_is_Ground = false;
			m_jump_velocity.y = 200.0f;
		}
	}
	if (m_is_Jump) {
		m_pos.y -= m_jump_velocity.y * delta_time;
		m_jump_velocity.y -= m_gravity.y * delta_time;		//ジャンプしたら重力適応
	}
	if (m_pos.y >=300) {
		m_pos.y = 300;						// グラウンドに着地したらy座標を修正
		m_is_Ground = true;					// 地面に接しているフラグをtrueにする
		m_is_Jump = false;
		m_jump_velocity.y =0;
	}
}

void Player::Finalize() 
{
	DeleteGraph(m_graph_hdl);
}