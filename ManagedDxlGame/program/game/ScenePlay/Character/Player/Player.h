#pragma once
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

class Camera;
class Map;
class Collision;
class Wind;
class Logo;

//プレイヤークラス

class Player :public Character
{
public:

	Player(const tnl::Vector3& initialPos, Collision* collision, Map* map,Wind* wind,Logo* logo);
	virtual ~Player() {}

private:

	//-----定数-----//
	static constexpr int SIZE = 35;						/*サイズ*/
	static constexpr int MAX_HP = 5;					/*HP*/

	static constexpr float VELOCITY_X = 100;			/*移動速度（pix / fps)*/
	static constexpr float VELOCITY_Y = 500;

	const float DASH_THRESHOLD = 0.8f;					/*ダッシュのしきい値*/

	const float HOVER_FIRST_FORCE = 1.2f;				/*初期の浮遊力*/
	const float HOVER_DECAY_FORCE = 1.0f;				/*浮遊力の減衰率*/

	const float STAMP_TIME= 1.5f;						/*着地時のアクションの時間*/

	const float ROLL_MAX_SPEED = VELOCITY_X;			/*ロールの最大速度*/
	const float ROLL_DECELERATION = VELOCITY_X * 0.05f;	/*減速度*/

	//-----メンバ変数-----//
	float m_hovering_force = 0.0f;						/*現在の浮遊力*/
	float m_stamp_time = 0.0f;							/*着地時のアクションのタイマー*/

	bool m_is_draw = true;								/*透明化フラグ*/

	bool m_is_hovering = false;							/*空中のフラグ*/
	bool m_is_hovered = false;							/*下降フラグ*/

	bool m_is_stamp = false;							/*着地のフラグ*/
	bool m_is_rolling=false;							/*ロールのフラグ*/

	//ゲームスティック用
	float normalized_input_x;							/*アナログスティックの傾きベクトル*/
	int m_input_x;
	int m_input_y;

	ePlayerAction e_currentAction = ePlayerAction::Idle_right;

	//-----ポインタ変数-----//
	Collision* m_collision=nullptr;
	Map* m_map=nullptr;
	Wind* m_wind=nullptr;
	Logo* m_logo=nullptr;

	//-----メンバ関数-----//
	void MoveHandle(float delta_time);			/*ゲームパッドスティック操作*/
	void ActionHandle(float delta_time);		/*入力処理*/

	void MoveRange();							/*移動範囲の制限*/
	void Gravity(float delta_time);				/*重力処理*/

	void ApplyWind(float delta_time);			/*風の影響*/

	void Hovering(float delta_time);			/*ホバリング処理*/
	void HoveringDirection(float delta_time);	/*ホバリング操作*/
	void HoveringStartRight(float delta_time);	/*ホバリング開始処理（右）*/
	void HoveringStartLeft(float delta_time);	/*ホバリング開始処理（左）*/
	//void HoveringEnd();						/*ホバリング終了処理*/

	void Invincible(float delta_time);			/*無敵時間の処理*/

public:

	void StampAction(float delta_time);			/*着地時のアクション*/
	void RollAction(float delta_time);			/*ロール時のアクション*/
	bool CheckIsGround();						/*接地判定*/

	void Update(float delta_time) override;
	void Draw(float delta_time, const Camera* camera) override;

	//-----Getter,Setter-----//
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }
	void SetIsStamp(bool is_stamp) { m_is_stamp = is_stamp; }
	bool GetIsRolling() const { return m_is_rolling; }
};

//Playerのボタン操作の挙動処理を行うクラス
//アニメーションの再生については別クラスを定義した方が分かりやすいかも