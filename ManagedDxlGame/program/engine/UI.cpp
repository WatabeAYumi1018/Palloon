#include "UI.h"

UI::UI(tnl::Vector3 m_pos) : m_pos(m_pos) {Initialize();}

UI::~UI() { Finalize(); }

void UI::Initialize() {
	//-----カメラ設定-----//
	m_camera = new dxe::Camera(148, 307);
	m_camera->pos_ = { 0,0,-100 };
	m_camera->target_ = { 0,0,0 };

	//-----メッシュ設定-----//

	//PlaySceneのUIを設定----------------------------------------------
	//HPバー
	m_mesh_hp = dxe::Mesh::CreatePlaneMV({ 40,30,0 });
	m_mesh_hp->setTexture(dxe::Texture::CreateFromFile("graphics/UI/Button_Midl.png"));
	m_mesh_hp->pos_ = { 0,0,100 };
	//フェイスバー
	m_mesh_face = dxe::Mesh::CreatePlaneMV({ 20,20,0 });
	m_mesh_face->setTexture(dxe::Texture::CreateFromFile("graphics/UI/player_face.png"));
	m_mesh_face->pos_ = { 0,0,100 };
	
	//能力バー----------
	//①ノーマル
	m_mesh_ability_normal = dxe::Mesh::CreatePlaneMV({ 20,20,0 });
	m_mesh_ability_normal->setTexture(dxe::Texture::CreateFromFile("graphics/UI/Button_Midl.png"));
	m_mesh_ability_normal->pos_ = { 0,0,100 };
	//②炎
	m_mesh_ability_fire = dxe::Mesh::CreatePlaneMV({ 20,20,0 });
	m_mesh_ability_fire->setTexture(dxe::Texture::CreateFromFile("graphics/UI/Button_Midl.png"));
	m_mesh_ability_fire->pos_ = { 0,0,100 };
	//③ビーム
	m_mesh_ability_beam = dxe::Mesh::CreatePlaneMV({ 20,20,0 });
	m_mesh_ability_beam->setTexture(dxe::Texture::CreateFromFile("graphics/UI/Button_Midl.png"));
	m_mesh_ability_beam->pos_ = { 0,0,100 };
}

void UI::Update(float delta_time) {
	m_mesh_hp->render(m_camera);
	m_camera->update();
}

void UI::Finalize() {
	if (m_mesh_hp) {
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
	}
}
