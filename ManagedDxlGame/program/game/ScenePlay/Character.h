#pragma once
#include "Object.h"

class CollisionCalc;

class Character {
public:
	Character(tnl::Vector3 pos, int size, int hp, float jump_time, tnl::Vector3 jump_velocity) :
		m_pos(pos), m_size(size), m_hp(hp), m_jump_time(jump_time), m_jump_velocity(jump_velocity)
	{
	}
	virtual ~Character() {}

	//-----メンバ変数-----//
protected:
	int m_size;								//サイズ
	int m_hp;								//HP
	int m_jump_time;						//ジャンプ時間
	
	tnl::Vector3 m_jump_velocity;			//ジャンプ速度
	tnl::Vector3 m_pos;						//座標(Object反映するまでの仮)
	tnl::Vector3 m_gravity = {0,100,0};		//重力
	tnl::Vector3 velocity;					//速度(エフェクトや遠距離の速さの時に使用するかも)

	bool m_is_Exit=false;					//存在フラグ
	bool m_is_Ground=true;					//接地中
	bool m_is_Jump=false;					//ジャンプ中
	bool m_is_Attack=false;					//攻撃中

	CollisionCalc* m_collision = nullptr;	//当たり判定

public:
	//-----メンバ関数-----//
	virtual void Initialize() = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Draw(float delta_time) = 0;
	virtual void Finalize() = 0;

	//-----Setter,Getter-----//
	tnl::Vector3 GetPos() const { return m_pos; }
	void SetPos(tnl::Vector3 pos) { m_pos = pos; }
	tnl::Vector3 GetVelocity() const { return velocity; }
	int GetSize() const { return m_size; }
};

//Effect* effect = nullptr;

//Characterクラスのデストラクタが特別な後処理を必要としない場合、
//virtual ~Character() = default;のように明示的に= defaultを使用することは、
//その意図を明確に伝えるために有効です。
