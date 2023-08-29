#pragma once
#include "GameEngine.h"
#include "GameObject.h"


class UI{

public:
	UI() { Initialize(); }
	virtual ~UI() {}
	
private:
	tnl::Vector3 m_pos = { 10,500,0 };
	int m_ui_hdl = 0;

public:
	//-----メンバ関数-----//
	void Initialize();
	void Draw(float delta_time) ;
};

//UIの処理一括を行うクラス