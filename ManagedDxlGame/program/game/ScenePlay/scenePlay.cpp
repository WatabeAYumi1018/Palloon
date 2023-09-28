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
#include "../ScenePlay/Effect/EffectBoss.h"
#include "../ScenePlay/Camera/Camera.h"
#include "../SceneSelect/SceneSelect.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "../SceneAll/BackGround.h"
#include "../SceneAll/ClearBalloon.h"
#include "../SceneAll/Balloon.h"
#include "../SceneAll/BalloonInstruction.h"
#include "../ScenePlay/Wind/Wind.h"
#include "../ScenePlay/Logo/Logo.h"
#include "../ScenePlay/Map/Map.h"
#include "../SceneAll/UI.h"
#include "ScenePlay.h"


ScenePlay::ScenePlay(const std::string& stageName) : m_stage_name(stageName)
{
	Initialize();
}

void ScenePlay::Initialize()
{
	m_camera=new Camera();
	m_collision = new Collision();
	m_backGround=new BackGround();
	m_balloonInstruction = new BalloonInstruction();
	m_clearBalloon = new ClearBalloon(m_collision);
	m_map = new Map(m_stage_name);
	m_wind = new Wind();
	m_logo = new Logo();

	m_backGround->SetBackground(m_map->GetCurrentStageInfo().s_background_hdl);
	
	tnl::Vector3 player_init_pos = m_map->GetCurrentStageInfo().s_initial_player_pos;	
	
	m_player = new Player(player_init_pos, m_collision, m_map, m_wind,m_logo);

	m_effectPlayer_beam = new EffectPlayer(m_player, eEffectPlayerType::Beam);
	m_effectPlayer_fire = new EffectPlayer(m_player, eEffectPlayerType::Fire);

	//プレイシーンに必要なObjectを読み込み、初期化する
	m_gameObjects.emplace_back(new Balloon());
	InitEnemy();
	m_gameObjects.emplace_back(m_player);
	m_gameObjects.emplace_back(m_effectPlayer_beam);
	m_gameObjects.emplace_back(m_effectPlayer_fire);
	m_gameObjects.emplace_back(m_clearBalloon);
	
	m_effectBoss = new EffectBoss(m_enemy,m_player);
	m_gameObjects.emplace_back(m_effectBoss);

	m_ui = new UI(m_player, m_enemy);	
	m_gameObjects.emplace_back(m_ui);
	m_gameObjects.emplace_back(m_logo);
}

void ScenePlay::InitMusic()
{
	// ステージ名からBGMのパスを取得
	std::string bgmPath = "";
	for (const auto& stageInfo : m_map->GetStageList())
	{
		if (stageInfo.s_stage_name == m_stage_name)
		{
			bgmPath = stageInfo.s_music_bgm;
			break;
		}
	}

	// BGMのロードと再生
	if (!bgmPath.empty())
	{
		MusicManager::GetInstance().LoadBGM(bgmPath);
		MusicManager::GetInstance().PlayBGM();
	}

	// SEのロード
	MusicManager::GetInstance().LoadSE("dead", "music/rollHit.mp3");
	MusicManager::GetInstance().LoadSE("fire", "music/playerFire.mp3");
	MusicManager::GetInstance().LoadSE("beam", "music/playerBeam.wav");
	MusicManager::GetInstance().LoadSE("enter", "music/pushStart.wav");
}

