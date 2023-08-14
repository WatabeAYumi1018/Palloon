#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../game/ScenePlay/Character.h"
#include "../game/ScenePlay/Player.h"
#include "../game/ScenePlay/MapChip.h"
#include "../engine/backGround.h"
#include "../game/ScenePlay/Collision.h"
#include "ScenePlay/PlayCamera.h"

//～8月中旬まで～
//①マップ、背景描画 OK
//②キャラクターの動向と当たり判定の実装
//③カメラ移動の実装　ひとまずOK
//④攻撃の当たり判定
//⑤敵キャラのAI
//⑥UIやパラメータなどとの紐づけ
//⑦アクションの動向とアニメーションなどの確認とひと通りのプレイ実現

//～８月中まで～
//⑧ステージセレクト画面作成
//⑨ひと通りゲームとして完成
//⑩ボス戦
//⑪アイテム実装

//～9月中旬まで～
//⑫デバック
//⑬画面セレクト作成
//⑭タイトル作成
//⑮エンディング作成

// ～期限まで～
//⑯最終確認


Player* player;
//MapChip* mapChip;
PlayCamera* camera;
backGround* back;

//Collision* collision = nullptr;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	//コンストラクタ作成
	back = new backGround();
	player = new Player();
	//collision = new Collision({0,0,0}, 16);	
	camera = new PlayCamera({0,0,0}, player);
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	////生成したコンストラクタでUpdate回す
	back->Update(delta_time);
	player->Update(delta_time);
	camera->Update(delta_time);

	//DrawLine(line_pos_start_x, line_pos_start_y, line_pos_end_x, line_pos_end_y, -1, 1);
	//DrawCircle(circle_pos.x, circle_pos.y, radius, -1, 1);

	////キー移動
	//if (Input::IsKeyDown(eKeys::KB_LEFT)) {
	//	circle_pos.x -= 10;
	//}
	//if (Input::IsKeyDown(eKeys::KB_RIGHT)) {
	//	circle_pos.x += 10;
	//}
	//if (Input::IsKeyDown(eKeys::KB_UP)) {
	//	circle_pos.y -= 10;
	//}
	//if (Input::IsKeyDown(eKeys::KB_DOWN)) {
	//	circle_pos.y += 10;
	//}

	////円と線の当たり判定
	//if (collision->CircleLine(circle_pos, radius, line_pos_start_x, line_pos_start_y, line_pos_end_x, line_pos_end_y)) {
	//	DrawFormatString(0, 0, -1, "当たってる");
	//}
	//else {
	//	DrawFormatString(0, 0, -1, "当たってない");
	//}
	//	
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	camera = nullptr;
	delete camera;
}
