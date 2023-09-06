#include "../../Camera/Camera.h"
#include "EnemySlim.h"
#include "../Player/Player.h"

EnemySlim::EnemySlim(const sEnemyData& data, const sEnemyInfo& info,Player* player) :
    Enemy(data, info, player)
{
    
}

EnemySlim::~EnemySlim() 
{

}

void EnemySlim::Update(float delta_time)
{
	//重力で下に落ちる
	m_pos.y += (m_gravity.y * delta_time)*0.1f;

	tnl_sequence_.update(delta_time);
}

void EnemySlim::Draw(float delta_time, const Camera* camera)
{
	//カメラの位置に合わせて描画位置をずらす
	tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
		tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    animLoader->Draw(delta_time, draw_pos);
}

bool EnemySlim::SeqMove(float delta_time)
{
    if (m_player) 
    {
        float chance = m_distribution(m_generator);

        //move→idleの確率
        if (chance < 0.001f)
        {
            tnl_sequence_.change(&Enemy::SeqIdle);
        }

        //プレイヤーとの距離計算
        if (std::abs(m_pos.x - m_player->GetPos().x) < 100.0f)
        {
            tnl_sequence_.change(&Enemy::SeqAttack);
        }
        DrawStringEx(0, 0, -1, "move");

        //経過時間をカウント
        m_moveTimeCounter += delta_time;

        if (m_moveTimeCounter <= 2.0f)
        {
            TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
            {
                    animLoader->SetAnimation(20);
                    m_pos.x += m_velocity.x * delta_time;

                    m_is_dirction_right = true;
            });
        }
        else if (m_moveTimeCounter > 2.0f && m_moveTimeCounter <= 4.0f)
        {
            TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
            {
                    animLoader->SetAnimation(21);
                    m_pos.x -= m_velocity.x * delta_time;

                    m_is_dirction_right = false;
            });
        }
        else if (m_moveTimeCounter > 4.0f)
        {
            m_moveTimeCounter = 0.0f;
        }

        tnl_sequence_.change(&Enemy::SeqMove);
        TNL_SEQ_CO_END;
    }
}

bool EnemySlim::SeqIdle(float delta_time)
{
    DrawStringEx(0, 0, -1, "idle");

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (m_is_dirction_right) 
        {
            animLoader->SetAnimation(20);
        }
        else
        {
			animLoader->SetAnimation(19);
		}
    });

    tnl_sequence_.change(&Enemy::SeqMove);
    TNL_SEQ_CO_END;
}

bool EnemySlim::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (m_is_dirction_right)
        {
			animLoader->SetAnimation(22);
            
		}
        else
        {
			animLoader->SetAnimation(23);
            m_pos.x -= m_velocity.x * delta_time;
		}
    });

    tnl_sequence_.change(&Enemy::SeqMove);
    TNL_SEQ_CO_END;
}

