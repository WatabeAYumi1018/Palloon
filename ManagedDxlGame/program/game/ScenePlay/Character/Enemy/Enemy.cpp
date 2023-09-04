#include <random>
#include "Enemy.h"
#include "../../Map/Map.h"
#include "../../Collision/Collision.h"
#include "../../Camera/Camera.h"
#include "../Player/Player.h"


Enemy::Enemy(const sEnemyData& data, const sEnemyInfo& info,Player* player)
    : Character(data.s_pos, info.s_size, info.s_hp, tnl::Vector3(100, 0, 0)),
    m_type_id(info.s_id), m_type(info.s_name), m_color(info.s_color), m_player(player)
{
}

float Enemy::DistanceCalc()
{
    float distance = std::sqrt
    (
        //pow‚Í2æiŽO•½•û‚Ì’è—j
        std::pow(m_pos.x - m_player->GetPos().x, 2) +
        std::pow(m_pos.y - m_player->GetPos().y, 2)
    );
    return distance;
}
