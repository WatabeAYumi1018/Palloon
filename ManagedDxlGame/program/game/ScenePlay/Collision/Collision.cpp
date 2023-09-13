#include "../../../wta_library/wta_IsIntersectCalc.h"
#include "../Character/Character.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Enemy.h"
#include "../Map/Map.h"
#include "Collision.h"

Collision::Collision() : m_lastCharaPos(0.0f, 0.0f, 0.0f)
{

}

tnl::Vector3 Collision::GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map)
{
    //キャラの位置からグリッド座標を取得
    float chip_x = charaPos.x / map->MAP_CHIP_SIZE;
    float chip_y = charaPos.y / map->MAP_CHIP_SIZE;

    return tnl::Vector3(chip_x, chip_y, 0.0f);
}

std::vector<sCollisionInfo> Collision::GetRowChips(int chip_x, int i, int range, const Map* map)
{
    std::vector<sCollisionInfo> rowChips;

    //キャラの座標から周囲のマップチップを取得
    for (int j = chip_x - range; j <= chip_x + range; ++j)
    {
        //範囲外は無視
        if (j < 0 || j >= map->GetCollisionInfo()[i].size())
        {
            continue;
        }

        sCollisionInfo info = map->GetCollisionInfo()[i][j];

        //当たり判定がない場合は無視
        if (info.s_type != eMapCollisionType::None)
        {
            rowChips.emplace_back(info);
        }
    }
    return rowChips;
}

bool Collision::IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips)
{
    //空じゃない場合のみ先に進む
    return !rowChips.empty();
}

//キャラクターの周囲のマップチップを取得する(当たり判定処理軽減のため)
//一般的にキャラを中心に(2*range+1)*(2*range+1)の範囲のマップチップを取得する
std::vector<std::vector<sCollisionInfo>> Collision::GetSurroundingChips(Character* chara, Map* map, int range)
{
    tnl::Vector3 currentPos = chara->GetPos();
    //現在の座標から前の座標を引いて、マップチップのサイズより小さい場合はキャッシュを返す
    if ((currentPos - m_lastCharaPos).length() < map->MAP_CHIP_SIZE)
    {
        return m_cachedChips;
    }

    std::vector<std::vector<sCollisionInfo>> chips;

    //キャラの座標からグリッド座標を取得
    tnl::Vector3 chipPos = GetCharacterMapChipPos(currentPos, map);

    for (int i = chipPos.y - range; i <= chipPos.y + range; ++i)
    {
        //範囲外は無視
        if (i < 0 || i >= map->GetCollisionInfo().size())
        {
            continue;
        }

        auto rowChips = GetRowChips(chipPos.x, i, range, map);

        if (IsRowCollisionExists(rowChips))
        {
            chips.emplace_back(rowChips);
        }
    }

    m_cachedChips = chips;
    m_lastCharaPos = currentPos;

    return chips;
}

//矩形との当たり判定計算
void Collision::CheckBoxCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            if (info.s_type == eMapCollisionType::None || info.s_type == eMapCollisionType::Line)
            {
                continue;
            }
            tnl::Vector3 nearly_point = tnl::GetNearestRectPoint(info.s_pos, info.s_size, info.s_size, chara->GetPos());

            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
                //衝突応答処理
                //DrawStringEx(0, 70, -1, "boxhit");
            }
        }
    }
}

//線分との当たり判定
void Collision::CheckLineCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            if (info.s_type == eMapCollisionType::None)
            {
                continue;
            }
            tnl::Vector3 nearly_point =

                tnl::GetNearestPointLine
                (
                    chara->GetPos(),
                    { info.s_pos.x - (info.s_size >> 1),info.s_pos.y + (info.s_size >> 1),0 },
                    { info.s_pos.x + (info.s_size >> 1),info.s_pos.y - (info.s_size >> 1),0 }
                );

            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
                
                
                //衝突応答処理
                //DrawStringEx(0, 90, -1, "linehit");
            }
        }
    }
}

////当たり判定に応じて分岐処理
void Collision::CollisionCalculate(Character* chara, Map* map, int range) {

    //判定範囲内のマップチップを取得
    auto surroundingChips = GetSurroundingChips(chara, map, range);

    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            // 当たり判定のタイプに基づいて処理
            switch (info.s_type)
            {
            case eMapCollisionType::Box:

                CheckBoxCollision(chara, map, surroundingChips);

                break;

            case eMapCollisionType::Line:

                CheckLineCollision(chara, map, surroundingChips);


                break;

            default:
                break;
            }
        }
    }
}

void Collision::CollisionCharacter(Player* player, Enemy* enemy)
{
    tnl::Vector3 player_pos = player->GetPos();
    float player_size = player->GetSize();

    tnl::Vector3 enemy_pos = enemy->GetPos();
    float enemy_size = enemy->GetSize();

    // 2つのキャラクターが衝突しているかチェック
    if (wta::IsIntersectCircleCircle(player_pos, player_size, enemy_pos, enemy_size))
    {
        //プレイヤーの座標が高い場合は敵のHPを減らす
        if (enemy_pos.y < player_pos.y)
        {
            enemy->DecreaseHP(1);
        }
        else {
            if (!player->GetIsInvincible())
            {
                //プレイヤーのHPを減らす
                player->DecreaseHP(1);

                player->MakeInvincible();

                if (player->GetIsDead())
                {
                    //プレイヤーが死んだらの処理

                }

                tnl::Vector3 diff = enemy_pos - player_pos;

                //衝突した2つのキャラクター間の距離
                float distance = diff.length();

                //衝突の度合いを計算
                float overlap = (player_size + enemy_size) - distance;

                //方向ベクトルを正規化
                diff = tnl::Vector3::Normalize(diff);

                //プレイヤーを適切な位置に移動
                player->SetPos(player_pos - diff * overlap);
            }
        }
    }
}
