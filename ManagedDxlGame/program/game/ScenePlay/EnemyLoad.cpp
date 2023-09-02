#include "../../library/tnl_csv.h"
#include "EnemyLoad.h"
#include "Camera.h"
#include "MapManager.h"
#include "Enemy.h"


std::map<int, sEnemyInfo> EnemyLoad::LoadEnemyInfo(const std::string& file_path) 
{
    std::map<int, sEnemyInfo> enemyInfo;

    // 敵のパラメーターなどをCSVから読み込む
    auto data = tnl::LoadCsv(file_path);

    // 最初の0行目は読み取り不要のため削除
    if (!data.empty())
    {
        data.erase(data.begin());
    }
    
    for (const auto& row : data) 
    {
        sEnemyInfo info;
        info.s_id = row[0].getInt();
        info.s_name = row[1].getString();
        info.s_color = row[2].getString();
        info.s_hp = row[3].getInt();
        info.s_size = row[4].getInt();

        enemyInfo[info.s_id] = info;
    }
    return enemyInfo;
}

std::vector<sEnemyData> EnemyLoad::LoadEnemyData(const std::string& file_path)
{
    std::vector<sEnemyData> enemyData;

    // CSVを読み取る
    auto csvData = tnl::LoadCsv(file_path);

    // 二次元配列をループで回す
    for (int i= 0; i < csvData.size(); ++i) 
    {
        for (int j = 0; j < csvData[i].size(); ++j) 
        {
            // 0ではない場合、敵データとして保存
            if (csvData[i][j].getInt() != 0) 
            {
                sEnemyData data;

                //当たり判定の中心座標を計算
                int posX = j * m_mapmanager->MAP_CHIP_SIZE;
                int posY = i * m_mapmanager->MAP_CHIP_SIZE;

                data.s_pos = tnl::Vector3(posX, posY,0); 
                data.s_type_id = csvData[i][j].getInt();
                enemyData.emplace_back(data);
            }
        }
    }
    return enemyData;
}

//
//
//EnemyLoad::EnemyLoad(MapManager* m_mapManager):m_mapManager(m_mapManager)
//{
//     Initialize();
//}
//
//EnemyLoad::~EnemyLoad()
//{
//
//}
//
//void EnemyLoad::Initialize()
//{
//    //敵のスポーン位置をcsvから読み込む
//    m_enemy_csv = tnl::LoadCsv<int>("csv/stage1-1enemy.csv");
//    //std::map<int, sEnemyInfo> enemyInfoMap = tnl::LoadCsv<CsvCell>("csv/enemyInfo.csv");
//    LoadEnemy();
//}
//
////void EnemyLoad::Draw(float delta_time, const Camera* camera)
////{
////    for (auto& enemy : m_enemy_info)
////    {
////        //カメラの位置に合わせて描画位置をずらす
////        tnl::Vector3 draw_pos = enemy.s_pos - camera->GetTarget() +
////            tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
////
////        switch (enemy.s_type)
////        {
////        case eEnemyType::None:
////            break;
////        case eEnemyType::Slim:
////        
////            //DrawCircle(draw_pos.x, draw_pos.y, m_enemy->GetSize(), -1);
////        
////            break;
////    defalut:
////        break;
////        }
////    }
////}
//
////csvファイルから情報を読み取り、構造体と関連付け
//void EnemyLoad::LoadEnemy()
//{
//    //ファイル上の数値を全て読み込む
//    for (int i = 0; i < m_enemy_csv.size(); ++i)
//    {
//        for (int j = 0; j < m_enemy_csv[i].size(); ++j)
//        {
//            //ワールド座標に変換
//            float posX = j * m_mapManager->MAP_CHIP_SIZE;
//            float posY = i * m_mapManager->MAP_CHIP_SIZE;
//            //eEnemyTypeTypeと読み取った数字を関連付ける（同じ数字で連動しやすいように）
//            eEnemyType type = static_cast<eEnemyType>(m_enemy_csv[i][j]);
//            //当たり判定の情報を各マップチップに格納
//            sEnemyData data;
//            data.s_pos = tnl::Vector3(posX, posY, 0);
//            data.s_type = type;
//            m_enemy_info.emplace_back(data);
//        }
//    }
//}
//
//std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath) {
//    std::map<int, sEnemyInfo> infoMap;
//    auto csvData = tnl::LoadCsv(csvPath);
//
//    if (!csvData.empty()) {
//        csvData.erase(csvData.begin());
//    }
//
//    for (const auto& row : csvData) {
//        sEnemyInfo info;
//        info.s_name = row[1].getString();
//        info.s_color = row[2].getString();
//        info.s_hp = row[3].getInt();
//        info.s_size = row[4].getInt();
//        infoMap[row[0].getInt()] = info;
//    }
//    return infoMap;
//}
