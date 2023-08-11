#pragma once
#include "../../engine/GameEngine.h"

//マップチップの情報を取得、管理するクラス
//当たり判定の基盤などもここで管理する
class MapChipID {
public:
	MapChipID();
	~MapChipID();
private:
	//-----csvファイル関連の変数-----//
	//読み取り
	std::string csv_map_tile_ID = "csv/tileStageID_1-1.csv";
	//int型で描画
	std::vector<std::vector<int>> m_map_tile_ID;	//csvファイル：マップチップID


public:
	//csvファイルからマップチップの情報を読み込む
	void Initialize();
	void LoadMapChipID();
	void Fainalize();
};