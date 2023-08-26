#pragma once
#include "../../engine/GameEngine.h"

//座標を持ってるだけのクラスが必要かな？と思って作ったけど、今のところ不明

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
};