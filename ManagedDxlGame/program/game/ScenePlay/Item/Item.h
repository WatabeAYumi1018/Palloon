#pragma once
#include "../../SceneAll/GameObject.h"

class Item :public GameObject
{
public:
	Item(tnl::Vector3 m_pos);
	virtual ~Item();

private:
	//-----メンバ変数-----//
	int m_item_type;			//アイテムタイプ


};