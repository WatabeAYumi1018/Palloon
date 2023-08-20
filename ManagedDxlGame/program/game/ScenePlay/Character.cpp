#include "Character.h"
#include "CollisionCalc.h"

Character::Character(tnl::Vector3 pos,int size, int hp, int attack, float jump_time, tnl::Vector3 jump_velocity) :
	m_pos(pos),m_size(size), m_hp(hp), m_attack(attack), m_jump_time(jump_time), m_jump_velocity(jump_velocity)
{
	Initialize();
}

Character::~Character() { Finalize(); }

void Character::Initialize() {m_collision = new CollisionCalc();}

void Character::Update(float delta_time) {
	//m_collision->CollisionCalculate(chara,mapChip,range);
}

void Character::Draw(float delta_time) {}

void Character::Finalize() { delete m_collision; }