#include "MapChip.h",

MapChip::MapChip(const std::string& csv_map_tile){
	//csvファイルの読み込み
	m_map_tile=tnl::LoadCsv<int>(csv_map_tile);
	Initialize();
}

MapChip::~MapChip() {Finalize();}

void MapChip::Initialize() {
	//画像の読み込み
	LoadDivGraph("graphics/Sprites.png", MAP_ALL_NUM, MAP_ROW_COL,MAP_ROW_COL, MAP_CHIP_SIZE, MAP_CHIP_SIZE, m_map_hdl);
}

void MapChip::Update(float delta_time) {Draw();}

void MapChip::Draw() {
	//マップ画像の描画
	for(int i = 0; i < m_map_tile.size(); ++i) {
		for (int j = 0; j < m_map_tile[i].size(); ++j) {
			DrawGraph(j * 16, i * 16, m_map_hdl[m_map_tile[i][j]], TRUE);
		}
	}
}

void MapChip::Finalize() {m_map_tile.clear();}