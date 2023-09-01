#pragma once
#include "../../engine/GameEngine.h"

class MapManager;
class Character;

//当たり判定の識別と具体的処理を行うクラス
//実際の計算式についてはwta_IsIntersectCalcにて定義

class CollisionCalc
{
public:
	CollisionCalc() {}
	virtual ~CollisionCalc() {}

	//-----メンバ関数-----//
	 static void CollisionCalculate(Character *chara, MapManager*mapChip,int range);

private:

	static std::vector<std::vector<sCollisionInfo>> GetSurroundingChips(Character *chara, MapManager*mapChip, int range);

	static void CheckBoxCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);

	static void CheckLineCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);
	
};

//当たり判定の処理を行うクラス（計算式はnamespaceにて定義）
//現状Character型のみの対応
