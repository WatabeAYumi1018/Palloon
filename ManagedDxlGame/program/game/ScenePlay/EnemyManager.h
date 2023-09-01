#pragma once
#include "../../engine/GameEngine.h"
#include "../SceneAll/GameObjectManager.h"

class MapManager;
class Camera;
class Enemy;

//敵の読み取りを管理するクラス
class EnemyManager : public GameObjectManager
{

public:
	EnemyManager();
	~EnemyManager();

private:
	std::vector<std::vector<int>> m_enemy_csv;						//敵場所の読み取り用
	std::vector<sEnemyData> m_enemy_info;							//敵場所の情報格納用
	
	MapManager* m_mapmanager = nullptr;		//マップマネージャー
	Enemy* m_enemy = nullptr;				//敵キャラ

public:

	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override {}
	void Draw(float delta_time, const Camera* camera) override;
	
	void LoadEnemy();							//敵キャラ生成
};