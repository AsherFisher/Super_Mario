#pragma once
#include "Enemy.h"

//===========================================================================
class Turtle :
	public Enemy
{

public:

	// c'tor
	Turtle();
	// c'tor
	Turtle(const sf::RectangleShape& shape,  const std::string & textureName, const std::string& animationName);
    // func to move the turtle left and right
	virtual void move(Board& board, sf::RenderWindow& wind);
	// change the direction when collide
	void changeDirection(const Direction prevDir);
	// clock to handle the smash option 
	sf::Clock c;
    // d'tor
	~Turtle();
};

