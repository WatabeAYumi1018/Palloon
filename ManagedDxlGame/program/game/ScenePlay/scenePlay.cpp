#include "../../dxlib_ext/dxlib_ext.h"
#include "ScenePlay.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "../SceneAll/BackGround.h"
#include "../SceneAll/Balloon.h"
#include "../ScenePlay/Map/Map.h"
#include "../SceneAll/UI.h"
#include "../ScenePlay/Character/Enemy/EnemyLoad.h"
#include "../ScenePlay/Collision/Collision.h"
#include "../ScenePlay/Character/Player/Player.h"
#include "../ScenePlay/Character/Enemy/Enemy.h"
#include "../ScenePlay/Camera/Camera.h"


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
	m_backGround = new BackGround();
	m_camera=new Camera();
	m_collision = new Collision();
	m_map = new Map();
	m_player = new Player();
	
	//プレイシーンに必要なObjectを読み込み、初期化する
	m_gameObjects.emplace_back(new Balloon());
	m_gameObjects.emplace_back(m_player);

	EnemyInit();

	m_gameObjects.emplace_back(new UI());
}

void ScenePlay::EnemyInit()
{
	EnemyLoad enemyLoad;
	m_enemyInfos = enemyLoad.LoadEnemyInfo("csv/EnemyLoad.csv");
	auto dataList = enemyLoad.LoadEnemyData("csv/stage1-1enemy.csv");

	for (const auto& data : dataList)
	{
		auto enemy = new Enemy(data, m_enemyInfos[data.s_type_id]);
		m_enemies.emplace_back(enemy);
		m_gameObjects.emplace_back(enemy); 
	}
}


void ScenePlay::Update(float delta_time) 
{	
	m_sequence.update(delta_time);

	m_camera->Update(delta_time, m_player, m_map);
	m_collision->CollisionCalculate(m_player, m_map, 10);
	m_map->LoadMapCollision(m_camera);

	for (auto enemy : m_enemies)
	{
		m_collision->CollisionCalculate(enemy, m_map, 10);
		m_collision->CollisionCharacter(m_player, enemy);
	}

	for (auto obj : m_gameObjects)
	{
		obj->Update(delta_time);
	}
}

void ScenePlay::Draw(float delta_time)
{
	m_backGround->Draw(delta_time, m_camera);
	m_map->Draw(m_camera);

	for (auto obj : m_gameObjects) 
	{
		obj->Draw(delta_time, m_camera);
	}
}

void ScenePlay::Finalize()
{
	for (auto obj : m_gameObjects)
	{
		delete obj;
	}
	m_backGround->Finalize();
	m_map->Finalize();
	m_enemies.clear();
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
