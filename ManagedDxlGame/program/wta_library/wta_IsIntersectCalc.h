#pragma once
#include <vector>
#include "tnl_math.h"

namespace wta {

	//‰~‚Æ‹éŒ`‚Ì“–‚½‚è”»’èŒvZ(ŒvZƒ~ƒX‚Å–¢Š®¬‚Ì‚½‚ßA‰Û‘èI—¹Œã‚É‰ü•Ï‚ğ–Úw‚·)
	bool IsIntersectCircleBox(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& box, const int boxSize);

	//‰~‚Æü•ª‚Ì“–‚½‚è”»’èŒvZ
	bool IsIntersectCircleLine(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);

	//‰~‚Æü•ª‚ÌÀ•W•â³
	tnl::Vector3 CorrectCircleLineCollision(const tnl::Vector3& circle, const int CircleSize, const tnl::Vector3& lineStart, const tnl::Vector3& lineEnd);

	//‰~“¯m‚Ì“–‚½‚è”»’èŒvZ
	bool IsIntersectCircleCircle(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02);

	//‰~‚Æ‰~‚ÌÀ•W•â³
	tnl::Vector3 CorrectCircleCircleOverlap(const tnl::Vector3& circle01, const int CircleSize01, const tnl::Vector3& circle02, const int CircleSize02); 
}

