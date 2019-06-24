#include "RemovableTile.h"

//======================================================================

RemovableTile::RemovableTile()
{
}

//======================================================================

RemovableTile::RemovableTile(const sf::RectangleShape & rect, const sf::FloatRect & figRect, const sf::Texture & txtr)
	: Tile(rect, figRect, txtr)
{
}

//=======================================================================

RemovableTile::~RemovableTile()
{
}
