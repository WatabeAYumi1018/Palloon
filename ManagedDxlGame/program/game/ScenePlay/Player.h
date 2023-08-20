#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"
#include "AnimLoad.h"

class MapChip;

class Player :public Character {

public:
	Player();
	~Player();

private:
	//-----定数-----//
	const int PLAYER_SPEED_WALK = 100;		//移動速度（pix/fps）
	const int PLAYER_SPEED_DASH = 300;		//ダッシュ速度（pix/fps）
	const int PLAYER_HP = 5;				//プレイヤーのHP

	//-----メンバ変数-----//
	int ye = 0;
	int animFileHdl=0;					//画像のハンドル
	bool m_was_Ground=false;			//前フレームの接地判定

	//-----アニメーション-----//
	//後日、アニメーションクラスを作成し、そこに移動
	AnimLoad* animLoop = nullptr;			//walk_right
	AnimLoad* animLoop2 = nullptr;			//walk_left
	AnimLoad* animLoop3 = nullptr;			//jump_right
	AnimLoad* animLoop4 = nullptr;			//jump_left
	AnimLoad* animLoop5 = nullptr;			//idle_right
	AnimLoad* animLoop6 = nullptr;			//idle_left
	AnimLoad* animLoop7 = nullptr;			//run_right
	AnimLoad* animLoop8 = nullptr;			//run_left
	AnimLoad* animLoop9 = nullptr;			//touchdown_right
	AnimLoad* animLoop10 = nullptr;			//touchdown_left

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Move(float delta_time);
	void Finalize() override;
	
	float overCenterX();
};

//Playerのボタン操作の挙動処理を行うクラス
//アニメーションの再生については別クラスを定義した方が分かりやすいかも