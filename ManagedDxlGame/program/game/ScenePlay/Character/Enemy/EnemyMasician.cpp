#include "../../Camera/Camera.h"
#include "EnemyMasician.h"
#include "../Player/Player.h"

EnemyMasician::EnemyMasician(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera) :
    Enemy(data, info, player, map, collision, camera)
{

}

EnemyMasician::~EnemyMasician()
{

}

void EnemyMasician::Update(float delta_time)
{
    //ちょっと浮かばせたい
    tnl_sequence_.update(delta_time);
}

void EnemyMasician::Draw(float delta_time, const Camera* camera)
{
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
        tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    animLoader->Draw(delta_time, draw_pos);
}

bool EnemyMasician::SeqIdle(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    //プレイヤーとの距離計算
    if (std::abs(distance_x) < 200)
    {
        tnl_sequence_.change(&EnemyMasician::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //初期値trueのため最初は右向きから
        if (m_is_direction_right)
        {
            animLoader->SetAnimation(28);
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //初期値trueのため最初は右向きから
        if (!m_is_direction_right)
        {
            animLoader->SetAnimation(29);
        }
    });

    tnl_sequence_.change(&EnemyMasician::SeqMove);
    TNL_SEQ_CO_END;
}

bool EnemyMasician::SeqMove(float delta_time)
{
    if (m_player)
    {
        float distance_x = m_pos.x - m_player->GetPos().x;

        if (std::abs(distance_x) < 200)
        {
            tnl_sequence_.change(&EnemyMasician::SeqAttack);
        }

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            animLoader->SetAnimation(30);
            m_pos.x += m_velocity.x * delta_time;
            m_is_direction_right = true;
        });

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            animLoader->SetAnimation(31);
            m_pos.x -= m_velocity.x * delta_time;
            m_is_direction_right = false;
        });

        tnl_sequence_.change(&EnemyMasician::SeqIdle);

        TNL_SEQ_CO_END;
    }
}
bool EnemyMasician::SeqAttack(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_player)
        {
            if (distance_x < 0)
            {
                animLoader->SetAnimation(32);
                m_pos.x += m_velocity.x * delta_time;
                m_is_direction_right = true;
            }
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_player)
        {
            if (distance_x > 0)
            {
                animLoader->SetAnimation(33);
                m_pos.x -= m_velocity.x * delta_time;
                m_is_direction_right = false;
            }
        }
    });

    tnl_sequence_.change(&EnemyMasician::SeqMove);
    TNL_SEQ_CO_END;
}
