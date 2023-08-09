#pragma once
#include "../../engine/GameEngine.h"
#include "PlayCamera.h"
#include "Player.h"
#include "MapChip.h"

//プレイヤー追従カメラ
//コンストラクタ（Objectのコンストラクタで初期化子）
PlayCamera::PlayCamera(tnl::Vector3 pos,Player* player) :Object(pos) ,m_player(player){
}

//デストラクタ
PlayCamera::~PlayCamera(){}

//毎フレーム更新
void PlayCamera::Update(float delta_time) {
	
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		// 1000.0fは移動速度の例
		m_pos.x += 500.0f * delta_time;
		// マップチップの描画位置をカメラの移動に合わせて調整
		m_map_chip->AdjustPosition(tnl::Vector3(1000.0f * delta_time, 0.0f, 0.0f));
	}
	Draw();
	//	DrawCircle(m_pos.x, m_pos.y, 10.0f, -1);
	//	//画面中央まで進んだら、横へスクロールして画面外にあったチップを描画
	//	if (m_pos.x > DXE_WINDOW_WIDTH / 2.0f) {
	//		DrawCircle(m_pos.x, m_pos.y, 10.0f, -1);
	//		mapChip->Update(delta_time);
	//	}
	//	
	//}
	//if (m_player) {
	//	//プレイヤーの座標が画面半分を超えたらカメラ座標を更新
	//	float playerScreenPosX = m_player->GetPos().x - m_pos.x + DXE_WINDOW_WIDTH / 2.0f;

	//	if (playerScreenPosX > DXE_WINDOW_WIDTH / 2.0f) {
	//		//プレイヤーの座標が画面半分を超えたらカメラ座標を更新
	//		m_pos.x = playerScreenPosX;
	//		DrawCircle(m_pos.x, m_pos.y, 10.0f, -1);
	//	}		
	//	else {
	//		//プレイヤーが画面半分へ移動するまではカメラ座標を更新しない
	//		m_pos.x = 0;
	//		DrawCircle(m_pos.x,m_pos.y,10.0f,-1);
	//	}
	//}
	//std::vector<Object*> objects;

	//// カメラ座標の制限
	//if (m_pos.x < 0) {
	//	m_pos.x = 0;
	//}
	//else if (m_pos.x > 500) {
	//	m_pos.x = 500;
	//}

	//// 表示されるオブジェクトの座標調整
	//for (Object* obj : objects) {
	//	obj->AdjustPosition(-m_move); // カメラの移動量と逆向きに調整
	//}
	//Draw(m_objects);
}

//スクリーン画面外描画
void PlayCamera::Draw() {
	//for (Object* obj : objects) {
	//	// オブジェクトのスクリーン座標を計算
	//	float objScreenPosX = m_pos.x + DXE_WINDOW_WIDTH / 2.0f;
	//	//カメラ座標からスクリーン画面外のオブジェクトを描画
	//	if (objScreenPosX >= 0 && objScreenPosX <= DXE_WINDOW_WIDTH) {
	//		obj->Draw();
	//	}
	//}
	// PlayCamera::Draw 内にデバッグ描画を追加
	DrawFormatString(10, 10, 1, "Camera X: %.2f", m_pos.x);
	//カメラ座標を描画
	//DrawCircle(m_pos.x, m_pos.y, 10.0f, -1);
}