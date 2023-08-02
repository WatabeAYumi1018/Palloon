#pragma once
#include "Object.h"

class Item :public Object {

public:
	Item(Vector3 m_pos, Vector3 m_velocity);
	~Item();

	//-----�����o�ϐ�-----//
private:
	int m_item_type;			//�A�C�e���^�C�v

	//-----�����o�֐�-----//
public:
	void Initialize();
	void Update(float delta_time);
	void Draw();
	void Finalize();
};