#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"

class Collision;

class MapChip :public Object{
public:
	//int型でコンストラクタ
	MapChip();
	~MapChip();

	//-----定数-----//
	static const int MAP_ROW_COL=7;				//マップチップの横幅
	static const int MAP_ALL_NUM=49;			//マップチップの縦幅
	static const int MAP_CHIP_SIZE = 32;		//マップチップのサイズ

private:
	//-----メンバ変数-----//
	int m_map_hdl[MAP_ALL_NUM];						//マップチップのタイルハンドル

	//-----csv描画関連の変数-----//
	//マップチップ描画データの読み取り
	std::string csv_map_tile_data = "csv/TileStage_1-1re32.csv";
	//int型で描画
	std::vector<std::vector<int>> m_map_tile;					//マップタイルステージ
	
	//-----csvファイル関連の変数-----//
	//当たり判定情報の読み取り
	std::string csv_map_tile_ID = "csv/tileStageID_1-1.csv";
	//int型で描画
	std::vector<std::vector<int>> m_csv_info;					//マップタイルステージ
	//当たり判定格納用
	std::vector<std::vector<Collision>> m_map_chip_collision;	//当たり判定

public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time,float m_scroll_x);
	void Draw(float m_scroll_x);
	void LoadMapChipCollision();
	void Finalize();
};

////マップチップIDの情報開始～終了(行列)
//const int MAP_CHIP_ID_ROW_START = 10;			//10列目
//const int MAP_CHIP_ID_ROW_END = 58;				//58列目
//const int MAP_CHIP_ID_COL_START = 0;			//0行目
//const int MAP_CHIP_ID_COL_END = 1;				//行目



//描画のことだけを本クラスで定義
//PlayCameraクラスで制御を行う