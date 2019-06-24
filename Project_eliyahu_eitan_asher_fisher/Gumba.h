 #pragma once
#include "Enemy.h"

//======================================================================

class Gumba :
	public Enemy
{

public:

	// c'tor
	Gumba();
	// c'tor
	Gumba(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName);
	// func to move the gumba left and right
	virtual void move(Board& board, sf::RenderWindow& wind);
	// change the direction when collide
	void changeDirection(const Direction prevDir);
	// d'tor
	~Gumba();
};