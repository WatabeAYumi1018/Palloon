#include "Character.h"

Character::Character(Vector3 pos, int hp, int attack, float jump_time, Vector3 jump_velocity) :
	m_pos(pos), m_hp(hp), m_attack(attack), m_jump_time(jump_time), m_jump_velocity(jump_velocity)
{

}

Character::~Character() {}


void Character::Initialize() {}

void Character::Update(float delta_time) {}

void Character::Draw(float delta_time) {}

void Character::Finalize() {}