#pragma once
#include "GameObject.h"

class Player;

class Effect : public GameObject
{
public:
	Effect(tnl::Vector3 m_pos,Player *player) :GameObject(m_pos), m_player(player) {}
	virtual ~Effect() {}

protected:
	//-----メンバ変数-----//
	int m_size = 20;						/*サイズ*/
	float duration = 0.8f;					/*エフェクトの持続時間*/
	float elapsed_time = 0.0f;				/*経過時間*/
	
	tnl::Vector3 m_offset;					/*オフセット*/
	
	bool m_is_moved = false;				/*終了フラグ*/

	eEffectPlayerType m_type;				/*エフェクトの種類*/

	Player* m_player = nullptr;				/*プレイヤー*/

public:

	int GetSize() const { return m_size; }

	void SetOffset(tnl::Vector3 offset) { m_offset = offset; }

	bool GetIsMoved() const { return m_is_moved; }
	void SetIsMoved(bool is_moved) { m_is_moved = is_moved; }
	
	float GetElapsedTime() const { return elapsed_time; }
	
	float GetDuration() const { return duration; }
};