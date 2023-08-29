#include "UI.h"

UI::UI() : GameObject(m_pos) {Initialize();}

UI::~UI() { Finalize(); }

void UI::Initialize() {

	//PlayScene‚ÌUI‚ðÝ’è----------------------------------------------


}

void UI::Update(float delta_time) {
	/*m_mesh_hp->render(m_camera);
	m_camera->update();*/
}

void UI::Draw(float delta_time, const PlayCamera* camera) {
	//m_mesh_hp->render(m_camera);
	//m_camera->update();
}

void UI::Finalize() {
	/*if (m_mesh_hp) {
		delete m_mesh_hp;
		m_mesh_hp = nullptr;
	}
	if (m_mesh_face) {
		delete m_mesh_face;
		m_mesh_face = nullptr;
	}
	if (m_mesh_ability_normal) {
		delete m_mesh_ability_normal;
		m_mesh_ability_normal = nullptr;
	}
	if (m_camera) {
		delete m_camera;
		m_camera = nullptr;
	}*/
}
