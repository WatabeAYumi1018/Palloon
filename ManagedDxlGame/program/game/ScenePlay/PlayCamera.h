#pragma once
#include "../../engine/GameEngine.h"

class Character;
class MapChip;

//プレイヤー追従カメラ
class PlayCamera{
public:
	PlayCamera(Character *player);
	~PlayCamera();

private:
	//-----メンバ変数-----//
	float m_scroll_x;			//スクロールのX座標

	//-----クラスポインタ変数-----//
	Character *m_player=nullptr;	//プレイヤー

public:
	//-----メンバ関数-----//
	void Update(float delta_time);	//座標更新
	void Scroll();	//スクロール

	//-----Getter-----//
	float GetScrollX() const { return m_scroll_x; }

};