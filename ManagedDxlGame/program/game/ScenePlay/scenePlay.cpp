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
	//m_graph_hdl = LoadGraph("graphics/beam001.png");

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
	m_player = new Player(m_collision, m_map);
	
	//プレイシーンに必要なObjectを読み込み、初期化する
	m_gameObjects.emplace_back(new Balloon());
	m_gameObjects.emplace_back(m_player);
	InitEnemy();
	m_gameObjects.emplace_back(new UI(m_player));
}

void ScenePlay::InitEnemy()
{
	m_enemyInfos = m_enemyLoad->LoadEnemyInfo("csv/EnemyLoad.csv");
	auto dataList = m_enemyLoad->LoadEnemyData("csv/stage1-1enemy.csv");
	//auto dataList = m_enemyLoad->LoadEnemyData("csv/stage1-1enemysample.csv"); デバッグ用

	for (auto& data : dataList)
	{

		switch (data.s_type_id)
		{
		case 0:
			
			m_enemy = new EnemySlim(data, m_enemyInfos[data.s_type_id], m_player,m_map,m_collision, m_camera);
			
			break;

		case 1:
			
			m_enemy = new EnemyPlant(data, m_enemyInfos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 2:
			
			m_enemy = new EnemyMasician(data, m_enemyInfos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 3:
			
			m_enemy = new EnemyFairy(data, m_enemyInfos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 4:
			
			m_enemy = new EnemyBird(data, m_enemyInfos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 5:
			
			m_enemy = new EnemyDoragon(data, m_enemyInfos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		default:
			
			continue;	//無効なIDの場合はスキップ
		}

		m_enemies.emplace_back(m_enemy);
		m_gameObjects.emplace_back(m_enemy);
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
	// エフェクトの持続時間を経過させる
	for (auto effect : m_effects)
	{
		effect->Update(delta_time);
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
	//DrawExtendGraph(400, 200,900,300, m_graph_hdl, TRUE);
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

void ScenePlay::CreateEffect()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z))
	{
		EffectPlayer* effect = new EffectPlayer(m_player, eEffectPlayerType::Beam);
		effect->SetPos(m_player->GetPos()); 
		effect->SetOffset(tnl::Vector3(400, 0, 0));
		effect->CalculateCollisionCircles();
		effect->SetIsMoved(true);
		m_gameObjects.emplace_back(effect);
		m_effects.emplace_back(effect);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X))
	{
		EffectPlayer* effect = new EffectPlayer(m_player, eEffectPlayerType::Fire);
		effect->SetPos(m_player->GetPos());
		effect->SetOffset(tnl::Vector3(200, 0, 0)); // ファイアの初期オフセット
		effect->SetIsMoved(true);
		m_gameObjects.emplace_back(effect);
		m_effects.emplace_back(effect);
	}
}

bool ScenePlay::SeqSceneIdle(float delta_time)
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
		if (enemy->GetIsDead())
		{
			continue; // 既に死んでいる敵に対する判定はスキップ
		}

		m_collision->CollisionCalculate(enemy, m_map, 10);
		m_collision->CollisionCharacter(m_player, enemy);

		for (auto effect : m_effects)
		{
			if (!effect->GetIsMoved())
			{
				continue; // 動いていないエフェクトの判定はスキップ
			}

			bool effectHitEnemy = false; // 当たり判定があったかどうかのフラグ

			// ここでeffect内の全ての円と敵との当たり判定をチェック
			for (auto circlePos : effect->GetCollisionCirclesPos())
			{
				if (wta::IsIntersectCircleCircle(circlePos, effect->GetSize(), enemy->GetPos(), enemy->GetSize()))
				{
					effectHitEnemy = true;
					break;
				}
			}

			// 1つ以上の円が敵にヒットした場合の処理
			if (effectHitEnemy)
			{
				enemy->SetIsDead(true);
				// 持続時間を超えるように設定
				//effect->elapsed_time = effect->duration + 1.0f;

				m_enemiesRemoveList.emplace_back(enemy);
				break;  // 敵は一度死んでしまったら、それ以上の当たり判定は不要なので、このエフェクトのループを抜ける
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

	// エフェクトの持続時間が経過したエフェクトを削除
	m_effects.remove_if([](EffectPlayer* effect) { return !effect->GetIsMoved(); });
}