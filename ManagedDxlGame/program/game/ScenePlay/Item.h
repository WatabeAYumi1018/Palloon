#pragma once
#include "../../engine/GameObject.h"

class Item :public GameObject
{
public:
	Item(tnl::Vector3 m_pos);
	virtual ~Item();

private:
	//-----メンバ変数-----//
	int m_item_type;			//アイテムタイプ

	//-----メンバ関数-----//
	void Initialize() override;
	void Update(float delta_time) override;
	void Draw(float delta_time, const PlayCamera* camera) override;
	void Finalize() override;
};