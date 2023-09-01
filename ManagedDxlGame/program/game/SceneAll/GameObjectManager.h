#pragma once

class Camera;

//各sceneでサブManagerクラスを管理するための基底クラス

class GameObjectManager
{

public:

	//-----メンバ関数-----//
	virtual void Update(float delta_time) { }
	virtual void Draw(float delta_time, const Camera* camera) {}
};