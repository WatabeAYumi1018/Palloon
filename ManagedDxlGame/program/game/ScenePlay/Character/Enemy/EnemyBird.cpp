#include "../../Camera/Camera.h"
#include "EnemyBird.h"
#include "../Player/Player.h"

EnemyBird::EnemyBird(const sEnemyData& data, const sEnemyInfo& info, Player* player, Map* map, Collision* collision, Camera* camera) :
    Enemy(data, info, player, map, collision, camera)
{

}

EnemyBird::~EnemyBird()
{
 
}

void EnemyBird::Update(float delta_time)
{
    tnl_sequence_.update(delta_time);
}

void EnemyBird::Draw(float delta_time, const Camera* camera)
{
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
        tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    animLoader->Draw(delta_time, draw_pos);
}

bool EnemyBird::SeqMove(float delta_time)
{
    if (m_player)
    {
        //プレイヤーとの距離計算
        if (std::abs(m_pos.x - m_player->GetPos().x) < 90.0f)
        {
            tnl_sequence_.change(&EnemyBird::SeqAttack);
        }

        DrawStringEx(0, 0, -1, "move");

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            animLoader->SetAnimation(40);
            m_pos.x -= m_velocity.x * delta_time;
        });

        TNL_SEQ_CO_END;
    }
}

bool EnemyBird::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        animLoader->SetAnimation(41);
        m_pos.x -= m_velocity.x * delta_time * 2;
    });

    tnl_sequence_.change(&EnemyBird::SeqMove);
    TNL_SEQ_CO_END;
}
