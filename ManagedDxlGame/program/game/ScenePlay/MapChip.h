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
	const int MAP_ROW_COL=7;				//マップチップの横幅
	const int MAP_ALL_NUM=49;				//マップチップの縦幅
	const int MAP_CHIP_SIZE=16;				//マップチップのサイズ

private:
	//-----メンバ変数-----//
	int m_map_hdl[49];						//マップチップのタイルハンドル
	Collision* collision_map=nullptr;		//当たり判定用クラス

	//-----csvファイル関連の変数-----//
	//読み取り
	std::string csv_map_tile_data = "csv/TileStage_1-1.csv";
	//int型で描画
	std::vector<std::vector<int>> m_map_tile;	//csvファイル：マップタイルステージ
	
public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time,float m_scroll_x);
	void Draw(float m_scroll_x);
	void Finalize();
};

//描画のことだけを本クラスで定義
//PlayCameraクラスで制御を行う