#include "backGround.h"

backGround::backGround() {
	Initialize();
}

backGround::~backGround() { Finalize(); }

void backGround::Initialize() {

	//カメラ設定
	m_camera = new Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	
	//{0,0,0}→エラー
	// x：値大→左へスライド、値小→右へスライド
	//y：値大→上へスライド（俯瞰して見る感じ）、値小→下へスライド（見上げる感じ）
	//z：値大→奥　※正、負どちらも値が大きくなるほど奥に行く
	m_camera->pos_ = { 0,0,100 };
	 
	//メッシュの周りを回転しながら映すようなカメラ
	//{0,0,0}→二次元での正面
	//x:右周りの回転移動？（左から画像を覗き見るような感じ）
	//ｙ:上周りの回転移動？（1000だと下から見上げるような感じ）
	//z:謎（変化なさそうだけど、-1000だと描画みえなくなる）
	m_camera->target_ = { 0,0,0 };

	//メッシュに背景画像を設定
	 
	//x:横幅,y:縦幅,z:奥行き(プレーンだと無効？よく分からん)
	m_mesh = Mesh::CreatePlaneMV({1000,1000,0});
	m_mesh->setTexture(Texture::CreateFromFile("graphics/PT_Skybox_Texture_01.png"));
	
	//x,y:基本０でOK
	//Z：奥行（正の値大→手前、負の値大→奥）
	m_mesh->pos_= { 0,0,-100 };
}

void backGround::Update(float delta_time) {
	m_mesh->render(m_camera);
	m_camera->update();
}


void backGround::Finalize() {
	if (m_mesh) {
		delete m_mesh;
		m_mesh = nullptr;
	}
	if (m_camera) {
		delete m_camera;
		m_camera = nullptr;
	}
}
