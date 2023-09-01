#pragma once
#include "../../engine/GameEngine.h"

//プレイヤー追従カメラ

class Character;
class MapManager;

class PlayCamera
{
private:

	//-----メンバ変数-----//
	tnl::Vector3 m_target = { 0, 0, 0 };
	bool is_active = false;

public:
	
	//-----メンバ関数-----//
	void Update(float delta_time, Character* chara, MapManager* mapChip);

private:
	
	void MoveRange(Character* chara, MapManager* mapChip);
	void Scroll(Character* chara, MapManager* mapChip);

public:

	//-----Getter&Setter-----//
	tnl::Vector3 GetTarget() const { return m_target; }
	void SetTarget(tnl::Vector3 target) { m_target = target; }
};

