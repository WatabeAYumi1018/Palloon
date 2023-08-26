#pragma once
#include "Object.h"

class Item :public Object {

public:
	Item(tnl::Vector3 m_pos, tnl::Vector3 m_velocity);
	virtual ~Item();

	//-----メンバ変数-----//
private:
	int m_item_type;			//アイテムタイプ

	//-----メンバ関数-----//
public:
	void Initialize();
	void Update(float delta_time);
	void Draw();
	void Finalize();
};