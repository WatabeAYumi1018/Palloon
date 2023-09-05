#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"

class Camera;

//スライムクラス

class EnemyBird :public Enemy
{
public:
	
	EnemyBird(const sEnemyData& data, const sEnemyInfo& info, Player* player);
	~EnemyBird();

private:

	TNL_CO_SEQUENCE(Enemy, &Enemy::SeqMove);						//コルーチンシーケンス

public:

	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理

private:

	bool SeqMove(const float delta_time) override;	//基本行動01（通常）
	bool SeqAttack(const float delta_time) override;		//攻撃処理(プレイヤーが一定以上近づくと攻撃)
};