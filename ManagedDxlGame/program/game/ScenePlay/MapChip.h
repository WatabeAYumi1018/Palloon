#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"

class Character;

class MapChip :public Object{
public:
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

	//-----当たり判定関連付けのためのmap配列の変数-----//
	std::unordered_map<int, eCollisionType> m_id_map_collision_type;

public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time,float m_scroll_x);
	void Draw(float m_scroll_x);
	void Finalize();

	//-----当たり判定実装において必要な個別変数-----//
	//ID取得
	int GetChipId(int row, int col);
	//IDから当たり判定の種類取得
	eCollisionType GetCollisionTypeById(int id);
	//IDとCollisionを関連付ける
	void LoadMapChipCollisionType();
	//斜線チップの線分座標取得
	void GetTileLineSegment(int row, int col, tnl::Vector3& start, tnl::Vector3& end);
	
	//-----Getter-----//
	tnl::Vector3 GetChipPos(int row, int col) {return tnl::Vector3(col * MAP_CHIP_SIZE, row * MAP_CHIP_SIZE, 0);}
	//戻り値としてのconst、関数としてのconst（値の変更を不可にし、オブジェクトの状態変更も阻止）
	const std::vector<std::vector<int>>& getMapChip() const {return m_csv_map_tile;}
};

//読み取りと描画、当たり判定のために必要な情報取得と概念を定義
