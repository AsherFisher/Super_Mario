#pragma once
#include "Constants.h"
#include <SFML\Graphics.hpp>
#include <sstream>
#include "Score.h"

//============================================================================

class InfoBar
{
public:
	// c'tor
	InfoBar();
	// draw the info bar - score, lives, etc.
	virtual void draw(sf::RenderWindow & win, int level);
    // set the lives 
	void setLives(const int & amnt);
	// get the lives
	size_t getLives();
	// reset the score and lives
	void resetScore();
	// to handle the score 
	Score m_score;
	// d'tor
	~InfoBar();

private:

	// lives of the mario
	size_t m_lives = 3;
	// to handle the infobar text
	sf::Text m_text;
	// for reading the input to draw
	std::stringstream m_ss;
	// the hearts images
	sf::Sprite m_hearts;
};

