#pragma once
#include "../dxlib_ext/dxlib_ext.h"

enum class eBalloonColor
{
	None,
	Red,
	Blue,
	Green,
	Max
};

enum class ePlayerAction
{
	Idle_right,
	Idle_left,
	Move_right,
	Move_left,
	Dash_right,
	Dash_left,
	Hover_right,
	Hover_left,
	Hover_end_right,
	Hover_end_left,
	Stamp_right,
	Stamp_left,
	Roll_right,
	Roll_left,
	Fire_right,
	Fire_left,
	Beam_right,
	Beam_left,
};

enum class eEffectPlayerType
{
	None,
	Fire,
	Beam,
};

enum class eEffectCollisionType
{
	None,
	Box,
	Circle,
	Line,
};

enum class eMapCollisionType
{
	None,
	Box,
	Line,
	Clear,
};

struct sCollisionInfo
{
	tnl::Vector3 s_pos;
	int s_size;
	eMapCollisionType s_type;
};

struct sEnemyData 
{
	int s_type_id;
	tnl::Vector3 s_pos;
};

struct sEnemyInfo
{
	int s_id;
	std::string s_name;
	std::string s_color;
	int s_hp;
	int s_size;
};

enum class eBalloonState
{
	Hidden,
	Rising,
	Floating,
	SceneChange
};

struct sStageInfo
{
	std::string s_stage_name;
	std::string s_map_csv;
	std::string s_collision_csv;
	std::string s_enemy_csv;
	tnl::Vector3 initial_player_position;  // プレイヤーの初期位置
};

struct RespawnInfo
{
	float respawnTimer = 0.0f;     // 再生成までのタイマー
	int respawnCount = 0;          // これまでの再生成回数
};