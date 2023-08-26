#pragma once
#include "../../engine/sceneBase.h"

class ScenePlay : public SceneBase {

public:
	ScenePlay();
	virtual ~ScenePlay();
	//-----メンバ関数-----//
	void Update(float delta_time) override;
	void Draw() override;

private:
	std::vector<GameObject*> gameObjects;
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqIdle);
	bool SeqIdle(float delta_time);

	//遷移後、back,Map,UI,Player,Enemyなどを描画する
	//現在のシーンで描画するグラフィックを変える
	int test_back_ground_gfx_ = 0;

};