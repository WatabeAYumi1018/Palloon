#include "../../Camera/Camera.h"
#include "EnemySlim.h"
#include "../Player/Player.h"

EnemySlim::EnemySlim(const sEnemyData& data, const sEnemyInfo& info,Player* player, Map* map, Collision* collision, Camera* camera) :
    Enemy(data, info, player,map,collision,camera)
{
    
}

EnemySlim::~EnemySlim() 
{

}

void EnemySlim::Update(float delta_time)
{
    if (m_is_active)
    {
        //重力で下に落ちる
        m_pos.y += (m_gravity.y * delta_time);

        tnl_sequence_.update(delta_time);
    }
}

void EnemySlim::Draw(float delta_time, const Camera* camera)
{
    if (m_is_active)
    {
        //カメラの位置に合わせて描画位置をずらす
        tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
            tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

        animLoader->Draw(delta_time, draw_pos);
    }
}

bool EnemySlim::SeqIdle(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    //プレイヤーとの距離計算
    if (std::abs(distance_x) < 100)
    {
        tnl_sequence_.change(&EnemySlim::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //初期値trueのため最初は右向きから
        if (m_is_direction_right)
        {
           animLoader->SetAnimation(18);
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //初期値trueのため最初は右向きから
        if (!m_is_direction_right)
        {
            animLoader->SetAnimation(18);
        }
    });

    tnl_sequence_.change(&EnemySlim::SeqMove);
    TNL_SEQ_CO_END;
}

bool EnemySlim::SeqMove(float delta_time)
{
    if (m_player)
    {
        float distance_x = m_pos.x - m_player->GetPos().x;

        if (std::abs(distance_x) < 100)
        {
            tnl_sequence_.change(&EnemySlim::SeqAttack);
        }

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            if (CanMoveRight())
            {
                animLoader->SetAnimation(20); 
                m_pos.x += m_velocity.x * delta_time;
                m_is_direction_right = true;
            }
        });

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            if (CanMoveLeft())
            {
                animLoader->SetAnimation(21); 
                m_pos.x -= m_velocity.x * delta_time;
                m_is_direction_right = false;
            }
        });

        tnl_sequence_.change(&EnemySlim::SeqIdle);

        TNL_SEQ_CO_END;
    }
}
bool EnemySlim::SeqAttack(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;
    
    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if(m_player)
        {
            if (CanMoveRight() && distance_x < 0)
            {
                animLoader->SetAnimation(22);
                m_pos.x += m_velocity.x * delta_time;
                m_is_direction_right = true;
            }
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_player)
        {
            if (CanMoveLeft() && distance_x > 0)
            {
                animLoader->SetAnimation(23);
                m_pos.x -= m_velocity.x * delta_time;
                m_is_direction_right = false;
            }
        }
    });

    tnl_sequence_.change(&EnemySlim::SeqMove);
    TNL_SEQ_CO_END;
}

