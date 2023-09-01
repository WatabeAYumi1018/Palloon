#include "../../wta_library/wta_IsIntersectCalc.h"
#include "CollisionCalc.h"
#include "../ScenePlay/Character.h"
#include "../ScenePlay/MapManager.h"

//キャラクターの周囲のマップチップを取得する(当たり判定処理軽減のため)
//一般的にキャラを中心に(2*range+1)*(2*range+1)の範囲のマップチップを取得する
std::vector<std::vector<sCollisionInfo>> CollisionCalc::GetSurroundingChips(Character* chara, MapManager* mapChip, int range)
{
    std::vector<std::vector<sCollisionInfo>> chips;
    tnl::Vector3 pos = chara->GetPos();
    //キャラの位置からマップチップの座標を取得
    int chip_x = static_cast<int>(pos.x / mapChip->MAP_CHIP_SIZE);
    int chip_y = static_cast<int>(pos.y / mapChip->MAP_CHIP_SIZE);

    for (int i = chip_y - range; i <= chip_y + range; ++i)
    {
        //範囲外の行はスキップ
        if (i < 0 || i >= mapChip->GetCollisionInfo().size())
        {
            continue;
        }
        //行の当たり判定を取得
        std::vector<sCollisionInfo> rowChips;
        for (int j = chip_x - range; j <= chip_x + range; ++j)
        {
            //範囲外の列はスキップ
            if (j < 0 || j >= mapChip->GetCollisionInfo()[i].size())
            {
                continue;
            }

            sCollisionInfo info = mapChip->GetCollisionInfo()[i][j];
            if (info.s_type != eCollisionType::None)
            {
                rowChips.emplace_back(info);
            }
        }
        //行に当たり判定がある場合のみ二次元に追加
        if (!rowChips.empty())
        {
            chips.emplace_back(rowChips);
        }
    }
    return chips;
}

//矩形との当たり判定計算
void CollisionCalc::CheckBoxCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            if (info.s_type == eCollisionType::None)
            { 
                continue;
            }
            tnl::Vector3 nearly_point = tnl::GetNearestRectPoint(info.s_pos, info.s_size, info.s_size, chara->GetPos());
            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
                //衝突応答処理
                DrawStringEx(0, 70, -1, "boxhit");
            }
        }
    }
}

//線分との当たり判定
void CollisionCalc::CheckLineCollision(Character* chara, MapManager* mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips) 
{
    for (const auto& row : surroundingChips) 
    {
        for (const auto& info : row) 
        {
          if (info.s_type == eCollisionType::None || info.s_type == eCollisionType::Box)
          {
              continue; 
          }
          tnl::Vector3 nearly_point = 
              tnl::GetNearestPointLine(
                  chara->GetPos() ,
                  { info.s_pos.x - (info.s_size >> 1),info.s_pos.y + (info.s_size>> 1 ),0 },
                  { info.s_pos.x + (info.s_size >> 1),info.s_pos.y - (info.s_size >> 1),0 }
                );
           if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
           {
              tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
              chara->SetPos(nearly_point + normalize * chara->GetSize());
              //衝突応答処理
              DrawStringEx(0, 90, -1, "linehit");
          }
        }
    }
}

////当たり判定に応じて分岐処理
void CollisionCalc::CollisionCalculate(Character *chara, MapManager*mapChip,int range) {
    //判定範囲内のマップチップを取得
    auto surroundingChips = GetSurroundingChips(chara, mapChip, range);
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            // 当たり判定のタイプに基づいて処理
            switch (info.s_type)
            {
            case eCollisionType::Box:
               
                CheckBoxCollision(chara, mapChip, surroundingChips);
               
                break;
            
            case eCollisionType::Line:

                CheckLineCollision(chara, mapChip, surroundingChips);
               
                break;
            
            default:
                break;
            }
        }               
    }
}

//-----------------------------無視してください--------------------------------//

////キャラクター位置を取得し、マップIDから当たり判定のタイプを取得
////eCollisionType CollisionCalc::GetCollisionTypeMap(Character* chara, MapChip* mapChip) {
//eCollisionType CollisionCalc::GetCollisionTypeMap(int px, int py, MapChip* mapChip) {
//    // キャラクターのワールド座標をマップのグリッド座標に変換
//    int chara_x = px / mapChip->MAP_CHIP_SIZE;
//    int chara_y = py / mapChip->MAP_CHIP_SIZE;
//
//    int mx[3] = { chara_x - 1, chara_x, chara_x + 1 };
//    int my[3] = { chara_y - 1, chara_y, chara_y + 1 };
//
//    for (int i = 0; i < 3; ++i) {
//        for (int k = 0; k < 3; ++k) {
//            if (mx[k] < 0) continue;
//            if (mx[k] >= mapChip->MAP_CHIP_SIZE) continue;
//            if (mx[i] < 0) continue;
//            if (mx[i] >= mapChip->MAP_CHIP_SIZE) continue;
//
//            int cellId = mapChip->GetChipId(mx[k], my[i]);
//            if (-1 != cellId) {
//                DrawStringEx(10, 10, -1, "m = %d", cellId);
//                return mapChip->GetCollisionTypeById(cellId);
//            }
//        }
//    }
//    return eCollisionType::eCollision_None;
//
//}
