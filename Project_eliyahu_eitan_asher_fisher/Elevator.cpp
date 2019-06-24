#include "Elevator.h"

//=======================================================================

Elevator::Elevator()
{
}

//=======================================================================

Elevator::Elevator(const sf::RectangleShape & shape, const std::string & textureName, const std::string & animationName)
	:Enemy(shape, textureName, animationName)
{
	m_anim.set("start");
	m_speed = 200;
}

//==================================================================================

void Elevator::move(Board & board, sf::RenderWindow& wind)
{

	// each for second change direction
	m_dir = (float)c.getElapsedTime().asSeconds() < 4.0f ? Up : Down;
	if ((float)c.getElapsedTime().asSeconds() >= 8.0f)
		c.restart();

	Enemy::move(board, wind);
}

//==============================================================================

void Elevator::resetPosition()
{
	ActiveObject::resetPosition();
	c.restart();
}
//=============================================================================

Elevator::~Elevator()
{
}
