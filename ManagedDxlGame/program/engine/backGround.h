#pragma once
#include "GameEngine.h"

class backGround 
	//:gameManager
{
public:
	backGround();
	~backGround();
	
private:
	//-----メンバ変数-----//
	int back_hdl=0;				//背景画像ハンドル
	Vector3 m_pos = {0,0,500};	//座標（後々多態性で削除。とりあえず）
	Mesh* m_mesh = nullptr;		//メッシュ
	Camera* m_camera = nullptr;


public:
	//-----メンバ関数-----//
	void Initialize();
	void Update(float delta_time);
	//void Draw();
	void Finalize();
};
