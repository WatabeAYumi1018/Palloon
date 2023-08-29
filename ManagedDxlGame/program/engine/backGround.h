#pragma once
#include "GameEngine.h"

class PlayCamera;

//背景を描画する
//シーンごとに別々の背景をロード、描画するのみ。
//構造体として扱い、アクセスを容易にする

class BackGround{

public:
	BackGround() { Initialize();}
	virtual ~BackGround() {}

private:
	//-----メンバ変数-----//
	tnl::Vector3 m_pos = { 0,0,0 };
	int m_back_hdl = 0;

public:
	//-----メンバ関数-----//
	void Initialize();
	void Draw(const PlayCamera* camera);
};
