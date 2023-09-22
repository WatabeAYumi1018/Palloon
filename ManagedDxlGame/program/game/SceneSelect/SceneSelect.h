#pragma once
#include "../../engine/sceneBase.h"


class GameObject;

class SceneSelect : public SceneBase 
{
public:

	SceneSelect();

private:

	//-----定数-----//
	const int STAGE_NUM = 4;					/*ステージ数*/

	//-----メンバ変数-----//
	int m_back_hdl = 0;
	int m_stage1_hdl = 0;
	int m_stage2_hdl = 0;
	int m_stage3_hdl = 0;
	int m_boss_hdl = 0;

	int m_selected_stage = 0;					/*選択中ステージ*/
	
	float m_balloon_time = 0.0f;				/*選択中風船の上下タイマー*/
	float m_balloon_offset_y = 10.0f;			/*上下オフセット*/
	float m_balloon_velocity_y = 5.0f;			/*上下速度*/
	
	std::vector<std::string> m_stage_names;		/*ステージ名*/

	//ゲームスティック用
	float normalized_input_x;					/*アナログスティックの傾きベクトル*/
	int m_input_x;
	int m_input_y;

	const float m_input_cooldown_time = 0.5f;	/*0.5秒の入力クールダウン*/
	const float m_deadzone = 0.2f;				/*20%のデッドゾーン(入力無視範囲)*/

	float m_input_cooldown = 0.0f;				/*入力クールダウンタイマー*/
	float m_previous_input_x = 0.0f;			/*前回の入力値*/


	tnl::Sequence<SceneSelect> sequence_ = tnl::Sequence<SceneSelect>(this, &SceneSelect::SeqIdle);

	//-----メンバ関数-----//
	bool SeqIdle(float delta_time);
	void MoveBalloon(float delta_time);

public:

	void Update(float delta_time) override;
	void Draw(float delta_time) override;
	void Finalize() override;

	//-----Setter,Getter-----//
	std::string GetSelectedStage() const { return m_stage_names[m_selected_stage]; };
};

