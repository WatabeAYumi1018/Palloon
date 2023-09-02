#pragma once
#include "../SceneAll/GameObjectManager.h"
#include "Enemy.h"

class MapManager;
class EnemyLoad;

//Enemyを基にスポーン、更新など

class EnemyManager : public GameObjectManager 
{

public:
    EnemyManager(MapManager* mapManager);
	~EnemyManager();

private:
    std::vector<Enemy*> m_enemies;
    EnemyLoad *m_enemy_load=nullptr;

public:

    void Update(float delta_time) override;
    void Draw(float delta_time, const Camera* camera) override;
    void Finalize() override;
    
    void CreateEnemies(const EnemyLoad *m_enemy_load);
};


//class EnemyManager {
//private:
//    std::vector<Enemy*> enemies;
//
//public:
//    void loadEnemies(const std::string& dataFile) {
//        EnemyDataReader reader;
//        std::vector<EnemyInfo> enemyData = reader.readDataFromCSV(dataFile);
//
//        for (const EnemyInfo& info : enemyData) {
//            enemies.push_back(new Enemy(info));
//        }
//    }
//
//    void updateAllEnemies() {
//        for (Enemy* enemy : enemies) {
//            enemy->update();
//        }
//    }
//
//    void drawAllEnemies() {
//        for (Enemy* enemy : enemies) {
//            enemy->draw();
//        }
//    }
//
//    ~EnemyManager() {
//        for (Enemy* enemy : enemies) {
//            delete enemy;
//        }
//        enemies.clear();
//    }
//};
