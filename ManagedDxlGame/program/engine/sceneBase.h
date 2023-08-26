#pragma once
#include "../library/tnl_sequence.h"

class SceneBase {

public:
	virtual void Update(float delta_time) {};
	virtual void Draw() = 0;
};

