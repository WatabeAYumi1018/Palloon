#pragma once
#include <vector>
#include "../library/tnl_math.h"

namespace wta
{
	//円同士の当たり判定計算
	bool IsIntersectCircleCircle(const tnl::Vector3& pos1, float radius1, const tnl::Vector3& pos2, float radius2);

}
	//使用には問題ないけれど、今回はここまでの判定処理は不要のため、tnl既存の関数を使用する
	////円同士の座標補正	
	////円と線分の当たり判定計算
	//bool IsIntersectCircleLine(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);

	////円と線分の座標補正
	//tnl::Vector3 CorrectCircleLineCollision(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);


	//円と円の座標補正
	//tnl::Vector3 CorrectCircleCircleOverlap(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02); 

	////★円と矩形の当たり判定計算(計算ミスで未完成のため、課題終了後に改変を目指す)
	//bool IsIntersectCircleBox(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& box, const int boxSize);