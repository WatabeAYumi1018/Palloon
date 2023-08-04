#include "Player.h"

//キャラクターの初期化子
Player::Player() :Character({ 100,0,0 }, 5, 1,5.0f, {0,500,0})
{
	Initialize();
}

Player::~Player() { Finalize(); }

void Player::Initialize() 
{
	//円形の当たり判定をもつ
	//m_collision = new Collision(m_pos, 50);

	//画像の読み込み(animLoopクラスを使用して読み込む)
	animLoop=new AnimLoop("graphics/slim");
}
void Player::Update(float delta_time) 
{
	Draw(delta_time);
	Move(delta_time);

}

void Player::Draw(float delta_time) {

	////画像をY軸回転
	//if (Input::IsKeyDown(eKeys::KB_RIGHT)) {
	//	// Y軸回転を適用した画像を描画
	//	Matrix mat = m_rotation.getMatrix();

	//	DrawGraph(m_pos.x, m_pos.y, m_graph_hdl, TRUE);}
	//else if (Input::IsKeyDown(eKeys::KB_LEFT)) {DrawGraph(m_pos.x, m_pos.y, m_graph_hdl, TRUE);}
	//else {
		//DrawGraph(m_pos.x, m_pos.y, m_graph_hdl, TRUE);
//}

	//アニメーション画像描画
	animLoop->drawAnimLoopFile(delta_time,m_pos);
}

void Player::Move(float delta_time) {

	//キャラクターの移動
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) { m_pos.x += PLAYER_SPEED_WALK * delta_time; }
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) { m_pos.x -= PLAYER_SPEED_WALK * delta_time; }

	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time;

	//着地中
	if (m_is_Ground) {
		//スペースボタンでジャンプ
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
 			m_is_Jump = true;
			m_is_Ground = false;
			m_jump_velocity.y = 500.0f;
			m_jump_time = 5.0f;
		}
	}

	//ジャンプ中
	if (m_is_Jump) {
		m_pos.y -= m_jump_velocity.y * delta_time;			//ジャンプ速度分y座標を上げる
		m_jump_velocity.y -= m_gravity.y * delta_time;		//ジャンプしたら重力適応
		m_jump_time -= delta_time;							//ジャンプ滞空時間を減らす
		
		//0になったらジャンプ終了
		if (m_jump_time <= 0) {
			m_is_Jump = false;
			m_jump_time = 0;
		}
	}
	// グラウンドに着地したらy座標を修正
	if (m_pos.y >=300) {
		m_pos.y = 300;						
		m_is_Ground = true;					// 地面に接しているフラグをtrueにする
		m_jump_velocity.y =0;				// ジャンプ速度を0にリセット
		m_jump_time = 0;					// ジャンプ時間を0にリセット
	}
}

void Player::Finalize() 
{
	DeleteGraph(m_graph_hdl);
}