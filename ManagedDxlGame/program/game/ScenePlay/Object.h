#pragma once
#include "../../engine/GameEngine.h"

class Object {
public:
	Object(tnl::Vector3 pos) :m_pos(pos){}
	virtual ~Object(){}

protected:
	tnl::Vector3 m_pos;			//座標
	dxe::Mesh* m_mesh=nullptr;	//メッシュ

public:
	 void Initialize() {}
	 void Update(float delta_time) {}
	 void Draw() {}
	 void Finalize() {}
	 // 座標を調整する関数
	 void AdjustPosition(const tnl::Vector3& offset) {m_pos += offset;}

	 //-----Setter,Getter-----//
	 //void SetPos(const tnl::Vector3& pos) {m_pos = pos;}
	 //tnl::Vector3 GetPos() const {return m_pos;}
};