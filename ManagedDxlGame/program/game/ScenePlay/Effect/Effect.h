#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../../SceneAll/GameObject.h"

class Character;

class Effect : public GameObject
{
public:

	Effect(tnl::Vector3 pos, Character* character);
	virtual ~Effect();

protected:
	//-----メンバ変数-----//
	int m_size = 30;						/*サイズ*/

	float active_time = 0.9f;				/*エフェクトの持続時間*/
	float run_time = 0.0f;					/*経過時間*/

	tnl::Vector3 m_offset;					/*オフセット*/

	bool m_is_active = false;				/*活性化フラぐ*/

	eEffectPlayerType m_type;				/*エフェクトの種類*/

	//-----ポインタ変数-----//
	wta::DrawAnim* animLoader = nullptr;	/*アニメーション*/
	Character *m_character = nullptr;		/*キャラクター*/

public:
	//-----Getter,Setter-----//
	int GetSize() const { return  m_size; }

	void SetOffset(tnl::Vector3 offset) { m_offset = offset; }

	bool GetIsActive() const { return m_is_active; }
	void SetIsActive(bool is_moved) { m_is_active = is_moved; }
};