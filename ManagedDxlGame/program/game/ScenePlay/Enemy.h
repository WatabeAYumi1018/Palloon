#pragma once
#include "../../engine/GameEngine.h"
#include "Character.h"

//主に敵のAIを管理するクラス

class Enemy :public Character {

public:
	Enemy();
	virtual ~Enemy();

private:
	//-----メンバ変数-----//
	eAttackType m_eAttackType;		//アタックタイプタグ判定用

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;
};