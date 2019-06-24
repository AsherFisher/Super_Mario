#pragma once
#include "Tile.h"


//==========================================================================

class RemovableTile :
	public Tile
{
public:

	// c'tor
	RemovableTile();
	// c'tor
	RemovableTile(const sf::RectangleShape& rect, const sf::FloatRect& objectRect, const sf::Texture& texture);
	// d'tor
	~RemovableTile();
};

