#include "EnemyManager.h"
#include "EnemyLoad.h"
#include "MapManager.h"

EnemyManager::EnemyManager(MapManager* mapManager)
{
    m_enemy_load = new EnemyLoad(mapManager);
    CreateEnemies(m_enemy_load);
}

EnemyManager::~EnemyManager()
{
    Finalize();
    delete m_enemy_load;
}

void EnemyManager::CreateEnemies(const EnemyLoad* m_enemy_load)
{
    //EnemyLoadクラスで読み込んだデータを基にEnemyクラスを生成
    for (int i = 0; i < m_enemy_load->GetEnemyInfo().size(); i++)
    {
		m_enemies.emplace_back(new Enemy(m_enemy_load->GetEnemyInfo()[i]));
	}
}

void EnemyManager::Update(float delta_time)
{
    for (Enemy* enemy : m_enemies)
    {
        enemy->Update(delta_time);
    }
}

void EnemyManager::Draw(float delta_time, const Camera* camera)
{
    for (Enemy* enemy : m_enemies)
    {
        enemy->Draw(delta_time, camera);
    }
}

void EnemyManager::Finalize() 
{
    for (Enemy* enemy : m_enemies)
    {
        delete enemy;
    }
    m_enemies.clear();
}