#include <random>
#include "Enemy.h"
#include "../../Map/Map.h"
#include "../../Collision/Collision.h"
#include "../../Camera/Camera.h"
#include "../Player/Player.h"
#include "../../Camera/Camera.h"

Enemy::Enemy(const sEnemyData& data, const sEnemyInfo& info,Player* player,Map* map, Collision* collision, Camera* camera)
         : Character(data.s_pos, info.s_size, info.s_hp, tnl::Vector3(100, 0, 0)),
             m_player(player), m_map(map), m_collision(collision),m_camera(camera)
{
    m_type_id = info.s_id;
    m_type = info.s_name;
    m_color = info.s_color;
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

//矩形ならば進行可能とする
bool Enemy::CanMoveRight()
{
    tnl::Vector3 forwardPos = m_pos + tnl::Vector3(32, 40, 0);
    tnl::Vector3 chipPos = m_collision->GetCharacterMapChipPos(forwardPos, m_map);
    sCollisionInfo forwardCollision = m_map->GetCollisionInfo()[chipPos.y][chipPos.x];
    DrawBoxEx(forwardPos, 30, 30, true);

    return forwardCollision.s_type == eMapCollisionType::Box;
}

bool Enemy::CanMoveLeft()
{
    tnl::Vector3 backwardPos = m_pos - tnl::Vector3(32, -40, 0);
    tnl::Vector3 chipPos = m_collision->GetCharacterMapChipPos(backwardPos, m_map);
    sCollisionInfo backwardCollision = m_map->GetCollisionInfo()[chipPos.y][chipPos.x];
    DrawBoxEx (backwardPos,30,30,true);
    
    return backwardCollision.s_type == eMapCollisionType::Box;
}
