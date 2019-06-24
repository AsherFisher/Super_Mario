#pragma once

#include "ActiveObject.h"

//======================================================================

class Coin
	: public ActiveObject
{
public:

	// c'tor
	Coin();
	// c'tor
	Coin(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName);
	// virtual func, based on the move of the active object - move the coin up and down 
	virtual void move(Board& board, sf::RenderWindow& window);
	// d'tor
	~Coin();

private:

	// to handle the direction of the coin
	sf::Clock m_Clock;
};


