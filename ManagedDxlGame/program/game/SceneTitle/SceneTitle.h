#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/Balloon.h"

class GameObject;

class SceneTitle : public SceneBase {

private:
	//-----メンバ変数-----//
	int m_back_hdl = 0;
	int m_logo_hdl = 0;
	int m_palloon_hdl = 0;
	int m_bounceCount = 0;								// バウンドした回数

	float m_current_width = 0;
	
	tnl::Vector3 m_chara_pos = { 0,-360,0 };			// イラストの初期Y位置。画面外上部に設定
	tnl::Vector3 m_velocity = {0,1.0f,0};					// 初期の下向きの速度
	tnl::Vector3 m_gravity = {0,0.1f,0};				// 重力の強さ

	bool m_is_logo_displayed = false;

	const int m_maxBounce = 2; // 最大バウンド回数
	const float m_ground_y = 50;		// 地面のY位置
	const float m_bounceRate = -1.0f;					// バウンド時の速度の減少率
	const float m_display_time = 100;

	std::vector<Balloon> balloons; // バルーンの配列 

	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqIdle);

public:
	//-----メンバ関数-----//
	void Update(float delta_time) override;
	void Draw(float delta_time) override;

private:

	bool SeqIdle(float delta_time);
	void logoHandle(float delta_time);
	void bounceHandle(float delta_time);
	void SpawnBalloon();
};
