#include "MapChip.h"
#include "Character.h"
#include "PlayCamera.h"

MapChip::MapChip() :Object(m_pos) {Initialize();}

MapChip::~MapChip() {Finalize();}

void MapChip::Initialize() {
	//csvファイルのマップタイル描画情報を読み込む
	m_csv_map_tile = tnl::LoadCsv<int>("csv/TileStage_1-1re32.csv");
	//csvファイルからマップチップの情報を読み込む(一時的な格納)
	m_csv_collision = tnl::LoadCsv<int>("csv/TileStage_1-1re32Collision.csv");
	//画像の読み込み
	LoadDivGraph("graphics/Sprites32.png", MAP_ALL_NUM, MAP_ROW_COL,MAP_ROW_COL, MAP_CHIP_SIZE, MAP_CHIP_SIZE, m_map_hdl);
	//当たり判定の読み込み
	//LoadMapChipCollisionType();
	//当たり判定の情報を読み込み
	//LoadMapCollision();
}

void MapChip::Update(float delta_time, const PlayCamera *camera) {
	Draw(camera);
	LoadMapCollision();//当たり判定の地形確認用
}

void MapChip::Draw(const PlayCamera *camera) {
	//マップ画像の描画
	for (int i = 0; i < m_csv_map_tile.size(); ++i) {			//行数はm_map_tileのサイズに基づく
		for (int j = 0; j < m_csv_map_tile[i].size(); ++j) {	//列数はm_map_tile[i]のサイズに基づく
			int posX = j * MAP_CHIP_SIZE - static_cast<int>(camera->GetScrollX());
			int posY = i * MAP_CHIP_SIZE;
			DrawGraph(posX, posY, m_map_hdl[m_csv_map_tile[i][j]], TRUE);
		}
	}
}

//当たり判定の読み込み
void MapChip::LoadMapCollision() {
	// サイズ初期化（m_csv_collision.size()で最初の0列目のサイズを読み取り、それがsizeの列分だけある）
	m_collision_info.resize(m_csv_collision.size(), std::vector<CollisionInfo>(m_csv_collision[0].size()));
	//ファイル上の数値を全て読み込む
	for (int i = 0; i < m_csv_collision.size(); ++i) {
		for (int j = 0; j < m_csv_collision[i].size(); ++j) {
			int posX = j * MAP_CHIP_SIZE;
			int posY = i * MAP_CHIP_SIZE;
			//eCollisionTypeと読み取った数字を関連付ける（同じ数字で連動しやすいように）
			eCollisionType type = static_cast<eCollisionType>(m_csv_collision[i][j]);
			//構造体型に各情報を代入
			CollisionInfo info;
			info.pos = tnl::Vector3(posX, posY,0);
			info.size = MAP_CHIP_SIZE;
			info.type= type;
			//当たり判定の情報を各マップチップに格納
			m_collision_info[i][j]=info;
			if (type != eCollisionType::eCollision_None) {
				DrawBoxEx(info.pos, info.size, info.size);
			}
		}
	}
}

void MapChip::Finalize() {
	m_csv_map_tile.clear();
	m_csv_collision.clear();
}

////マップチップのIDを取得
//int MapChip::GetChipId(int y, int x) {
//	if (y < 0 || y >= m_csv_map_tile.size() || x < 0 || x >= m_csv_map_tile[y].size())
//	{
//		return -1;  //空白なら-1
//	}
//	return m_csv_map_tile[y][x];
//}
//
////IDを取得し、初期値を返す
//eCollisionType MapChip::GetCollisionTypeById(int id) {
//	if (m_id_map_collision_type.find(id) != m_id_map_collision_type.end()) {
//		return m_id_map_collision_type[id];
//	}
//	return eCollisionType::eCollision_None;
//}
//
////IDとCollisionを関連付ける
//void MapChip::LoadMapChipCollisionType() {
//	for (int i = MAP_CHIP_ID_ROW_START; i < MAP_CHIP_ID_ROW_END; ++i) {
//		//csvにてIDは0列目に格納
//		int id = m_csv_collision[i][0];
//		//csvにてCollisionTypeは1列目に格納
//		eCollisionType type = static_cast<eCollisionType>(m_csv_collision[i][1]);
//		m_id_map_collision_type[id] = type;
//	}
//}
//
////斜線との当たり判定のため、マップチップの左下と右上の座標を取得
//void MapChip::GetTileLineSegment(int y, int x, tnl::Vector3& start, tnl::Vector3& end) {
//	// マップチップの左下の座標を取得
//	start.x = x * MAP_CHIP_SIZE;
//	start.y = y * MAP_CHIP_SIZE;
//	// マップチップの右上の座標を取得
//	end.x = start.x + MAP_CHIP_SIZE;
//	end.y = start.y + MAP_CHIP_SIZE;
//}


//メモ書き
// イベントチップを上書きして追加イベントとかもあり
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
