#pragma once
#include "../engine/GameObject.h"

class Effect : public GameObject
{
public:
	Effect(tnl::Vector3 m_pos);
	virtual ~Effect();

	//-----ƒƒ“ƒoŠÖ”-----//
private:
	void Update(float delta_time) override;
	void Draw(float delta_time, const PlayCamera* camera) override;
};