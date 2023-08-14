#include "DrawAnim.h"

DrawAnim::DrawAnim() {
	//csvファイルから情報を読み込む
	m_csv_anim = tnl::LoadCsv<int>(csv_anim);
	Initialize();
}

DrawAnim::~DrawAnim() { Finalize(); }

void DrawAnim::Initialize() {LoadFilePath();}

//ファイルパスを読み込み、enum管理
void DrawAnim::LoadFilePath() {
	//
	//-----ファイルパスの読み込み-----//
}

void DrawAnim::Finalize() {m_csv_anim.clear();}