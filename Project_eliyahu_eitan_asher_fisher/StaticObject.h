#pragma once
#include "GameObject.h"

//============================================================================

class StaticObject : public GameObject
{
public:

	// c'tor
	StaticObject();
	// c'tor
	StaticObject(const sf::RectangleShape& shape, const sf::FloatRect rect, const sf::Texture& texture);
	// c'tor
	StaticObject(const sf::FloatRect rect);
	// func to get the global boundsof the rect
	virtual sf::FloatRect getRect() const;
	// d'tor
	virtual ~StaticObject() = 0;

private:
	
	// rect for the global bounds
	sf::FloatRect m_rect;
};

