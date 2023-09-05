#include "../../Camera/Camera.h"
#include "EnemyBird.h"
#include "../Player/Player.h"

EnemyBird::EnemyBird(const sEnemyData& data, const sEnemyInfo& info, Player* player) :
    Enemy(data, info, m_player)
{

}

EnemyBird::~EnemyBird()
{
    delete animLoader;
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
    if (m_player) {

        //プレイヤーとの距離計算
        if (std::abs(m_pos.x - m_player->GetPos().x) < 2.0f)
        {
            tnl_sequence_.change(&Enemy::SeqAttack);
        }
    }
    DrawStringEx(0, 0, -1, "move");

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
            DrawStringEx(0, 50, -1, "left");
            m_pos.x -= m_velocity.x * delta_time;
    });
    
        
    tnl_sequence_.change(&Enemy::SeqMove);
    TNL_SEQ_CO_END;
}

bool EnemyBird::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
            //攻撃アニメーション再生
    });

    tnl_sequence_.change(&Enemy::SeqMove);
    TNL_SEQ_CO_END;
}

