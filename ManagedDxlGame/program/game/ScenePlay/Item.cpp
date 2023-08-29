#include "Item.h"


Item::Item(tnl::Vector3 m_pos) :GameObject(m_pos) {}

Item::~Item() { Finalize(); }


void Item::Initialize() {}

void Item::Update(float delta_time) {}

void Item::Draw(float delta_time, const PlayCamera* camera) {}

void Item::Finalize() {}
