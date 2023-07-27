#pragma once
#include "Character.h"

class Enemy :public Character {

public:
	Enemy(Vector3 m_pos, Vector3 m_velocity);
	~Enemy();
	//-----メンバ変数-----//

private:
	eAttackType m_eAttackType;		//アタックタイプタグ判定用

	//-----メンバ関数-----//
public:
	void Initialize();
	void Update(float delta_time);
	void Draw();
	void Finalize();
};

