#pragma once
#include "../../engine/GameEngine.h"
#include "PlayCamera.h"
#include "Object.h"
#include "Player.h"

//プレイヤー追従カメラ
//コンストラクタ（Objectのコンストラクタで初期化子）
PlayCamera::PlayCamera(tnl::Vector3 pos,Player* player) :Object(m_pos) ,m_player(player)
{}

//デストラクタ
PlayCamera::~PlayCamera(){}

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	if (m_player) {
		if (m_player->GetPos().x <DXE_WINDOW_WIDTH/2) {
			//プレイヤーが画面半分へ移動するまではカメラ座標を更新しない
			m_pos.x = 0;
		}		
		else {
			//プレイヤーの座標が画面半分を超えたらカメラ座標を更新
			m_pos.x = m_player->GetPos().x;
		}
	}
}
