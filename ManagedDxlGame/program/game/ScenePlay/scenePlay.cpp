#include "../../dxlib_ext/dxlib_ext.h"
#include "ScenePlay.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "Player.h"
#include "Enemy.h"
#include "../../engine/UI.h"

ScenePlay::ScenePlay() {
	//背景の初期化と描画
	back_ground.Initialize();
	back_ground.Draw();
	Initialize();
}

void ScenePlay::Initialize() {
	//プレイシーンに必要なObjectを読み込み、初期化する
	gameObjects.emplace_back(new Player());
	gameObjects.emplace_back(new Enemy());
	gameObjects.emplace_back(new UI());

}

void ScenePlay::Update(float delta_time) {
	for (auto obj : gameObjects) {obj->Update(delta_time);}
	sequence_.update(delta_time);
}

void ScenePlay::Draw(float delta_time) {
	for (auto obj : gameObjects) {obj->Draw(delta_time);}
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

void ScenePlay::Finalize() {
	for (auto obj : gameObjects) {delete obj;}
}