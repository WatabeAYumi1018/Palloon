#include "Player.h"
#include "MapChip.h"

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
	m_mapchip = new MapChip();

	//★画像の読み込み(animLoopクラスを使用して読み込む)（非効率のため修正必須）
	animLoop = new Anim("graphics/player/walk_right");
	animLoop2 = new Anim("graphics/player/walk_left");
	animLoop3 = new Anim("graphics/player/jump_right");
	animLoop4 = new Anim("graphics/player/jump_left");
	animLoop5 = new Anim("graphics/player/idle_right");
}
void Player::Update(float delta_time) 
{
	Draw(delta_time);
	Move(delta_time);
}

void Player::Draw(float delta_time) {
	DrawFormatString(10, 30, 1, "Player X: %.2f", m_pos.x);
	//★現状方法が非効率のように感じる…
	 
	//このあたりは別で専用のクラスを作成して、そこで処理するようにする方がスマート
	//歩きアニメーション
	if(m_is_Ground){
		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
			animLoop->drawAnimLoopFile(delta_time, m_pos, "graphics/player/walk_right");
		}
		else if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
			animLoop2->drawAnimLoopFile(delta_time, m_pos, "graphics/player/walk_left");
		}
		//アニメーション画像描画
		else{ 
			animLoop5->drawAnimLoopFile(delta_time, m_pos, "graphics/player/idle_right");
		}
	}
	//ジャンプアニメーション
	else {
		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
			animLoop3->drawAnimLoopFile(delta_time, m_pos, "graphics/player/jump_right");
		}
		else if (tnl::Input::IsKeyDown(eKeys::KB_SPACE) && tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
			animLoop4->drawAnimLoopFile(delta_time, m_pos, "graphics/player/jump_left");
		}
		else {
			animLoop3->drawAnimLoopFile(delta_time, m_pos, "graphics/player/jump_right");
		}
	}
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
		if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
 			m_is_Jump = true;
			m_is_Ground = false;
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
	//画像の解放
	delete animLoop;
	animLoop = nullptr;
	delete animLoop2;
	animLoop2 = nullptr;
	delete animLoop3;
	animLoop3 = nullptr;
}