#include "MapChip.h"
#include "Collision.h"

MapChip::MapChip() :Object(m_pos) {
	//csvファイルの読み込み
	m_map_tile=tnl::LoadCsv<int>(csv_map_tile_data);
	//csvファイルからマップチップの情報を読み込む(一時的な格納)
	m_csv_info = tnl::LoadCsv<int>(csv_map_tile_ID);
	Initialize();
}

MapChip::~MapChip() {Finalize();}

void MapChip::Initialize() {
	//画像の読み込み
	LoadDivGraph("graphics/Sprites32.png", MAP_ALL_NUM, MAP_ROW_COL,MAP_ROW_COL, MAP_CHIP_SIZE, MAP_CHIP_SIZE, m_map_hdl);
	//当たり判定の読み込み
	LoadMapChipCollision();
}

void MapChip::Update(float delta_time,float scroll_x) {
	Draw(scroll_x);
}

void MapChip::Draw(float scroll_x) {
	//マップ画像の描画
	for (int i = 0; i < m_map_tile.size(); ++i) {			//行数はm_map_tileのサイズに基づく
		for (int j = 0; j < m_map_tile[i].size(); ++j) {	//列数はm_map_tile[i]のサイズに基づく
			int posX = j * MAP_CHIP_SIZE - scroll_x;		//スクロールの値を考慮
			int posY = i * MAP_CHIP_SIZE ;			
			DrawGraph(posX, posY, m_map_hdl[m_map_tile[i][j]], TRUE);
			// デバッグ描画
			DrawFormatString(0, 0, -1, "+");
		}
	}
}

//マップチップIDの情報から、チップが自分自身の判定を持つようにする
void MapChip::LoadMapChipCollision() {
	// 当たり判定情報を格納するためにサイズを設定
	m_map_chip_collision.resize(m_map_tile.size(),
								std::vector<Collision>(m_map_tile[0].size()));
	for (int i = 0; i < m_csv_info.size(); ++i) {
		for (int j = 0; j < m_csv_info[i].size(); ++j) {
			eCollisionType type = eCollisionType::eCollision_None;
			if (m_csv_info[i][j] == 1) {type = eCollisionType::eCollision_Block;}
			else if (m_csv_info[i][j] == 2) {type = eCollisionType::eCollision_Line;}
			m_map_chip_collision[i][j] = Collision(type);
		}
	}
}

void MapChip::Finalize() {
	m_map_tile.clear();
	m_csv_info.clear();
	m_map_chip_collision.clear();
}