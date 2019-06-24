#pragma once

#include "Tile.h"

//============================================================================

class CoinTile
	: public Tile
{
public:
	// c'tor
	CoinTile();
	// c'tor
	CoinTile(const sf::RectangleShape& rect, const sf::FloatRect& objectRect, const sf::Texture& texture);
	// get the amount of coins that left in the tile
	int getCoins() const { return coins; }
	// reduce the amount of coins in the tile
	void reduceCoins();
	// d'tor
	~CoinTile();

private:

	// number of coins in the tile
	int coins;
};

