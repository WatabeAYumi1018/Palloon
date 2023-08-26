#pragma once
#include "../../engine/GameEngine.h"

class Character;
class MapManager;

//プレイヤー追従カメラ
//座標取得から補正まで全て管理

class PlayCamera{

public:
	PlayCamera(Character *player);
	virtual ~PlayCamera();

private:
	//-----メンバ変数-----//
	float m_scroll_x;				//スクロールのX座標
	Character *m_player=nullptr;	//プレイヤー追従用

public:
	//-----メンバ関数-----//
	void Update(float delta_time);	//更新
	void Scroll();					//スクロール
	void PosRevise();				//座標補正

	//-----Getter-----//
	float GetScrollX() const { return m_scroll_x; }
};
