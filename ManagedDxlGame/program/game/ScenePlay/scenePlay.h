#pragma once
#include "../../engine/sceneBase.h"

class PlayCamera;
class BackGround;
class MapManager;
class UI;
class CollisionCalc;
class GameObject;
class Character;

class ScenePlay : public SceneBase 
{
public:
	ScenePlay();
	virtual ~ScenePlay();

	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;

	//-----メンバ変数-----//
	PlayCamera *m_camera=nullptr;
	BackGround *m_back_ground=nullptr;
	MapManager *m_map_chip_manager=nullptr;
	UI *m_ui=nullptr;
	CollisionCalc *m_collision_calc=nullptr;
	Character *m_player =nullptr;

private:
	std::vector<GameObject*> gameObjects;
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqIdle);
	bool SeqIdle(float delta_time);

	//遷移後、back,Map,UI,Player,Enemyなどを描画する
	//現在のシーンで描画するグラフィックを変える
	int graph_hdl = 0;
};