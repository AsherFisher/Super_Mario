#include "Enemy.h"
#include "Mario.h"
#include "SolidTile.h"
#include "CoinTile.h"
#include "RemovableTile.h"
#include "Board.h"


//==========================================================================

Enemy::Enemy()
{
}


//============================================================================

Enemy::Enemy(const sf::RectangleShape & shape, const std::string & txtrPath, const std::string& animPath)
	: ActiveObject(shape, txtrPath, animPath), m_dir(Left)
{
	m_anim.set("WalkLeft");
}

//=============================================================================

void Enemy::move(Board & board, sf::RenderWindow& wind)
{
	sf::Vector2f m_direction;
	m_velocity = fmin(float(m_movementClock.restart().asSeconds() * (m_speed - 150.f)), 5.0f);

	switch (m_dir)
	{
	case Up:
		m_direction = { 0 , -m_velocity };
		break;
	case Down:
		m_direction = { 0 , m_velocity };
		break;
	case Right:
		m_direction = { m_velocity , 0 };
		break;
	case Left:
		m_direction = { -m_velocity , 0 };
		break;
	}
	
	m_shape.move(m_direction);
	board.checkCollision(*this, m_velocity);
}

//==========================================================================

Enemy::~Enemy()
{
}