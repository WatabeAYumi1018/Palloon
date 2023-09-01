#pragma once
#include "../engine/GameEngine.h"
#include "GameObject.h"


//背景を描画する
//シーンごとに別々の背景をロード、描画するのみ。
//構造体として扱い、アクセスを容易にする

class BackGround : public GameObject
{

public:
	BackGround();
	virtual ~BackGround() {}

private:
	//-----メンバ変数-----//
	float m_scroll_speed = 0.05f;
	int m_back_hdl = 0;

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Draw(float delta_time, const Camera* camera) override;
};
