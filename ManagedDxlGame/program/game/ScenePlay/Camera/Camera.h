#pragma once
#include "../../../engine/GameEngine.h"

//プレイヤー追従カメラ

class Player;
class Map;

class Camera
{

private:

	//-----メンバ変数-----//
	tnl::Vector3 m_target = { 0, 0, 0 };	/*追従ターゲット*/
	bool m_is_scroll = false;				/*カメラスクロール軌道*/

	//-----メンバ関数-----//
	void MoveRange(Player* player, Map* map);
	void Scroll(Player* player, Map* map);

public:

	void Update(float delta_time, Player* player, Map* map);

	//-----Getter&Setter-----//
	tnl::Vector3 GetTarget() const { return m_target; }
};

