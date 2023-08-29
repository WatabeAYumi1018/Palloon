#include "../../dxlib_ext/dxlib_ext.h"
#include "ScenePlay.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "../../engine/BackGround.h"
#include "MapManager.h"
#include "CollisionCalc.h"
#include "Player.h"
#include "Enemy.h"
#include "../../engine/UI.h"
#include "PlayCamera.h"

ScenePlay::ScenePlay(){Initialize();}

ScenePlay::~ScenePlay() {Finalize();}

void ScenePlay::Initialize() {
	//背景の初期化と描画
	camera=new PlayCamera();
	back_ground = new BackGround();
	map_chip_manager = new MapManager();
	ui = new UI();
	collision_calc = new CollisionCalc();
	player = new Player();

	//プレイシーンに必要なObjectを読み込み、初期化する
	gameObjects.emplace_back(player);
	gameObjects.emplace_back(new Enemy());
	//gameObjects.emplace_back(new UI());
}

void ScenePlay::Update(float delta_time) {
	collision_calc->CollisionCalculate(player, map_chip_manager,3);	
	map_chip_manager->LoadMapCollision(camera);
	//camera->Update(delta_time);
	camera->target += (player->GetPos() - camera->target) * 0.05f;

	
	for (auto obj : gameObjects) {obj->Update(delta_time);}
	
	sequence_.update(delta_time);
}

void ScenePlay::Draw(float delta_time) {
	back_ground->Draw(camera);
	map_chip_manager->Draw(camera);
	for (auto obj : gameObjects) {obj->Draw(delta_time, camera);}
	ui->Draw(delta_time);
}

bool ScenePlay::SeqIdle(float delta_time) {
	//if (sequence_.isStart()) {
	//	graph_hdl = LoadGraph("graphics/PT_Skybox_Texture_01.png");
	//}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto scene = SceneManager::GetInstance();
		scene->ChangeScene(new SceneTitle());
	}
	return true;
}

void ScenePlay::Finalize() {
	for (auto obj : gameObjects) {delete obj;}
}