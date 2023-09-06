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
	tnl::Vector3 m_velocity = {1000,0,0};	/*速度*/
	bool m_is_moved = false;				/*終了フラグ*/
	float duration = 3.0f;					/*エフェクトの持続時間*/
	float elapsed_time = 0.0f;				/*経過時間*/
	eEffectType m_type;						/*エフェクトの種類*/

	Player* m_player = nullptr;				/*プレイヤー*/

public:
	int GetSize() const { return m_size; }
	bool GetIsMoved() const { return m_is_moved; }
	void SetIsMoved(bool is_moved) { m_is_moved = is_moved; }
	float GetElapsedTime() const { return elapsed_time; }
	float GetDuration() const { return duration; }
};