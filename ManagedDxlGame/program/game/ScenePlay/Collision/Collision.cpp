#include "../../../wta_library/wta_IsIntersectCalc.h"
#include "../Character/Character.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Enemy.h"
#include "../Map/Map.h"
#include "Collision.h"

Collision::Collision() : m_last_chara_pos(0, 0, 0)
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
    tnl::Vector3 current_pos = chara->GetPos();
    //現在の座標から前の座標を引いて、マップチップのサイズより小さい場合はキャッシュを返す
    if ((current_pos - m_last_chara_pos).length() < map->MAP_CHIP_SIZE)
    {
        return m_cachedChips;
    }

    std::vector<std::vector<sCollisionInfo>> chips;

    //キャラの座標からグリッド座標を取得
    tnl::Vector3 chip_pos = GetCharacterMapChipPos(current_pos, map);

    for (int i = chip_pos.y - range; i <= chip_pos.y + range; ++i)
    {
        //範囲外は無視
        if (i < 0 || i >= map->GetCollisionInfo().size())
        {
            continue;
        }

        auto rowChips = GetRowChips(chip_pos.x, i, range, map);

        if (IsRowCollisionExists(rowChips))
        {
            chips.emplace_back(rowChips);
        }
    }
    m_cachedChips = chips;
    m_last_chara_pos = current_pos;

    return chips;
}

//矩形との当たり判定計算
void Collision::CheckBoxCollision(Character* chara, Map* map, const std::vector<std::vector<sCollisionInfo>>& surroundingChips)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            if (info.s_type == eMapCollisionType::None || info.s_type == eMapCollisionType::Line ||
                info.s_type == eMapCollisionType::Clear)
            {
                continue;
            }
            tnl::Vector3 nearly_point = tnl::GetNearestRectPoint(info.s_pos, info.s_size, info.s_size, chara->GetPos());

            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
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
            if (info.s_type == eMapCollisionType::None || info.s_type == eMapCollisionType::Clear)
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
            }
        }
    }
}

//当たり判定に応じて分岐処理
void Collision::CollisionCalculate(Character* chara, Map* map, int range)
{
    auto surrounding_chips = GetSurroundingChips(chara, map, range);

    for (const auto& row : surrounding_chips) 
    {
        for (const auto& info : row) 
        {
            if (info.s_type == eMapCollisionType::Clear) 
            {
                 m_clear_pos = info.s_pos;
                m_is_clear = true;
                
                break;
            }
        }
        // 既にClear位置を検出したので、このループも終了
        if (m_is_clear)
        {
            break;
        }
    }
    // 一度だけBoxとLineの当たり判定を呼び出す
    CheckBoxCollision(chara, map, surrounding_chips);
    CheckLineCollision(chara, map, surrounding_chips);
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
        if (!player->GetIsInvincible())
        {
            if (enemy_pos.y > player_pos.y)
            {
                //プレイヤーが敵を踏んでいると設定
                player->SetIsStamp(true);
                enemy->SetIsDead(true);
            }

            else if (player->GetIsRolling())
            {
				//プレイヤーが回転中なら敵を倒す
				enemy->SetIsDead(true);
			}

            else
            {
                //プレイヤーのHPを減らす
                player->DecreaseHP(1);
                player->MakeInvincible();
            }
        }
    }
}

//////当たり判定に応じて分岐処理
//void Collision::CollisionCalculate(Character* chara, Map* map, int range) {
//
//    //判定範囲内のマップチップを取得
//    auto surroundingChips = GetSurroundingChips(chara, map, range);
//
//    bool hasClearCollision = false;
//
//    for (const auto& row : surroundingChips)
//    {
//        for (const auto& info : row)
//        {
//            // 当たり判定のタイプに基づいて処理
//            switch (info.s_type)
//            {
//            case eMapCollisionType::Box:
//
//                CheckBoxCollision(chara, map, surroundingChips);
//
//                break;
//
//            case eMapCollisionType::Line:
//
//                CheckLineCollision(chara, map, surroundingChips);
//
//            case eMapCollisionType::Clear:
//
//                //Clearの座標を保持
//                m_clear_pos = info.s_pos;
//
//                break;
//            }
//        }
//    }
//}
