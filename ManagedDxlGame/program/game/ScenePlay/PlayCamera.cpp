#include "PlayCamera.h"
#include "Player.h"
#include "MapManager.h"

void PlayCamera::Update(float delta_time) {

	if (m_player->GetPos().x > DXE_WINDOW_WIDTH / 2) {

		if (!is_active) {

			tnl::Vector3 newPos = m_player->GetPos();
			newPos.x = target.x;
			m_player->SetPos(newPos);
			is_active = true;
		}
	}
	if (m_player->GetPos().y > DXE_WINDOW_HEIGHT / 2) {

		if (!is_active) {

			tnl::Vector3 newPos = m_player->GetPos();
			newPos.x = target.x;
			m_player->SetPos(newPos);
			is_active = true;
		}
	}

	if (is_active) {
		target += (m_player->GetPos() - target) * 0.1f;
	}

	if (target.x < DXE_WINDOW_WIDTH / 2) {
		target.x = DXE_WINDOW_WIDTH / 2;
	}
	if (target.x > m_map_manager->MAP_CHIP_SIZE * m_map_manager->GetMapChip().size() - DXE_WINDOW_WIDTH / 2) {
		//target.x = m_map_manager->MAP_CHIP_SIZE * m_map_manager->GetMapChip().size() - DXE_WINDOW_WIDTH / 2;
	}
	if (target.y < DXE_WINDOW_HEIGHT / 2) {
		target.y = DXE_WINDOW_HEIGHT / 2;
	}
	if (target.y > m_map_manager->MAP_CHIP_SIZE * 25 - DXE_WINDOW_HEIGHT / 2) {
		target.y = m_map_manager->MAP_CHIP_SIZE * 25 - DXE_WINDOW_HEIGHT / 2;
	}


}
