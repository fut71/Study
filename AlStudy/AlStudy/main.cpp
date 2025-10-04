#include <SFML/Graphics.hpp>
#include <SimpleMath.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "SAT.h"  

using DirectX::SimpleMath::Vector2;
using geom2d::Circle2;
using geom2d::AABB2;
using geom2d::Poly2;

static constexpr float DT = 1.f / 60.f;

// ����
static const sf::Color OK(80, 200, 120);
static const sf::Color HIT(64, 140, 255);
static const sf::Color BG(24, 26, 32);

// ���� ��ȯ
sf::CircleShape makeCircle(const Circle2& c, sf::Color col)
{
	sf::CircleShape s(c.r);
	s.setOrigin({c.r, c.r});
	s.setPosition({c.c.x, c.c.y});
	s.setFillColor(col);
	return s;
}
sf::RectangleShape makeRect(const AABB2& b, sf::Color col)
{
	sf::RectangleShape r;
	const float w = b.mx.x - b.mn.x;
	const float h = b.mx.y - b.mn.y;
	r.setSize({w, h});
	r.setPosition({b.mn.x, b.mn.y});
	r.setFillColor(col);
	return r;
}
sf::ConvexShape makePoly(const Poly2& p, sf::Color col)
{
	sf::ConvexShape s;
	s.setPointCount(p.verts.size());
	for(std::size_t i = 0; i < p.verts.size(); ++i) s.setPoint(i, {p.verts[i].x, p.verts[i].y});
	s.setFillColor(col);
	return s;
}

// ���� ��� ƨ�� (SFML 3: Rect�� position/size ���)
inline void bounceCircle(Circle2& c, Vector2& v, const sf::FloatRect& world)
{
	const float lx = world.position.x;
	const float rx = world.position.x + world.size.x;
	const float ty = world.position.y;
	const float by = world.position.y + world.size.y;

	if(c.c.x - c.r < lx)
	{
		c.c.x = lx + c.r; v.x *= -1.f;
	}
	if(c.c.x + c.r > rx)
	{
		c.c.x = rx - c.r; v.x *= -1.f;
	}
	if(c.c.y - c.r < ty)
	{
		c.c.y = ty + c.r; v.y *= -1.f;
	}
	if(c.c.y + c.r > by)
	{
		c.c.y = by - c.r; v.y *= -1.f;
	}
}
inline void bounceAABB(AABB2& b, Vector2& v, const sf::FloatRect& world)
{
	const float lx = world.position.x;
	const float rx = world.position.x + world.size.x;
	const float ty = world.position.y;
	const float by = world.position.y + world.size.y;

	const float w = b.mx.x - b.mn.x, h = b.mx.y - b.mn.y;

	if(b.mn.x < lx)
	{
		b.mn.x = lx; b.mx.x = b.mn.x + w; v.x *= -1.f;
	}
	if(b.mx.x > rx)
	{
		b.mx.x = rx; b.mn.x = b.mx.x - w; v.x *= -1.f;
	}
	if(b.mn.y < ty)
	{
		b.mn.y = ty; b.mx.y = b.mn.y + h; v.y *= -1.f;
	}
	if(b.mx.y > by)
	{
		b.mx.y = by; b.mn.y = b.mx.y - h; v.y *= -1.f;
	}
}
inline void movePoly(Poly2& p, const Vector2& dv)
{
	for(auto& v : p.verts) v += dv;
}
// ������ AABB ���
inline void polyAABB(const Poly2& p, float& minx, float& miny, float& maxx, float& maxy)
{
	minx = miny = std::numeric_limits<float>::infinity();
	maxx = maxy = -std::numeric_limits<float>::infinity();
	for(const auto& v : p.verts)
	{
		if(v.x < minx) minx = v.x;
		if(v.x > maxx) maxx = v.x;
		if(v.y < miny) miny = v.y;
		if(v.y > maxy) maxy = v.y;
	}
}

