#pragma once
#include "../../SceneAll/GameObject.h"
#include "../../../wta_library/wta_DrawAnim.h"


//Player,Enemyの基底クラス

class Character :public GameObject
{

public:
	Character(const tnl::Vector3 pos, int size, int hp, const tnl::Vector3 velocity) :
		GameObject(pos), m_size(size), m_hp(hp), m_velocity(velocity) 
	{
		// CSVからアニメーションデータをロード
		animLoader = new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");
	}
	virtual ~Character() 
	{
		delete animLoader;
	}

	//-----メンバ変数-----//
protected:
	int m_size;									/*当たり判定用サイズ*/
	int m_hp;									/*HP*/

	tnl::Vector3 m_velocity = { 100,0,0 };		/*速度*/
	tnl::Vector3 m_gravity = { 0,100,0 };			/*重力*/

	bool m_is_ground = true;						/*接地中*/
	bool m_is_jump = false;						/*ジャンプ中*/
	bool m_is_attack = false;						/*攻撃中*/
	bool m_is_die = false;						/*死亡*/

	wta::DrawAnim* animLoader = nullptr;		//アニメーションデータをロード

public:
	//-----Setter,Getter-----//
	int GetSize() const { return m_size; }
	int GetHp() const { return m_hp; }

	tnl::Vector3 GetVelocity() const { return m_velocity; }
	void SetVelocity(tnl::Vector3 velocity) { m_velocity = velocity; }
};


//Characterクラスのデストラクタが特別な後処理を必要としない場合、
//virtual ~Character() = default;のように明示的に= defaultを使用することは、
//その意図を明確に伝えるために有効です。
