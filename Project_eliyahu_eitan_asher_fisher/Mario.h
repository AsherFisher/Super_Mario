#pragma once

#include <vector>
#include "ActiveObject.h"
#include <SFML\Audio.hpp>

//===============================================================================

class Mario : public ActiveObject
{
public:

	// c'tor
	Mario();
	// c'tor
	Mario(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName, const sf::View& view);
	// func to move the mario based on the user input
	virtual void move(Board& board, sf::RenderWindow& wind);
	// func to draw the mario eith the animation
	virtual void draw(sf::RenderWindow& window);
	// func to move back the mario when collide with solid object
	virtual void moveBack(const Direction prevDir);
	// reset the position of the mario
	virtual void resetPosition();
	// func to calc where the mario should move based on the user input
	void calcDirection(sf::RenderWindow& wind, Board& board);
	// set the current mode based on the user input
	void handleMode();
	// set the matching animation based on the mode of the mario
	void setAnimation();
	// d'tor
	~Mario();

private:

	// to keep the center at the mario position
	sf::View m_view;
	// to calc how many pixel should the mario move
	sf::Vector2f m_direction;
	// bolliens members to know how to move the mario
	bool m_jump = false;
	bool m_walkRight = false;
	bool m_walkLeft = false;
	bool m_turnRight = true;
	
};

