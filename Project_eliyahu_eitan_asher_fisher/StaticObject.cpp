#include "StaticObject.h"

//====================================================================================

StaticObject::StaticObject()
{
}

//=====================================================================================

StaticObject::StaticObject(const sf::RectangleShape & shape, const sf::FloatRect rect, const sf::Texture& texture) 
	: GameObject(shape, texture), m_rect(rect)
{
}

//=====================================================================================

StaticObject::StaticObject(const sf::FloatRect rect) 
	: m_rect(rect)
{
}

//=====================================================================================

sf::FloatRect StaticObject::getRect() const
{
	return m_rect;
}

//=====================================================================================

StaticObject::~StaticObject()
{
}
