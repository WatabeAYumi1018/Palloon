#pragma once
#include "../../engine/GameEngine.h"
#include "../SceneAll/GameObjectManager.h"
#include "EnemyManager.h"
#include "MapManager.h"

class EnemyLoad
{

private:

   MapManager *m_mapmanager=nullptr;

public:

    std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);
    std::vector<sEnemyData> LoadEnemyData(const std::string& csvPath);
};
