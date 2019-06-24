#include "InfoBar.h"
#include <iostream>

//========================================================================

InfoBar::InfoBar()
{
	m_score.setScore(0);

	//Font load
	if(!fonts::ib_font.loadFromFile(paths::font_path))
		throw(std::ios_base::failure("cant load Font"));
	m_text.setFont(fonts::ib_font);
	m_text.setCharacterSize(sizes::font_size);
	m_text.setFillColor(sf::Color::Green);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);
	m_text.setLetterSpacing(1.8);
	
	// the hearts image
	if(!textures::sh_heart.loadFromFile(paths::sh_heart))
		throw(std::ios_base::failure("cant load heart"));
	m_hearts.setTexture(textures::sh_heart);
	m_hearts.scale(.13, .13);
}

//============================================================================

void InfoBar::draw(sf::RenderWindow & win, int level)
{
	//Level
	m_text.setPosition(260.0, 10.0);
	m_ss.str(std::string()); //clear the string
	m_ss << "Level: " << level;
	m_text.setString(m_ss.str());
	win.draw(m_text);

	//Score
	m_text.setPosition(460.0, 10.0);
	m_ss.str(std::string()); //clear the string
	m_ss << "Score: " << m_score.getScore();
	m_text.setString(m_ss.str());
	win.draw(m_text);

	//	Lives left
	m_text.setPosition(700.0, 10.0);
	m_ss.str(std::string());
	m_ss << "Lives: ";
	m_text.setString(m_ss.str());
	win.draw(m_text);

	for (size_t i = 0; i < m_lives; i++)   // draw the hearts
	{
		m_hearts.setPosition(800.0 + 40 * i, 14.0);
		win.draw(m_hearts);
	}
}

//===========================================================================

void InfoBar::setLives(const int & amnt)
{
	m_lives = amnt;
}

//===========================================================================

size_t InfoBar::getLives()
{
	return m_lives;
}

//============================================================================

void InfoBar::resetScore()
{
	m_score.setScore(0);
	m_lives = 3;
}

//=============================================================================

InfoBar::~InfoBar()
{}
