#include "Collision.h"

//Collision::Collision(int width, int height):m_width(width),m_height(height){}
Collision::Collision(int radius) :m_radius(radius) {}

Collision::~Collision() { delete this; }

//★出来てるはずなのになんか違うらしい
// 線分と円の当たり判定
bool Collision::CircleLine(const Vector3& circle_pos, float radius,float line_pos_start_x,
                            float line_pos_end_x,float line_pos_start_y, float line_pos_end_y) 
{
    // 線分の始点と終点のベクトル
    Vector3 line_vec = { line_pos_end_x - line_pos_start_x, line_pos_end_y - line_pos_start_y, 0 };
    // 線分の始点から円の中心までのベクトル
    Vector3 circle_vec = { circle_pos.x - line_pos_start_x, circle_pos.y - line_pos_start_y, 0 };

    // 線分の長さの2乗
    float line_length_pow = line_vec.x * line_vec.x + line_vec.y * line_vec.y;
    // 線分の始点から円の中心までの距離（線分の向きを考慮した内積）
    float dot_product = line_vec.x * circle_vec.x + line_vec.y * circle_vec.y;

    // 線分上の交点を計算
    float t = dot_product / line_length_pow;
    // 交点が線分上に存在するかを判定
    bool point_on_segment = (t >= 0 && t <= 1.0f);

    if (point_on_segment) {
        // 交点から円の中心までの距離を計算
        Vector3 intersection_point = { line_pos_start_x + t * line_vec.x, line_pos_start_y + t * line_vec.y, 0 };
        float distance_squared = (intersection_point.x - circle_pos.x) * (intersection_point.x - circle_pos.x) +
            (intersection_point.y - circle_pos.y) * (intersection_point.y - circle_pos.y);

        // 距離が円の半径以下かを判定
        float radius_squared = radius * radius;
        if (distance_squared <= radius_squared) {
            return true; // 当たり
        }
    }
    return false; // 当たりなし
}



//キャラクター同士の当たり判定をチェック
//bool Collision::HitCheck(const Vector3& pos, const Object* other) {}