// ħ����ŭ ��� ���� + �ش� �� �ӵ��� ����
inline void bouncePoly(Poly2& p, Vector2& vel, const sf::FloatRect& world)
{
	const float lx = world.position.x;
	const float rx = world.position.x + world.size.x;
	const float ty = world.position.y;
	const float by = world.position.y + world.size.y;

	float minx, miny, maxx, maxy;
	polyAABB(p, minx, miny, maxx, maxy);

	// �ణ�� ����(���̾)�� ���� ����
	constexpr float SLOP = 0.5f;

	// X�� �浹 ó��
	if(minx < lx)
	{
		float push = (lx - minx) + SLOP;     // ���� �� ������ ���� ħ����
		for(auto& v : p.verts) v.x += push; // �� ������ ���������� �̵�
		vel.x = -vel.x;
	}
	else if(maxx > rx)
	{
		float push = (rx - maxx) - SLOP;     // ������ �� ħ��(����)
		for(auto& v : p.verts) v.x += push; // �� ������ �������� �̵�
		vel.x = -vel.x;
	}

	// Y�� �浹 ó��
	polyAABB(p, minx, miny, maxx, maxy);     // X ���� �� AABB ����
	if(miny < ty)
	{
		float push = (ty - miny) + SLOP;     // ���� �� ħ����
		for(auto& v : p.verts) v.y += push; // �� ������ �Ʒ��� �̵�
		vel.y = -vel.y;
	}
	else if(maxy > by)
	{
		float push = (by - maxy) - SLOP;     // �Ʒ��� �� ħ��(����)
		for(auto& v : p.verts) v.y += push; // �� ������ ���� �̵�
		vel.y = -vel.y;
	}
}

int main()
{
	// â
	sf::VideoMode mode({1280u, 720u});
	sf::RenderWindow window(mode, "SAT Demo: 1=CC, 2=AABB, 3=PP", sf::Style::Default);
	window.setFramerateLimit(120);
	const sf::FloatRect world({0.f, 0.f}, {1280.f, 720.f}); // SFML3 Rect ����

	// ���� ���: 1=CC, 2=AABB, 3=PP
	int modeIdx = 1;

	// ���� CC �¾�
	Circle2 c1{Vector2(300.f, 360.f), 70.f};
	Circle2 c2{Vector2(900.f, 360.f), 90.f};
	Vector2 vc1(160.f, 120.f), vc2(-130.f, -100.f);

	// ���� AABB �¾�
	AABB2 b1{Vector2(200.f, 200.f), Vector2(360.f, 360.f)};
	AABB2 b2{Vector2(800.f, 320.f), Vector2(1040.f, 540.f)};
	Vector2 vb1(150.f, 110.f), vb2(-140.f, -90.f);

	// ���� PP �¾� (����, CCW)
	Poly2 p1{{ Vector2(300.f,160.f), Vector2(460.f,220.f), Vector2(420.f,360.f), Vector2(260.f,320.f) }};
	Poly2 p2{{ Vector2(900.f,180.f), Vector2(1050.f,260.f), Vector2(980.f,420.f),  Vector2(840.f,340.f) }};
	Vector2 vp1(120.f, 80.f), vp2(-110.f, -90.f);

	while(window.isOpen())
	{
		// �̺�Ʈ
		while(auto ev = window.pollEvent())
		{
			if(ev->is<sf::Event::Closed>()) window.close();
			if(const auto* key = ev->getIf<sf::Event::KeyPressed>())
			{
				using K = sf::Keyboard::Scancode;
				if(key->scancode == K::Escape) window.close();
				if(key->scancode == K::Num1 || key->scancode == K::Numpad1) modeIdx = 1;
				if(key->scancode == K::Num2 || key->scancode == K::Numpad2) modeIdx = 2;
				if(key->scancode == K::Num3 || key->scancode == K::Numpad3) modeIdx = 3;
			}
		}

		// ������Ʈ
		if(modeIdx == 1)
		{
			c1.c += vc1 * DT; c2.c += vc2 * DT;
			bounceCircle(c1, vc1, world); bounceCircle(c2, vc2, world);
		}
		else if(modeIdx == 2)
		{
			b1.mn += vb1 * DT; b1.mx += vb1 * DT;
			b2.mn += vb2 * DT; b2.mx += vb2 * DT;
			bounceAABB(b1, vb1, world); bounceAABB(b2, vb2, world);
		}
		else
		{
			movePoly(p1, vp1 * DT); movePoly(p2, vp2 * DT);
			bouncePoly(p1, vp1, world); bouncePoly(p2, vp2, world);
		}

		// �浹 ���� (���� ��常) ? sat2d ���ӽ����̽� ȣ��
		bool hit = false;
		if(modeIdx == 1)
		{
			hit = sat2d::CC(c1, c2).hit;
		}
		else if(modeIdx == 2)
		{
			hit = sat2d::AABB(b1, b2).hit;
		}
		else
		{
			hit = sat2d::PP(p1, p2).hit;
		}

		// ����
		window.clear(BG);

		if(modeIdx == 1)
		{
			window.draw(makeCircle(c1, hit ? HIT : OK));
			window.draw(makeCircle(c2, hit ? HIT : OK));
		}
		else if(modeIdx == 2)
		{
			window.draw(makeRect(b1, hit ? HIT : OK));
			window.draw(makeRect(b2, hit ? HIT : OK));
		}
		else
		{
			window.draw(makePoly(p1, hit ? HIT : OK));
			window.draw(makePoly(p2, hit ? HIT : OK));
		}

		window.display();
	}
	return 0;
}
