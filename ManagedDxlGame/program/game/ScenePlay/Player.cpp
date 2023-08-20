#include "Player.h"
#include "MapChip.h"

//キャラクターの初期化子
Player::Player() :Character({ 100,0,0 },5, 5, 1,5.0f, {0,500,0})
{
	Initialize();
}

Player::~Player() { Finalize(); }

void Player::Initialize() 
{
	//★画像の読み込み(animLoopクラスを使用して読み込む)（冗長気味のため修正必須かなと）
	//csvファイルでまとめる
	//animLoop  = new AnimLoad("graphics/player/walk_right",true);
	//animLoop2 = new AnimLoad("graphics/player/walk_left",true);
	//animLoop3 = new AnimLoad("graphics/player/jump_right",true);
	//animLoop4 = new AnimLoad("graphics/player/jump_left",true);
	//animLoop5 = new AnimLoad("graphics/player/idle_right",true);
	//animLoop6 = new AnimLoad("graphics/player/idle_left",true);
	//animLoop7 = new AnimLoad("graphics/player/run_right",true);
	//animLoop8 = new AnimLoad("graphics/player/run_left",true);
	//animLoop9 = new AnimLoad("graphics/player/touchdown_right",false);
	//animLoop10= new AnimLoad("graphics/player/touchdown_left",false);
}
void Player::Update(float delta_time) 
{
	Draw(delta_time);
	Move(delta_time);
}

//void Player::Draw(float delta_time) {
//	DrawFormatString(10, 30, 1, "Player X: %.2f", m_pos.x);
//	//★現状方法が非効率のように感じる…
//
//		//地面にいる時のアニメーション
//	if (m_is_Ground) {
//		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
//			if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {
//				animLoop7->drawAnimFile(delta_time, m_pos);
//			}
//			else animLoop->drawAnimFile(delta_time, m_pos);
//		}
//		else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
//			if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {
//				animLoop8->drawAnimFile(delta_time, m_pos);
//			}
//			else animLoop2->drawAnimFile(delta_time, m_pos);
//		}
//		//アニメーション画像描画
//		else { animLoop5->drawAnimFile(delta_time, m_pos); }
//	}
//	//ジャンプ中アニメーション(要検討)
//	else {
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
//			//animLoop3->drawAnimLoopFile(delta_time, m_pos);
//		}
//		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
//			animLoop4->drawAnimFile(delta_time, m_pos);
//		}
//		else { animLoop3->drawAnimFile(delta_time, m_pos); }
//		if (m_pos.y == 500) { animLoop9->drawAnimFile(delta_time, m_pos); }
//	}
//}

void Player::Move(float delta_time) {
	//キャラクターの移動
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) { m_pos.x += PLAYER_SPEED_WALK * delta_time; }
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) { m_pos.x -= PLAYER_SPEED_WALK * delta_time; }

	//重力で下に落ちる
	m_pos.y += m_gravity.y * delta_time;

	//着地中
	if (m_is_Ground) {
		//スペースボタンでジャンプ
		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
 			m_is_Jump = true;
			m_is_Ground = false;
			m_was_Ground = false;
			m_jump_velocity.y = 1000.0f;
			m_jump_time = 10.0f;
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
			m_was_Ground = false;
			m_jump_time = 0;
		}
	}
	// グラウンドに着地したらy座標を修正
	if (m_pos.y >= 500) {
		m_pos.y = 500;
		m_is_Ground = true;					// 地面に接しているフラグをtrueにする
		m_was_Ground = true;				// 地面に接しているフラグをfalseにする
		m_jump_velocity.y = 0;				// ジャンプ速度を0にリセット
		m_jump_time = 0;					// ジャンプ時間を0にリセット
	}
}

void Player::Finalize() 
{
	//画像の解放
	//delete animLoop;
	//animLoop = nullptr;
	//delete animLoop2;
	//animLoop2 = nullptr;
	//delete animLoop3;
	//animLoop3 = nullptr;
	//delete animLoop4;
	//animLoop4 = nullptr;
	//delete animLoop5;
	//animLoop5 = nullptr;
	//delete animLoop6;
	//animLoop6 = nullptr;
	//delete animLoop7;
	//animLoop7 = nullptr;
	//delete animLoop8;
	//animLoop8 = nullptr;
	//delete animLoop9;
	//animLoop9 = nullptr;
	//delete animLoop10;
	//animLoop10 = nullptr;
}