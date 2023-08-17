#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"

class Character;
class MapChip;

//プレイヤー追従カメラ
class PlayCamera :public Object{
public:
	PlayCamera(tnl::Vector3 pos, Character* player);
	~PlayCamera();
private:
	//-----メンバ変数-----//
	//float m_height;			//高さ
	float m_scroll_x;			//スクロールのX座標

	//-----クラスポインタ変数-----//
	Character* m_player = nullptr;	//プレイヤー
	MapChip* m_map_chip = nullptr;	//マップチップ

public:
	//-----メンバ関数-----//
	void Update(float delta_time);	//座標更新
	void Scroll();	//スクロール
};