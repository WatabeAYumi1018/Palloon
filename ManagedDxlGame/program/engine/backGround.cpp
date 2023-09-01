#include "../engine/BackGround.h"
#include "../game/ScenePlay/PlayCamera.h"


void BackGround::Initialize()
{
	m_back_hdl = LoadGraph("graphics/backSky.jpg");
}

void BackGround::Draw(const PlayCamera* camera) 
{
	tnl::Vector3 draw_pos =
		m_pos - (camera->GetTarget()*m_scroll_speed) + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0f, 0, m_back_hdl, true);
}
	//Movie(camera);

//void BackGround::Movie(const PlayCamera* camera){
//
//	tnl::Vector3 draw_pos =
//		m_pos - camera->GetTarget() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
//
//	//動画の画像サイズを取得
//	int size_x = 0;
//	int size_y = 0;
//
//	GetGraphSize(m_back_hdl, &size_x, &size_y);
//
//	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
//	m_screen_handle = MakeScreen(size_x, size_y, TRUE);
//
//	//動画の再生開始
//	PlayMovieToGraph(m_back_hdl, DX_PLAYTYPE_LOOP);
//
//	//透過する方法として明るさクリップフィルターがある
//	//「一定以上/以下の明るさの色をすべて塗りつぶす」という力強い処理ができる
//	//FilterType以降の引数...比較方法（LESS/GREATER),比較する値,該当する色を塗りつぶすか,
//	//塗りつぶした後の色,塗りつぶした後の色の不透明度(透明にしたいので0)
//	GraphFilterBlt(m_back_hdl, m_screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, m_bright_border, true, GetColor(0, 0, 0), 0);
//
//	//透過処理された画像を画面いっぱいに描画
//	DrawExtendGraph(draw_pos.x, draw_pos.y, draw_pos.x+DXE_WINDOW_WIDTH, draw_pos.y+DXE_WINDOW_WIDTH, m_screen_handle, TRUE);
//	//DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0f, 0, m_screen_handle, true);
//}

