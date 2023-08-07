#pragma once
#include "../../engine/GameEngine.h"
#include "Player.h"

class Object;

//プレイヤー追従カメラ
class PlayCamera :public Object{
public:
	PlayCamera(tnl::Vector3 pos,Player* player);
	~PlayCamera();
private:
	//-----メンバ変数-----//
	tnl::Vector3 m_up;			//上方向
	tnl::Vector3 m_right;		//右方向
	tnl::Vector3 m_front;		//前方向
	tnl::Vector3 m_move;		//移動量
	float m_height;				//高さ
	float m_speed;				//移動速度
	Player* m_player;			//プレイヤー

public:
	//-----メンバ関数-----//
	void Update(float delta_time);	//座標更新

	//-----Setter,Getter-----//
	void SetMove(tnl::Vector3 move) { m_move = move; }
	tnl::Vector3 GetMove () { return m_move; }
	void SetHeight(float height) { m_height = height; }
	float GetHeight () { return m_height; }
	void SetSpeed(float speed) { m_speed = speed; }
	float GetSpeed () { return m_speed; }
	void SetUp(tnl::Vector3 up) { m_up = up; }
	tnl::Vector3 GetUp () { return m_up; }
	void SetRight(tnl::Vector3 right) { m_right = right; }
	tnl::Vector3 GetRight () { return m_right; }
	void SetFront(tnl::Vector3 front) { m_front = front; }
	tnl::Vector3 GetFront () { return m_front; }
};