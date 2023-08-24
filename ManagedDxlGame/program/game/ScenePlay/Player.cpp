#include "Player.h"
#include "PlayCamera.h"

//キャラクターの初期化子
Player::Player(PlayCamera *camera) :Character({ 0,-100,0 },30, 5,5.0f, {0,500,0})
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
	Draw(delta_time);
	Move(delta_time);
}

void Player::Draw(float delta_time) {
	//カメラのスクロール量を取得
	float cameraScroll_x=m_camera->GetScrollX();
	//プレイヤーの描画位置をカメラのスクロール量に合わせる
	tnl::Vector3 renderPos = m_pos;
	renderPos.x -= cameraScroll_x;
	//アニメーションの描画
	animLoader->Draw(delta_time, renderPos);
	//★デバッグ用
	DrawCircle(renderPos.x, renderPos.y, m_size, -1, TRUE);
	DrawFormatString(10, 50, 1, "Player_x: %.2f", m_pos.x);
	DrawFormatString(10, 30, 1, "renderPos_x: %.2f", m_pos.x);
}

void Player::Move(float delta_time) {
	//状況によってセットするアニメーションIDを変える(ID番号はcsvにて確認)
	animLoader->SetAnimation(0); //idle_right
	//キャラクターの移動
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) { m_pos.x += PLAYER_SPEED_WALK * delta_time; }
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) { m_pos.x -= PLAYER_SPEED_WALK * delta_time; }

	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time;

	//着地中
	
	//if (m_is_Ground) {
		//スペースボタンでジャンプ
		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
 			m_is_Jump = true;
			m_is_Ground = false;
			m_was_Ground = false;
			m_jump_velocity.y = 1000.0f;
			m_jump_time = 10.0f;
		}
	//}
	//ジャンプ中
	if (m_is_Jump) {
		m_pos.y -= m_jump_velocity.y * delta_time;			//ジャンプ速度分y座標を上げる
		m_jump_velocity.y -= m_gravity.y * delta_time;		//ジャンプしたら重力適応
		m_jump_time -= delta_time;							//ジャンプ滞空時間を減らす
		//0になったらジャンプ終了
		if (m_jump_time <= 0) {
			m_is_Jump = false;
			m_was_Ground = false;
			m_jump_time = 0;
		}
	}
	// グラウンドに着地したらy座標を修正
	else{
		m_is_Ground = true;					// 地面に接しているフラグをtrueにする
		m_was_Ground = true;				// 地面に接しているフラグをfalseにする
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

