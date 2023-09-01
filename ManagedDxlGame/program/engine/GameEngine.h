#pragma once
#include "../dxlib_ext/dxlib_ext.h"

enum class eAttackType
{
	eAttack_Push,
	eAttack_Fire,
	eAttack_Beam,
	eAttack_Max
};

enum class eCharaType
{
	Player,
	Slim,
	Plant,
	Bird,
	Masician,
	Fairy,
	Boss,
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

enum class eEnemyType
{
	None,
	Slim,
	Plant,
	Bird,
	Masician,
	Fairy,
	Boss,
	Max
};

struct sEnemyData 
{
	tnl::Vector3 s_pos;
	eEnemyType s_type;
};

