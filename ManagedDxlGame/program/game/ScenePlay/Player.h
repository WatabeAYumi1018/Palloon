#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"
#include "../../wta_library/wta_DrawAnim.h"

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
	wta::DrawAnim *animLoader = nullptr;
	
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