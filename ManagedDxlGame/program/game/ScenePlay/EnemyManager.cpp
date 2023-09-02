#include "EnemyManager.h"
#include "EnemyLoad.h"
#include "MapManager.h"


EnemyManager::EnemyManager()
{
    m_enemyInfos = m_enemyLoad->LoadEnemyInfo("csv/EnemyLoad.csv");
   
    Initialize();
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

//EnemyManager::EnemyManager(MapManager* mapManager)
//{
//    m_enemy_load = new EnemyLoad(mapManager);
//    CreateEnemies(m_enemy_load);
//}
//
//EnemyManager::~EnemyManager()
//{
//    Finalize();
//    delete m_enemy_load;
//}
//
//void EnemyManager::CreateEnemies(const EnemyLoad* m_enemy_load)
//{
//    //EnemyLoadクラスで読み込んだデータを基にEnemyクラスを生成
//    for (int i = 0; i < m_enemy_load->GetEnemyInfo().size(); i++)
//    {
//		m_enemies.emplace_back(new Enemy(m_enemy_load->GetEnemyInfo()[i]));
//	}
//}
//
//void EnemyManager::Update(float delta_time)
//{
//    for (Enemy* enemy : m_enemies)
//    {
//        enemy->Update(delta_time);
//    }
//}
//
//void EnemyManager::Draw(float delta_time, const Camera* camera)
//{
//    for (Enemy* enemy : m_enemies)
//    {
//        enemy->Draw(delta_time, camera);
//    }
//}
//
//void EnemyManager::Finalize() 
//{
//    for (Enemy* enemy : m_enemies)
//    {
//        delete enemy;
//    }
//    m_enemies.clear();
//}