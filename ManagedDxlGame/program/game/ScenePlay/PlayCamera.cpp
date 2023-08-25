#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"
#include "PlayCamera.h"
#include "Character.h"
#include "MapChip.h"


//プレイヤー追従カメラ
//コンストラクタ（Objectのコンストラクタで初期化子）
PlayCamera::PlayCamera(Character *player) :m_player(player) , m_scroll_x(0){}
//デストラクタ
PlayCamera::~PlayCamera(){ }

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	Scroll();
}

void PlayCamera::Scroll() {
	// 画面中央の座標を計算
	float center_x = m_player->GetPos().x;
	// プレイヤーが画面の中央に到達したか
	if (center_x >= DXE_WINDOW_WIDTH / 2) {
		m_scroll_x = center_x - DXE_WINDOW_WIDTH / 2;
		DrawFormatString(290, 30, 1, "true");

	}
	else {
		m_scroll_x = 0;
		DrawFormatString(290, 30, 1, "false");

	}
	DrawFormatString(190, 30, 1, "centerX:%f", center_x);
	DrawFormatString(190,50,1,"m_scroll_x:%f", m_scroll_x);
}
	//マップ値読み取りサイズ（画面端）へカメラがスクロールしたら、再びカメラ固定
	//if (m_scroll_x >= 0) {m_scroll_x = 0;}

		//スクロールスピードを設定(背景とチップでのスクロールスピード調整のために使うかも)	
		//m_scroll_x == m_player->GetVelocity().x;

//PlayCamera内でMapChipを生成するとエラーなったのは、MapChip内でもPlayCameraのコンストラクタを呼び出しているため
//方向性をちゃんと定めること