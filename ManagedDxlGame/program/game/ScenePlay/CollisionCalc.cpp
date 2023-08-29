#include "../../wta_library/wta_IsIntersectCalc.h"
#include "CollisionCalc.h"
#include "../ScenePlay/Character.h"
#include "../ScenePlay/MapManager.h"

//キャラクターの周囲のマップチップを取得する(当たり判定処理軽減のため)
//一般的にキャラを中心に(2*range+1)*(2*range+1)の範囲のマップチップを取得する
std::vector<std::vector<sCollisionInfo>> CollisionCalc::GetSurroundingChips(Character *chara, MapManager*mapChip, int range) {
    std::vector<std::vector<sCollisionInfo>> chips;
    tnl::Vector3 pos = chara->GetPos();
    //グリッド座標に変換
    int chip_x = static_cast<int>(pos.x / mapChip->MAP_CHIP_SIZE);
    int chip_y = static_cast<int>(pos.y / mapChip->MAP_CHIP_SIZE);
    //キャラ座標を中心に5*5の範囲のマップチップを取得
   

    for (int i = chip_y - range; i <= chip_y + range; ++i) {
        std::vector<sCollisionInfo> rowChips;
        for (int j = chip_x - range; j <= chip_x + range; ++j) {
            //範囲外はスキップ
            if (i < 0 || i >= mapChip->GetCollisionInfo().size() || j < 0 || j >= mapChip->GetCollisionInfo()[i].size())
            {
                rowChips.emplace_back(sCollisionInfo());  // None typeのCollisionInfoを追加
                 continue;
            }
            rowChips.emplace_back(mapChip->GetCollisionInfo()[i][j]);
        }
        chips.emplace_back(rowChips);
    }
    return chips;
}

//矩形との当たり判定計算
void CollisionCalc::CheckBoxCollision(Character *chara, MapManager*mapChip, const std::vector<std::vector<sCollisionInfo>>& surroundingChips) {
    for (const auto& row : surroundingChips) {
        for (const auto& info : row) {
            if (info.type == eCollisionType::None) { continue; }
            tnl::Vector3 nearly_point = tnl::GetNearestRectPoint(info.pos, info.size, info.size, chara->GetPos());
            if ((nearly_point - chara->GetPos()).length() < chara->GetSize()) {
                tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                chara->SetPos(nearly_point + normalize * chara->GetSize());
                //衝突応答処理
                DrawStringEx(0, 70, -1, "boxhit");
            }
        }
    }
}

////当たり判定に応じて分岐処理
void CollisionCalc::CollisionCalculate(Character *chara, MapManager*mapChip,int range) {
    //判定範囲内のマップチップを取得
    auto surroundingChips = GetSurroundingChips(chara, mapChip, range);
    for (const auto& row : surroundingChips) {
        for (const auto& info : row) {
            // 当たり判定のタイプに基づいて処理
            switch (info.type) {
            case eCollisionType::Box:
                CheckBoxCollision(chara, mapChip, surroundingChips);
                break;
            case eCollisionType::Line:
                //矩形の判定をした上で、線分の判定も行う
                CheckBoxCollision(chara, mapChip, surroundingChips);
                //CheckLineCollision(chara, mapChip, range);
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


//線分との当たり判定
//矩形と同じ処理を行うために、処理が二重になってしまうが、可読性と保守性を考慮にしている
//void CollisionCalc::CheckLineCollision(Character* chara, MapChip* mapChip, int range) {
//    auto tiles = GetSurroundingChips(chara, mapChip, range);
//    for (const auto& tile : tiles) {
//        int x = static_cast<int>(tile.x);
//        int y = static_cast<int>(tile.y);
//        //線分の始点と終点を取得
//        tnl::Vector3 lineStart, lineEnd;
//        mapChip->GetTileLineSegment(y, x, lineStart, lineEnd);
//        if (wta::IsIntersectCircleLine(chara->GetPos(), chara->GetSize(), lineStart, lineEnd))
//        {
//            // 衝突応答処理
//            DrawStringEx(0, 70, -1, "linehit");
//        }
//    }
//}
