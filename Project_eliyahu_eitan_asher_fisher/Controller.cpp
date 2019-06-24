#include "Controller.h"
#include <iostream>



//========================================================================

Controller::Controller() :
	m_win(sf::VideoMode(sizes::win_wd, sizes::win_ht), "super mario", sf::Style::Close)
{
	loadButtons();
}

//============================================================================

void Controller::run()
{

	// check what button the user pressed
	MenuAction action = m_menu.show(m_win, cursor);
	
	while (action != MenuAction::Exit)  
	{
		if (action == MenuAction::Play)
			m_board.startPlay(m_win);   // start the game
		if (action == MenuAction::Help)
			showPic(m_help);            // show help screen
		if (action == MenuAction::Credits)
			showPic(m_credits);         // show credits screen

		action = m_menu.show(m_win, cursor);
	}
	
}

//==================================================================================

//	Shows one page such as the 'help' page or the 'credits'.
void Controller::showPic(sf::Sprite & pic)
{
	GameButton okBtn{ {float(sizes::bt_back_x), float(sizes::bt_back_y)} };

	if (!textures::bt_v_txtr.loadFromFile(paths::bt_v_path))
		throw(std::ios_base::failure("cant load back image"));
	okBtn.setTexture(textures::bt_v_txtr);

	while (m_win.isOpen())
	{
		sf::Event myEvent;

		m_menu.handleCursor(cursor, m_win);
		
		while (m_win.pollEvent(myEvent))
		{
			switch (myEvent.type)
			{
			case sf::Event::Closed:
				m_win.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (okBtn.pressed(sf::Mouse::getPosition(m_win)))
					return;
			case sf::Event::MouseMoved:
				if (okBtn.contains({ float(sf::Mouse::getPosition(m_win).x), float(sf::Mouse::getPosition(m_win).y) }))
					okBtn.hover();
				else
					okBtn.nonHover();
				break;
			default:
				break;
			}
		}

		m_win.clear();
		m_win.draw(pic);
		okBtn.draw(m_win);
		m_win.draw(cursor);
		m_win.display();
	}
}


//===============================================================================

void Controller::loadButtons()
{
		if (!textures::help_txtr.loadFromFile(paths::help_path))
			throw(std::ios_base::failure("cant load help"));
		m_help.setTexture(textures::help_txtr);

		if (!textures::crds_txtr.loadFromFile(paths::crds_path))
			throw(std::ios_base::failure("cant load crdits"));
		m_credits.setTexture(textures::crds_txtr);

		if (!texture.loadFromFile(paths::cursor_path))
			throw(std::ios_base::failure("cant load cursor"));

		cursor.setTexture(texture);	
}

//=============================================================================

Controller::~Controller()
{
}
//===========================================================================
