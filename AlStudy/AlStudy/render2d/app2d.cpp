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
	Scene2D scene; // �ھ� ȣ�⸸ �ϴ� ���
	DebugDraw2D_SFML dd(win_);
	while(win_.isOpen())
	{
		sf::Event e; while(win_.pollEvent(e))
		{
			if(e.type == sf::Event::Closed) win_.close();
			input_.onEvent(e);
		}
		// �Է�: ���콺 �ٷ� ��, WSAD ��(����)
		float wheel = input_.wheelDelta(); if(wheel != 0.f) cam_.zoom(1.f + wheel * 0.1f);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cam_.setCenter({cam_.screenToWorld(win_, {0,0}).x - 0.1f, 0});
		cam_.applyTo(win_);

		win_.clear(sf::Color(24, 26, 32));
		// ��� ������Ʈ/��ο�
		scene.update(1.0f / 120.0f);
		scene.debugDraw(dd);

		win_.display();
	}
}
