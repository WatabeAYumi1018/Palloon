#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"

//妖精クラス

class EnemyFairy :public Enemy
{
public:

	enum sFairyType
	{
		Peach,
		Blue,
		Yellow
	};

	EnemyFairy(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera);
	~EnemyFairy();

private:

	sFairyType s_type= Peach;		//タイプ

	TNL_CO_SEQUENCE(EnemyFairy, &EnemyFairy::SeqIdle);						//コルーチンシーケンス

public:
	
	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理

	void RandomType();		//ランダムでタイプ決定

	bool SeqIdle(const float delta_time);
	bool SeqMove(const float delta_time);
	bool SeqAttack(const float delta_time);
};
