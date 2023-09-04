#include "../../Camera/Camera.h"
#include "EnemyPlant.h"
#include "../Player/Player.h"

EnemyPlant::EnemyPlant(const sEnemyData& data, const sEnemyInfo& info) :
    Enemy(data, info, m_player)
{

}

EnemyPlant::~EnemyPlant()
{
    delete animLoader;
}

void EnemyPlant::Update(float delta_time)
{
    //重力で下に落ちる
    m_pos.y += m_gravity.y * delta_time;

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
    DrawStringEx(0, 0, -1, "idle");

    if (m_player) {
     
        //プレイヤーとの距離計算
        if (std::abs(m_pos.x - m_player->GetPos().x) < 2.0f)
        {
            tnl_sequence_.change(&Enemy::SeqAttack);
        }
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            animLoader->SetAnimation(18);   /*こんな感じで*/
        });
    tnl_sequence_.change(&Enemy::SeqIdle);
    TNL_SEQ_CO_END;
}

bool EnemyPlant::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
        {
            //攻撃アニメーション再生
        });

    tnl_sequence_.change(&Enemy::SeqMove);
    TNL_SEQ_CO_END;
}

