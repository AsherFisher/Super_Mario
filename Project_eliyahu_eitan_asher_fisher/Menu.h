#pragma once
#include "GameButton.h"
#include "Board.h"

//=========================================================================

enum MenuAction
 { Play, Help, Credits, Exit, None };

//=========================================================================
class Menu
{
public:

	// c'tor
	Menu();
	// handle the new modern cursor
	void handleCursor(sf::Sprite & cursor, sf::RenderWindow & win);
	// func to show the menu 
	MenuAction show(sf::RenderWindow & win, sf::Sprite &cursor);
	// func to handle the events of the menu
	void menuEvents(sf::RenderWindow & win);
	// d'tor
	~Menu();

private:

	// the background of the menu
	sf::Sprite m_background;

	// the 4 buttons
	GameButton m_play;
	GameButton m_help;
	GameButton m_crds;
	GameButton m_exit;

	// enum to act based on user input
	MenuAction m_action;

};
