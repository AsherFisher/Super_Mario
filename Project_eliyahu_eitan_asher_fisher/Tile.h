#pragma once
#include "StaticObject.h"

//=========================================================================

class Tile :
	public StaticObject
{
public:

	// c'tor
	Tile();
	// c'tor
	Tile(const sf::RectangleShape& shape, const sf::FloatRect rect, const sf::Texture& texture);
	// c'tor
	Tile(const sf::FloatRect rect);
	// d'tor
	virtual ~Tile();
};

