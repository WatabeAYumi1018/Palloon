#pragma once
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

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
	static constexpr float PLAYER_POS_X = 100;			//初期位置
	static constexpr float PLAYER_POS_Y = -100;

	static constexpr int PLAYER_SIZE = 35;				//サイズ
	static constexpr int PLAYER_MAX_HP = 5;				//HP

	static constexpr float PLAYER_VELOCITY_X = 100;		//移動速度（pix/fps）
	static constexpr float PLAYER_VELOCITY_Y = 500;

	static constexpr int PLAYER_JUMP_MAX_COUNT = 3;		//最大ジャンプ回数

	//-----メンバ変数-----//
	int m_hp_hdl = 0;									//HP画像
	int m_jump_count = 0;								//ジャンプ回数
	float m_jump_time = 10;								//ジャンプ時間
	tnl::Vector3 m_jump_height = { 0,200,0 };			//ジャンプ高さ

	//フラグ
	bool m_is_jump = false;								//ジャンプ中
	bool m_is_falling = false;							//落下中
	bool m_was_ground = false;							//前フレームの接地判定

	bool m_pad_direction_right;							//パッドでの入力方向
	bool m_key_direction_right;							//キーでの入力方向

	//ゲームスティック用
	float normalizedInputX;								/*アナログスティックの傾きベクトル*/
	const float DASH_THRESHOLD = 0.8f;					/*ダッシュのしきい値を定義*/
	int m_input_x;
	int m_input_y;

	ePlayerAction e_currentAction = ePlayerAction::Idle_right;		//アクション

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;
	void Finalize() override;

	//-----Getter-----//
	int GetMaxHP() const { return PLAYER_MAX_HP; }

private:
	void HpHandle();						//HPの挙動処理
	void MoveHandle(float delta_time);	//ゲームパッドスティック操作

	void ActionHandle(float delta_time);		//入力処理
};

//Playerのボタン操作の挙動処理を行うクラス
//アニメーションの再生については別クラスを定義した方が分かりやすいかも