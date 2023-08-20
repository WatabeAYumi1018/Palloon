#include "../../wta_library/wta_Animation.h"
#include "CollisionCalc.h"
#include "../ScenePlay/Character.h"
#include "../ScenePlay/MapChip.h"


//キャラクター位置を取得し、マップIDから当たり判定のタイプを取得
eCollisionType CollisionCalc::GetCollisionTypeMap(Character* chara, MapChip* mapChip) {
    // キャラクターのワールド座標をマップのグリッド座標に変換
    int charaRow = chara->GetPos().y / MapChip::MAP_CHIP_SIZE;
    int charaCol = chara->GetPos().x / MapChip::MAP_CHIP_SIZE;
    // 当該位置のIDを取得
    int cellId = mapChip->GetChipId(charaRow, charaCol);
    // IDを使用して当たり判定のタイプを確認
    return mapChip->GetCollisionTypeById(cellId);
}

//キャラクターの周囲のマップチップを取得する(当たり判定処理軽減のため)
//一般的にキャラを中心に(2*range+1)*(2*range+1)の範囲のマップチップを取得する
std::vector<tnl::Vector3> CollisionCalc::GetSurroundingChips(Character* chara, MapChip* mapChip, int range) {
    std::vector<tnl::Vector3> chips;
    tnl::Vector3 pos = chara->GetPos();
    //グリッド座標に変換
    int row = pos.y / mapChip->MAP_CHIP_SIZE;
    int col = pos.x / mapChip->MAP_CHIP_SIZE;
    //キャラ座標を中心に5*5の範囲のマップチップを取得
    for (int i = row - range; i <= row + range; ++i) {
        for (int j = col - range; j <= col + range; ++j) {
            //範囲外はスキップ
            if (i < 0 || i >= mapChip->getMapChip().size() || j < 0 || j >= mapChip->getMapChip()[i].size())
            {
                continue;
            }
            chips.emplace_back(tnl::Vector3(j, i, 0));
        }
    }
    return chips;
}

//矩形との当たり判定
void CollisionCalc::CheckBoxCollision(Character* chara, MapChip* mapChip, int range) {
    //判定範囲内のマップチップを取得
    auto tiles = GetSurroundingChips(chara, mapChip, range);
    for (const auto& tile : tiles) {
        //Vector3→int型に変換
        int row = static_cast<int>(tile.x);
        int col = static_cast<int>(tile.y);
        if (wta::IsIntersectCircleBox(chara->GetPos(), chara->GetSize(), mapChip->GetChipPos(row, col), mapChip->MAP_CHIP_SIZE))
        {
            // 衝突応答処理
            DrawStringEx(0, 50, -1, "boxhit");
        }
    }
}

//線分との当たり判定
//矩形と同じ処理を行うために、処理が二重になってしまうが、可読性と保守性を考慮にしている
void CollisionCalc::CheckLineCollision(Character* chara, MapChip* mapChip, int range) {
    auto tiles = GetSurroundingChips(chara, mapChip, range);
    for (const auto& tile : tiles) {
        int row = static_cast<int>(tile.x);
        int col = static_cast<int>(tile.y);
        //線分の始点と終点を取得
        tnl::Vector3 lineStart, lineEnd;
        mapChip->GetTileLineSegment(row, col, lineStart, lineEnd);
        if (wta::IsIntersectCircleLine(chara->GetPos(), chara->GetSize(), lineStart, lineEnd))
        {
            // 衝突応答処理
            DrawStringEx(0, 70, -1, "linehit");
        }
    }
}

//当たり判定に応じて分岐処理
void CollisionCalc::CollisionCalculate(Character *chara, MapChip *mapChip,int range) {
    // キャラクターと地形との当たり判定のタイプを取得
    eCollisionType collisionType= GetCollisionTypeMap(chara, mapChip);
    // 当たり判定のタイプに基づいて処理
    switch (collisionType) {
    case eCollisionType::eCollision_Box:
        CheckBoxCollision(chara,mapChip,range);
        break;
    case eCollisionType::eCollision_Line:
        //矩形の判定をした上で、線分の判定も行う
        CheckBoxCollision(chara, mapChip, range);
        CheckLineCollision(chara, mapChip, range);
        break;
    default:
        break;
    }
}

//当たり判定の流れ
//①マップチップのIDを取得（MapChipクラス）
//②①から当たり判定のタイプを取得（MapChipクラス）
//③キャラクターの座標を中心として５×５の範囲のマップチップを取得（CollisionCalcクラス）
//④③から当たり判定のタイプを取得（MapChipクラス）
//⑤②と④を比較し、当たり判定のタイプを決定（CollisionCalcクラス）
//⑥⑤からタイプに応じた当たり判定の判定、計算を行う（CollisionCalcクラス）
//⑦⑥からキャラクターの座標を更新（CollisionCalcクラス）   ★キャラを押し出す処理は未実装
