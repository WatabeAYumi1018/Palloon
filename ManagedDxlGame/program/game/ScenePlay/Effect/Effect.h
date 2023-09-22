#pragma once
#include "../../SceneAll/GameObject.h"

class Player;

class Effect : public GameObject
{
public:
	Effect(tnl::Vector3 m_pos, Player* player) :GameObject(m_pos), m_player(player) {}
	virtual ~Effect() {}

protected:
	//-----メンバ変数-----//
	int m_size = 30;						/*サイズ*/

	float active_time = 0.8f;				/*エフェクトの持続時間*/
	float run_time = 0.0f;					/*経過時間*/

	tnl::Vector3 m_offset;					/*オフセット*/

	bool m_is_active = false;				/*活性化フラぐ*/

	eEffectPlayerType m_type;				/*エフェクトの種類*/

	//-----ポインタ変数-----//
	Player* m_player = nullptr;				/*プレイヤー*/

public:
	//-----Getter,Setter-----//
	int GetSize() const { return  m_size; }

	void SetOffset(tnl::Vector3 offset) { m_offset = offset; }

	bool GetIsActive() const { return m_is_active; }
	void SetIsActive(bool is_moved) { m_is_active = is_moved; }
};