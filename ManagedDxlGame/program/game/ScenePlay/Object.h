#pragma once
#include "../../engine/GameEngine.h"

class Object {
	Object(tnl::Vector3 pos);
	virtual ~Object();

protected:
	tnl::Vector3 m_pos;						//À•W
	dxe::Mesh* m_mesh;						//ƒƒbƒVƒ…

public:
	 void Initialize() {}
	 void Update(float delta_time) {}
	 void Draw() {}
	 void Finalize() {}
};