#pragma once
#include "../../engine/GameEngine.h"
#include "Player.h"


class Object;
class Player;

class Collision {

public:
	Collision(tnl::Vector3 pos,int radius);
	Collision(tnl::Vector3 pos,int width,int height);
	virtual ~Collision();

private:
	//-----メンバ変数-----//
	tnl::Vector3 m_pos;
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
	//キャラクター同士、エフェクトとの当たり判定（円同士）
	bool HitCheck(const tnl::Vector3& circle01, const Object* circle02) {}
	//キャラクターと床の当たり判定（円と矩形）
	bool HitCheckFloor(const tnl::Vector3& circle, const Object* box) {}
	//キャラクターと線分の当たり判定（円と線分）
	bool HitCircleLine(const tnl::Vector3& circle, const Object& line);

	//-----Setter,Getter-----//
	void SetWidth(int width) { m_width = width; }
	int GetWidth() { return m_width; }

	void SetHeight(int height) { m_height = height; }
	int GetHeight() { return m_height; }
};