#include "ActiveObject.h"

//=============================================================================

ActiveObject::ActiveObject()
{
}

//=====================   c'tor  ===========================================

ActiveObject::ActiveObject(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName)
	: GameObject(shape, m_texture), m_startPosition(shape.getPosition()), m_velocity(0), m_mode(Falling)
{
	setTexture(textureName);
    if (animationName != "None")  // if this active has an animation
    	m_anim.loadFromXML(animationName, m_texture);
}

//=============================================================================

void ActiveObject::setPosition(const sf::Vector2f & newPosition)
{
	m_shape.setPosition(newPosition);
}

//=============================================================================

void ActiveObject::resetPosition()
{
	setPosition(m_startPosition);
	m_jumpClock.restart();
}

//=============================================================================

//move back when collide with solid object
void ActiveObject::moveBack(const Direction prevDir)
{
	switch (prevDir)  // adjust the new position acorrding to the direction that collide accured from
	{
	case Up:         // object was going up and than collide
		m_shape.move({ 0,  m_velocity });
		break;
	case Down:      
		m_shape.move({ 0, -m_velocity });
		break;
	case Right:    // object was going right and than collide
		m_shape.move({ -m_velocity, 0 });
		break;
	case Left:
		m_shape.move({ m_velocity, 0 });
		break;
	}
}

//=============================================================================

sf::Vector2f ActiveObject::getStartPosition()
{
	return m_startPosition;
}

//=============================================================================

void ActiveObject::draw(sf::RenderWindow & window)
{
	m_anim.tick(m_velocity * 10);  // set the new frame in the animation
	m_anim.draw(window, int(m_shape.getPosition().x), int(m_shape.getPosition().y +32));
	GameObject::draw(window);
}

//=============================================================================

sf::FloatRect ActiveObject::getRect() const
{
	return m_shape.getGlobalBounds();
}

//=============================================================================

void ActiveObject::updateMode(const Mode newMode)  // update the mode - falling, on ground, etc.
{
	m_mode = newMode;
}

//=============================================================================

Mode ActiveObject::getMode()
{
	return m_mode;
}

//=============================================================================

ActiveObject::~ActiveObject()
{
}
