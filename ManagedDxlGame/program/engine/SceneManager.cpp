#include "../dxlib_ext/dxlib_ext.h"
#include "SceneManager.h"
#include "../engine/sceneBase.h"

//コンストラクタの引数をGameManagerの引数に初期化
SceneManager::SceneManager(SceneBase* start_scene) : now_scene_(start_scene) 
{
	//トランジション用のグラフィックを読み込む(黒背景)
	tansition_graph_hdl_ = LoadGraph("graphics/black.bmp");
}

SceneManager* SceneManager::GetInstance(SceneBase* start_scene)
{
	//シングルトン
	static SceneManager* instance = nullptr;
	
	if (!instance) 
	{
		instance = new SceneManager(start_scene);
	}
	return instance;
}

//現在のシーンの更新と描画
void SceneManager::Update(float delta_time)
{
	if (now_scene_) 
	{
		now_scene_->Update(delta_time);
		now_scene_->Draw(delta_time);
	}
	sequence_.update(delta_time);
}

//シーンの切り替え
void SceneManager::ChangeScene(SceneBase* next_scene, float trans_time) 
{
	next_scene_ = next_scene;
	trans_time_ = trans_time;
	//トランジションの開始
	sequence_.change(&SceneManager::SeqTransOut);
}

//シーンの切り替え（フェードイン）
bool SceneManager::SeqTransIn(const float delta_time)
{
	//少しずつ透明にしていく
	int alpha = 255 - (sequence_.getProgressTime() / trans_time_ * 255.0f);
	if (alpha <= 0) 
	{
		sequence_.change(&SceneManager::SeqRunScene);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	return true;
}

//シーンの切り替え（フェードアウト）
bool SceneManager::SeqTransOut(const float delta_time)
{
	int alpha = (sequence_.getProgressTime() / trans_time_ * 255.0f);

	if (alpha >= 255)
	{
		sequence_.change(&SceneManager::SeqTransIn);
		now_scene_->Finalize();		//現在のシーンの終了処理
		delete now_scene_;			//現在のシーン削除
		now_scene_ = nullptr;
		now_scene_ = next_scene_;	//次のシーンを現在のシーンに
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	return true;
}

//シーンの実行
bool SceneManager::SeqRunScene(const float delta_time) 
{
	return true;
}

void SceneManager::Finalize() 
{
	delete GetInstance();
}


//使用方法
//SceneManager::GetInstance( new SceneTitle() );　最初のシーンを設定して
//SceneManager::GetInstance()->Update();　毎フレーム呼び出す