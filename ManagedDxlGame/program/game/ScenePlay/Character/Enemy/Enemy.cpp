#include <random>
#include "Enemy.h"
#include "../../Map/Map.h"
#include "../../Collision/Collision.h"
#include "../../Camera/Camera.h"
#include "../Player/Player.h"


Enemy::Enemy(const sEnemyData& data, const sEnemyInfo& info)
    : Character(data.s_pos, info.s_size, info.s_hp, tnl::Vector3(100, 0, 0)),
    m_type_id(info.s_id), m_type(info.s_name), m_color(info.s_color)
{
    // CSVからアニメーションデータをロード
    animLoader = new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");
}

float Enemy::DistanceCalc()
{
    float distance = std::sqrt
    (
        //powは2乗（三平方の定理）
        std::pow(m_pos.x - m_player->GetPos().x, 2) +
        std::pow(m_pos.y - m_player->GetPos().y, 2)
    );
    return distance;
}
