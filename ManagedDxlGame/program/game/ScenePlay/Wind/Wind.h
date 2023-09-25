#pragma once
#include "../../SceneAll/GameObject.h"



class Wind
{
	enum class sWindState
	{
		Blowing,
		Stopped
	};

public:

	Wind();

private:

	//-----メンバ変数-----//
	int m_direction;								/*風の方向*/
	float m_wind_strength=2.0f;						/*風の強さ*/
	float m_time;									/*発生時間*/
	const float BLOWING_TIME = 2.0f;				/*風が吹く時間*/
	const float STOPPED_TIME = 10.0f;				/*風が止む時間*/
	sWindState s_wind_state= sWindState::Stopped;	/*風の状態*/

public:

	//-----メンバ関数-----//
	void Update(float delta_time);	/*風の強さの更新*/

	//-----Getter&Setter-----//
	int GetDirection() const { return m_direction; }
	float GetWindStrength() const { return m_wind_strength; }
};