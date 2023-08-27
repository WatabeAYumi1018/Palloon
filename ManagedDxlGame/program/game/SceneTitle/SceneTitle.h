#pragma once
#include "../../engine/sceneBase.h"

class GameObject;

class SceneTitle : public SceneBase {

public:
	void Update(float delta_time) override;
	void Draw(float delta_time) override;

private:
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqIdle);
	bool SeqIdle(float delta_time);
	void TitlePlayMovie();


	//タイトル画面のグラフィック 
	int title_back_gif = 0;

	//スクリーン(フィルター処理した画像を保存する用)ハンドル
	int screen_handle = 0;

	//明るさクリップフィルターに使用する閾値
	int bright_border = 150;
};
