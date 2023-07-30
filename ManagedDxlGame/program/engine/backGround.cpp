#include "backGround.h"

backGround::backGround() {
	//back_hdl=LoadGraph("graphics/PT_Skybox_Texture_01.png");
	Initialize();
}

backGround::~backGround() { Finalize(); }

void backGround::Initialize() {

	//ƒJƒƒ‰Ý’è
	m_camera = new Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	m_camera->pos_ = { 100,100,0 };
//	m_camera->target_ = { 0,0,0 };

	//ƒƒbƒVƒ…‚É”wŒi‰æ‘œ‚ðÝ’è
	m_mesh = Mesh::CreatePlaneMV({1000,1000,0});
	m_mesh->setTexture(Texture::CreateFromFile("graphics/PT_Skybox_Texture_01.png"));
	m_mesh->pos_= { -1000,0,500 };
}

void backGround::Update(float delta_time) {
	m_mesh->render(m_camera);
	m_camera->update();
//	Draw();
}
//
//void backGround::Draw() {
//	if(m_mesh) {
//		DrawGraph(m_pos.x,m_pos.y, back_hdl,true);
//	}
//}

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
