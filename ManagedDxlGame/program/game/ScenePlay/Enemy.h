#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"


class Enemy :public Character {

public:
	Enemy(Vector3 pos);
	~Enemy();

private:
	//-----メンバ変数-----//
	eAttackType m_eAttackType;		//アタックタイプタグ判定用

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw() override;
	void Finalize() override;
};

