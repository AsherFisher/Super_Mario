#pragma once
#include "Constants.h"
#include <SFML\Graphics.hpp>
#include <sstream>
#include <map>
#include <string>
#include "Constants.h"


//==========================================================================

class message
{

public:

	// c'tor
	message();
	// game over message - when lost
	void gameOver(sf::RenderWindow & win, int score, bool New);
	// game won message - when won
	void gameCompleted(sf::RenderWindow & win, int score, bool New);
	// func to print the score message
	void printScore(sf::RenderWindow & win, int score, bool New);
	// new level message
	void levelUp(sf::RenderWindow & win);
	// d'tor
	~message();

private:
	// to handle the text of the message
	sf::Text m_text;
	// to read the wanted message
	std::stringstream m_ss;
	// map to set the sprite based on the message
	std::map<sf::String, sf::Sprite> m_mas;

};

