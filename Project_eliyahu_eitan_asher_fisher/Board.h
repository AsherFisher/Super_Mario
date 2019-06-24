#pragma once

//============   include section  ===================================

#include <fstream>
#include <vector>
#include <memory> 
#include "GameObject.h"
#include "FileReader.h"
#include "StaticObject.h"
#include "ActiveObject.h"
#include "SolidTile.h"
#include "RemovableTile.h"
#include "CoinTile.h"
#include "Mario.h"
#include "level.hpp"
#include <string>
#include "Collision.h"
#include "Turtle.h"
#include "Coin.h"
#include "NonGround.h"
#include "Door.h"
#include "Elevator.h"
#include "InfoBar.h"
#include "Sounds.h"
#include "message.h"
#include "Gumba.h"
#include "Score.h"

//=====================================================================

class Board
{

public:
	// c'tor
	Board();
	// load the backgrounds of the levels
	void loadBackgrounds();
	// update members, sounds, etc. at when level starts
	void handleStartLevel(sf::RenderWindow & window, std::string levelName, Level & level);
	// reset the score
	void resetScore();
	// handle level finshed/ game over etc.
	void checkDiffrentsEnds(sf::RenderWindow & window);
	// clear the vectors of the objects 
	void clear();
	// load the level and start running the run game func in loop
	void startPlay(sf::RenderWindow & window);
	// to use from other class, set the level name
	void setLevelName(const std::string& levelName);
	// main loop of the game - draw, move, etc.
	bool runLevel(int& levelNum, sf::RenderWindow & window, std::string levelName);
	// working with tmx file, read the objects and create them.
	void createLevelObjects(Level& level, const int levelNum);
	// check witch object to create
	void createObject(Object& gameObject, const int levelNum);
	void createTile(const sf::FloatRect& objectRect, const enum TileType type, const std::string& textureName = "None");
	void createMario(const std::string& textureName, const std::string& animationName, const sf::FloatRect& objectRect);
	void createTurtle(const std::string & textureName, const std::string & animationName, const sf::FloatRect & objectRect);
	void createGumba(const std::string & textureName, const std::string & animationName, const sf::FloatRect & objectRect);
	void createElevator(const std::string & textureName, const std::string & animationName, const sf::FloatRect & objectRect);
	void createCoin(const std::string& textureName, const std::string& animationName, sf::FloatRect& objectRect);
	void createNonGround(const sf::FloatRect& objectRect);
	void createDoor(const sf::FloatRect& objectRect);
	// reset the level when mario is hit
	void marioHit();
	// the main func - draw active and static and move only the active objects
	void drawAndMove(Level level, sf::RenderWindow & window);
	// check if collision is accured
	void checkCollision(GameObject& activeObject, const float velocity);
	// this func will call when mario jump on turtle or gumba
	void TurtleDead(Enemy& enemy);
	// this func will call when mario collide with coin tile from down
	void marioGotCoin(const sf::FloatRect& coinTileRect);
	// delete object from the vector based on position
	void deleteObject(const GameObject& object, bool isActive);
	// this func will call when mario reached the door
	void successLevel();
	// func to handle best score 
	bool handleEndScore();
	// d'tor
	~Board();

private:

	// vector of all the static objects
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	// vector of all the active objects
	std::vector<std::unique_ptr<ActiveObject>> m_activeObjects;
	// this object is for handling the tmx file
	Level level;
	// level name
	std::string m_levelName;
	sf::Clock m_clock;
	// arr of sprites that will be loaded according the current level
	sf::Sprite m_background[sizes::numofLevels];
	// view to keep the backgrounf steady
	sf::View m_graphView;
	// to handle the data of the game in the top of the window
	InfoBar m_info;
	// main view of the game - will move with mario
	sf::View gameView;
	// level number
	int levelNum = 0;
	// to handle reading level names
	std::stringstream m_ss;
	// is the level done sucssesfuly
	bool m_levelFinished;
	// player end
	bool m_gameOver;
	// to handling printing messeges in the window
	message m_mes;
	

};

    // enum of the 3 types of tiles
	const enum TileType { Solid, Removable, coinTile };
