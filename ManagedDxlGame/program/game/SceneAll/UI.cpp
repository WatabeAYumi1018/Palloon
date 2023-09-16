#include "../../game/ScenePlay/Character/Player/Player.h"
#include "../game/SceneAll/UI.h"

UI::UI(Player* player) : GameObject(tnl::Vector3{ 10,500,0 }), m_player(player)
{
	Initialize();
}

void UI::Initialize()
{
	m_ui_hdl = LoadGraph("graphics/UI/HPUI.png");
	m_hp_hdl = LoadGraph("graphics/balloon/balloon_red001.png");
}

void UI::Draw(float delta_time, const Camera* camera)
{
	DrawExtendGraph(m_pos.x, m_pos.y, m_pos.x + m_extend_x, m_pos.y + m_extend_y, m_ui_hdl, true);
	HpBalloons();
}

void UI::HpBalloons()
{
	if (!m_player)
	{
		return;
	}

	int current_hp = m_player->GetHp();

	for (int i = 0; i <current_hp; i++)
	{
		DrawExtendGraph(130 + (i * 65), 560, 210 + (i * 65),640, m_hp_hdl, TRUE);
	}
}