#pragma once
#include "Enemy.h"
#include "SolidTile.h"

//============================================================================

class Elevator :
	public Enemy
{
public:
	// c'tor
	Elevator();
	// c'tor
	Elevator(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName);
	// move the elevator up and down
	virtual void move(Board& board, sf::RenderWindow& wind);
	// reset the position and clock
	void resetPosition();
	// clock for moving up and down
	sf::Clock c;
	// d'tor
	~Elevator();
};

