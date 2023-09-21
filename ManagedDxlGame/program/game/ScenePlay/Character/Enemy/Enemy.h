#pragma once
#include "../../../../library/tnl_sequence.h"
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

//主に敵のAIを管理するクラス

class Collision;
class Camera;
class Player;
class Map;

class Enemy :public Character
{
public:

	Enemy(const sEnemyData& data, const sEnemyInfo& info,Player* player, Map*map,Collision * collision, Camera* camera);
	virtual ~Enemy() {}

protected:

	//-----メンバ変数-----//
	int m_type_id;											/*敵のタイプID*/
	
	std::string m_type;										/*敵のタイプ*/
	std::string m_color;									/*敵の色*/
	
	bool m_is_dirction_right = true;						/*右向き*/

	bool m_is_active = true;								/*攻撃中*/

	Player* m_player = nullptr;		
	Map* m_map = nullptr;
	Collision * m_collision = nullptr;
	Camera* m_camera = nullptr;

	//-----メンバ関数-----//
	float DistanceCalc();						//プレイヤーとの距離計算
	
public:
	virtual void Update(const float delta_time)  {}	//更新処理
	virtual void Draw(const float delta_time, const Camera* camera)  {}		//描画処理d 

	bool CanMoveRight();
	bool CanMoveLeft();

	//-----Setter&Getter-----//
	int GetTypeID() const { return m_type_id; }

	bool GetIsActive() const { return m_is_active; }
	void SetIsActive(const bool is_active) { m_is_active = is_active; }
};
