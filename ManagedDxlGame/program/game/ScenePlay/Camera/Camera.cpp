#include "Camera.h"
#include "../Character/Player/Player.h"
#include "../Map/Map.h"

void Camera::Update(float delta_time, Player* player, Map* map)
{
	Scroll(player, map);
	MoveRange(player, map);
}

void Camera::MoveRange(Player* player, Map* map)
{
	const float halfWidth = DXE_WINDOW_WIDTH >> 1;
	const float halfHeight = DXE_WINDOW_HEIGHT >> 1;
	const float maxX = map->MAP_CHIP_SIZE * map->GetMapChipX() - halfWidth;
	const float maxY = map->MAP_CHIP_SIZE * map->GetMapChipY() - halfHeight;

	//clamp関数で範囲内に収める。clamp(値, 最小値, 最大値)
	m_target.x = std::clamp(m_target.x, halfWidth, maxX);
	m_target.y = std::clamp(m_target.y, halfHeight, maxY);
}

//★背景とチップのスクロール値調節すること
void Camera::Scroll(Player* player, Map* map)
{
	if (!m_is_active)
	{
		if (player->GetPos().x > DXE_WINDOW_WIDTH >> 1 ||
			player->GetPos().y > DXE_WINDOW_HEIGHT >> 1)
		{
			m_target = player->GetPos();
			m_is_active = true;
		}
	}
	else
	{
		m_target += (player->GetPos() - m_target) * 0.1f;

		if ((player->GetPos().x <= DXE_WINDOW_WIDTH >> 1 &&
			player->GetPos().y <= DXE_WINDOW_HEIGHT >> 1))
		{
			m_is_active = false;
		}
	}
}
