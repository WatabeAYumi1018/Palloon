#include "Collision.h"

//Collision::Collision(int width, int height):m_width(width),m_height(height){}
Collision::Collision(int radius) :m_radius(radius) {}

Collision::~Collision() { delete this; }

//★計算ミスのため、明日確認
bool Collision::CircleLine(const Vector3& circle_pos, float radius, float line_pos_start_x, float line_pos_end_x, float line_pos_start_y, float line_pos_end_y) {

	//Step 1: 円の中心と線分の最寄り点を求める
	//線分のベクトル
	float ABx = line_pos_end_x - line_pos_start_x;
	float ABy = line_pos_end_y - line_pos_start_y;
	//ABとAOの内積
	float AB_dot = (circle_pos.x - line_pos_start_x) * ABx + (circle_pos.y - line_pos_start_y) * ABy;
	//内積/線分の長さ
	float t = AB_dot / (ABx * ABx + ABy * ABy);
	t = fmax(0, fmin(1, t));

	// 線分の始点から最寄り点までのベクトルを求める
	float closestPoint_x = line_pos_start_x + t * ABx;
	float closestPoint_y = line_pos_start_y + t * ABy;

	//Step 2: 最寄り点が線分上にあるかどうか判定する
	//最寄り点と円の中心の距離の２乗を求める
	float distanceSquared = (closestPoint_x - circle_pos.x) * (closestPoint_x - circle_pos.x)
								+ (closestPoint_y - circle_pos.y) * (closestPoint_y - circle_pos.y);
	
	////円の半径の２乗と比較する（平方根での高コスト削減のため二乗で比較）
	//if (distanceSquared < radius * radius || t < 0 || t > 1 ) {return false;}

	////Step 3: 最寄り点と円の中心の距離を求める
	//float distance = distanceSquared;

	//Step 4: 距離が円の半径よりも小さいかどうかを判定する
	if(distanceSquared <= radius * radius) {return true;}

	else { return false; }
}

	////-----円の中心と線分の距離を求める-----//
	////①AOのベクトルを求める(zは0)
	//Vector3 AO = { circle_pos.x - line_pos_start_x,circle_pos.y - line_pos_start_y,0 };
	////②AOの大きさ（長さ）を求める
	//float AO_size = sqrt(AO.x * AO.x + AO.y * AO.y);
	////③AOの単位ベクトルを求める（正規化）
	//Vector3 AO_unit = { AO.x / AO_size,AO.y / AO_size,0 };

	////④ABのベクトルを求める
	//Vector3 AB = { line_pos_end_x - line_pos_start_x,line_pos_end_y - line_pos_start_y,0 };
	////⑤ABの大きさ（長さ）を求める
	//float AB_size = sqrt(AB.x * AB.x + AB.y * AB.y);
	////⑥ABの単位ベクトルを求める（正規化）
	//Vector3 AB_unit = { AB.x / AB_size,AB.y / AB_size,0 };

	////⑦AOとABの内積を求める
	//float AO_dot_AB = AO.x * AB_unit.x + AO.y * AB_unit.y;

	////⑧点Pの座標を求める
	//Vector3 P = { line_pos_start_x * AO_dot_AB, line_pos_start_y * AO_dot_AB ,0 };

	////⑨AOとAPの外積
	//float AO_cross_AP = AO.x * P.y - AO.y * P.x;
	//
	////OPの長さと円の半径を比較
	//if (AO_cross_AP <= radius) {
	//	return false;
	//}
	//else {
	//	return true;
	//}
//}

//キャラクター同士の当たり判定をチェック
//bool Collision::HitCheck(const Vector3& pos, const Object* other) {}
