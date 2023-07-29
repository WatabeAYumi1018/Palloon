#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../game/ScenePlay/Character.h"
#include "../game/ScenePlay/Player.h"
#include "../game/ScenePlay/MapChip.h"
#include "../engine/backGround.h"

//～8月中旬まで～
//①マップ描画 OK
//②キャラクターの動向と当たり判定の実装
//③カメラ移動の実装
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
MapChip* mapChip;

backGround* back;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	//背景のコンストラクタ作成
	back = new backGround();

	//プレイヤーのコンストラクタ生成
	player = new Player({ 100,100,0 });

	//マップチップのCSVファイル
	string csv_map_tile_data = "csv/TileStage_1-1.csv";	

	//マップチップのコンストラクタ生成
	mapChip = new MapChip(csv_map_tile_data);
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//生成したコンストラクタでUpdate回す
	back->Update(delta_time);
	player->Update(delta_time);
	mapChip->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
