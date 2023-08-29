#pragma once
#include "../../engine/GameEngine.h"

//プレイヤー追従カメラ
//座標取得から補正まで全て管理

class PlayCamera{
public:
	tnl::Vector3 target = { 0, 0, 0 };	
};

