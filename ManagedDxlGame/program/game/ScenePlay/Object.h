#pragma once
#include "../../engine/GameEngine.h"

class Object {
	Object(Vector3 pos);
	virtual ~Object();

protected:
	Vector3 m_pos;						//À•W
	Mesh* m_mesh;						//ƒƒbƒVƒ…

public:
	 void Initialize() {}
	 void Update(float delta_time) {}
	 void Draw() {}
	 void Finalize() {}
};