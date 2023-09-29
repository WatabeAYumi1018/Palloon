#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


//ボスクラス

class EnemyDoragon :public Enemy
{
public:
	
	EnemyDoragon(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera);
	~EnemyDoragon();

private:

	TNL_CO_SEQUENCE(EnemyDoragon, &EnemyDoragon::SeqIdle);						//コルーチンシーケンス

	//-----メンバ関数-----//
	bool SeqIdle(const float delta_time);
	bool SeqFireBall(const float delta_time);
	bool SeqFlame(const float delta_time);

public:
	
	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理
};