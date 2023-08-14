#pragma once
#include "../../engine/GameEngine.h"

//アニメーション情報をcsvから読み取るクラス（ループと単発で二種類存在）
class DrawAnim {

public:
	//int型でコンストラクタ
	DrawAnim();
	~DrawAnim();

private:
	//-----定数-----//
	//①ループアニメーション
	//IDとフォルダパスの情報開始～終了(行列)
	const int ANIM_LOOP_ROW_START = 1;			//1行目
	const int ANIM_LOOP_ROW_END = 20;			//20行目
	const int ANIM_LOOP_COL_START = 0;			//0列目
	const int ANIM_LOOP_COL_END = 1;			//1列目
	//②単発アニメーション
	//IDとフォルダパスの情報開始～終了(行列)
	const int ANIM_NOTLOOP_ROW_START = 1;			//1行目
	const int ANIM_NOTLOOP_ROW_END = 16;			//16行目
	const int ANIM_NOTLOOP_COL_START = 3;			//3列目
	const int ANIM_NOTLOOP_COL_END = 4;				//4列目

private:
	//-----csvファイルパス関連の変数-----//
	//IDとファイルパスの読み取り
	std::string csv_anim= "csv/PlayerAnimLoop.csv";
	//
	std::vector<std::vector<int>> m_csv_anim;		

public:
	//-----メンバ関数-----//
	void Initialize();
	void LoadFilePath();
	void Finalize();
};

