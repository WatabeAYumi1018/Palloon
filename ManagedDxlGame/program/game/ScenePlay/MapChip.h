#pragma once
#include "../../engine/GameEngine.h"
#include "Object.h"

class PlayCamera;
class Collision;

class MapChip :public Object{
public:
	//int型でコンストラクタ
	MapChip(const std::string& csv_map_tile);
	~MapChip();

private:
	//-----メンバ変数-----//
	int m_map_hdl[49];						//マップチップのタイルハンドル
	Collision* collision_map=nullptr;		//当たり判定用クラス
	PlayCamera* m_play_camera = nullptr;	//プレイヤー追従カメラ

	//-----定数-----//
	const int MAP_ROW_COL=7;				//マップチップの横幅
	const int MAP_ALL_NUM=49;				//マップチップの縦幅
	const int MAP_CHIP_SIZE=16;				//マップチップのサイズ

	//int型でcsvファイルの読み込み
	std::vector<std::vector<int>> m_map_tile;	//csvファイル：マップタイルステージ
	
public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time);
	void Draw();
	void Finalize();

	// 座標を調整する関数
	void AdjustPosition(const tnl::Vector3& offset) {m_pos.x+=offset.x;}
};