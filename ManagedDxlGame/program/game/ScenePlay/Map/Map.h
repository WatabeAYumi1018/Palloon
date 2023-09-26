#pragma once
#include "../../../engine/GameEngine.h"

//csvからのマップチップ、当たり判定の読み取り

class Camera;
class Player;

class Map
{
public:

	Map(const std::string& stageName);
	virtual ~Map();

	//-----定数-----//
	//マップチップの基本情報
	static const int MAP_ROW_COL = 7;			/*横幅*/
	static const int MAP_ALL_NUM = 49;			/*縦幅*/
	static const int MAP_CHIP_SIZE = 32;		/*サイズ*/

private:
	//-----メンバ変数-----//
	int m_map_hdl[MAP_ALL_NUM];									/*タイルハンドル*/
	
	tnl::Vector3 m_pos;											/*座標*/
	
	std::vector<std::vector<int>> m_csv_map_tile;				/*描画情報*/
	std::vector<std::vector<int>> m_csv_collision;				/*当たり判定の描画情報*/
	std::vector<std::vector<sCollisionInfo>> m_collision_info;	/*当たり判定の情報*/

	std::vector<sStageInfo> stageList =						
	{ 
		{"stage1","graphics/stage1-1.jpg","csv/stage1-1.csv","csv/stage1-1collision.csv","csv/stage1-1enemy.csv","music/stage1-1.mp3",{0,100,0}},
		{"stage2","graphics/stage1-2.png","csv/stage1-2.csv","csv/stage1-2collision.csv","csv/stage1-2enemy.csv","music/stage1-2.mp3",{500,6000,0}},
		{"stage3","graphics/stage1-3.png","csv/stage1-3.csv","csv/stage1-3collision.csv","csv/stage1-3enemy.csv","music/stage1-3.mp3",{100,300,0}}
	};															/*ステージ分けlist*/							

	sStageInfo s_current_stage_info;							/*現在のステージ情報*/

public:
	//-----メンバ関数-----//
	void LoadMapCollision();									/*当たり判定専用のマップ関数*/
	
	void Initialize(const std::string& stageName);
	void Draw(const Camera* camera);
	void Finalize();

	//-----Getter-----//
	const size_t GetMapChipX() const { return m_csv_map_tile[0].size(); }
	const size_t GetMapChipY() const { return m_csv_map_tile.size(); }
	
	const std::vector<std::vector<sCollisionInfo>>& GetCollisionInfo() const { return m_collision_info; }
	
	const sStageInfo& GetCurrentStageInfo() const { return s_current_stage_info; }

	const std::vector<sStageInfo> GetStageList() const { return stageList; }
};


//----------------------------------------------------------------念のため残しておくだけ
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
