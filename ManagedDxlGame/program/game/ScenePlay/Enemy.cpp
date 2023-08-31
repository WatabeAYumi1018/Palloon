#include <random>
#include "Enemy.h"
#include "Player.h"
#include "MapManager.h"
#include "PlayCamera.h"

Enemy::Enemy() : Character(m_pos,m_size,m_hp,m_velocity)
{
    Initialize();
}

Enemy::~Enemy(){}

void Enemy::Initialize()
{
    //敵のスポーン位置をcsvから読み込む
    m_enemy_csv = tnl::LoadCsv<int>("csv/TileStageEnemy1-1.csv");
    LoadEnemy();
}

void Enemy::Update(float delta_time) 
{
    tnl_sequence_.update(delta_time);

    //重力で下に落ちる
    m_pos.y += 100 * delta_time;
}

void Enemy::Draw(float delta_time, const PlayCamera* camera) 
{
    for (auto& enemy : m_enemy_info)
    {
        //カメラの位置に合わせて描画位置をずらす
        tnl::Vector3 draw_pos = enemy.s_pos - camera->GetTarget() +
            tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
        

        switch (enemy.s_type) 
        {
            case eEnemyType::None:
			    break;
            case eEnemyType::Slim: 
            {        	    
                DrawCircle(draw_pos.x, draw_pos.y, m_size, -1);
			    break;
            }
           defalut:
                break;
        }
	}
}

float Enemy::DistanceCalc()
{
    float distance = std::sqrt
    (
        std::pow(m_pos.x - m_player->GetPos().x, 2) +
        std::pow(m_pos.y - m_player->GetPos().y, 2)
    );
    return distance;
}

//カメラに映っている間敵を生成する
void Enemy::LoadEnemy()
{
    //ファイル上の数値を全て読み込む
    for (int i = 0; i < m_enemy_csv.size(); ++i)
    {
        for (int j = 0; j < m_enemy_csv[i].size(); ++j)
        {
            //当たり判定の中心座標を計算
            int posX = j * m_mapmanager->MAP_CHIP_SIZE + (m_mapmanager->MAP_CHIP_SIZE >> 1);
            int posY = i * m_mapmanager->MAP_CHIP_SIZE + (m_mapmanager->MAP_CHIP_SIZE >> 1);
            //eEnemyTypeTypeと読み取った数字を関連付ける（同じ数字で連動しやすいように）
            eEnemyType type = static_cast<eEnemyType>(m_enemy_csv[i][j]);
            //当たり判定の情報を各マップチップに格納
            sEnemyData data;
            data.s_pos =  tnl::Vector3 (posX,posY,0);
            data.s_type = type;
            m_enemy_info.emplace_back(data);
        }
    }
}

bool Enemy::SeqBaseAction(const float delta_time) 
{ 
    if (m_player) {
        float chance = m_distribution(m_generator);

        //move→idleの確率
        if (chance < 0.001f)
        {
            tnl_sequence_.change(&Enemy::SeqNextAction);
        }

        //プレイヤーとの距離計算
        if (std::abs(m_pos.x - m_player->GetPos().x) < 2.0f)
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
                    DrawStringEx(0, 50, -1, "right");
                    m_pos.x += m_velocity.x * delta_time;
                });
        }
        else if (m_moveTimeCounter > 2.0f && m_moveTimeCounter <= 4.0f)
        {
            TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
                {
                    DrawStringEx(0, 50, -1, "left");
                    m_pos.x -= m_velocity.x * delta_time;
                });
        }
        else if (m_moveTimeCounter > 4.0f)
        {
            m_moveTimeCounter = 0.0f;
        }
        tnl_sequence_.change(&Enemy::SeqBaseAction);
        TNL_SEQ_CO_END;
    }
}

bool Enemy::SeqNextAction(const float delta_time)
{ 
	DrawStringEx(0, 0, -1, "idle");

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        //アニメーション画像再生表示とか
    });
    tnl_sequence_.change(&Enemy::SeqBaseAction);
    TNL_SEQ_CO_END;
}

bool Enemy::SeqAttack(const float delta_time)
{ 
    DrawStringEx(0, 0, -1, "attack");

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        //攻撃アニメーション再生
    });

    tnl_sequence_.change(&Enemy::SeqBaseAction);
    TNL_SEQ_CO_END;
}

void Enemy::Finalize() {

}