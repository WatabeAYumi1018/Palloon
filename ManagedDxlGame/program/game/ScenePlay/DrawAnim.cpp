//#include "DrawAnim.h"
//
//DrawAnim::DrawAnim() {
//	//csvファイルから情報を読み込む
//	m_anim_path=tnl::LoadCsv<std::string>(csv_anim);
//	Initialize();
//}
//
//DrawAnim::~DrawAnim() { Finalize(); }
//
//void DrawAnim::Initialize() { 
//	LoadPathLoop();
//	LoadPathNotLoop();
//}
//
////ファイルパスを読み込む（ループ）
//void DrawAnim::LoadPathLoop() {
//	for (int i = ANIM_LOOP_ROW_START; i < ANIM_LOOP_ROW_END; ++i) {
//		std::vector<std::string> m_anim_loop;
//		//ファイルパス情報のみ格納
//		m_anim_loop.emplace_back(m_anim_path[i][1]);
//	}
//}
//
////ファイルパスを読み込む（notループ）
//void DrawAnim::LoadPathNotLoop() {
//	for (int i = ANIM_NOTLOOP_ROW_START; i < ANIM_NOTLOOP_ROW_END; ++i) {
//		std::vector<std::string> m_anim_notLoop;
//		//ファイルパス情報のみ格納
//		m_anim_notLoop.emplace_back(m_anim_path[i][4]);
//	}
//}
//
//
//void DrawAnim::Finalize() {
//	m_anim_path.clear();
//}