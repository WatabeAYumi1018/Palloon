#pragma once
#include "../../engine/GameEngine.h"

class MapChip;
class Character;

class CollisionCalc {

public:
	CollisionCalc() {}
	~CollisionCalc() {}

private:
	//-----メンバ変数-----//
	eCollisionType m_type = eCollisionType::eCollision_None;

private:

	static std::vector<tnl::Vector3> GetSurroundingChips(Character* chara, MapChip* mapChip, int range);

	static eCollisionType GetCollisionTypeMap(Character* character, MapChip* mapChip);

	static void CheckBoxCollision(Character* character, MapChip* mapChip,int range);

	static void CheckLineCollision(Character* character, MapChip* mapChip, int range);

public:

	static void CollisionCalculate(Character* character, MapChip* mapChip,int range);
};

//当たり判定の処理を行うクラス（計算式はnamespaceにて定義）
//現状Character型のみの対応
