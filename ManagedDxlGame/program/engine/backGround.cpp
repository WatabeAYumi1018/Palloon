#include "backGround.h"

backGround::backGround() {
	//back_hdl=LoadGraph("graphics/PT_Skybox_Texture_01.png");
	Initialize();
}

backGround::~backGround() { Finalize(); }

void backGround::Initialize() {
	m_mesh = Mesh::CreatePlane({ 10,10,0 });
	m_mesh->setTexture(Texture::CreateFromFile("graphics/PT_Skybox_Texture_01.png"));
}

void backGround::Update(float delta_time) {
	Draw();
}

void backGround::Draw() {
	if(m_mesh) {
		DrawGraph(m_pos.x,m_pos.y, back_hdl,true);
	}
}

void backGround::Finalize() {
	if (m_mesh) {
		delete this;
		m_mesh = nullptr;
	}
}
