#include "message.h"
#include <windows.h>

//======================================================================  

void z() { Sleep(4000); }
void g() { Sleep(1500); }

//======================================================================
message::message()
{
	//Font load
	fonts::ib_font.loadFromFile(paths::font_path);
	m_text.setFont(fonts::ib_font);
	m_text.setCharacterSize(sizes::mes_font_size);
	m_text.setFillColor(sf::Color::Green);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);


	//Images load
	if(!textures::game_over_txtr.loadFromFile(paths::massage_game_over_path))
		throw(std::ios_base::failure("cant load game over path"));
	if(!textures::game_completed_txtr.loadFromFile(paths::massage_game_completed_path))
		throw(std::ios_base::failure("cant load game completed path"));
	if(!textures::level_up_txtr.loadFromFile(paths::massage_level_up_path))
		throw(std::ios_base::failure("cant load level up path"));

	m_mas["game over"] = sf::Sprite(textures::game_over_txtr);
	m_mas["game completed"] = sf::Sprite(textures::game_completed_txtr);
	m_mas["level up"] = sf::Sprite(textures::level_up_txtr);
}

//======================================================================

void message::gameOver(sf::RenderWindow & win, int score, bool New)
{
	win.clear(sf::Color(0, 240, 240, 140));
	win.draw(m_mas["game over"]);
	printScore(win, score, New);
}

//======================================================================

void message::gameCompleted(sf::RenderWindow & win, int score, bool New)
{
	win.clear(sf::Color(0,240,240,140));
	win.draw(m_mas["game completed"]);
	printScore(win, score, New);
}

//======================================================================

void message::levelUp(sf::RenderWindow & win)
{
	win.clear(sf::Color(0, 240, 240, 140));
	win.draw(m_mas["level up"]);
	win.display();
	g();
}

//======================================================================

void message::printScore(sf::RenderWindow & win, int score, bool New)
{
	if (New)   // it's a new high score
	{
		m_text.setPosition(50.0, 450.0);
		m_ss.str(std::string()); //clear the string
		m_ss << "New high Score:";
		m_text.setString(m_ss.str());
		win.draw(m_text);
		m_text.setPosition(330.0, 570.0);
		m_ss.str(std::string()); //clear the string
		m_ss << score;
		m_text.setString(m_ss.str());
		win.draw(m_text);
		win.display();
		z();
	}
	else
	{
		m_text.setPosition(240.0, 500.0);
		m_ss.str(std::string()); //clear the string
		m_ss << "Score: " << score;
		m_text.setString(m_ss.str());
		win.draw(m_text);
		win.display();
		z();
	}
}

//======================================================================

message::~message()
{
}
