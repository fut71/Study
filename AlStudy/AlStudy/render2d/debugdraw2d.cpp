// DebugDraw2D.cpp
#include "DebugDraw2D.hpp"
#include "InteropSFML.hpp"
using namespace r2d; using interop::toSF; using core::Vec2;
static sf::Color C(r2d::DDColor c)
{
	return sf::Color(c.r, c.g, c.b, c.a);
}
void DebugDraw2D_SFML::line(Vec2 a, Vec2 b, DDColor c)
{
	sf::Vertex v[2] = {sf::Vertex(toSF(a), C(c)), sf::Vertex(toSF(b), C(c))};
	win_.draw(v, 2, sf::Lines);
}
void DebugDraw2D_SFML::rect(const core::AABB2& b, DDColor c, bool filled)
{
	sf::RectangleShape r; r.setPosition(b.mn.x, b.mn.y);
	r.setSize({b.mx.x - b.mn.x, b.mx.y - b.mn.y});
	if(filled)
	{
		r.setFillColor(C(c)); r.setOutlineThickness(0.f);
	}
	else
	{
		r.setFillColor(sf::Color::Transparent); r.setOutlineColor(C(c)); r.setOutlineThickness(1.f);
	}
	win_.draw(r);
}
void DebugDraw2D_SFML::circle(Vec2 center, float radius, DDColor col, bool filled)
{
	sf::CircleShape cc(radius); cc.setOrigin(radius, radius); cc.setPosition(center.x, center.y);
	if(filled)
	{
		cc.setFillColor(C(col)); cc.setOutlineThickness(0.f);
	}
	else
	{
		cc.setFillColor(sf::Color::Transparent); cc.setOutlineColor(C(col)); cc.setOutlineThickness(1.f);
	}
	win_.draw(cc);
}
void DebugDraw2D_SFML::text(Vec2 p, const char* s, DDColor col, unsigned px)
{
	static sf::Font font; static bool loaded = false;
	if(!loaded)
	{
		font.loadFromFile("arial.ttf"); loaded = true;
	} // 임시: 리소스 시스템 도입 전
	sf::Text t; t.setFont(font); t.setString(s); t.setCharacterSize(px); t.setFillColor(C(col));
	t.setPosition(p.x, p.y); win_.draw(t);
}
