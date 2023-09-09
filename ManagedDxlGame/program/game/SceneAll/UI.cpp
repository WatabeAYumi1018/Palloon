#include "../../game/ScenePlay/Character/Player/Player.h"
#include "../game/SceneAll/UI.h"

UI::UI() : GameObject(tnl::Vector3{ 10,500,0 })
{
	Initialize();
}

void UI::Initialize()
{
	m_ui_hdl = LoadGraph("graphics/UI/HPUI.png");
	m_hp_hdl = LoadGraph("graphics/balloon/balloon_red.png");
}

void UI::Draw(float delta_time, const Camera* camera)
{
	DrawExtendGraph(m_pos.x, m_pos.y, m_pos.x + m_extend_x, m_pos.y + m_extend_y, m_ui_hdl, true);
	HpBalloons();
}

//ï`âÊèáÇÃÇ±Ç∆ÇçlÇ¶ÇÈÇ∆Ç±Ç±Ç≈ëÄçÏÇ∑Ç◊Ç´ÅH
void UI::HpBalloons()
{
	for (int i = 0; i < m_player->GetMaxHP(); i++)		
	{
		DrawExtendGraph(80 + (i * 65), 530, 250 + (i * 65),680, m_hp_hdl, TRUE);
	}
	

}