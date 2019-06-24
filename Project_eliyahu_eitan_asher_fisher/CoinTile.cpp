#include "CoinTile.h"
#include "Board.h"

//=========================================================================

CoinTile::CoinTile() : coins(4)
{
}

//=========================================================================

CoinTile::CoinTile(const sf::RectangleShape & rect, const sf::FloatRect & objectRect, const sf::Texture & texture)
	: Tile(rect, objectRect, texture), coins((rand() % 5) + 1) {}

//=========================================================================

void CoinTile::reduceCoins()
{
	coins--;
}

//==============================================================================  
CoinTile::~CoinTile()
{
}
