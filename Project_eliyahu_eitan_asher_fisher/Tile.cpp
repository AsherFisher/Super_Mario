#include "Tile.h"

//===========================================================================

Tile::Tile()
{
}

//===========================================================================
Tile::Tile(const sf::RectangleShape & shape, const sf::FloatRect rect, const sf::Texture & txtre)
	:StaticObject(shape, rect, txtre)
{
}

//===========================================================================

Tile::Tile(const sf::FloatRect rect)
	:StaticObject(rect)
{
}

//===========================================================================

Tile::~Tile()
{
}
