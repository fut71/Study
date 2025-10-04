// InputSFML.cpp
#include "InputSFML.hpp"
using namespace r2d;
bool InputSFML::keyDown(sf::Keyboard::Key k) const
{
	return sf::Keyboard::isKeyPressed(k);
}
sf::Vector2i InputSFML::mousePos(const sf::Window& w) const
{
	return sf::Mouse::getPosition(w);
}
float InputSFML::wheelDelta() const
{
	return wheelAccum_;
}
void InputSFML::onEvent(const sf::Event& e)
{
	if(e.type == sf::Event::MouseWheelScrolled) wheelAccum_ += e.mouseWheelScroll.delta;
}
