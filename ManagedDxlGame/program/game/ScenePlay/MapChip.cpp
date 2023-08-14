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
	LoadMapChipInfo();
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
		}
	}
}

//IDとCollision情報のみを一時格納
void MapChip::LoadMapChipInfo() {
	// 読み取った情報をvectorに格納
	for (int i = MAP_CHIP_ID_ROW_START; i < MAP_CHIP_ID_ROW_END; ++i) {
		//行（外ベクトル）の情報格納
		std::vector<IDCollision> row;
		//2つずつ読み取る（密接に関係しているため）
		for (int j = MAP_CHIP_ID_COL_START; j <= MAP_CHIP_ID_COL_END; j += 2) {
			//IDとCollision情報を格納する構造体変数
			IDCollision id_collision;
			//ID情報定義
			id_collision.id = m_csv_info[i][j];
			//Collision情報定義
			int collisionType = m_csv_info[i][j + 1];
			// 1:ブロック 2:線 3:判定なし
			id_collision.collision = collisionType == 1 ? eCollisionType::eCollision_Block :
				collisionType == 2 ? eCollisionType::eCollision_Line : eCollisionType::eCollision_None;
			//当たり判定を格納
			row.emplace_back(id_collision);
		}
		//全て格納
		map_id_collision.emplace_back(row);
	}
}

//読み取った情報を基に、チップが自分自身の判定を持つようにする
void MapChip::LoadMapChipCollision() {
	// 当たり判定情報を格納するためにサイズを設定
	m_map_chip_collision.resize(m_map_tile.size(), std::vector<Collision>(m_map_tile[0].size()));
	//描画しているチップIDに対応するCollision情報を格納（当たり判定情報を独自で管理するため）
	for (int i = 0; i < m_map_tile.size(); ++i) {
		for (int j = 0; j < m_map_tile[i].size(); ++j) {
			//マップチップのIDを取得
			int chipID = m_map_tile[i][j];
			//そのIDに対応する当たり判定タイプを取得
			//eCollisionType type = map_id_collision[chipID][1].collision; //1列目に当たり判定のため
			//対応する位置に当たり判定情報を格納
			//m_map_chip_collision[i][j] = Collision(type);
		}
	}
}

void MapChip::Finalize() {
	m_map_tile.clear();
	m_csv_info.clear();
	m_map_chip_collision.clear();
}