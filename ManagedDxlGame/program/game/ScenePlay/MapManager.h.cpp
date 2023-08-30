#include "MapManager.h"
#include "Character.h"
#include "PlayCamera.h"

MapManager::MapManager(){Initialize();}

MapManager::~MapManager() {Finalize();}

void MapManager::Initialize() {
	//csvファイルのマップタイル描画情報を読み込む
	m_csv_map_tile = tnl::LoadCsv<int>("csv/TileStage_1-1.csv");
	//csvファイルからマップチップの情報を読み込む(一時的な格納)
	m_csv_collision = tnl::LoadCsv<int>("csv/TileStageCollision_1-1.csv");
	//画像の読み込み
	LoadDivGraph("graphics/Stage1-1.png", MAP_ALL_NUM, MAP_ROW_COL,MAP_ROW_COL, MAP_CHIP_SIZE, MAP_CHIP_SIZE, m_map_hdl);
}

void MapManager::Update(float delta_time, const PlayCamera* camera) {
	LoadMapCollision(camera);
}

//★描画(現状毎フレーム読み取るようになってしまった…)
//読み取りとDrawを分けるべきだったので、vectorに情報を入れて。カメラに合わせて描画するのがbestかな？と考え中
void MapManager::Draw(const PlayCamera* camera) {
	//マップ画像の描画
	for (int i = 0; i < m_csv_map_tile.size(); ++i) {			//行数はm_map_tileのサイズに基づく
		for (int j = 0; j < m_csv_map_tile[i].size(); ++j) {	//列数はm_map_tile[i]のサイズに基づく
			//tnl::Vector3 draw_pos;
			m_pos.x = j * MAP_CHIP_SIZE;
			m_pos.y = i * MAP_CHIP_SIZE;
			//カメラの位置に合わせて描画位置をずらす
			tnl::Vector3 draw_pos = m_pos - camera->target +
				tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

			DrawGraph(draw_pos.x, draw_pos.y, m_map_hdl[m_csv_map_tile[i][j]], TRUE);
		}
	}
}

//★当たり判定の読み込み(現状毎フレーム読み取るようになってしまったので…上に同じかな)
void MapManager::LoadMapCollision(const PlayCamera* camera) {
	// サイズ初期化（m_csv_collision.size()で最初の0列目のサイズを読み取り、それがsizeの列分だけある）
	m_collision_info.resize(m_csv_collision.size(), std::vector<sCollisionInfo>(m_csv_collision[0].size()));
	//ファイル上の数値を全て読み込む
	for (int i = 0; i < m_csv_collision.size(); ++i) {
		for (int j = 0; j < m_csv_collision[i].size(); ++j) {
			//当たり判定の中心座標を計算
			int posX = j * MAP_CHIP_SIZE +(MAP_CHIP_SIZE>>1);
			int posY = i * MAP_CHIP_SIZE +(MAP_CHIP_SIZE>>1);
			//eCollisionTypeと読み取った数字を関連付ける（同じ数字で連動しやすいように）
			eCollisionType type = static_cast<eCollisionType>(m_csv_collision[i][j]);
			//構造体型に各情報を代入
			sCollisionInfo info;
			info.pos = tnl::Vector3(posX, posY,0);
			info.size = MAP_CHIP_SIZE;
			info.type= type;
			//当たり判定の情報を各マップチップに格納
			m_collision_info[i][j]=info;
			if (type != eCollisionType::None) {
				//カメラの位置に合わせて描画位置をずらす
				tnl::Vector3 draw_pos = info.pos - camera->target +
					tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
				//DrawBoxEx(draw_pos, info.size, info.size);
			}
		}
	}
}

void MapManager::Finalize() {
	m_csv_map_tile.clear();
	m_csv_collision.clear();
}

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
