#pragma once
#include <vector>
#include "tnl_math.h"

namespace wta {

	////ファイルを読み込む関数
	//int loadAnimLoopFile(const char* path);

	////アニメーションを描画する関数
	//int drawAnimLoopFile(float delta_time, tnl::Vector3 pos, int path_hdl, float angle = 0, float scale = 1.0f);

	//円と矩形の当たり判定計算
	bool IsIntersectCircleBox(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& box, const int boxSize);

	//円と線分の当たり判定計算
	bool IsIntersectCircleLine(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);

	//円同士の当たり判定計算
	bool IsIntersectCircleCircle(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02);
}