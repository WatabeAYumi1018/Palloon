#pragma once
#include "../../engine/GameEngine.h"
#include "../SceneAll/GameObjectManager.h"
#include "EnemyManager.h"
#include "Map.h"

class EnemyLoad
{

private:

   Map *m_map=nullptr;

public:

    std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);
    std::vector<sEnemyData> LoadEnemyData(const std::string& csvPath);
};
