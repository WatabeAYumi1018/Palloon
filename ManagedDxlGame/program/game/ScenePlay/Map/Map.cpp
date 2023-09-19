#include "Map.h"
#include "../Character/Character.h"
#include "../Camera/Camera.h"

Map::Map(const std::string& stageName)
{
	Initialize(stageName);
}

Map::~Map()
{
	Finalize();
}

void Map::Initialize(const std::string& stageName)
{
	if (!m_map_hdl[0]) 
	{
		//画像の読み込み
		LoadDivGraph("graphics/stagetile/Stage1-1.png", MAP_ALL_NUM, MAP_ROW_COL, MAP_ROW_COL, MAP_CHIP_SIZE, MAP_CHIP_SIZE, m_map_hdl);
	}

	// ステージ情報の読み込み
	for (const auto& stage : stageList)
	{
		if (stage.s_stage_name == stageName) 
		{
			s_current_stage_info = stage; // 現在のステージ情報を保存
			m_csv_map_tile = tnl::LoadCsv<int>(stage.s_map_csv);
			m_csv_collision = tnl::LoadCsv<int>(stage.s_collision_csv);

			break;
		}
	}
}

//描画
void Map::Draw(const Camera* camera)
{
	//マップ画像の描画
	for (int i = 0; i < m_csv_map_tile.size(); ++i) //行数はm_map_tileのサイズに基づく
	{
		for (int j = 0; j < m_csv_map_tile[i].size(); ++j) //列数はm_map_tile[i]のサイズに基づく
		{
			m_pos.x = j * MAP_CHIP_SIZE;
			m_pos.y = i * MAP_CHIP_SIZE;
			//カメラの位置に合わせて描画位置をずらす
			tnl::Vector3 draw_pos = m_pos - camera->GetTarget() +
				tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

			DrawGraph(draw_pos.x, draw_pos.y, m_map_hdl[m_csv_map_tile[i][j]], TRUE);
		}
	}
	LoadMapCollision();
}

//当たり判定の読み込み
void Map::LoadMapCollision()
{
	// サイズ初期化（m_csv_collision.size()で最初の0列目のサイズを読み取り、それがsizeの列分だけある）
	m_collision_info.resize(m_csv_collision.size(), std::vector<sCollisionInfo>(m_csv_collision[0].size()));
	//ファイル上の数値を全て読み込む
	for (int i = 0; i < m_csv_collision.size(); ++i)
	{
		for (int j = 0; j < m_csv_collision[i].size(); ++j)
		{
			//当たり判定の中心座標を計算
			int posX = j * MAP_CHIP_SIZE + (MAP_CHIP_SIZE >> 1);
			int posY = i * MAP_CHIP_SIZE + (MAP_CHIP_SIZE >> 1);
			//eCollisionTypeと読み取った数字を関連付ける（同じ数字で連動しやすいように）
			eMapCollisionType type = static_cast<eMapCollisionType>(m_csv_collision[i][j]);
			//構造体型に各情報を代入
			sCollisionInfo info;
			info.s_pos = tnl::Vector3(posX, posY, 0);
			info.s_size = MAP_CHIP_SIZE;
			info.s_type = type;
			//当たり判定の情報を各マップチップに格納
			m_collision_info[i][j] = info;
		}
	}
}

void Map::Finalize()
{
	m_csv_map_tile.clear();
	m_csv_collision.clear();
	DeleteGraph(m_map_hdl[0]);
}
