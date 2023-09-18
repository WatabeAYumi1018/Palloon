#pragma once
#include "../../../../engine/GameEngine.h"
#include "../../Map/Map1.h"

class EnemyLoad
{

private:

    Map1* m_map = nullptr;

public:

    std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);
    std::list<sEnemyData> LoadEnemyData(const std::string& csvPath);
};
