#pragma once
#include "../../engine/GameEngine.h"
#include "../SceneAll/GameObjectManager.h"

class MapManager;
class Camera;
class Enemy;

//“G‚Ì“Ç‚İæ‚è‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class EnemyLoad 
{

public:
	EnemyLoad(MapManager* m_mapManager);
	~EnemyLoad();

private:
	
	std::vector<std::vector<int>> m_enemy_csv;			/*“GêŠ‚Ì“Ç‚İæ‚è—p*/
	std::vector<sEnemyData> m_enemy_info;				/*“GêŠ‚Ìî•ñŠi”[—p*/	

    std::map<int, sEnemyInfo> enemyInfoMap;			/*ID*/


	MapManager* m_mapManager = nullptr;

public:

	//-----ƒƒ“ƒoŠÖ”-----//
	void Initialize() ;
	void Update(float delta_time)  {}
	void LoadEnemy();
	const std::vector<sEnemyData>& GetEnemyData() const;
    //std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);
	
	//-----Getter&Setter-----//
	const std::vector<sEnemyData>& GetEnemyInfo() const { return m_enemy_info; }
};
	//void Draw(float delta_time, const Camera* camera) override;
