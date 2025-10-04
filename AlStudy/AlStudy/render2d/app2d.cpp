// App2D.cpp
#include "App2D.hpp"
#include "../scenes/Scene2D.hpp"
#include <sstream>
using namespace r2d; using core::Vec2; using core::AABB2;
App2D::App2D(unsigned w, unsigned h, const char* title)
	: win_(sf::VideoMode(w, h), title), cam_(64.f)
{
	win_.setFramerateLimit(120);
}
void App2D::run()
{
	Scene2D scene; // 코어 호출만 하는 장면
	DebugDraw2D_SFML dd(win_);
	while(win_.isOpen())
	{
		sf::Event e; while(win_.pollEvent(e))
		{
			if(e.type == sf::Event::Closed) win_.close();
			input_.onEvent(e);
		}
		// 입력: 마우스 휠로 줌, WSAD 팬(예시)
		float wheel = input_.wheelDelta(); if(wheel != 0.f) cam_.zoom(1.f + wheel * 0.1f);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cam_.setCenter({cam_.screenToWorld(win_, {0,0}).x - 0.1f, 0});
		cam_.applyTo(win_);

		win_.clear(sf::Color(24, 26, 32));
		// 장면 업데이트/드로우
		scene.update(1.0f / 120.0f);
		scene.debugDraw(dd);

		win_.display();
	}
}
