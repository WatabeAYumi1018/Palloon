#pragma once
#include "../../engine/GameEngine.h"
#include "PlayCamera.h"
#include "Player.h"
#include "MapChip.h"

//プレイヤー追従カメラ
//コンストラクタ（Objectのコンストラクタで初期化子）
PlayCamera::PlayCamera(tnl::Vector3 pos,Player* player) :
	Object(pos) ,m_player(player),m_scroll_x(0.0f){
	m_map_chip = new MapChip();
}

//デストラクタ
PlayCamera::~PlayCamera(){ delete m_map_chip; }

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	// 画面中央の座標を計算
	float centerX = m_player->GetPos().x;
	float centerY = m_player->GetPos().y;
	// プレイヤーが画面の中央に到達したか
	if (centerX >= DXE_WINDOW_WIDTH / 2) {
		m_scroll_x = centerX - DXE_WINDOW_WIDTH / 2;}

	Draw();
	// マップチップの更新と描画
	m_map_chip->Update(delta_time,m_scroll_x);
}

//PlayCamera内でMapChipを生成するとエラーなるのは、MapChip内でもPlayCameraのコンストラクタを呼び出しているため
//方向性をちゃんと定めること