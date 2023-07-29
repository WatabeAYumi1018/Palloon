#pragma once
#include "../../engine/GameEngine.h"

class Collision;

class MapChip {
public:
	MapChip(const string& csv_map_tile);
	~MapChip();

private:
	//-----メンバ変数-----//
	int m_map_hdl[49];						//マップチップのタイルハンドル
	Collision* collision_map=nullptr;		//当たり判定用クラス

	//-----定数-----//
	const int MAP_ROW_COL=7;				//マップチップの横幅
	const int MAP_ALL_NUM=49;				//マップチップの縦幅
	const int MAP_CHIP_SIZE=16;				//マップチップのサイズ

	//string型(csvファイル読み取り用)
	vector<vector<string>> m_map_tile;		//csvファイル：マップタイルステージ
	
	//int型に変換（描画用）
	vector<vector<int>> m_map_tile_num;		//csvファイル：マップタイルステージ	

public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time);
	void Draw();
	void Finalize();
};