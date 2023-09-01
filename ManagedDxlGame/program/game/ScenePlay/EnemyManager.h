#pragma once
#include "../SceneAll/GameObjectManager.h"

class Camera;

//“G‚Ì“Ç‚İæ‚è‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class EnemyManager : public GameObjectManager
{

public:
	
	//-----ƒƒ“ƒoŠÖ”-----//
	virtual void Update(float delta_time) override;
	virtual void Draw(float delta_time, const Camera* camera) override;
};