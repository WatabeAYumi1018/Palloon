#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"
#include "Aniｍ.h"

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
	Anim* animLoop = nullptr;			//アニメーションループ
	Anim* animLoop2 = nullptr;			//アニメーションループ
	Anim* animLoop3 = nullptr;			//アニメーションループ

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Move(float delta_time);
	void Finalize() override;

	//-----Setter,Getter-----//
	//void SetCamera(dxe::Camera* camera) { m_camera = camera; }
	//dxe::Camera* GetCamera() const { return m_camera; }
	void SetPos(tnl::Vector3 pos) { m_pos = pos; }
	tnl::Vector3 GetPos() const { return m_pos; }

	//void SetAttackType(eAttackType type) { m_eAttackType = type; }
	//eAttackType GetAttackType() { return m_eAttackType; }
};