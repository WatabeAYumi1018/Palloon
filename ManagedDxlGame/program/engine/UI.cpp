#include "UI.h"

void UI::Initialize() {
	m_ui_hdl = LoadGraph("graphics/UI/HPUI.png");
}

void UI::Draw(float delta_time) {DrawExtendGraph(m_pos.x, m_pos.y, m_pos.x+500, m_pos.y+200,m_ui_hdl, true);}
