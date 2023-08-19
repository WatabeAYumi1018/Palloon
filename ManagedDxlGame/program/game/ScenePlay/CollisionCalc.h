#pragma once
#include "../../engine/GameEngine.h"

class MapChip;
class Character;

class CollisionCalc {

public:
	CollisionCalc();
	CollisionCalc(eCollisionType type);
	virtual ~CollisionCalc();

private:
	//-----メンバ変数-----//
	eCollisionType m_type = eCollisionType::eCollision_None;

//public:
	//static tnl::Vector3 HandlePlayerMapCollision(Character* player, MapChip* mapChip);

private:
	//static void CheckCollisionByType(const tnl::Vector3& playerPos, float playerRadius, MapChip* mapChip, int i, int j);

	static eCollisionType GetCollisionTypeMap(Character& character, MapChip& mapChip);

	static void CheckBoxCollision(Character& character, MapChip& mapChip);

	static void CheckLineCollision(Character& character, MapChip& mapChip);

public:

	static void Calculate(Character& character, MapChip& mapChip);


	//-----メンバ関数-----//
	////キャラクターと地形(eCollisionType)との当たり判定（円と矩形）
	////座標を返すからtnl::Vector3にすべきかも
	//tnl::Vector3 HitMapBoxCheck(eCollisionType type,Character *chara);

	////キャラクターと地形(eCollisionType)との当たり判定（円と線分）
	////HitMapBoxCheck==trueの場合のみ、HitMapLineCheckを呼び出す
	//tnl::Vector3 HitMapLineCheck(eCollisionType type, Character *chara);

	////円と矩形の当たり判定計算
	//bool IsIntersectCircleBox(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& box, const int boxSize);

	////円と線分の当たり判定計算
	//bool IsIntersectCircleLine(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);

	////円同士の当たり判定計算
	//bool IsIntersectCircleCircle(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02);
};