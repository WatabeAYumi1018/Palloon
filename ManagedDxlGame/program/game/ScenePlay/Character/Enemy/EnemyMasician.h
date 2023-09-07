#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"

class Camera;
class Player;

//スライムクラス

class EnemyMasician :public Enemy
{
public:

	EnemyMasician(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision);
	~EnemyMasician();

private:

	TNL_CO_SEQUENCE(Enemy, &Enemy::SeqMove);						//コルーチンシーケンス

public:

	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理

private:

	bool SeqMove(const float delta_time) override;	//基本行動01（通常）
	bool SeqIdle(const float delta_time) override;	//基本行動02（通常〜遷移がある場合のみ使用）
	bool SeqAttack(const float delta_time) override;		//攻撃処理(プレイヤーが一定以上近づくと攻撃)
};
