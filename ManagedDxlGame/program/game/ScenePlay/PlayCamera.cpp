#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"
#include "PlayCamera.h"
#include "Character.h"
#include "MapChip.h"


//プレイヤー追従カメラ
//コンストラクタ（Objectのコンストラクタで初期化子）
PlayCamera::PlayCamera(tnl::Vector3 pos,Character *player) : Object(pos) {}
//デストラクタ
PlayCamera::~PlayCamera(){ delete m_map_chip; }

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	Scroll();
	m_player->Update(delta_time);
}

void PlayCamera::Scroll() {
	// 画面中央の座標を計算
	float centerX = m_player->GetPos().x;
	// プレイヤーが画面の中央に到達したか
	if (centerX >= DXE_WINDOW_WIDTH / 2) {
		m_scroll_x = centerX - DXE_WINDOW_WIDTH / 2;
	}
}
	//マップ値読み取りサイズ（画面端）へカメラがスクロールしたら、再びカメラ固定
	//if (m_scroll_x >= 0) {m_scroll_x = 0;}

		//スクロールスピードを設定(背景とチップでのスクロールスピード調整のために使うかも)	
		//m_scroll_x == m_player->GetVelocity().x;

//PlayCamera内でMapChipを生成するとエラーなったのは、MapChip内でもPlayCameraのコンストラクタを呼び出しているため
//方向性をちゃんと定めること