#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneTitle.h"
#include "../ScenePlay/scenePlay.h"
#include "../../engine/SceneManager.h"

void SceneTitle::Update(float delta_time) {
	sequence_.update(delta_time);
}

void SceneTitle::Draw() {
	title_back_gif = LoadGraph("gif/clearCracker.mp4");
}

// ムービーを再生状態にします
bool SceneTitle::SeqIdle(float delta_time) {
	if (sequence_.isStart()) {
		TitlePlayMovie();
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new ScenePlay());
	}
	return true;
}

void SceneTitle::TitlePlayMovie() {
	
	int size_x = 0;
	int size_y = 0;

	GetGraphSize(title_back_gif, &size_x, &size_y);
	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
	screen_handle = MakeScreen(size_x, size_y, TRUE);
	//動画の再生開始
	PlayMovieToGraph(title_back_gif, DX_PLAYTYPE_LOOP);
	//透過処理
	GraphFilterBlt(title_back_gif, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, true, GetColor(0, 0, 0), 0);
	//透過処理された画像を画面いっぱいに描画
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);
}