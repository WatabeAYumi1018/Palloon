#pragma once
#include "../../engine/sceneBase.h"

class PlayCamera;
class BackGround;
class MapManager;
class UI;
class CollisionCalc;
class GameObject;
class Character;

class ScenePlay : public SceneBase {

public:
	ScenePlay();
	virtual ~ScenePlay();

	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;

	//-----メンバ変数-----//
	PlayCamera *camera=nullptr;
	BackGround *back_ground=nullptr;
	MapManager *map_chip_manager=nullptr;
	UI *ui=nullptr;
	CollisionCalc *collision_calc=nullptr;
	Character *player =nullptr;

private:
	std::vector<GameObject*> gameObjects;
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqIdle);
	bool SeqIdle(float delta_time);

	//遷移後、back,Map,UI,Player,Enemyなどを描画する
	//現在のシーンで描画するグラフィックを変える
	int graph_hdl = 0;
};