#include "../../Camera/Camera.h"
#include "EnemyFairy.h"
#include "../Player/Player.h"

EnemyFairy::EnemyFairy(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera) :
    Enemy(data, info, player, map, collision, camera)
{

}

EnemyFairy::~EnemyFairy()
{

}

void EnemyFairy::Update(float delta_time)
{
    //ちょっと浮かばせたい

    tnl_sequence_.update(delta_time);
}

void EnemyFairy::Draw(float delta_time, const Camera* camera)
{
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
        tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    animLoader->Draw(delta_time, draw_pos);
}

bool EnemyFairy::SeqIdle(float delta_time)
{
    DrawStringEx(0, 50, -1, "idle");

    float distance_x = m_pos.x - m_player->GetPos().x;

    //プレイヤーとの距離計算
    if (std::abs(distance_x) < 100)
    {
        tnl_sequence_.change(&EnemyFairy::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            //初期値trueのため最初は右向きから
            if (m_is_dirction_right)
            {
                animLoader->SetAnimation(34);
            }
        });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            //初期値trueのため最初は右向きから
            if (!m_is_dirction_right)
            {
                animLoader->SetAnimation(35);
            }
        });

    tnl_sequence_.change(&EnemyFairy::SeqMove);
    TNL_SEQ_CO_END;
}

bool EnemyFairy::SeqMove(float delta_time)
{
    if (m_player)
    {
        float distance_x = m_pos.x - m_player->GetPos().x;

        if (std::abs(distance_x) < 100)
        {
            tnl_sequence_.change(&EnemyFairy::SeqAttack);
        }
        DrawStringEx(0, 0, -1, "move");

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
            {
                if (CanMoveRight())
                {
                    animLoader->SetAnimation(36);
                    m_pos.x += m_velocity.x * delta_time;
                    m_is_dirction_right = true;
                }
            });

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
            {
                if (CanMoveLeft())
                {
                    animLoader->SetAnimation(37);
                    m_pos.x -= m_velocity.x * delta_time;
                    m_is_dirction_right = false;
                }
            });

        tnl_sequence_.change(&EnemyFairy::SeqIdle);

        TNL_SEQ_CO_END;
    }
}
bool EnemyFairy::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    float distance_x = m_pos.x - m_player->GetPos().x;

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
        {
            if (m_player)
            {
                if (CanMoveRight() && distance_x < 0)
                {
                    DrawStringEx(0, 100, -1, "Moving right");
                    animLoader->SetAnimation(38);
                    DrawString(0, 150, "%d", m_pos.x, -1);
                    m_pos.x += m_velocity.x * delta_time;
                    DrawString(0, 200, "%d", m_pos.x, -1);
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
                    DrawStringEx(0, 100, -1, "Moving left");
                    animLoader->SetAnimation(39);
                    m_pos.x -= m_velocity.x * delta_time;
                    m_is_dirction_right = false;
                }
            }
        });

    tnl_sequence_.change(&EnemyFairy::SeqMove);
    TNL_SEQ_CO_END;
}
