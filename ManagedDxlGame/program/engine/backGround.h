#pragma once
#include "GameEngine.h"

//背景を描画する
//シーンごとに別々の背景をロード、描画するのみ。
//構造体として扱い、アクセスを容易にする

struct BackGround{
	//-----メンバ変数-----//
	int s_back_hdl = 0;
	tnl::Vector3 s_pos = { 0,0,0 };
	
	//-----メンバ関数-----//
	void Initialize() {s_back_hdl = LoadGraph("image/backGround.png");}
	void Draw() {DrawGraph(s_pos.x, s_pos.y, s_back_hdl, TRUE);}
};
