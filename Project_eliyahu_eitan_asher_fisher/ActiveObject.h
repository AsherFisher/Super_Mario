#pragma once

#include "GameObject.h"
#include "Animation.hpp"
#include "Constants.h"

class Board;
//==========================================================================

class ActiveObject : public GameObject
{
public:
	
	ActiveObject();
	//c'tor gets: rectangle, texture name, animation name - path to xml file
	ActiveObject(const sf::RectangleShape& shape, const std::string & textureName, const std::string& animationName = "None");
	// set the position of the shape
	void setPosition(const sf::Vector2f& newPosition); 
    // reset position as the level start/restart
	virtual void resetPosition();
	// move back after collides with solid objects
	virtual void moveBack(const Direction prevDir);
	// get the default position of the shape
	sf::Vector2f getStartPosition();
	// virtual func to move all of the active objects
	virtual void move(Board& board, sf::RenderWindow& window) = 0;
	// virtual func to draw the objects to the window
	virtual void draw(sf::RenderWindow& window);
	// get the global bounds of the shape 
	virtual sf::FloatRect getRect() const;
	// virtual func to update the mode af the chracter 
	virtual void updateMode(const Mode newMode);
	// get the mode of the character - dead/onGround..
	Mode getMode();
	// set the speed of the character
	void setSpeed(const float newSpeed) { m_speed = newSpeed; }
	// restart the movement clock of the character 
	virtual void restartClock() { m_movementClock.restart(); }
	//d'tor
	virtual ~ActiveObject();

private:
    
	// the dafault position of the shape
	sf::Vector2f m_startPosition;

protected:

	// to handle the animation of the character
	AnimationManager m_anim;
	// to hold the current mode of the character
	Mode m_mode;
	// clock for move and jump
	sf::Clock m_jumpClock, m_movementClock;
	// the speed of the character
	float m_speed = 260;
	// to combine speed with clock
	float m_velocity;
};
