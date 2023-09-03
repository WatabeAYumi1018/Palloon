//#pragma once
//#include "../SceneAll/GameObjectManager.h"
//#include "Enemy.h"
//
//class Camera;
//class EnemyLoad;
//class Collision;
//class MapManager;
//class Character;
//
////Enemyを基にスポーン、更新など
//
//class EnemyManager : public GameObjectManager 
//{
//public:
//
//    EnemyManager();
//	~EnemyManager();
//
//private:
//    EnemyLoad* m_enemyLoad=nullptr;
//
//    std::vector<Enemy*> m_enemies;
//    std::map<int, sEnemyInfo> m_enemyInfos;
//
//public:
//    void Initialize() override;
//    void Update(float delta_time) override;
//    void Draw(float delta_time, const Camera* camera) override;
//    void Finalize() override;
//};
//
//
////class EnemyManager {
////private:
////    std::vector<Enemy*> enemies;
////
////public:
////    void loadEnemies(const std::string& dataFile) {
////        EnemyDataReader reader;
////        std::vector<EnemyInfo> enemyData = reader.readDataFromCSV(dataFile);
////
////        for (const EnemyInfo& info : enemyData) {
////            enemies.push_back(new Enemy(info));
////        }
////    }
////
////    void updateAllEnemies() {
////        for (Enemy* enemy : enemies) {
////            enemy->update();
////        }
////    }
////
////    void drawAllEnemies() {
////        for (Enemy* enemy : enemies) {
////            enemy->draw();
////        }
////    }
////
////    ~EnemyManager() {
////        for (Enemy* enemy : enemies) {
////            delete enemy;
////        }
////        enemies.clear();
////    }
////};
