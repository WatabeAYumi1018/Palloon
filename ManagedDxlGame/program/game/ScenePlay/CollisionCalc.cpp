#include "../../wta_library/wta_IsIntersectCalc.h"
#include "CollisionCalc.h"
#include "../ScenePlay/Character.h"
#include "../ScenePlay/MapChip.h"


//キャラクター位置を取得し、マップIDから当たり判定のタイプを取得
//eCollisionType CollisionCalc::GetCollisionTypeMap(Character* chara, MapChip* mapChip) {
eCollisionType CollisionCalc::GetCollisionTypeMap(int px, int py, MapChip* mapChip) {
    // キャラクターのワールド座標をマップのグリッド座標に変換
    int chara_x = px / MapChip::MAP_CHIP_SIZE;
    int chara_y = py / MapChip::MAP_CHIP_SIZE;

    int mx[3] = { chara_x - 1, chara_x, chara_x + 1 };
    int my[3] = { chara_y - 1, chara_y, chara_y + 1 };

    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            if (mx[k] < 0) continue;
            if (mx[k] >= MapChip::MAP_CHIP_SIZE) continue;
            if (mx[i] < 0) continue;
            if (mx[i] >= MapChip::MAP_CHIP_SIZE) continue;

            int cellId = mapChip->GetChipId(mx[k], my[i]);
            if (-1 != cellId) {
                DrawStringEx(10, 10, -1, "m = %d", cellId);
                return mapChip->GetCollisionTypeById(cellId);
            }
        }
    }
    return eCollisionType::eCollision_None;

}

//キャラクターの周囲のマップチップを取得する(当たり判定処理軽減のため)
//一般的にキャラを中心に(2*range+1)*(2*range+1)の範囲のマップチップを取得する
std::vector<tnl::Vector3> CollisionCalc::GetSurroundingChips(Character* chara, MapChip* mapChip, int range) {
    std::vector<tnl::Vector3> chips;
    tnl::Vector3 pos = chara->GetPos();
    //グリッド座標に変換
    int chip_x = pos.x / mapChip->MAP_CHIP_SIZE;
    int chip_y = pos.y / mapChip->MAP_CHIP_SIZE;
    //キャラ座標を中心に5*5の範囲のマップチップを取得
    for (int i = chip_y - range; i <= chip_y + range; ++i) {
        for (int j = chip_x - range; j <= chip_x + range; ++j) {
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
        int x = static_cast<int>(tile.x);
        int y = static_cast<int>(tile.y);
        //tnl::Vector3 character_y= chara->GetPos() + tnl::Vector3(0, 15, 0);
        //当たり判定と補正座標取得
        tnl::Vector3 nearly_point = tnl::GetNearestRectPoint(mapChip->GetChipPos(x, y), mapChip->MAP_CHIP_SIZE, mapChip->MAP_CHIP_SIZE, chara->GetPos());
        if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
        {
            tnl::Vector3 normalize = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
            chara->SetPos( nearly_point + normalize * chara->GetSize() );
            //衝突応答処理
            DrawStringEx(0, 50, -1, "boxhit");
        }
    }
   


}

//線分との当たり判定
//矩形と同じ処理を行うために、処理が二重になってしまうが、可読性と保守性を考慮にしている
void CollisionCalc::CheckLineCollision(Character* chara, MapChip* mapChip, int range) {
    auto tiles = GetSurroundingChips(chara, mapChip, range);
    for (const auto& tile : tiles) {
        int x = static_cast<int>(tile.x);
        int y = static_cast<int>(tile.y);
        //線分の始点と終点を取得
        tnl::Vector3 lineStart, lineEnd;
        mapChip->GetTileLineSegment(y, x, lineStart, lineEnd);
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
    eCollisionType collisionType= GetCollisionTypeMap(chara->GetPos().x, chara->GetPos().y, mapChip);
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
    {
        int a = 0;
        a++;
    }
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
