#include "UI.h"

UI::UI() : GameObject(tnl::Vector3{ 10,500,0 })
{
	Initialize();
}

void UI::Initialize()
{
	m_extend_x = 500;
	m_extend_y = 200;
	m_ui_hdl = LoadGraph("graphics/UI/HPUI.png");
}

void UI::Draw(float delta_time, const Camera* camera)
{
	DrawExtendGraph(m_pos.x, m_pos.y, m_pos.x+ m_extend_x, m_pos.y+ m_extend_y,m_ui_hdl, true);
}
