#pragma once
#include "../../engine/GameEngine.h"

class MapManager;
class Character;

//当たり判定の識別と具体的処理を行うクラス
//実際の計算式についてはwta_IsIntersectCalcにて定義

class CollisionCalc
{
private:
	//-----メンバ変数-----//
	eCollisionType m_type = eCollisionType::None;

private:

	static std::vector<std::vector<sCollisionInfo>> GetSurroundingChips(Character *chara, MapManager*mapChip, int range);

public:
	static void CheckBoxCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);

	static void CheckLineCollision(Character *character, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);
	
	static void CollisionCalculate(Character *character, MapManager*mapChip,int range);
};

//当たり判定の処理を行うクラス（計算式はnamespaceにて定義）
//現状Character型のみの対応
