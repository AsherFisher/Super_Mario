#include "Coin.h"
#include "Board.h"

//========================================================================

Coin::Coin()
{
}

//=========================================================================

Coin::Coin(const sf::RectangleShape & shape, const std::string & textureName, const std::string& animationName)
	: ActiveObject(shape, textureName, animationName)
{
	m_Clock.restart();
}

//==========================================================================

void Coin::move(Board & board, sf::RenderWindow& window)
{
	// to be safe when the long time pass from last visit
	m_velocity = std::fmin(float(m_movementClock.restart().asSeconds() * m_speed), 5.f);

	m_anim.set("Spin");
	m_shape.move((m_Clock.getElapsedTime().asSeconds() < 0.75 ? sf::Vector2f{ 0, -m_velocity } : sf::Vector2f{ 0, m_velocity }));
	
	board.checkCollision(*this, m_velocity);
}

//=========================================================================
Coin::~Coin()
{
}