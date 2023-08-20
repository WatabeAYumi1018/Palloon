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

	//IDと当たり判定の情報開始～終了(行)
	const int MAP_CHIP_ID_ROW_START = 10;
	const int MAP_CHIP_ID_ROW_END = 58;

private:
	//-----メンバ変数-----//
	int m_map_hdl[MAP_ALL_NUM];											//マップチップのタイルハンドル
	std::vector<std::vector<int>> m_csv_map_tile;						//描画ファイル
	std::vector<std::vector<int>> m_csv_collision;						//チップ情報ファイル
	std::unordered_map<int, eCollisionType> m_id_map_collision_type;	//IDと当たり判定のmap配列

public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time,float m_scroll_x);
	void Draw(float m_scroll_x);
	void Finalize();

	//当たり判定実装において必要な個別関数
	int GetChipId(int row, int col);													//ID取得
	eCollisionType GetCollisionTypeById(int id);										//IDから当たり判定の種類取得
	void LoadMapChipCollisionType();													//当たり判定の種類を読み込む	
	void GetTileLineSegment(int row, int col, tnl::Vector3& start, tnl::Vector3& end);	//斜線チップの線分座標取得
	
	//-----Getter-----//
	tnl::Vector3 GetChipPos(int row, int col) {return tnl::Vector3(col * MAP_CHIP_SIZE, row * MAP_CHIP_SIZE, 0);}
	//戻り値としてのconst、関数としてのconst（値の変更を不可にし、オブジェクトの状態変更も阻止）
	const std::vector<std::vector<int>>& getMapChip() const {return m_csv_map_tile;}
};

//読み取りと描画、当たり判定のために必要な情報取得と概念を定義
