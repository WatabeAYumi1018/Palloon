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
	std::vector<std::vector<int>> m_map_tile_ID;		//csvファイル：ID
	std::vector<std::vector<int>> m_map_tile_collision;	//csvファイル：当たり判定

	//マップチップIDの情報開始～終了(行列)
	const int MAP_CHIP_ID_ROW_START = 10;			//10列目
	const int MAP_CHIP_ID_ROW_END = 58;				//58列目
	const int MAP_CHIP_ID_COL_START = 0;			//0行目
	const int MAP_CHIP_ID_COL_END = 1;				//3行目

public:
	//csvファイルからマップチップの情報を読み込む
	void Initialize();
	void LoadMapChipID();
	void LoadMapChipCollision();
	void Fainalize();
};