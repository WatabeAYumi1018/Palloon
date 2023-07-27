#pragma once
#include "Character.h"


class Player :public Character {

public:
	Player(Vector3 m_pos, Vector3 m_velocity);
	~Player();

	//-----メンバ変数-----//
private:
	int m_dash;						//ダッシュスピード
	eAttackType m_eAttackType;		//アタックタイプタグ判定用
	Camera* m_camera = nullptr;		//カメラ

	//-----メンバ関数-----//
public:
	void Initialize();
	void Update(float delta_time);
	void Draw();
	void Finalize();

};