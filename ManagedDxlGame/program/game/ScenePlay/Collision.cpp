#include "Collision.h"

//Collision::Collision(int width, int height):m_width(width),m_height(height){}
Collision::Collision(int radius) :m_radius(radius) {}

Collision::~Collision() { delete this; }

//★計算ミスのため、明日確認
bool Collision::CircleLine(const Vector3& circle_pos, float radius, int line_pos_start_x, int line_pos_end_x, int line_pos_start_y, int line_pos_end_y) {

	//-----円の中心と線分の距離を求める-----//
	//①ベクトルを求める（a,b）
	int a = circle_pos.x - line_pos_start_x;
	int b = circle_pos.y - line_pos_start_y;

	//②内積を求めるa・b
	int inner_x(line_pos_end_x - line_pos_start_x);
	int inner_y(line_pos_end_y - line_pos_start_y);

	//③内積をベクトルの大きさで割る
	float distance = abs((inner_x)+(inner_y)) / sqrt(a * a + b * b);

	//④ベクトルと中心座標の垂直接点座標を求める
	//(line_pos_start_x,line_pos_end_x)+(a,b)
	int contact_x = line_pos_start_x + distance * a;
	int contact_y = line_pos_start_y + distance * b;		//(contact_x,contact_y)

	//⑤円の半径と線分の距離を求める(contact_x,contact_y) - (circle_pos.x,circle_pos.y) x同士、y同士の計算
	float dis = (contact_x - circle_pos.x) * (contact_x - circle_pos.x) + (contact_y - circle_pos.y) * (contact_y - circle_pos.y);

	//円の半径と線分の距離を比較
	if (dis > radius) {
		return false;
	}
	return true;
}


//キャラクター同士の当たり判定をチェック
//bool Collision::HitCheck(const Vector3& pos, const Object* other) {}
