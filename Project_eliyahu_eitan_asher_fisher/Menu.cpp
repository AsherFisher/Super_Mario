#include "Menu.h"
#include "Sounds.h"
#include "Constants.h"
 

//===================================================================================

//	Assigns the menu properties and its buttons.
Menu::Menu()
	:
	m_play({ float(sizes::bt_play_x), float(sizes::bt_play_y) }),
	m_help({ float(sizes::bt_menu_x), float(sizes::bt_help_y) }),
	m_crds({ float(sizes::bt_menu_x), float(sizes::bt_crd_y) }),
	m_exit({ float(sizes::bt_menu_x), float(sizes::bt_exit_y) }),
	m_action(MenuAction::None)
{

	
	textures::menu_txtr.loadFromFile(paths::menu_path);
	if(!textures::bt_play_txtr.loadFromFile(paths::bt_play_path))
		throw(std::ios_base::failure("cant load play path"));
	if(!textures::bt_help_txtr.loadFromFile(paths::bt_help_path))
		throw(std::ios_base::failure("cant load help path"));
	if(!textures::bt_crds_txtr.loadFromFile(paths::bt_crds_path))
		throw(std::ios_base::failure("cant load credits path"));
	if(!textures::bt_exit_txtr.loadFromFile(paths::bt_exit_path))
		throw(std::ios_base::failure("cant load exit path"));

	m_background.setTexture(textures::menu_txtr);
	m_play.setTexture(textures::bt_play_txtr);
	m_help.setTexture(textures::bt_help_txtr);
	m_crds.setTexture(textures::bt_crds_txtr);
	m_exit.setTexture(textures::bt_exit_txtr);
}

//===================================================================================

void Menu::handleCursor(sf::Sprite & cursor, sf::RenderWindow & win)
{
	win.setMouseCursorVisible(false);
	sf::Vector2f mousePos = { float(sf::Mouse::getPosition(win).x),float(sf::Mouse::getPosition(win).y) };
	cursor.setPosition(mousePos);
}

//===================================================================================
//	Shows the menu and returns the user's choice.
MenuAction Menu::show(sf::RenderWindow & win, sf::Sprite &cursor)
{
	m_action = MenuAction::None;

	Sounds::play("menu");
	while (win.isOpen())
	{
		menuEvents(win);
		handleCursor(cursor, win);
		if (m_action != MenuAction::None)
			break;

		win.clear();

		win.draw(m_background);
		win.draw(cursor);
		m_play.draw(win);
		m_help.draw(win);
		m_crds.draw(win);
		m_exit.draw(win);
		
		win.display();
	}
	Sounds::pause("menu");

	return m_action;
}

//=======================================================================================

//	Handles the menu events such as mouse clicking or moving.
void Menu::menuEvents(sf::RenderWindow & win)
{
	sf::Event myEvent;

	while (win.pollEvent(myEvent))
	{
		sf::Vector2f mousePos = { float(sf::Mouse::getPosition(win).x),float(sf::Mouse::getPosition(win).y) };

		switch (myEvent.type)
		{
		case sf::Event::Closed:
			win.close();
			break;
		case sf::Event::MouseMoved:
		{
			if (m_play.contains(mousePos))
				m_play.hover();
			else
				m_play.nonHover();
			if (m_help.contains(mousePos))
				m_help.hover();
			else
				m_help.nonHover();
			if (m_crds.contains(mousePos))
				m_crds.hover();
			else
				m_crds.nonHover();
			if (m_exit.contains(mousePos))
				m_exit.hover();
			else
				m_exit.nonHover();
		}
		break;

		case sf::Event::KeyPressed:
		{
			if (myEvent.key.code == sf::Keyboard::Enter)
				m_action = MenuAction::Play;
		}
		break;

		case sf::Event::MouseButtonPressed:
		{
			if (m_play.pressed(sf::Mouse::getPosition(win)))
				m_action = MenuAction::Play;
			if (m_help.pressed(sf::Mouse::getPosition(win)))
				m_action = MenuAction::Help;
			if (m_crds.pressed(sf::Mouse::getPosition(win)))
				m_action = MenuAction::Credits;
			if (m_exit.pressed(sf::Mouse::getPosition(win)))
				m_action = MenuAction::Exit;
		}
		break;
		}
	}
}

//======================================================================================

Menu::~Menu()
{}

