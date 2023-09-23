#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/Music/MusicManager.h"
#include "../SceneAll/Balloon.h"

class GameObject;

class SceneTitle : public SceneBase 
{
private:

	//-----定数-----//
	const int MAX_BOUNDE = 2; // 最大バウンド回数
	const float GROUND_Y = 50;		// 地面のY位置
	const float BOUND_RATE = -1.0f;					// バウンド時の速度の減少率
	const float DISPLAY_TIME = 100;
	const int BALLOON_SPAWN = 20; // バルーンの生成数
	const float SPAWN_INTERVSL = 0.5f; //バルーン生成間隔

	//-----メンバ変数-----//
	int m_back_hdl = 0;
	int m_logo_hdl = 0;
	int m_palloon_hdl = 0;
	
	int m_bound_count = 0;								// バウンドした回数
	
	float m_current_width = 0;
	float m_balloon_spawn_timer = 0.0f;

	tnl::Vector3 m_chara_pos = { 0,-360,0 };			// イラストの初期Y位置。画面外上部に設定
	tnl::Vector3 m_velocity = {0,1.0f,0};					// 初期の下向きの速度
	tnl::Vector3 m_gravity = {0,0.1f,0};				// 重力の強さ

	bool m_is_logo_displayed = false;

	std::vector<Balloon> balloons; // バルーンの配列 

	MusicManager m_musicManager;

	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqIdle);

public:
	//-----メンバ関数-----//
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;

private:

	bool SeqIdle(float delta_time);
	void LogoHandle(float delta_time);
	void BoundHandle(float delta_time);
	void SpawnBalloon();
};
