#pragma once
#include "Object.h"

class Collision;

class Character :public Object {

public:
	Character(Vector3 m_pos, Vector3 m_velocity);
	virtual ~Character();

	//-----メンバ変数-----//
protected:
	int m_graph_hdl;					//画像ハンドル
	int m_hp;							//HP
	int m_attack;						//攻撃力
	int m_defence;						//防御力
	int m_jump;							//ジャンプ力

	Vector3 m_velocity;					//速度
	Vector3 m_gravity;					//重力
	Vector3 m_size;						//サイズ

	bool m_is_Exit;						//存在フラグ
	bool m_is_Jump;						//ジャンプ中
	bool m_is_Attack;					//攻撃中

	Collision* collision = nullptr;		//当たり判定
	//Effect* effect = nullptr;

	//-----メンバ関数-----//
public:
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw() override;
	void Finalize() override;
};