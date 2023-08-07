#pragma once
#include "../../engine/GameEngine.h"

class Object {
public:
	Object(tnl::Vector3 pos) :m_pos(pos){}
	virtual ~Object(){}

protected:
	tnl::Vector3 m_pos;			//À•W
	dxe::Mesh* m_mesh=nullptr;	//ƒƒbƒVƒ…

public:
	 void Initialize() {}
	 void Update(float delta_time) {}
	 void Draw() {}
	 void Finalize() {}
};