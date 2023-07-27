#pragma once
#include "Object.h"

class Collision;

class Character 
	//:public Object 
{

public:
	Character(Vector3 pos,int hp,int attack, Vector3 jump);
	virtual ~Character();

	//-----メンバ変数-----//
protected:
	int m_graph_hdl;					//画像ハンドル
	int m_hp;							//HP
	int m_attack;						//攻撃力
	
	Vector3 m_jump;						//ジャンプ力

	Vector3 m_pos;						//座標(Object反映するまでの仮)
	//Vector3 velocity;					//速度(エフェクトや遠距離の速さの時に使用するかも)
	Vector3 m_gravity = {0,100,0};		//重力
	Quaternion m_rotation;				//回転
	//Vector3 m_size;					//サイズ

	bool m_is_Exit=false;				//存在フラグ
	bool m_is_Jump=false;				//ジャンプ中
	bool m_is_Attack=false;				//攻撃中

	Collision* collision = nullptr;		//当たり判定
	//Effect* effect = nullptr;

	//-----メンバ関数-----//
public:
	virtual void Initialize() ;
	virtual void Update(float delta_time) ;
	virtual void Draw() ;
	virtual void Finalize() ;
};