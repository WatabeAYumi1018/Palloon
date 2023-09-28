#include "../../Camera/Camera.h"
#include "EnemyDoragon.h"
#include "../Player/Player.h"

EnemyDoragon::EnemyDoragon(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera) :
    Enemy(data, info, player, map, collision, camera)
{
    m_is_direction_right = false;
}

EnemyDoragon::~EnemyDoragon()
{

}

void EnemyDoragon::Update(float delta_time)
{
    if (m_player)
    {
        tnl_sequence_.update(delta_time);
    }

    Invincible(delta_time);
}

void EnemyDoragon::Draw(float delta_time, const Camera* camera)
{
    //無敵中は点滅描画
    if (m_is_invincible)
    {
        // 0.1秒ごとに表示・非表示を切り替えて点滅
        if (static_cast<int>(m_invincible_time * 10) % 2 == 0)
        {
            animLoader->Draw(delta_time, m_pos);
        }
    }
    else
    {
        animLoader->Draw(delta_time, m_pos);
    }
}

//常に左向き
//Moveのみ右に戻ることも
//プレイヤーとの距離が近ければ火炎放射、離れていれば火の玉
//離れているとプレイヤーの方向へ進む（火の玉と突進は確率で二分）
bool EnemyDoragon::SeqIdle(float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
    {
        if (!m_is_direction_right)
        {
            animLoader->SetAnimation(60);
        }
    });

    float distance_x = m_pos.x - m_player->GetPos().x;
    float distance_y = m_pos.y - m_player->GetPos().y;

    //プレイヤーとの距離が遠ければ火の玉か突進
    if (std::abs(distance_x) > 700 && std::abs(distance_y) > 700)
    {
        tnl_sequence_.change(&EnemyDoragon::SeqFireBall);

        TNL_SEQ_CO_END;
    }

    if (std::abs(distance_x) <= 700 && std::abs(distance_y) <= 700)
    {
        tnl_sequence_.change(&EnemyDoragon::SeqFlame);

        TNL_SEQ_CO_END;
    }

    TNL_SEQ_CO_END;
}

bool EnemyDoragon::SeqFireBall(float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
    {
        m_is_fireball = true;
        m_is_active_boss = true;

        animLoader->SetAnimation(62);
    });

    tnl_sequence_.change(&EnemyDoragon::SeqIdle);

    TNL_SEQ_CO_END;
}

bool EnemyDoragon::SeqFlame(float delta_time)
{
    TNL_SEQ_CO_TIM_YIELD_RETURN(3, delta_time, [&]()
    {
        m_is_flame= true;
        m_is_active_boss = true;

        animLoader->SetAnimation(62);
    });

    tnl_sequence_.change(&EnemyDoragon::SeqIdle);

    TNL_SEQ_CO_END;
}

//bool EnemyDoragon::SeqMove(float delta_time)
//{
//    float distance_x = m_pos.x - m_player->GetPos().x;
//    float distance_y = m_pos.y - m_player->GetPos().y;
//
//    if (std::abs(distance_x) > 200 && std::abs(distance_y) > 200)
//    {
//        tnl_sequence_.change(&EnemyDoragon::SeqFireBall);
//
//        TNL_SEQ_CO_END;
//    }
//
//    if (std::abs(distance_x) < 200 && std::abs(distance_y) < 200)
//    {
//		tnl_sequence_.change(&EnemyDoragon::SeqFire);
//
//		TNL_SEQ_CO_END;
//	}
//
//    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
//    {
//        animLoader->SetAnimation(61);
//        m_pos.x -= m_velocity.x * delta_time;
//    });
//
//    tnl_sequence_.change(&EnemyDoragon::SeqIdle);
//
//    TNL_SEQ_CO_END;
//}