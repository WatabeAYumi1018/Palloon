
#include "Enemy.h"

Enemy::Enemy(Vector3 pos) : Character(pos,m_hp,m_attack,m_jump){}
Enemy::~Enemy(){}

void Enemy::Initialize() {}
void Enemy::Update(float delta_time) {}
void Enemy::Draw() {}
void Enemy::Finalize() {}