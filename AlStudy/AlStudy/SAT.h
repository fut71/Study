#pragma once
#include "SimpleMath.h"

namespace geom2d
{
	using DirectX::SimpleMath::Vector2;
	struct AABB2
	{
		Vector2 mn{}, mx{};
	};
	struct Circle2
	{
		Vector2 c{}; float r{};
	};
	struct OBB2
	{
		Vector2 v1;
		Vector2 v2;
		Vector2 v3;
		Vector2 v4;
// 		Vector2 c{};
// 		Vector2 ax{};
// 		Vector2 ay{};
// 		Vector2 half{};
	};
	struct Poly2
	{
		std::vector<Vector2> verts;
	};

	struct SATHit
	{
		bool    hit{};          // 충돌 여부
		float   overlap{};      // 최소 겹침량
		Vector2 axis{};         // 최소축(단위벡터, A->B)
		Vector2 mtv{};          // 최소이동벡터(부호 포함)
	};

// 추가 가능한 요소들
// 	struct Interval
// 	{
// 		float min{}, max{};
// 	};
// 	struct OverlapInfo
// 	{
// 		bool overlap{}; float amount{};
// 	};
// 	struct Contact
// 	{
// 		Vector2 point{};
// 		Vector2 normal{};
// 		float   depth{};
// 	};
// 	struct Manifold
// 	{
// 		bool    hit{};
// 		Vector2 normal{};
// 		float   depth{};
// 		Contact contacts[2]{};
// 		int     contactCount{};
// 	};
}

namespace sat2d
{
	using namespace DirectX::SimpleMath;
	using namespace geom2d;

	SATHit CC(const Circle2& a, const Circle2 b);
	SATHit AABB(const AABB2& a, const AABB2 b);
	SATHit OBB(const OBB2& a, const OBB2& b);
	SATHit PP(const Poly2& a, const Poly2& b);

	SATHit PA(const Poly2& p, const AABB2& a);
	SATHit AP(const AABB2& a, const Poly2& p);
	
	SATHit CP(const Circle2& c, const Poly2& p);
	SATHit PC(const Poly2& p, const Circle2& c);

	SATHit PntC(Vector2 p, const Circle2& c);
	SATHit PntA(Vector2 p, const AABB2& a);
	SATHit PntP(Vector2 p, const Poly2& poly);
}