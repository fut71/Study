#include "SAT.h"
#include "SimpleMath.h"
#include <cfloat>

constexpr float EPS = 1e-6f;

namespace sat2d
{
	using namespace geom2d;

	geom2d::SATHit CC(const Circle2& a, const Circle2 b)
	{
		Vector2 ab = b.c - a.c;

		float dist = ab.Length();
		float rSum = a.r + b.r;

		SATHit out{};

		if(dist >= rSum)
		{
			out.hit = false;
			return out;
		}

		out.hit = true;
		out.overlap = rSum - dist;
		if(dist < EPS)
		{
			out.axis = Vector2(1.f, 0.f);
		}
		else
		{
			out.axis = ab / dist;
		}
		out.mtv = out.axis * out.overlap;

		return out;
	}

	geom2d::SATHit AABB(const AABB2& a, const AABB2 b)
	{
		SATHit out{};

		if(a.mx.x <= b.mn.x || b.mx.x <= a.mn.x
			|| a.mx.y <= b.mn.y || b.mx.y <= a.mn.y)
		{
			out.hit = false;
			return out;
		}

		out.hit = true;

		float overlapX = min(a.mx.x, b.mx.x) - max(a.mn.x, b.mn.x);
		float overlapY = min(a.mx.y, b.mx.y) - max(a.mn.y, b.mn.y);

		Vector2 centerA = (a.mn + a.mx) * 0.5f;
		Vector2 centerB = (b.mn + b.mx) * 0.5f;

		if(overlapX < overlapY)
		{
			float sign = centerB.x >= centerA.x ? 1.f : -1.f;
			out.axis = {sign, 0.f};
			out.overlap = overlapX;
		}
		else
		{
			float sign = centerB.y >= centerA.y ? 1.f : -1.f;
			out.axis = {0.f, sign};
			out.overlap = overlapY;
		}
		out.mtv = out.axis * out.overlap;

		return out;
	}

	geom2d::SATHit OBB(const OBB2& a, const OBB2& b)
	{
		// 임시로 PP 재사용.
		Poly2 pa{{a.v1, a.v2, a.v3, a.v4}};
		Poly2 pb{{b.v1, b.v2, b.v3, b.v4}};

		return PP(pa,pb);
	}

	geom2d::SATHit PP(const Poly2& a, const Poly2& b)
	{
		SATHit out{};

		// 축 수집
		std::vector<Vector2> axes{};
		auto pushAxes = [&](const Poly2& p)
		{
			const size_t n = p.verts.size();
			for(size_t i = 0; i < n; ++i)
			{
				Vector2 e = p.verts[(i + 1) % n] - p.verts[i];
				if(e.LengthSquared() < EPS * EPS)
				{
					continue;
				}
				Vector2 axis = {-e.y, e.x};
				axis.Normalize();
				axes.push_back(axis);
			}
		};

		pushAxes(a);
		pushAxes(b);

		// 축별 투영 검사
		float bestOverlap = FLT_MAX;
		Vector2 bestAxis{};

		for(auto& v : axes)
		{
			float aMin = FLT_MAX;
			float aMax = -FLT_MAX;
			float bMin = FLT_MAX;
			float bMax = -FLT_MAX;

			for(const auto& va : a.verts)
			{
				float s = v.Dot(va);
				if(s < aMin)
				{
					aMin = s;
				}
				if(s > aMax)
				{
					aMax = s;
				}
			}
			for(const auto& vb : b.verts)
			{
				float s = v.Dot(vb);
				if(s < bMin)
				{
					bMin = s;
				}
				if(s > bMax)
				{
					bMax = s;
				}
			}

			// 분리축 판정
			if(aMax < bMin || bMax < aMin)
			{
				out.hit = false;
				return out;
			}

			// overlap 계산 및 최소 overlap 축 갱신
			float overlap = min(aMax, bMax) - max(aMin, bMin);
			if(overlap < bestOverlap)
			{
				bestOverlap = overlap;
				bestAxis = v;
			}
		}

		// MTV 방향
		Vector2 cA{};
		Vector2 cB{};
		for(const auto& p : a.verts)
		{
			cA += p;
		}
		cA /= static_cast<float>(a.verts.size());
		for(const auto& p : b.verts)
		{
			cB += p;
		}
		cB /= static_cast<float>(b.verts.size());

		float sign = (bestAxis.Dot(cB - cA) >= 0.f) ? 1.f : -1.f;

		out.hit = true;
		out.overlap = bestOverlap;
		out.axis = bestAxis * sign;
		out.mtv = out.axis * bestOverlap;

		return out;
	}

	geom2d::SATHit CP(const Circle2& c, const Poly2& p)
	{
		return {};
	}

	geom2d::SATHit PA(const Poly2& p, const AABB2& a)
	{
		return {};
	}

	geom2d::SATHit AP(const AABB2& a, const Poly2& p)
	{
		return PA(p, a);
	}

	geom2d::SATHit PC(const Poly2& p, const Circle2& c)
	{
		return CP(c, p);
	}

	geom2d::SATHit PntC(Vector2 p, const Circle2& c)
	{
		SATHit out{};

		Vector2 dvec = p - c.c;
		float dist = dvec.Length();

		// 내부 판정
		if(dist > c.r)
		{
			out.hit = false;
			return out;
		}

		if(dist > EPS)
		{
			out.axis = dvec / dist;
		}
		else
		{
			out.axis = Vector2(1.f, 0.f);
		}

		out.overlap = c.r - dist;
		out.mtv = dist * out.axis;

		return out;
	}

	geom2d::SATHit PntA(Vector2 p, const AABB2& a)
	{
		SATHit out{};

		// 1. 내부 판정
		if(!(a.mn.x <= p.x && a.mn.y <= p.y && a.mx.x >= p.x && a.mx.y >= p.y))
		{
			out.hit = false;
			return out;
		}

		// 2. 각 면까지의 거리 계산
		const float dxL = p.x - a.mn.x;
		const float dxR = a.mx.x - p.x;
		const float dyT = p.y - a.mn.y;
		const float dyB = a.mx.y - p.y;

		// 3. 가장 가까운 면 선택
		float overlap;
		Vector2 axis;

		if(min(dxL, dxR) < min(dyT, dyB))
		{
			if(dxL < dxR)
			{
				axis = Vector2(-1.f, 0.f);
				overlap = dxL;
			}
			else
			{
				axis = Vector2(1.f, 0.f);
				overlap = dxR;
			}
		}
		else
		{
			if(dyT < dyB)
			{
				axis = Vector2(0.f, -1.f);
				overlap = dyT;
			}
			else
			{
				axis = Vector2(0.f, 1.f);
				overlap = dyB;
			}
		}

		out.hit = true;
		out.overlap = overlap;
		out.axis = axis;
		out.mtv = axis * overlap;

		return out;

	}

	geom2d::SATHit PntP(Vector2 p, const Poly2& poly)
	{
		SATHit out{};

		const size_t n = poly.verts.size();

		if(n < 3)
		{
			out.hit = false;
			return out;
		}

		for(size_t i = 0; i < n; ++i)
		{
			Vector2 e = poly.verts[(i + 1) % n] - poly.verts[i];

			if(e.LengthSquared() < EPS * EPS)
			{
				continue;
			}

			Vector2 inward = Vector2(e.y, -e.y);
			inward.Normalize();
		}

		float bestOverlap = FLT_MAX;
		Vector2 bestAxis = {0.f, 0.f};

		return out;
	}

}
