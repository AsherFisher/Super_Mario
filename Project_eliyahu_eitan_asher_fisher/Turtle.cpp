#include "Turtle.h"


//==========================================================================

Turtle::Turtle()
{
}

//==========================================================================

Turtle::Turtle(const sf::RectangleShape & shape, const std::string & textureName, const std::string & animationName)
      :Enemy(shape, textureName, animationName)
{
}

//==================================================================================

void Turtle::move(Board & board, sf::RenderWindow& wind)
{
	if (m_mode == Dead)
	{
		m_anim.set("Dead");
		m_dir = Down;
	}

	if (m_mode == Smash)
	{
		m_anim.set("Smash");
	}

	Enemy::move(board, wind);
}

//===========================================================================

void Turtle::changeDirection(const Direction prevDir)
{
	if (prevDir == m_dir)
	{
		switch (m_dir)
		{
		case Right:
			m_dir = Left;
			m_anim.set("WalkLeft");
			break;
		case Left:
			m_dir = Right;
			m_anim.set("WalkRight");
			break;

		default:
			break;
		}
	}
}

//=========================================================================

Turtle::~Turtle()
{
}
