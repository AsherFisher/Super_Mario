#include <algorithm>
#include "Mario.h"
#include "Constants.h"
#include "Enemy.h"
#include "solidTile.h"
#include "Board.h"

//=======================================================================================

Mario::Mario()
{
}

//=======================================================================================

Mario::Mario(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName, const sf::View& view)
	: ActiveObject(shape, textureName, animationName), m_view(view)
{
}

//=======================================================================================

void Mario::move(Board & board, sf::RenderWindow& wind)
{
	calcDirection(wind, board);   // check for what side to move based on the input
	
	m_shape.move(m_direction);
	m_view.move(m_direction);  // move the view with the mario

	board.checkCollision(*this, m_velocity);

	if (m_direction.y > 0 && getMode() != Dead)  // mario should be going down
		m_mode = Falling;

	setAnimation();  // set the current animation based on the mode

}

//==============================================================================

void Mario::draw(sf::RenderWindow & window)
{
	window.setView(m_view);
	ActiveObject::draw(window);
}

//===============================================================================

void Mario::moveBack(const Direction prevDir)
{
	ActiveObject::moveBack(prevDir);  

	switch (prevDir)
	{
	case Up:    // if the collition with static object accured on the way up
		m_mode = Falling;
		m_view.move({ 0, m_velocity });
		m_direction += { 0, m_velocity };
		break;
	case Down:
		m_view.move({ 0, -m_velocity });
		m_direction += { 0, -m_velocity };
		break;
	case Right:
		m_view.move({ -m_velocity, 0 });
	    m_direction += { -m_velocity, 0 };
		break;
	case Left:
		m_view.move({ m_velocity, 0 });
	    m_direction += {  m_velocity, 0 };
		break;
	}
}
//==================================================================================

void Mario::handleMode()
{
	if (m_jump)  //  mario is in gump and havn't reachd the highest spot
	{
		if (m_mode != Falling && m_jumpClock.getElapsedTime().asSeconds() < 0.42)
		{
			m_direction += {0, -m_velocity};
			m_mode = Jump;
		}
		else   // mario past the highest spot
		{
			m_jump = false;
			m_mode = Falling;
		}
	}

	if (!m_jump)
		m_direction += {0, m_velocity};
	if (m_walkRight)
		m_direction += { m_velocity, 0};
	if (m_walkLeft)
		m_direction += {-m_velocity, 0};
}

//====================================================================================

void Mario::resetPosition()
{
	ActiveObject::resetPosition();

	m_mode = Falling;
	m_turnRight = true;
	m_view.setCenter(m_shape.getPosition());

	m_jump = m_walkRight = m_walkLeft = false;
}

//==================================================================================

void Mario::setAnimation()
{
	if (getMode() == Dead)
		m_anim.set("Dead");

	else if (m_jump || m_mode == Falling || m_mode == Jump)
		m_anim.set(m_turnRight ? "JumpRight" : "JumpLeft");

	else if (m_walkRight)
		m_anim.set("WalkRight");

	else if (m_walkLeft)
		m_anim.set("WalkLeft");

	else
		m_anim.set(m_turnRight ? "StandRight" : "StandLeft");

}

//=====================================================================================

void Mario::calcDirection(sf::RenderWindow& wind, Board& board)
{
	m_direction = { 0,0 };
	// in case of long time has been past from the last time here
	m_velocity = fmin(float(m_movementClock.restart().asSeconds() * m_speed), 5.0f);

	if (getMode() == Dead)   //  maario is dead
	{
		m_direction += {0, m_velocity};
		return;
	}

	sf::Event event;
	while (wind.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:  // jump
				if (m_mode == OnGround && !m_jump)
				{ 
					Sounds::play("jump");
					m_jump = true;
					m_jumpClock.restart();
				}
				break;
			case sf::Keyboard::Right:
				if (!m_walkRight)
				{
					m_walkRight = true;
					m_turnRight = true;
				}
				break;
			case sf::Keyboard::Left:
				if (!m_walkLeft)
				{
					m_walkLeft = true;
					m_turnRight = false;
				}
				break;
			
			default:
				break;
			}
			break;

		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Right:
				if (m_walkRight)
					m_walkRight = false;
				break;
			case sf::Keyboard::Left:
				if (m_walkLeft)
					m_walkLeft = false;
				break;
			default:
				break;
			}
			break;

		case sf::Event::Closed:
			exit(0);
			break;
		}
	}

	handleMode();
}

//================================================================================

Mario::~Mario()
{
}
