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
	//�d�͂ŉ��ɗ�����
	m_pos.y += (m_gravity.y * delta_time)*0.1f;

	tnl_sequence_.update(delta_time);
}

void EnemySlim::Draw(float delta_time, const Camera* camera)
{
    //�J�����̈ʒu�ɍ��킹�ĕ`��ʒu�����炷
    tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
        tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    animLoader->Draw(delta_time, draw_pos);
    //DrawCircle(draw_pos.x, draw_pos.y, m_size, -1, TRUE);
}

bool EnemySlim::SeqIdle(float delta_time)
{
    DrawStringEx(0, 50, -1, "idle");

    float distance_x = m_pos.x - m_player->GetPos().x;

    //�v���C���[�Ƃ̋����v�Z
    if (std::abs(distance_x) < 100)
    {
        tnl_sequence_.change(&EnemySlim::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //�����ltrue�̂��ߍŏ��͉E��������
        if (m_is_dirction_right) 
        {
           animLoader->SetAnimation(18);
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //�����ltrue�̂��ߍŏ��͉E��������
        if (!m_is_dirction_right)
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
        DrawStringEx(0, 0, -1, "move");

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            if (CanMoveRight())
            {
                animLoader->SetAnimation(20); 
                m_pos.x += m_velocity.x * delta_time;
                m_is_dirction_right = true;
            }
        });

        TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
        {
            if (CanMoveLeft())
            {
                animLoader->SetAnimation(21); 
                m_pos.x -= m_velocity.x * delta_time;
                m_is_dirction_right = false;
            }
        });

        tnl_sequence_.change(&EnemySlim::SeqIdle);

        TNL_SEQ_CO_END;
    }
}
bool EnemySlim::SeqAttack(float delta_time)
{
    DrawStringEx(0, 0, -1, "attack");

    float distance_x = m_pos.x - m_player->GetPos().x;
    
    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if(m_player)
        {
            if (CanMoveRight() && distance_x < 0)
            {
                DrawStringEx(0, 100, -1, "Moving right"); 
                animLoader->SetAnimation(22);
                DrawString(0, 150, "%d",m_pos.x,-1);
                m_pos.x += m_velocity.x * delta_time;
                DrawString(0, 200,  "%d", m_pos.x,-1); 
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
                animLoader->SetAnimation(23);
                m_pos.x -= m_velocity.x * delta_time;
                m_is_dirction_right = false;
            }
        }
    });

    tnl_sequence_.change(&EnemySlim::SeqMove);
    TNL_SEQ_CO_END;
}
