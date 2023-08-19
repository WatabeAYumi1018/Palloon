#pragma once
#include "../dxlib_ext/dxlib_ext.h"

enum class eAttackType {
	eAttack_Push,
	eAttack_Fire,
	eAttack_Beam,
	eAttack_Max
};

enum class eCollisionType {
	eCollision_None,
	eCollision_Box,
	eCollision_Line,
	eCollision_Max
};

enum class eCharacterType {
	eCharacter_Player,
	eCharacter_Slim,
	eCharacter_plant,
	eCharacter_bird,
	eCharacter_Max
};