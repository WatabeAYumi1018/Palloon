#pragma once
#include "../../engine/GameEngine.h"

class MapManager;
class Character;

//当たり判定の識別と具体的処理を行うクラス
//実際の計算式についてはwta_IsIntersectCalcにて定義

class Collision
{

public:
	Collision();
	~Collision() {}

private:
	//-----メンバ変数-----//
	tnl::Vector3 m_lastCharaPos;							/*前回取得したキャラクターの座標*/
	std::vector<std::vector<sCollisionInfo>> m_cachedChips; /*前回取得した当たり判定情報*/
	
	//-----メンバ関数-----//
	tnl::Vector3 GetCharacterMapChipPos(const tnl::Vector3& charaPos, const MapManager* mapChip) ;

	std::vector<sCollisionInfo> GetRowChips(int chip_x, int i, int range, const MapManager* mapChip) ;

	bool IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips) ;

	std::vector<std::vector<sCollisionInfo>> GetSurroundingChips(Character *chara, MapManager*mapChip, int range);

	void CheckBoxCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);

	void CheckLineCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);

public:

	void CollisionCalculate(Character *chara, MapManager*mapChip,int range);
};

//当たり判定の処理を行うクラス（計算式はnamespaceにて定義）
//現状Character型のみの対応
