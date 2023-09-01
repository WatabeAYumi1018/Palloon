#include "EnemyManager.h"
#include "Camera.h"
#include "MapManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager() 
{
     Initialize();
}

EnemyManager::~EnemyManager()
{
	delete m_enemy;
}

void EnemyManager::Initialize()
{
    //敵のスポーン位置をcsvから読み込む
    m_enemy_csv = tnl::LoadCsv<int>("csv/TileStageEnemy1-1.csv");
    LoadEnemy();
}

void EnemyManager::Draw(float delta_time, const Camera* camera)
{
    for (auto& enemy : m_enemy_info)
    {
        //カメラの位置に合わせて描画位置をずらす
        tnl::Vector3 draw_pos = enemy.s_pos - camera->GetTarget() +
            tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

        switch (enemy.s_type)
        {
        case eEnemyType::None:
            break;
        case eEnemyType::Slim:
        
            //DrawCircle(draw_pos.x, draw_pos.y, m_enemy->GetSize(), -1);
        
            break;
    defalut:
        break;
        }
    }
}

//カメラに映っている間敵を生成する
void EnemyManager::LoadEnemy()
{
    //ファイル上の数値を全て読み込む
    for (int i = 0; i < m_enemy_csv.size(); ++i)
    {
        for (int j = 0; j < m_enemy_csv[i].size(); ++j)
        {
            //当たり判定の中心座標を計算
            int posX = j * m_mapmanager->MAP_CHIP_SIZE + (m_mapmanager->MAP_CHIP_SIZE >> 1);
            int posY = i * m_mapmanager->MAP_CHIP_SIZE + (m_mapmanager->MAP_CHIP_SIZE >> 1);
            //eEnemyTypeTypeと読み取った数字を関連付ける（同じ数字で連動しやすいように）
            eEnemyType type = static_cast<eEnemyType>(m_enemy_csv[i][j]);
            //当たり判定の情報を各マップチップに格納
            sEnemyData data;
            data.s_pos = tnl::Vector3(posX, posY, 0);
            data.s_type = type;
            m_enemy_info.emplace_back(data);
        }
    }
}
