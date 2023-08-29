#pragma once
#include "../library/tnl_sequence.h"

class PlayCamera;

class SceneBase {
public:
	virtual void Initialize() {}
	virtual void Update(float delta_time) {}
	virtual void Draw(float delta_time) {}
	virtual void Finalize() {}
};

