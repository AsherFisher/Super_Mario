#pragma once
#include <fstream>
#include "Menu.h"
#include "Sounds.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Mario.h"
#include "Constants.h"

//============================================================================

class Controller
{

	// main window of the game
	sf::RenderWindow m_win;

	// sprites for the menu 
	sf::Sprite m_background;
	sf::Sprite m_help;
	sf::Sprite m_credits;
	sf::Sprite cursor;
	sf::Texture texture;

	// object of menu to handle the menu 
	Menu m_menu;
    // to handle the board and draw.
	Board m_board;
	// to handle the sounds
	Sounds m_sounds;

public:

	//c'tor
	Controller();
	// Shows one page such as the 'help' page or the 'credits'.
	void showPic(sf::Sprite & pic);
	// load the textures of the buttons
	void loadButtons();
	// start run the menu 
	void run();
	// d'tor
	virtual ~Controller();
	
};

