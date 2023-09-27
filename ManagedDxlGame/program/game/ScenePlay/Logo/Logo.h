#pragma once
#include "../../SceneAll/GameObject.h"

class Logo :public GameObject
{
public:

	Logo();
	~Logo();

private:
	
	//-----’è”-----//
	float BLINK_TIME = 2.0f;

	//-----ƒƒ“ƒo•Ï”-----//
	int m_clear_botton_hdl = 0;
	int m_clear_logo_hdl = 0;
	int m_burst_logo_hdl = 0;
	int m_fall_logo_hdl = 0;

	int m_botton_size = 150;
	int m_result_x_size = 400;
	int m_result_y_size = 200;

	float m_blink_time = 0.0f;

	bool m_is_clear = false;
	bool m_is_draw = false;

	eLogoState e_logo_state = eLogoState::None;

public:

	//-----ƒƒ“ƒoŠÖ”-----//
	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;

	//-----Getter&Setter-----//
	void SetIsClear(bool is_clear) { m_is_clear = is_clear; }

	eLogoState GetLogoState() const { return e_logo_state; }
	void SetLogoState(eLogoState logo_state) { e_logo_state = logo_state; }
};
