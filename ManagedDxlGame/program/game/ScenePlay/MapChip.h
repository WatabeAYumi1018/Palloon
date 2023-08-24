#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"

class PlayCamera;
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

private:
	//-----メンバ変数-----//
	int m_map_hdl[MAP_ALL_NUM];											//マップチップのタイルハンドル
	std::vector<std::vector<int>> m_csv_map_tile;						//描画ファイル
	std::vector<std::vector<int>> m_csv_collision;						//チップ情報ファイル
	std::vector<std::vector<CollisionInfo>> m_collision_info;			//当たり判定の情報格納用

public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time, const PlayCamera *camera);
	void Draw(const PlayCamera *camera);
	void Finalize();

	//当たり判定専用のマップ関数
	void LoadMapCollision();
	
	//-----Getter-----//
	const std::vector<std::vector<CollisionInfo>>& GetCollisionInfo() const { return m_collision_info; }
};
	//IDと当たり判定の情報開始～終了(行)
	//const int MAP_CHIP_ID_ROW_START = 10;
	//const int MAP_CHIP_ID_ROW_END = 58;

	//std::unordered_map<int, eCollisionType> m_id_map_collision_type;	//IDと当たり判定のmap配列

	//std::vector<std::vector<CollisionInfo>> GetCollisionInfo() const { return m_collision_info; }
	//tnl::Vector3 GetChipPos(int x ,int y) {return tnl::Vector3(x * MAP_CHIP_SIZE, y * MAP_CHIP_SIZE, 0);}
	//戻り値としてのconst、関数としてのconst（値の変更を不可にし、オブジェクトの状態変更も阻止）
	//const std::vector<std::vector<int>>& getMapChip() const {return m_csv_map_tile;}

	//当たり判定実装において必要な個別関数
	//int GetChipId(int y, int x);
	//eCollisionType GetCollisionTypeById(int id);										//IDから当たり判定の種類取得
	//void LoadMapChipCollisionType();													//当たり判定の種類を読み込む	
	//void GetTileLineSegment(int y, int x, tnl::Vector3& start, tnl::Vector3& end);	//斜線チップの線分座標取得

	//読み取りと描画、当たり判定のために必要な情報取得と概念を定義
