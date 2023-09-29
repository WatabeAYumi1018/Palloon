#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"

//植物クラス

class EnemyPlant :public Enemy
{
public:

	EnemyPlant(const sEnemyData& data, const sEnemyInfo& info,Player *player, Map* map, Collision* collision, Camera* camera);
	~EnemyPlant();

private:

	TNL_CO_SEQUENCE(EnemyPlant, &EnemyPlant::SeqIdle);						//コルーチンシーケンス

public:

	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理

private:

	bool SeqIdle(const float delta_time);	
	bool SeqAttack(const float delta_time);
};
