#pragma once

class SceneBase;

class SceneManager 
{
public:
	//-----static関数-----//
	static SceneManager* GetInstance(SceneBase* start_scene = nullptr);
	static void Finalize();

	//-----メンバ関数-----//
	void ChangeScene(SceneBase* next_scene, float trans_time = 0.5f);
	void Update(float delta_time);

private:
	//-----singleton-----//
	SceneManager(SceneBase* start_scene);

	//-----メンバ変数-----//
	float trans_time_ = 0.5f;
	int tansition_graph_hdl_ = 0;
	SceneBase* now_scene_ = nullptr;
	SceneBase* next_scene_ = nullptr;
	
	//-----シーケンス-----//
	tnl::Sequence<SceneManager> sequence_ = tnl::Sequence<SceneManager>(this, &SceneManager::SeqTransIn);
	
	//-----シーケンス関数-----//
	bool SeqTransIn(const float delta_time);
	bool SeqTransOut(const float delta_time);
	bool SeqRunScene(const float delta_time);
};