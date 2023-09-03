#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"
#include "../../wta_library/wta_DrawAnim.h"

class Camera;

//プレイヤーのクラス
//主にボタン操作の挙動処理を行う
//描画についての主な定義はwta_LoadAnim, wta_DrawAnimにて

class Player :public Character 
{
public:
	Player();
	virtual ~Player();

private:
	//-----定数-----//
	static constexpr float PLAYER_POS_X = 100;			//プレイヤーの初期位置
	static constexpr float PLAYER_POS_Y = 250;
	
	static constexpr int PLAYER_SIZE = 35;				//プレイヤーのサイズ
	static constexpr int PLAYER_HP = 5;					//プレイヤーのHP
	
	static constexpr float PLAYER_VELOCITY_X = 100;		//移動速度（pix/fps）
	static constexpr float PLAYER_VELOCITY_Y = 100;

	static constexpr int PLAYER_JUMP_MAX_COUNT = 3;		//最大ジャンプ回数

	//-----メンバ変数-----//
	int m_jump_count = 0;								//ジャンプ回数
	float m_jump_time=10;								//ジャンプ時間
	tnl::Vector3 m_jump_height = {0,500,0};			//ジャンプ高さ
	
	//フラグ
	bool m_is_jump = false;								//ジャンプ中
	bool m_is_falling = false;							//落下中
	bool m_was_ground=false;							//前フレームの接地判定
	bool m_is_dirction_right = true;					//向き


	//-----アニメーション-----//
	wta::DrawAnim *animLoader = nullptr;

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;
	void Finalize() override;

private:
	void MoveHandle(float delta_time);		//移動による座標変化
	void AnimHandle(float delta_time);		//アニメーションの再生
	void isFlag(float delta_time);
};

//Playerのボタン操作の挙動処理を行うクラス
//アニメーションの再生については別クラスを定義した方が分かりやすいかも