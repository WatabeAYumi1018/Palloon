#pragma once
#include <random>
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

//主に敵のAIを管理するクラス

class Camera;
class Player;
class Map;
class Collision;

class Enemy :public Character
{

public:

	Enemy(const sEnemyData& data, const sEnemyInfo& info,Player* player,Map *map,Collision *coiision);
	virtual ~Enemy() {}

protected:

	//-----メンバ変数-----//
	int m_type_id;											/*敵のタイプID*/
	std::string m_type;										/*敵のタイプ*/
	std::string m_color;									/*敵の色*/
	bool m_is_dirction_right = true;						/*右向き*/

	float m_moveTimeCounter = 0.0f;

	std::default_random_engine m_generator;								//ジェネレーター（乱数分布と組み合わせて生成）
	std::uniform_real_distribution<float> m_distribution{ 0.0f, 1.0f };	//乱数調節（idle→move）

	Player* m_player = nullptr;		
	Map * m_map = nullptr;
	Collision * m_collision = nullptr;

	//-----メンバ関数-----//
	float DistanceCalc();						//プレイヤーとの距離計算
	
public:
	virtual void Update(const float delta_time)  {}	//更新処理
	virtual void Draw(const float delta_time, const Camera* camera)  {}		//描画処理

	virtual bool SeqMove(const float delta_time) { return 0; }	//基本行動01（通常）
	virtual bool SeqIdle(const float delta_time) { return 0; }	//基本行動02（通常～遷移がある場合のみ使用）
	virtual bool SeqAttack(const float delta_time) { return 0; }		//攻撃処理(プレイヤーが一定以上近づくと攻撃)
};
