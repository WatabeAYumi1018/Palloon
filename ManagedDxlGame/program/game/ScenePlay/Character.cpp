#include "Character.h"

Character::Character(Vector3 pos, int hp, int attack, Vector3 jump) :
	m_pos(pos), m_hp(hp), m_attack(attack), m_jump(jump) 
{

}

Character::~Character() {}


void Character::Initialize() {}

void Character::Update(float delta_time) {}

void Character::Draw() {}

void Character::Finalize() {}