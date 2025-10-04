// Camera2D.cpp
#include "Camera2D.hpp"
#include "../core/Math.hpp"
using namespace r2d; using core::Vec2;
Camera2D::Camera2D(float ppu) : ppu_(ppu)
{
	view_.setSize(800.f, -600.f); // 높이에 - 부호로 y축 뒤집기
	view_.setCenter(0.f, 0.f);
}
void Camera2D::setCenter(Vec2 c)
{
	view_.setCenter(c.x, c.y);
}
void Camera2D::zoom(float factor)
{
	view_.zoom(1.f / factor);
} // factor>1 확대
void Camera2D::applyTo(sf::RenderWindow& win) const
{
	win.setView(view_);
}
Vec2 Camera2D::screenToWorld(const sf::RenderWindow& win, sf::Vector2i s) const
{
	auto p = win.mapPixelToCoords(s, view_); return {p.x, p.y};
}
