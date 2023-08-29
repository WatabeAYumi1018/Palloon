#pragma once
#include "GameEngine.h"
#include "GameObject.h"

//今、だいぶ荒れてます

class UI:public GameObject{

public:
	UI();
	virtual ~UI();
	

public:
	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time, const PlayCamera* camera) override;
	void Finalize() override;
};

//UIの処理一括を行うクラス