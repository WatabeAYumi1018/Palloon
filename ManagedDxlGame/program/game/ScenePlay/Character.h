#pragma once
#include "../../engine/GameObject.h"

//Player,Enemyの基底クラス（抽象クラス）

class Character :public GameObject{
public:
	Character(tnl::Vector3 m_pos, int size, int hp, tnl::Vector3 velocity) :GameObject(m_pos), m_size(size), m_hp(hp), m_velocity(velocity){}
	virtual ~Character() {}

	//-----メンバ変数-----//
protected:
	std::string m_name;							//名前
	int m_size;									//当たり判定用サイズ
	int m_hp;									//HP

	tnl::Vector3 m_gravity = {0,100,0};			//重力
	tnl::Vector3 m_velocity;					//速度(エフェクトや遠距離の速さの時に使用するかも)

	eCharaType e_chara_type = eCharaType::Max;	//キャラタイプ判定用

	bool m_is_ground=true;						//接地中
	bool m_is_attack=false;						//攻撃中

public:
	//-----Setter,Getter-----//
	std::string GetName() const { return m_name; }
	int GetSize() const { return m_size; }
	int GetHp() const { return m_hp; }

	eCharaType GetTag() const { return e_chara_type; }
	void SetTag(eCharaType charaType) { e_chara_type = charaType; }

	tnl::Vector3 GetVelocity() const { return m_velocity; }
};

//Effect* effect = nullptr;

//Characterクラスのデストラクタが特別な後処理を必要としない場合、
//virtual ~Character() = default;のように明示的に= defaultを使用することは、
//その意図を明確に伝えるために有効です。
