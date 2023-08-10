#include "MapChip.h"
#include "PlayCamera.h"
#include "Player.h"

MapChip::MapChip() :Object(m_pos) {
	//csvファイルの読み込み
	m_map_tile=tnl::LoadCsv<int>(csv_map_tile_data);
	Initialize();
}

MapChip::~MapChip() {Finalize();}

void MapChip::Initialize() {
	//画像の読み込み
	LoadDivGraph("graphics/Sprites32.png", MAP_ALL_NUM, MAP_ROW_COL,MAP_ROW_COL, MAP_CHIP_SIZE, MAP_CHIP_SIZE, m_map_hdl);
}

void MapChip::Update(float delta_time,float scroll_x) {
	Draw(scroll_x);
}

void MapChip::Draw(float scroll_x) {
	//マップ画像の描画
	for (int i = 0; i < m_map_tile.size(); ++i) {
		for (int j = 0; j < m_map_tile[i].size(); ++j) {
			int posX = j * MAP_CHIP_SIZE - scroll_x; // スクロールの値を考慮
			int posY = i * MAP_CHIP_SIZE ;			
			DrawGraph(posX, posY, m_map_hdl[m_map_tile[i][j]], TRUE);
			// デバッグ描画
			DrawFormatString(0, 0, -1, "+");
		}
	}
}

void MapChip::Finalize() {m_map_tile.clear();}