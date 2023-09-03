#include "EnemyManager.h"
#include "EnemyLoad.h"
#include "Collision.h"
#include "MapManager.h"
#include "Character.h"

EnemyManager::EnemyManager()
{
    m_enemyInfos = m_enemyLoad->LoadEnemyInfo("csv/EnemyLoad.csv");
   
    Initialize();
}

EnemyManager::~EnemyManager()
{
	Finalize();
}

void EnemyManager::Initialize()  
{
    auto dataList = m_enemyLoad->LoadEnemyData("csv/stage1-1enemy.csv");
    
    for (const auto& data : dataList)
    {
        m_enemies.emplace_back(new Enemy(data, m_enemyInfos[data.s_type_id]));
    }
}

void EnemyManager::Update(float delta_time)
{

    for (auto& enemy : m_enemies) 
    {
        enemy->Update(delta_time);
    }
}

void EnemyManager::Draw(float delta_time, const Camera* camera)
{
    for (const auto& enemy : m_enemies)
    {
        enemy->Draw(delta_time, camera);
    }
}

void EnemyManager::Finalize()
{
    m_enemies.clear();
}
