#include "../../wta_library/wta_IsIntersectCalc.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../ScenePlay/Character/Enemy/EnemyLoad.h"
#include "../ScenePlay/Collision/Collision.h"
#include "../ScenePlay/Character/Player/Player.h"
#include "../ScenePlay/Character/Enemy/Enemy.h"
#include "../ScenePlay/Character/Enemy/EnemySlim.h"
#include "../ScenePlay/Character/Enemy/EnemyPlant.h"
#include "../ScenePlay/Character/Enemy/EnemyBird.h"
#include "../ScenePlay/Character/Enemy/EnemyMasician.h"
#include "../ScenePlay/Character/Enemy/EnemyKobold.h"
#include "../ScenePlay/Character/Enemy/EnemyFairy.h"
#include "../ScenePlay/Character/Enemy/EnemyDoragon.h"
#include "../ScenePlay/Effect/EffectPlayer.h"
#include "../ScenePlay/Camera/Camera.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "../SceneAll/BackGround.h"
#include "../SceneAll/Balloon.h"
#include "../ScenePlay/Map/Map.h"
#include "../SceneAll/UI.h"
#include "ScenePlay.h"


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

	InitEnemy();
	m_gameObjects.emplace_back(new UI());
}

void ScenePlay::InitEnemy()
{
	EnemyLoad enemyLoad;
	m_enemyInfos = enemyLoad.LoadEnemyInfo("csv/EnemyLoad.csv");
	auto dataList = enemyLoad.LoadEnemyData("csv/stage1-1enemy.csv");

	for (const auto& data : dataList)
	{
		Enemy* enemy = nullptr;

		switch (data.s_type_id)
		{
		case 0:
			enemy = new EnemySlim(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		case 1:
			enemy = new EnemyPlant(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		case 2:
			enemy = new EnemyMasician(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		case 3:
			enemy = new EnemyKobold(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		case 4:
			enemy = new EnemyFairy(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		case 5:
			enemy = new EnemyBird(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		case 6:
			enemy = new EnemyDoragon(data, m_enemyInfos[data.s_type_id], m_player);
			break;

		default:
			continue;	//無効なIDの場合はスキップ
		}

		m_enemies.emplace_back(enemy);
		m_gameObjects.emplace_back(enemy);
		
	}
}

void ScenePlay::CreateEffect()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z))
	{
		EffectPlayer* effect = new EffectPlayer();
		effect->SetPos(m_player->GetPos()); 
		effect->SetIsMoved(true);
		m_gameObjects.emplace_back(effect);
		m_effects.emplace_back(effect);
	}
}

void ScenePlay::Update(float delta_time) 
{	
	m_sequence.update(delta_time);

	m_collision->CollisionCalculate(m_player, m_map, 10);
	m_camera->Update(delta_time, m_player, m_map);
	m_map->LoadMapCollision(m_camera);

	CreateEffect();

	CollisionCheck();
	
	RemoveAndDelete();

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
	m_effects.clear();
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

void ScenePlay::CollisionCheck()
{
    for (auto enemy : m_enemies)
    {
        m_collision->CollisionCalculate(enemy, m_map, 10);
        m_collision->CollisionCharacter(m_player, enemy);

        for (auto effect : m_effects)
        {
			if (!effect->GetIsMoved()) 
			{
				m_effectsRemoveList.emplace_back(effect);
				continue;
			}

			if(wta::IsIntersectCircleCircle(effect->GetPos(), effect->GetSize(), enemy->GetPos(), enemy->GetSize()))
            {
                enemy->SetIsDead(true);
                effect->SetIsMoved(false);

                m_enemiesRemoveList.emplace_back(enemy);
				m_effectsRemoveList.emplace_back(effect);
            }
        }
    }
}

void ScenePlay::RemoveAndDeleteEffect(EffectPlayer* effect)
{
	m_gameObjects.remove(effect);
	m_effects.remove(effect);
}

void ScenePlay::RemoveAndDeleteEnemy(Enemy* enemy)
{
	m_gameObjects.remove(enemy);
	m_enemies.remove(enemy);
}

void ScenePlay::RemoveAndDelete()
{
	for (auto effect : m_effectsRemoveList)
	{
		RemoveAndDeleteEffect(effect);
	}

	m_effectsRemoveList.clear();

	for (auto enemy : m_enemiesRemoveList)
	{
		RemoveAndDeleteEnemy(enemy);
	}

	m_enemiesRemoveList.clear();
}