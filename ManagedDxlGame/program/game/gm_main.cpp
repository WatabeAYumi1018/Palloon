#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../game/ScenePlay/Character.h"
#include "../game/ScenePlay/Player.h"
#include "../game/ScenePlay/MapChip.h"
#include "../engine/backGround.h"
#include "../game/ScenePlay/CollisionCalc.h"
#include "ScenePlay/PlayCamera.h"
#include "../engine/UI.h"

//〜8月中旬まで〜
//�@マップ、背景描画 OK
//�Aキャラクターの動向と当たり判定の実装
//�Bカメラ移動の実装　ひとまずOK
//�C攻撃の当たり判定
//�D敵キャラのAI
//�EUIやパラメータなどとの紐づけ
//�Fアクションの動向とアニメーションなどの確認とひと通りのプレイ実現

//〜８月中まで〜
//�Gステージセレクト画面作成
//�Hひと通りゲームとして完成
//�Iボス戦
//�Jアイテム実装

//〜9月中旬まで〜
//�Kデバック
//�L画面セレクト作成
//�Mタイトル作成
//�Nエンディング作成

// 〜期限まで〜
//�O最終確認

MapChip * mapChip = nullptr;
UI* ui=nullptr;
Character *player=nullptr;
PlayCamera* camera=nullptr;
backGround* back=nullptr;
CollisionCalc* m_collision = nullptr;	//当たり判定


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	//コンストラクタ作成(後に多態性でまとめて管理)
	back = new backGround();
	ui = new UI({10,0,50});
	player = new Player();
	camera = new PlayCamera({0,0,0},player);
	m_collision = new CollisionCalc();
	mapChip = new MapChip();
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	////生成したコンストラクタでUpdate回す
	//back->Update(delta_time);
	ui->Update(delta_time);
	player->Update(delta_time);
	mapChip->Update(delta_time, camera);
	m_collision->CollisionCalculate(player, mapChip, 2);
	m_collision->CheckBoxCollision(player, mapChip, mapChip->GetCollisionInfo());
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	player = nullptr;
	delete player;
	mapChip = nullptr;
	delete mapChip;
	back = nullptr;
	delete back;
	ui = nullptr;
	delete ui; 
	camera = nullptr;
	delete camera;
	m_collision = nullptr;
	delete m_collision;
}
