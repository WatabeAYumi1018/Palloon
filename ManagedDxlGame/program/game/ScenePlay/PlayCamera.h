#pragma once
#include "../../engine/GameEngine.h"

//プレイヤー追従カメラ

class MapManager;
class Player;


class PlayCamera{
public:
	tnl::Vector3 target = { 0, 0, 0 };

private:
	bool is_active = false;
	MapManager *m_map_manager=nullptr;
	Player *m_player=nullptr;

public:
	void Update(float delta_time);
};

