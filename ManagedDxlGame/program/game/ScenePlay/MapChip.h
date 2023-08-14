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
	//マップチップの基本情報
	static const int MAP_ROW_COL=7;				//マップチップの横幅
	static const int MAP_ALL_NUM=49;			//マップチップの縦幅
	static const int MAP_CHIP_SIZE = 32;		//マップチップのサイズ

	//IDと当たり判定の情報開始～終了(行列)
	const int MAP_CHIP_ID_ROW_START = 10;			//10行目
	const int MAP_CHIP_ID_ROW_END = 58;				//58行目

private:
	//-----メンバ変数-----//
	int m_map_hdl[MAP_ALL_NUM];						//マップチップのタイルハンドル

	//-----csv描画関連の変数-----//
	//マップチップ描画データの読み取り
	std::string csv_map_tile_data = "csv/TileStage_1-1re32.csv";
	//int型で描画
	std::vector<std::vector<int>> m_csv_map_tile;		//マップタイル描画情報
	
	//-----csv当たり判定関連の変数-----//
	//当たり判定情報の読み取り
	std::string csv_map_tile_ID = "csv/tileStageID_1-1.csv";
	//int型で描画
	std::vector<std::vector<int>> m_csv_collision;		//マップタイル当たり判定情報

public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time,float m_scroll_x);
	void Draw(float m_scroll_x);
	void LoadMapChipCollisionType();
	void Finalize();
};


//std::vector<IDCollision> map_id_collision;		//必要情報のみ一時格納用
//当たり判定格納用
//std::vector<eCollisionType> m_map_chip_collision;	//当たり判定

//読み取りと描画（定義付け）のみ定義
//Collisionクラスで当たり判定の計算処理を行う
//※MapChipクラスで当たり判定の情報を読み取り、Collisionクラスで当たり判定の計算処理を行う