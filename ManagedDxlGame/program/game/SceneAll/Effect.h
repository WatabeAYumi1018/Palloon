#pragma once
#include "GameObject.h"

class Player;

class Effect : public GameObject
{
public:
	Effect(tnl::Vector3 m_pos,Player *player) :GameObject(m_pos){}
	virtual ~Effect() {}

protected:
	//-----メンバ変数-----//
	int m_size = 20;						/*サイズ*/
	tnl::Vector3 m_velocity = {1000,0,0};		/*速度*/
	eEffectType m_type;				/*エフェクトの種類*/

	Player* m_player = nullptr;		/*プレイヤー*/
};