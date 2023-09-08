#pragma once
#include "../../../engine/GameEngine.h"

class Map;
class Character;
class Player;
class Enemy;

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

public:
	//-----メンバ関数-----//
	tnl::Vector3 GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map);

private:

	std::vector<sCollisionInfo> GetRowChips(int chip_x, int i, int range, const Map* map);

	bool IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips);

	std::vector<std::vector<sCollisionInfo>> GetSurroundingChips(Character* chara, Map* map, int range);

	void CheckBoxCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);

	void CheckLineCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips);

public:

	void CollisionCalculate(Character* chara, Map* map, int range);

	void CollisionCharacter(Player* player, Enemy* enemy);
};

//当たり判定の処理を行うクラス（計算式はnamespaceにて定義）
//現状Character型のみの対応
