#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"


class Player :public Character {

public:
	Player(Vector3 pos);
	~Player();

private:
	//-----定数-----//
	const int PLAYER_SPEED_WALK = 400;		//移動速度（pix/fps）
	const int PLAYER_SPEED_DASH = 800;		//ダッシュ速度（pix/fps）
	const int PLAYER_HP = 5;				//プレイヤーのHP

	//-----メンバ変数-----//
	Vector3 m_jump_velocity = {0,0,0};		//ジャンプ力（pix/fps）
	int m_dash;								//ダッシュスピード
	Camera* m_camera = nullptr;				//カメラ

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw() override;
	void Finalize() override;

	//-----Setter,Getter-----//
	void SetDash(int dash) { m_dash = dash; }
	int GetDash() { return m_dash; }
	
	void SetCamera(Camera* camera) { m_camera = camera; }
	Camera* GetCamera() { return m_camera; }

	//void SetAttackType(eAttackType type) { m_eAttackType = type; }
	//eAttackType GetAttackType() { return m_eAttackType; }
};