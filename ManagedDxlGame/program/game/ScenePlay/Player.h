#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"
#include "../../wta_library/wta_DrawAnim.h"

//プレイヤーのクラス
//主にボタン操作の挙動処理を行う
//描画についての主な定義はwta_LoadAnim, wta_DrawAnimにて

class Player :public Character {

public:
	Player();
	virtual ~Player();

private:
	//-----定数-----//
	const tnl::Vector3 PLAYER_POS = { 0,-100,0 };		//プレイヤーの初期位置
	const int PLAYER_SIZE = 50;							//プレイヤーのサイズ
	const int PLAYER_HP = 5;							//プレイヤーのHP
	const tnl::Vector3 PLAYER_VELOCITY = { 100,100,0 };	//移動速度（pix/fps）

	//-----メンバ変数-----//
	int m_jump_time;						//ジャンプ時間
	tnl::Vector3 m_jump_velocity;			//ジャンプ速度
	bool m_is_jump = false;					//ジャンプ中
	bool m_was_ground=false;				//前フレームの接地判定

	//-----アニメーション-----//
	wta::DrawAnim *animLoader = nullptr;

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Move(float delta_time);
	void Finalize() override;
};

//Playerのボタン操作の挙動処理を行うクラス
//アニメーションの再生については別クラスを定義した方が分かりやすいかも