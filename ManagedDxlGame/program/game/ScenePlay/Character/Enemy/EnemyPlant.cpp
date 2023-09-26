#include "../../Camera/Camera.h"
#include "EnemyPlant.h"
#include "../Player/Player.h"

EnemyPlant::EnemyPlant(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map*map,Collision *collision, Camera* camera) :
    Enemy(data, info, player, map, collision, camera)
{
    m_is_dirction_right = false;
}

EnemyPlant::~EnemyPlant()
{

}

void EnemyPlant::Update(float delta_time)
{
    //重力で下に落ちる
    m_pos.y += m_gravity.y * delta_time*0.1;

    tnl_sequence_.update(delta_time);
}

void EnemyPlant::Draw(float delta_time, const Camera* camera)
{
    if (m_is_active)
    {
        //カメラの位置に合わせて描画位置をずらす
        tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
            tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

        animLoader->Draw(delta_time, draw_pos);
    }
}

bool EnemyPlant::SeqIdle(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    //プレイヤーとの距離計算
    if (std::abs(distance_x) < 200)
    {
        tnl_sequence_.change(&EnemyPlant::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //初期値trueのため最初は右向きから
        if (m_is_dirction_right)
        {
            animLoader->SetAnimation(24);
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //初期値trueのため最初は右向きから
        if (!m_is_dirction_right)
        {
            animLoader->SetAnimation(25);
        }
    });

    TNL_SEQ_CO_END;
}

bool EnemyPlant::SeqAttack(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_player)
        {
            if (CanMoveRight() && distance_x < 0)
            {
                animLoader->SetAnimation(26);
                m_is_dirction_right = true;
            }
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_player)
        {
            if (CanMoveLeft() && distance_x > 0)
            {
                animLoader->SetAnimation(27);
                m_is_dirction_right = false;
            }
        }
    });

    tnl_sequence_.change(&EnemyPlant::SeqIdle);
    TNL_SEQ_CO_END;
}
