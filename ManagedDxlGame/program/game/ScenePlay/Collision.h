#pragma once
#include "../../engine/GameEngine.h"

class Object;

class Collision {

public:
	Collision(int radius);
	//Collision(int width,int height);
	virtual ~Collision();

private:
	//-----矩形当たり判定-----//
	int m_width = 0;
	int m_height = 0;

	int m_radius = 0;//試しに追加

public:
	//-----メンバ関数-----//
	//キャラクター同士の当たり判定をチェック
	bool HitCheck(const Vector3& pos, const Object* other) {}
	//キャラクターと床の当たり判定をチェック
	bool HitCheckFloor(const Vector3& pos, const Object* other) {}
	//円と線分との当たり判定
	bool CircleLine(const Vector3& circle_pos, float radius, float line_pos_start_x, float line_pos_end_x, float line_pos_start_y, float line_pos_end_y);


	//-----Setter,Getter-----//
	void SetWidth(int width) { m_width = width; }
	int GetWidth() { return m_width; }

	void SetHeight(int height) { m_height = height; }
	int GetHeight() { return m_height; }
};