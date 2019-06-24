#include "Gumba.h"


//==========================================================================
Gumba::Gumba()
{
}


//========================================================================

Gumba::Gumba(const sf::RectangleShape & shape, const std::string & textureName, const std::string & animationName)
	:Enemy(shape, textureName, animationName)
{
}

//==================================================================================

void Gumba::move(Board & board, sf::RenderWindow& wind)
{
	if (m_mode == Dead)
	{
		m_anim.set("Dead");
		m_dir = Down;
	}

	Enemy::move(board, wind);
}

//==============================================================================

void Gumba::changeDirection(const Direction prevDir)
{
	if (prevDir == m_dir)
	{
		switch (m_dir)
		{
		case Right:
		{
			m_dir = Left;
			break;
		}
		case Left:
		{
			m_dir = Right;
			break;
		}
		default:
			break;
		}
	}
}

//=========================================================================

Gumba::~Gumba()
{
}