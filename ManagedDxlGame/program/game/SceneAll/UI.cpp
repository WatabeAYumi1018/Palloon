#include "../../game/ScenePlay/Character/Player/Player.h"
#include "../game/SceneAll/UI.h"

UI::UI(Player* player) : GameObject(tnl::Vector3{ 10,500,0 }), m_player(player)
{
	Initialize();
}

void UI::Initialize()
{
	m_hp_hdl = LoadGraph("graphics/balloon/balloon_red001.png");
}

void UI::Draw(float delta_time, const Camera* camera)
{
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
		DrawExtendGraph(0 + (i * 65), 650, 70 + (i * 65),720, m_hp_hdl, TRUE);
	}
}