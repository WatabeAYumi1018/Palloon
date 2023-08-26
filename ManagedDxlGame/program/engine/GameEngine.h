#pragma once
#include "../dxlib_ext/dxlib_ext.h"

enum class eAttackType {
	eAttack_Push,
	eAttack_Fire,
	eAttack_Beam,
	eAttack_Max
};

enum class eCollisionType {
	None,
	Box,
	Line,
	Max
};

enum class eCharaType {
	Player,
	Slim,
	Plant,
	Bird,
	Masician,
	Fairy,
	Boss,
	Max
};

struct sCollisionInfo {
	tnl::Vector3 pos;
	int size;
	eCollisionType type;
};