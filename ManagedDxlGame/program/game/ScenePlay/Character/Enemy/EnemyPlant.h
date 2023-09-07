#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"

class Camera;
class Player;

//スライムクラス

class EnemyPlant :public Enemy
{
public:

	EnemyPlant(const sEnemyData& data, const sEnemyInfo& info,Player *player, Map* map, Collision* collision);
	~EnemyPlant();

private:

	TNL_CO_SEQUENCE(Enemy, &Enemy::SeqIdle);						//コルーチンシーケンス

public:

	void Update(const float delta_time) override;	//更新処理
	void Draw(const float delta_time, const Camera* camera) override;		//描画処理

private:

	bool SeqIdle(const float delta_time) override;	//基本行動（
	bool SeqAttack(const float delta_time) override;//攻撃処理(プレイヤーが一定以上近づくと攻撃)
};