void ScenePlay::InitEnemy()
{
	m_enemy_infos = m_enemyLoad->LoadEnemyInfo("csv/EnemyLoad.csv");
	auto dataList = m_enemyLoad->LoadEnemyData(m_map->GetCurrentStageInfo().s_enemy_csv);

	for (auto& data : dataList)
	{
		switch (data.s_type_id)
		{
		case 0:
			
			m_enemy = new EnemySlim(data, m_enemy_infos[data.s_type_id], m_player,m_map,m_collision, m_camera);
			
			break;

		case 1:
			
			m_enemy = new EnemyPlant(data, m_enemy_infos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 2:
			
			m_enemy = new EnemyMasician(data, m_enemy_infos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 3:
			
			m_enemy = new EnemyFairy(data, m_enemy_infos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			if (m_stage_name == "stage3")
			{
				static_cast<EnemyFairy*>(m_enemy)->RandomType();
			}

			break;

		case 4:
			
			m_enemy = new EnemyBird(data, m_enemy_infos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
			break;

		case 5:
					
			m_enemy = new EnemyDoragon(data, m_enemy_infos[data.s_type_id], m_player, m_map, m_collision, m_camera);
			
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
	m_collision->CollisionCalculate(m_player, m_map, 10);
	m_camera->Update(delta_time, m_player, m_map);

	if (m_stage_name == "stage1")
	{
		m_clearBalloon->SetIsDraw(true);
		m_balloonInstruction->Update(delta_time);
	}
	
	m_map->LoadMapCollision();

	if (m_stage_name == "stage2")
	{
		m_clearBalloon->SetIsDraw(true);
		m_wind->Update(delta_time);
	}

	CollisionCheck(delta_time);

	if (m_stage_name == "stage3")
	{
		CreateEnemy(delta_time);

		if (m_total_respawns >= max_total_respawns)
		{
			m_clearBalloon->SetIsDraw(true);
		}
	}

	if (m_stage_name == "stageBoss")
	{
		CollisionCheckBoss();

		if (m_enemy->GetIsDead())
		{
			m_clearBalloon->SetIsDraw(true);
		}
	}

	RemoveAndDelete();

	CreateEffect();

	for (auto obj : m_gameObjects)
	{
		obj->Update(delta_time);
	}

	m_sequence.update(delta_time);
}

void ScenePlay::Draw(float delta_time)
{
	//m_backGround->Draw(delta_time, m_camera);
	
	if (m_stage_name == "stage1")
	{
		m_balloonInstruction->Draw(delta_time, m_camera);
	}
	
	if (m_stage_name == "stageBoss")
	{
		m_ui->SetIsDraw(true);
	}

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

	MusicManager::GetInstance().StopBGM();
}

void ScenePlay::CreateEffect()
{
	if (m_player->GetIsDraw())
	{
		if (!m_effectPlayer_beam->GetIsActive() &&
			(tnl::Input::IsKeyDownTrigger(eKeys::KB_C) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)))
		{
			m_is_effect = true;
			MusicManager::GetInstance().PlaySE("beam");

			m_effectPlayer_beam->SetIsActive(true);
			m_effectPlayer_beam->SetPos(m_player->GetPos());
			m_effectPlayer_beam->SetOffset(tnl::Vector3(400, 0, 0));
			m_effectPlayer_beam->CalculateCollisionCircles();
		}
		else if (!m_effectPlayer_fire->GetIsActive() &&
			(tnl::Input::IsKeyDownTrigger(eKeys::KB_X) || tnl::Input::IsPadDownTrigger(ePad::KEY_0)))
		{
			m_is_effect = true;
			MusicManager::GetInstance().PlaySE("fire");

			m_effectPlayer_fire->SetIsActive(true);
			m_effectPlayer_fire->SetPos(m_player->GetPos());
			m_effectPlayer_fire->SetOffset(tnl::Vector3(270, 0, 0));
			m_effectPlayer_fire->CalculateCollisionCircles();
		}
	}
}

void ScenePlay::CreateEnemy(float delta_time)
{
	auto it = m_enemies_respawn_list.begin();
	while (it != m_enemies_respawn_list.end())
	{
		Enemy* enemy = it->first;
		float& respawn_timer = it->second;

		respawn_timer += delta_time;

		if (respawn_timer > 3.0f)
		{
			if (m_total_respawns < max_total_respawns)  // 追加するチェック
			{
				const sEnemyData& respawn_data = enemy->GetEnemyData();
				m_enemy = new EnemyFairy(respawn_data, m_enemy_infos[respawn_data.s_type_id], m_player, m_map, m_collision, m_camera);
				static_cast<EnemyFairy*>(m_enemy)->RandomType();

				m_enemies.emplace_back(m_enemy);
				m_gameObjects.emplace_back(m_enemy);

				m_total_respawns++;  // 再生成回数を増やす
			}

			delete enemy;
			it = m_enemies_respawn_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool ScenePlay::SeqIdle(float delta_time)
{
	if (m_sequence.isStart())
	{
		InitMusic();
	}

	if (m_clearBalloon->GetIsChangeGraphic())
	{
		MusicManager::GetInstance().StopBGM();
		m_player->SetIsDraw(false);
		m_is_change_scene = true;
		m_logo->SetIsClear(true);
		m_logo->SetLogoState(eLogoState::Clear);
	}
	
	if((m_is_change_scene && (tnl::Input::IsKeyDown(eKeys::KB_RETURN) || tnl::Input::IsPadDown(ePad::KEY_1))) ||
		(m_player->GetIsDead() && (tnl::Input::IsKeyDown(eKeys::KB_RETURN) || tnl::Input::IsPadDown(ePad::KEY_1))))
	{
		MusicManager::GetInstance().PlaySE("enter");
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new SceneTitle());
	}
	return true;
}

void ScenePlay::CollisionCheckBoss()
{
	if (!m_enemy->GetIsActiveBoss()) return;

	// ボスのエフェクトの位置を取得
	tnl::Vector3 circlePosBoss = m_effectBoss->GetPos();
	
	if (wta::IsIntersectCircleCircle(m_effectBoss->GetPos(), m_effectBoss->GetSize(), m_player->GetPos(), m_player->GetSize()))
	{
		// 無敵状態でない場合に敵のHPを減少
		if (!m_player->GetIsInvincible())
		{
			MusicManager::GetInstance().PlaySE("damaged");
			m_player->DecreaseHP(1); // ここでHPを減少させる
			m_player->MakeInvincible(); // 一定時間無敵状態にする
		}
	}
}

void ScenePlay::CollisionCheck(float delta_time)
{
	for (auto enemy : m_enemies)
	{
		if (enemy->GetIsDead())
		{
			m_enemies_remove_list.emplace_back(enemy); // 既に死んでいる敵に対する判定はスキップ	
			
			if (m_stage_name == "stage3" && enemy->GetTypeID() == 3)
			{
				m_enemies_respawn_list.emplace_back(enemy,0.0f);
			}

			continue;
		}

		m_collision->CollisionCalculate(enemy, m_map, 10);
		m_collision->CollisionCharacter(m_player, enemy);
		
		for (auto effect : { m_effectPlayer_beam, m_effectPlayer_fire })
		{
			if (!effect->GetIsActive()) continue;

			bool effect_hit_enemy = false;

			for (auto circlePos : effect->GetCollisionCirclesPos())
			{
				if (wta::IsIntersectCircleCircle(circlePos, effect->GetSize(), enemy->GetPos(), enemy->GetSize()))
				{
					effect_hit_enemy = true;
					break;
				}
			}

			// 1つ以上の円が敵にヒットした場合の処理
			if (effect_hit_enemy)
			{
				// 無敵状態でない場合に敵のHPを減少
				if (!enemy->GetIsInvincible())
				{
					enemy->DecreaseHP(1); // ここでHPを減少させる
					enemy->MakeInvincible(); // 一定時間無敵状態にする
				}

				if (enemy->GetHp() <= 0)
				{
					MusicManager::GetInstance().PlaySE("dead");
					enemy->SetIsDead(true); // HPが0以下の場合、敵を死亡とする
				}

				break; //死んだらまたは無敵状態である場合は当たり判定不要
			}
		}
	}
}

void ScenePlay::RemoveAndDeleteEnemy(Enemy* enemy)
{
	m_gameObjects.remove(enemy);
	m_enemies.remove(enemy);
}

void ScenePlay::RemoveAndDelete()
{
	for (auto enemy : m_enemies_remove_list)
	{
		RemoveAndDeleteEnemy(enemy);
	}

	m_enemies_remove_list.clear();
}