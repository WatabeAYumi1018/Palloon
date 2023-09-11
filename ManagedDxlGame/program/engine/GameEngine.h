#pragma once
#include "../dxlib_ext/dxlib_ext.h"

enum class ePlayerAction
{
	Idle_right,
	Idle_left,
	Move_right,
	Move_left,
	Dash_right,
	Dash_left,
	Jump_right,
	Jump_left,
	Stamp_right,
	Stamp_left,
	Roll_right,
	Roll_left,
	Fire_right,
	Fire_left,
	Beam_right,
	Beam_left,
	Max
};

enum class eEffectPlayerType
{
	None,
	Fire,
	Beam,
	Max
};

enum class eCollisionType
{
	None,
	Box,
	Line,
	Max
};

struct sCollisionInfo
{
	tnl::Vector3 s_pos;
	int s_size;
	eCollisionType s_type;
};

struct sEnemyData 
{
	int s_type_id;
	tnl::Vector3 s_pos;
};

struct sEnemyInfo
{
	int s_id;
	std::string s_name;
	std::string s_color;
	int s_hp;
	int s_size;
};

enum class eEffectCollisionType
{
	None,
	Box,
	Circle,
	Line,
	Max
};

