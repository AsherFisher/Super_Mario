#pragma once

#include "ActiveObject.h"
#include "constants.h"


//=========================================================================

class Enemy 
	: public ActiveObject
{
public:

	// c'tor
	Enemy();
	// c'tor
	Enemy(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName);
	// virtual func to move the enemy
	virtual void move(Board& board, sf::RenderWindow& window);
	// d'tor
	~Enemy();

protected:

	// enum to handle the direction to move
	Direction m_dir;
};
