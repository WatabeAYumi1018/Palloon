#pragma once
#include "../../engine/sceneBase.h"

class GameObject;

class SceneTitle : public SceneBase {

private:
	//-----ƒƒ“ƒo•Ï”-----//
	int m_back_hdl = 0;
	int m_logo_hdl = 0;
	float m_current_width = 0;
	const float m_display_time = 100;

	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqIdle);

public:
	//-----ƒƒ“ƒoŠÖ”-----//
	void Update(float delta_time) override;
	void Draw(float delta_time) override;

private:

	bool SeqIdle(float delta_time);
	void logoHandle(float delta_time);
 
};
