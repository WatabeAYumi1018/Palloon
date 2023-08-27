#pragma once
#include "../../engine/GameEngine.h"
#include "PlayCamera.h"
#include "Character.h"
#include "MapManager.h"


//プレイヤー追従カメラ
PlayCamera::PlayCamera(Character *player) :m_player(player) , m_scroll_x(0){}
PlayCamera::~PlayCamera(){ }

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	Scroll();
	//PosRevise();
}

//カメラのスクロール
void PlayCamera::Scroll() {
	// 画面中央の座標を計算
	float center_x = m_player->GetPos().x;
	// プレイヤーが画面の中央に到達したか
	if (center_x >= DXE_WINDOW_WIDTH / 2) {
		m_scroll_x = center_x - DXE_WINDOW_WIDTH / 2;
		DrawFormatString(300, 30, 1, " move:true");
	}
	else {
		m_scroll_x = 0;
		DrawFormatString(300, 30, 1, " move:false");
	}
	DrawFormatString(150, 30, 1, " =centerX:%.2f", center_x);
	DrawFormatString(150,50,1,"  scroll_x:%.2f", m_scroll_x);
}

//★プレイヤーの表示位置を調整？
void PlayCamera::PosRevise() {
	tnl::Vector3 pos = m_player->GetPos();
	tnl::Vector3 screenPos;
	screenPos.x = pos.x - m_scroll_x;
	screenPos.y = pos.y;
	screenPos.z = pos.z;
	if (pos.x >= DXE_WINDOW_WIDTH / 2) {
		// カメラの中心にプレイヤーを配置する
		m_player->SetPos(screenPos);
	}
}

	//マップ値読み取りサイズ（画面端）へカメラがスクロールしたら、再びカメラ固定
	//if (m_scroll_x >= 0) {m_scroll_x = 0;}

	//スクロールスピードを設定(背景とチップでのスクロールスピード調整のために使うかも)	
	//m_scroll_x == m_player->GetVelocity().x;

//PlayCamera内でMapChipを生成するとエラーなったのは、MapChip内でもPlayCameraのコンストラクタを呼び出しているため
//方向性をちゃんと定めること