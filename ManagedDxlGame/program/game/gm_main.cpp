#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../game/ScenePlay/Character.h"
#include "../game/ScenePlay/Player.h"
#include "../game/ScenePlay/MapManager.h"
#include "../engine/backGround.h"
#include "../game/ScenePlay/CollisionCalc.h"
#include "ScenePlay/PlayCamera.h"
#include "../engine/UI.h"
#include "../game/ScenePlay/Enemy.h"
#include "../game/ScenePlay/ScenePlay.h"
#include "../game/SceneTitle/SceneTitle.h"
#include "../engine/SceneManager.h"


//①マップ、背景描画 OK
//②キャラクターの動向と当たり判定の実装　多分OK
//③カメラ移動の実装　ひとまずOK
//④攻撃の当たり判定
//⑤敵キャラのAI		ひとまずOK
//⑥UIやパラメータなどとの紐づけ
//⑦アクションの動向とアニメーションなどの確認とひと通りのプレイ実現
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


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
	SetWindowText("Title");
	
	SceneManager::GetInstance(new ScenePlay());
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {


	SceneManager::GetInstance()->Update(delta_time);
	//DrawGraph(1000, 50, LoadGraph("graphics/color-yellow001.PNG"), true);
	//DrawGraph(1100, 50, LoadGraph("graphics/color-yellow002.PNG"), true);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
