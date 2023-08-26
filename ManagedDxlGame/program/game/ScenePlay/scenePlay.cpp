#include "../../dxlib_ext/dxlib_ext.h"
#include "ScenePlay.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "Player.h"

ScenePlay::ScenePlay() {
	//プレイシーンに必要なObjectを読み込み、初期化する
	gameObjects.emplace_back(new Player());
	gameObjects.emplace_back(new UI());
	gameObjects.emplace_back(new Player());

}

void ScenePlay::Update(float delta_time) {
	sequence_.update(delta_time);
}

void ScenePlay::Draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, test_back_ground_gfx_, true);
}

bool ScenePlay::SeqIdle(float delta_time) {
	if (sequence_.isStart()) {
		test_back_ground_gfx_ = LoadGraph("graphics/back_ground.jpg");
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new SceneTitle());
	}

	return true;

}