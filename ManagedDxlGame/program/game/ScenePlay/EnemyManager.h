#pragma once
#include "../SceneAll/GameObjectManager.h"

class Camera;

//敵の読み取りを管理するクラス
class EnemyManager : public GameObjectManager
{

public:
	
	//-----メンバ関数-----//
	virtual void Update(float delta_time) override;
	virtual void Draw(float delta_time, const Camera* camera) override;
};