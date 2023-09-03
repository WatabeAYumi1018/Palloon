#pragma once
#include "../engine/GameEngine.h"
#include "../game/SceneAll/GameObject.h"

class Camera;


//UIの処理一括を行うクラス
class UI : public GameObject
{
public:
	UI();
	virtual ~UI() {}
	
private:
	//-----メンバ変数-----//
	int m_ui_hdl = 0;
	int m_extend_x;
	int m_extend_y;

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Draw(float delta_time, const Camera* camera) override;
};
