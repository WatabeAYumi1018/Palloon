#include "../../dxlib_ext/dxlib_ext.h"
#include "ScenePlay.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "../../engine/BackGround.h"
#include "MapManager.h"
#include "CollisionCalc.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "../../engine/UI.h"
#include "PlayCamera.h"

ScenePlay::ScenePlay()
{
	Initialize();
}

ScenePlay::~ScenePlay() 
{
	Finalize();
}

void ScenePlay::Initialize() 
{
	//背景の初期化と描画
	m_camera=new PlayCamera();
	m_back_ground = new BackGround();
	m_map_chip_manager = new MapManager();
	m_ui = new UI();
	m_collision_calc = new CollisionCalc();
	m_player = new Player();
	m_enemy = new Enemy();

	//プレイシーンに必要なObjectを読み込み、初期化する
	gameObjects.emplace_back(m_player);
	gameObjects.emplace_back(m_enemy);
	//gameObjects.emplace_back(new UI());
}

void ScenePlay::Update(float delta_time) 
{	
	m_map_chip_manager->LoadMapCollision(m_camera);
	m_camera->Update(delta_time, m_player, m_map_chip_manager);

	for (auto obj : gameObjects)
	{
		if (Character* chara = dynamic_cast<Character*>(obj))
		{
			m_collision_calc->CollisionCalculate(chara, m_map_chip_manager, 3);
		}
		obj->Update(delta_time);
	}
	
	sequence_.update(delta_time);
}

void ScenePlay::Draw(float delta_time)
{
	m_back_ground->Draw(m_camera);
	m_map_chip_manager->Draw(m_camera);
	
	for (auto obj : gameObjects) 
	{
		obj->Draw(delta_time, m_camera);
	}
	
	m_ui->Draw(delta_time);
}

bool ScenePlay::SeqIdle(float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
	{
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new SceneTitle());
	}
	return true;
}

void ScenePlay::Finalize()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
}