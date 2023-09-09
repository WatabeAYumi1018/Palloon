#pragma once
#include "../../../../engine/GameEngine.h"
#include "../../Map/Map.h"

class EnemyLoad
{

private:

    Map* m_map = nullptr;

public:

    std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);
    std::list<sEnemyData> LoadEnemyData(const std::string& csvPath);
};
