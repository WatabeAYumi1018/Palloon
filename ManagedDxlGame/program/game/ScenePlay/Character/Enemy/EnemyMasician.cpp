#include "../../Camera/Camera.h"
#include "EnemyMasician.h"
#include "../Player/Player.h"

EnemyMasician::EnemyMasician(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision) :
    Enemy(data, info, m_player, map, collision)
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
    DrawStringEx(0, 50, -1, "idle");

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
            if (m_is_dirction_right)
            {
            //    animLoader->SetAnimation(18);
            }
            else
            {
            //    animLoader->SetAnimation(19);
            }
    });

    tnl_sequence_.change(&EnemyMasician::SeqMove);
    TNL_SEQ_CO_END;
}

bool EnemyMasician::SeqMove(float delta_time)
{
    if (m_player)
    {
        //プレイヤーとの距離計算
        if (std::abs(m_pos.x - m_player->GetPos().x) < 90.0f)
        {
            if (CanMoveRight() || CanMoveLeft())
            {
                tnl_sequence_.change(&EnemyMasician::SeqAttack);
            }
            else
            {
                tnl_sequence_.change(&EnemyMasician::SeqIdle);
            }
        }
        DrawStringEx(0, 0, -1, "move");

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            //animLoader->SetAnimation(20);

            if (CanMoveRight())
            {
                m_pos.x += m_velocity.x * delta_time;
                m_is_dirction_right = true;
            }
        });

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            animLoader->SetAnimation(21);

            if (CanMoveLeft())
            {
                m_pos.x -= m_velocity.x * delta_time;
                m_is_dirction_right = false;
            }
        });

        tnl_sequence_.change(&EnemyMasician::SeqIdle);

        TNL_SEQ_CO_END;
    }
}

bool EnemyMasician::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_is_dirction_right)
        {
            //animLoader->SetAnimation(22);
            m_pos.x += m_velocity.x * delta_time;
        }
        else
        {
            //animLoader->SetAnimation(23);
            m_pos.x -= m_velocity.x * delta_time;
        }
    });

    tnl_sequence_.change(&EnemyMasician::SeqMove);
    TNL_SEQ_CO_END;
}