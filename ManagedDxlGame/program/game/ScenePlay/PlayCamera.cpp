#pragma once
#include "../../engine/GameEngine.h"
#include "PlayCamera.h"
#include "Player.h"
#include "MapChip.h"

//プレイヤー追従カメラ
//コンストラクタ（Objectのコンストラクタで初期化子）
PlayCamera::PlayCamera(tnl::Vector3 pos,Player* player) :
	Object(pos) ,m_player(player),m_scroll_x(5.0f){
	m_map_chip = new MapChip();
}

//デストラクタ
PlayCamera::~PlayCamera(){ delete m_map_chip; }

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	Draw();
	//プレイヤーが画面中央に達したら、カメラを動かす
	if (m_player->GetPos().x >= DXE_WINDOW_WIDTH / 2) {
		m_scroll_x = m_player->GetPos().x - DXE_WINDOW_WIDTH / 2;
	}
	// マップチップの更新と描画
	m_map_chip->Update(delta_time,m_scroll_x);
}

//スクリーン画面外描画
void PlayCamera::Draw() {
	//カメラ座標を描画
	DrawCircle(m_pos.x, m_pos.y, 10.0f, -1);
}

//PlayCamera内でMapChipを生成するとエラーなるのは、MapChip内でもPlayCameraのコンストラクタを呼び出しているため
//方向性をちゃんと定めること