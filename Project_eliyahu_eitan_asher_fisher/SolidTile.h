#pragma once
#include "Tile.h"

//==========================================================================

class SolidTile
	: public Tile
{
public:

	// c'tor
	SolidTile();
	// c'tor
	SolidTile(const sf::FloatRect& objectRect);
	// d'tor
	~SolidTile();
};

