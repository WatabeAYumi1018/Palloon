#pragma once
#include "../../engine/GameEngine.h"

class Object;

class Collision {

public:
	Collision(int width,int height);
	virtual ~Collision();

	//-----矩形当たり判定-----//
private:
	int m_width = 0;
	int m_height = 0;

	//-----メンバ関数-----//
public:
	//キャラクター同士の当たり判定をチェック
	bool HitCheck(const Vector3& pos,const Object* other);

	//-----Setter,Getter-----//
public:
	void SetWidth(int width) { m_width = width; }
	int GetWidth() { return m_width; }

	void SetHeight(int height) { m_height = height; }
	int GetHeight() { return m_height; }
};