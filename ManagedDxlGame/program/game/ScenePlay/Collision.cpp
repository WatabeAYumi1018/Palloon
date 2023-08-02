#include "Collision.h"


Collision::Collision(Vector3 pos,int radius):m_pos(pos),m_radius(radius){}



Collision::~Collision() { delete this; }

// 線分と円の当たり判定
//bool Collision::HitCircleLine(const Player& circle, const Object& line) {
//   
//    // 線分の始点と終点のベクトル
//    Vector3 line_vec = line.m_end - line.m_start;
//    // 線分の始点から円の中心までのベクトル
//    Vector3 circle_vec = circle.m_pos - line.m_start;
//
//    // 線分の長さの2乗
//    float line_length_pow = line_vec.x * line_vec.x + line_vec.y * line_vec.y;
//    // 線分の始点から円の中心までの距離（線分の向きを考慮した内積）
//    float dot_product = line_vec.x * circle_vec.x + line_vec.y * circle_vec.y;
//
//    // 線分上の交点を計算
//    float t = dot_product / line_length_pow;
//
//	// tが0~1の間にある場合：線分上に交点が存在する
//    if (t >= 0 && t <= 1.0f) {
//        // 交点から円の中心までの距離を計算
//        Vector3 intersection_point = line.m_start + t * line_vec;
//        // 距離の2乗を計算
//        float distance_squared = (intersection_point.x - circle.m_pos.x) * (intersection_point.x - circle.m_pos.x) +
//            (intersection_point.y - circle.m_pos.y) * (intersection_point.y - circle.m_pos.y);
//        //円の半径の2乗
//        float radius_squared = m_radius * m_radius;
//        // 距離が円の半径以下かを判定
//        if (distance_squared <= radius_squared) {return true;}
//    }
//
//	//tが0~1の外：線分両端の点と円の当たり判定をチェック
//    else {
//        // 線分の始点と円の中心の距離の2乗
//        Vector3 distance1 = line.m_start - circle.m_pos;
//        // 線分の終点と円の中心の距離の2乗
//        Vector3 distance2 = { line.m_end - circle.m_pos;
//        //円の半径の2乗
//        float radius_squared = m_radius * m_radius;
//        //それぞれの長さを計算
//        float distance1_squared = distance1.x * distance1.x + distance1.y * distance1.y;
//        float distance2_squared = distance2.x * distance2.x + distance2.y * distance2.y;
//        // 距離が円の半径以下かを判定
//        if (distance1_squared <= radius_squared || distance2_squared <= radius_squared) { return true; }
//    }
//    return false;
//}

//キャラクター同士の当たり判定をチェック
//bool Collision::HitCheck(const Vector3& pos, const Object* other) {}
