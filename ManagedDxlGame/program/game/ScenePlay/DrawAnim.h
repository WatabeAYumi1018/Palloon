//#pragma once
//#include "../../engine/GameEngine.h"
//
////アニメーション情報をcsvから読み取るクラス（ループと単発で二種類存在）
//class DrawAnim {
//
//public:
//	//int型でコンストラクタ
//	DrawAnim();
//	~DrawAnim();
//
//private:
//	//-----定数-----//
//	//①ループアニメーション
//	const int ANIM_LOOP_ROW_START = 1;			//1行目
//	const int ANIM_LOOP_ROW_END = 20;			//20行目
//	//②単発アニメーション
//	const int ANIM_NOTLOOP_ROW_START = 1;		//1行目
//	const int ANIM_NOTLOOP_ROW_END = 16;		//16行目
//
//private:
//	//-----csvファイルパス関連の変数-----//
//	//IDとファイルパスの読み取り
//	std::string csv_anim= "csv/AnimPath.csv";
//	//string型で格納
//	std::vector<std::vector<std::string>> m_anim_path;
//
//public:
//	//-----メンバ関数-----//
//	void Initialize();
//	void LoadPathLoop();		//ループアニメーションの読み取り
//	void LoadPathNotLoop();		//単発アニメーションの読み取り
//	void Finalize();
//};
//
