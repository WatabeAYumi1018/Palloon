#include "MapChip.h"
#include "CollisionCalc.h"

MapChip::MapChip() :Object(m_pos) {
	//csvファイルのマップタイル描画情報を読み込む
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
	LoadMapChipCollisionType();
}

void MapChip::Update(float delta_time,float scroll_x) {Draw(scroll_x);}

void MapChip::Draw(float scroll_x) {
	//マップ画像の描画
	for (int i = 0; i < m_map_tile.size(); ++i) {			//行数はm_map_tileのサイズに基づく
		for (int j = 0; j < m_map_tile[i].size(); ++j) {	//列数はm_map_tile[i]のサイズに基づく
			int posX = j * MAP_CHIP_SIZE - scroll_x;		//スクロールの値を考慮
			int posY = i * MAP_CHIP_SIZE ;			
			DrawGraph(posX, posY, m_map_hdl[m_map_tile[i][j]], TRUE);
		}
	}
}

//IDとCollision情報のみを一時格納
void MapChip::LoadMapChipCollisionType() {
	for (int i = MAP_CHIP_ID_ROW_START; i < MAP_CHIP_ID_ROW_END; ++i) {
		//当たり判定の情報のみ格納
		std::vector<eCollisionType> collisionType;
		//int型をeCollisionType型にキャスト
		collisionType.emplace_back(static_cast<eCollisionType>(m_csv_info[i][1]));
	}
}

void MapChip::Finalize() {
	m_map_tile.clear();
	m_csv_info.clear();
}

//イベントチップを上書きして追加イベントとかもあり
////LoadMapChipInfo()関数で読み取った情報を基に、チップが自分自身の判定を持つようにしたい
//void MapChip::LoadMapChipCollision() {
//	// 当たり判定情報を格納するためにサイズを設定
//	//m_map_chip_collision.resize(m_map_tile.size(), std::vector<Collision>(m_map_tile[0].size()));
//	//描画しているチップIDに対応するCollision情報を格納（当たり判定情報を独自で管理するため）
//	for (int i = 0; i < m_map_tile.size(); ++i) {
//		for (int j = 0; j < m_map_tile[i].size(); ++j) {
//			//マップチップのIDを取得
//			int chipID = m_map_tile[i][j];
//			if(chipID==-1)continue;
//			else {
//				eCollisionType type = m_map_chip_collision[chipID]; // マップから当たり判定を取得
//				//オブジェクト指向にはなるけど、マップ全体となると非効率（今回は見送り濃厚）
//				//m_map_tile[i][j] = type;
//			}
//		}
//	}
//}
