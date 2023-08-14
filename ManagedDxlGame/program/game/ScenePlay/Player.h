#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"
#include "AnimLoadLoop.h"

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
	int animFileHdl=0;					//画像のハンドル
	//dxe::Camera* m_camera = nullptr;	//カメラ
	MapChip* m_mapchip = nullptr;		//マップチップ
	//-----アニメーション-----//
	//後日、アニメーションクラスを作成し、そこに移動
	AnimLoadLoop* animLoop = nullptr;			//walk_right
	AnimLoadLoop* animLoop2 = nullptr;			//walk_left
	AnimLoadLoop* animLoop3 = nullptr;			//jump_right
	AnimLoadLoop* animLoop4 = nullptr;			//jump_left
	AnimLoadLoop* animLoop5 = nullptr;			//idle_right
	AnimLoadLoop* animLoop6 = nullptr;			//idle_left
	AnimLoadLoop* animLoop7 = nullptr;			//run_right
	AnimLoadLoop* animLoop8 = nullptr;			//run_left
	AnimLoadLoop* animLoop9 = nullptr;			//touchdown_right
	AnimLoadLoop* animLoop10 = nullptr;			//touchdown_left

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Move(float delta_time);
	void Finalize() override;
	
	float overCenterX();

	//-----Setter,Getter-----//
	void SetPos(tnl::Vector3 pos) { m_pos = pos; }
	tnl::Vector3 GetPos() const { return m_pos; }
};

//Playerのボタン操作の挙動処理を行うクラス
//アニメーションの再生については別クラスを定義した方が分かりやすいかも