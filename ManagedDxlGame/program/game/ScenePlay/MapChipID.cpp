#include "MapChipID.h"

MapChipID::MapChipID() {
	//csvファイルからマップチップの情報を読み込む
	m_map_tile_ID = tnl::LoadCsv<int>(csv_map_tile_ID);
	Initialize();
}

MapChipID::~MapChipID() {}

void MapChipID::Initialize() {
	//csvファイルから当たり判定の情報を読み込む
	LoadMapChipID();
}

void MapChipID::LoadMapChipID() {
	//読み取った情報をvectorに格納
	for (int i = MAP_CHIP_ID_ROW_START; i < MAP_CHIP_ID_ROW_END; ++i) {
		for (int j = MAP_CHIP_ID_COL_START; j < MAP_CHIP_ID_COL_END; ++j) {
			std::vector<int> map_info;
			//マップタイルのIDとCollisionの情報を格納
			map_info.push_back(m_map_tile_ID[i][j]);
		}
	}
}

void MapChipID::LoadMapChipCollision() {
	//vectorに格納した情報を元に、当たり判定をグループごとに分けて格納
	for (int i = 0; i < m_map_tile_ID.size(); ++i) {
		for (int j = 0; j < m_map_tile_ID[i].size(); ++j) {
			//マップチップのIDが0の場合、当たり判定なし
			if (m_map_tile_ID[i][1] == 0) {break;}
			//マップチップのIDが1の場合、当たり判定あり
			else if (m_map_tile_ID[i][1] == 1 || m_map_tile_ID[i][1] == 2) {
				std::vector<int> map_collision;
				//マップタイルのIDとCollisionの情報を格納
				map_collision.push_back(m_map_tile_collision[i][j]);
			}
		}
	}
}

void MapChipID::Fainalize() {}

