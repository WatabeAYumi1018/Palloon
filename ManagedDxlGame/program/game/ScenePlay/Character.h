#pragma once
#include "Object.h"

class Collision;

class Character 
//	:public Object 
{

public:
	Character(tnl::Vector3 pos,int hp,int attack, float jump_time, tnl::Vector3 jump_velocity);
	virtual ~Character();

	//-----メンバ変数-----//
protected:
	int m_graph_hdl;					//画像ハンドル
	int m_hp;							//HP
	int m_attack;						//攻撃力
	int m_jump_time;					//ジャンプ時間
	
	tnl::Vector3 m_jump_velocity;			//ジャンプ速度
	tnl::Vector3 m_pos;						//座標(Object反映するまでの仮)
	tnl::Vector3 m_gravity = {0,100,0};		//重力
	tnl::Quaternion m_rotation;				//回転

	//Vector3 velocity;					//速度(エフェクトや遠距離の速さの時に使用するかも)
	//Vector3 m_size;					//サイズ

	bool m_is_Exit=false;				//存在フラグ
	bool m_is_Ground=true;				//接地中
	bool m_is_Jump=false;				//ジャンプ中
	bool m_is_Attack=false;				//攻撃中

	Collision* m_collision = nullptr;		//当たり判定
	//Effect* effect = nullptr;

	//-----メンバ関数-----//
public:
	virtual void Initialize() ;
	virtual void Update(float delta_time) ;
	virtual void Draw(float delta_time) ;
	virtual void Finalize() ;
};