#include "../../Camera/Camera.h"
#include "EnemyPlant.h"
#include "../Player/Player.h"

EnemyPlant::EnemyPlant(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map*map,Collision *collision, Camera* camera) :
    Enemy(data, info, player, map, collision, camera)
{

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
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
        tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    animLoader->Draw(delta_time, draw_pos);
}

bool EnemyPlant::SeqIdle(float delta_time)
{
    DrawStringEx(0, 50, -1, "idle");

    //if (m_player)
    //{
    //    //プレイヤーとの距離計算
    //    if (std::abs(m_pos.x - m_player->GetPos().x) < 90.0f)
    //    {
    //        tnl_sequence_.change(&EnemyPlant::SeqAttack);
    //    }
    //}

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (m_is_dirction_right)
        {
            animLoader->SetAnimation(24);
        }
        else
        {
            animLoader->SetAnimation(25);
        }
    });

    TNL_SEQ_CO_END;
}

bool EnemyPlant::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_is_dirction_right)
        {
            animLoader->SetAnimation(26);
        }
        else
        {
            animLoader->SetAnimation(26);
        }
    });

    tnl_sequence_.change(&EnemyPlant::SeqIdle);
    TNL_SEQ_CO_END;
}
