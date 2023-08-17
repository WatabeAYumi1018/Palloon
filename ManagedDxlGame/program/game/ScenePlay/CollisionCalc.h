#pragma once
#include "../../engine/GameEngine.h"


class Character;

class CollisionCalc {

public:
	CollisionCalc();
	CollisionCalc(eCollisionType type);
	virtual ~CollisionCalc();

private:
	//-----メンバ変数-----//
	tnl::Vector3 m_pos;
	eCollisionType m_type = eCollisionType::eCollision_None;
	//-----矩形当たり判定-----//
	int m_width = 0;
	int m_height = 0;
	//-----円当たり判定-----//
	int m_radius = 0;
	//-----線分当たり判定-----//
	int m_lineStart = 0;
	int m_lineEnd = 0;

public:
	//-----メンバ関数-----//
	//キャラクターと地形(eCollisionType)との当たり判定（円と矩形）
	//座標を返すからtnl::Vector3にすべきかも
	tnl::Vector3 HitMapBoxCheck(eCollisionType type,Character *chara);

	//キャラクターと地形(eCollisionType)との当たり判定（円と線分）
	//HitMapBoxCheck==trueの場合のみ、HitMapLineCheckを呼び出す
	tnl::Vector3 HitMapLineCheck(eCollisionType type, Character *chara);

	//円と矩形の当たり判定計算
	bool IsIntersectCircleBox(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& box, const int boxSize);

	//円と線分の当たり判定計算
	bool IsIntersectCircleLine(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);

	//円同士の当たり判定計算
	bool IsIntersectCircleCircle(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02);
	
	//-----Setter,Getter-----//
	void SetWidth(int width) { m_width = width; }
	int GetWidth() { return m_width; }
	void SetHeight(int height) { m_height = height; }
	int GetHeight() { return m_height; }
};