#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"


using namespace std;
using namespace tnl;

//～8月中旬まで～
//①マップ描画
//②キャラクターの動向と当たり判定の実装
//③攻撃の当たり判定
//④敵キャラのAI
//⑤UIやパラメータなどとの紐づけ
//⑥アクションの動向とアニメーションなどの確認とひと通りのプレイ実現

//～８月中まで～
//⑦ステージセレクト画面作成
//⑧ひと通りゲームとして完成
//⑨ボス戦
//⑩アイテム実装

//～9月中旬まで～
//⑪デバック
//⑫画面セレクト作成
//⑬タイトル作成
//⑭エンディング作成

// ～期限まで～
//⑮最終確認

class SceneBase {};

//プレイヤー、敵、カメラ、アイテム、攻撃etc
class ScenePlay
	//:public SceneBase
{};

class Camera {};

class Effect {};

class UI {};

class Collision {};

class Character {

	Character(Vector3 m_pos, Vector3 m_velocity);
	virtual ~Character();

protected:
	int graph_hdl;						//画像ハンドル
	int hp;


	Vector3 m_pos;						//座標
	Vector3 m_velocity;					//速度
	Vector3 m_gravity;					//重力

	bool is_Exit;						//存在フラグ
	bool is_Jump;						//ジャンプ中
	bool is_Attack;						//攻撃中

	Collision* collision = nullptr;		//当たり判定
	//Effect* effect = nullptr;
};

class Player :public Character {};

class Enemy :public Character {};

class Item :public Character {};



//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
