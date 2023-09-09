#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"

//スライムクラス

class EnemySlim :public Enemy
{
public:

	EnemySlim(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera);
	~EnemySlim();

private:

	TNL_CO_SEQUENCE(EnemySlim, &EnemySlim::SeqIdle);						//コルーチンシーケンス

public:
	
	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理

private:

	bool SeqIdle(const float delta_time) ;	
	bool SeqMove(const float delta_time) ;	
	bool SeqAttack(const float delta_time);
};

//idleだとスライム。attackだと植物になってる