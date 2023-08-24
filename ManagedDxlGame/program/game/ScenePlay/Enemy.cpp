#include "Enemy.h"

Enemy::Enemy() : Character(m_pos,m_size,m_hp,m_jump_time,m_jump_velocity){}
Enemy::~Enemy(){}

void Enemy::Initialize() {}
void Enemy::Update(float delta_time) {}
void Enemy::Draw(float delta_time) {}
void Enemy::Finalize() {}