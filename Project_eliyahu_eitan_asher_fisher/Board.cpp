#include "Board.h"
#include <iostream>
#include "Utilities.h"


//=============================================================================

Board::Board()
{
	loadBackgrounds();
}

//=============================================================================

void Board::loadBackgrounds()
{
	// load the backgrounds of the levels
	if(!textures::backrnd_game_txtr1.loadFromFile(paths::backrnd_game_path1))
		throw(std::ios_base::failure("cant load background texture1"));
	m_background[0].setTexture(textures::backrnd_game_txtr1);

	if(!textures::backrnd_game_txtr2.loadFromFile(paths::backrnd_game_path2))
		throw(std::ios_base::failure("cant load background texture2"));
    m_background[1].setTexture(textures::backrnd_game_txtr2);

	if(!textures::backrnd_game_txtr3.loadFromFile(paths::backrnd_game_path3))
		throw(std::ios_base::failure("cant load background texture3"));
	m_background[2].setTexture(textures::backrnd_game_txtr3);
}

//=====================================================================================

void Board::handleStartLevel(sf::RenderWindow & window, std::string levelName, Level & level)
{
	Sounds::play("game");

	clear();
	setLevelName(levelName);

	m_graphView = window.getDefaultView();  // the background should stay steady 
	gameView = window.getDefaultView();

	if(!level.LoadFromFile(m_levelName)) 	// load the tmx file
		throw(std::ios_base::failure("cant load tmx file"));
	createLevelObjects(level, levelNum);

	m_clock.restart();

	m_levelFinished = false;
}

//=============================================================================

void Board::setLevelName(const std::string& levelName)
{
	m_levelName = levelName;
}

//=============================================================================

void Board::resetScore()
{
	m_info.resetScore();
}

//=============================================================================

void Board::startPlay(sf::RenderWindow & window)
{
	resetScore();
	levelNum = 0;
	m_gameOver = false;

	// run while levels not ends and user not lost total
	while (levelNum < sizes::numofLevels && !m_gameOver)  
	{
		std::string levelName = paths::level_path;
		m_ss.str(std::string());     // clear the string
		m_ss << levelName << levelNum + 1 << ".tmx";
		levelName = m_ss.str();

		if (runLevel(levelNum, window, levelName))  // level end sucsesfully
		{
			levelNum++;
			continue;
		}
		else
			break;
	}
}

//=============================================================================

bool Board::runLevel(int &levelNum, sf::RenderWindow & window, std::string levelName)
{

	Level level;
	handleStartLevel(window, levelName, level);
	
	while (window.isOpen() && !m_levelFinished && !m_gameOver)
	{
		window.clear();

		window.setView(m_graphView);  // view for the background
		window.draw(m_background[levelNum]);

		window.setView(gameView);     // the main view follow the mario

		drawAndMove(level, window);

		gameView = window.getView();
		window.setView(m_graphView);

		m_info.draw(window, levelNum + 1);  // draw the info bar
		window.display();
	}

	Sounds::pause("game");

	checkDiffrentsEnds(window);  // find out why the loop is done and print message accordingly
	return true;
}

//=============================================================================

void Board::checkDiffrentsEnds(sf::RenderWindow & window)
{
	// to know what messege to print
	if (levelNum + 1 == sizes::numofLevels && !m_gameOver)  // the mario won all the levels
		m_mes.gameCompleted(window, m_info.m_score.getScore(), handleEndScore());
	else if (m_gameOver)                                    // the mario lost
		m_mes.gameOver(window, m_info.m_score.getScore(), handleEndScore());
	else                                                    // the mario move to next level
		m_mes.levelUp(window);
}

//=============================================================================

void Board::successLevel()  
{
	m_levelFinished = true;
	m_info.m_score.setScore(m_info.m_score.getScore() + 200);
}

//=============================================================================

bool Board::handleEndScore()  // check wether user sets best score or not
{
	if (!m_info.m_score.checkBest(m_info.m_score.getScore()))
	{
		if (m_levelFinished)
			Sounds::play("gameWon");
		return false;
	}
	else    //new high score
	{
		m_info.m_score.setBest(m_info.m_score.getScore());
		if (!m_gameOver)
			Sounds::play("applause");
		return true;  
	}
}

//=============================================================================

void Board::clear()
{
	m_activeObjects.clear();
	m_staticObjects.clear();
}

//=============================================================================

void Board::drawAndMove(Level level, sf::RenderWindow & window)
{
	level.Draw(window);  // draw the objects at the tmx file
	
	// draw the objects in the vectors
	std::for_each(m_staticObjects.begin(), m_staticObjects.end(), [&window](const auto & dr) { dr->draw(window); });
	std::for_each(m_activeObjects.begin(), m_activeObjects.end(), [&window](const auto & dr) { dr->draw(window); });

	// move func, works by polymorphism
	for (int i = 0; i < m_activeObjects.size(); ++i)
		m_activeObjects[i]->move(*this, window);
}

//============================================================================

void Board::createLevelObjects(Level & lvl, const int levelNum)
{
	std::vector<Object> levelObjects;
	levelObjects = lvl.GetAllObjects();   // from the tmx file

	for (size_t i = 0; i < levelObjects.size(); ++i)  
		createObject(levelObjects[i], levelNum);
}

//===================================================================================

void Board::createObject(Object& gameObj, const int levelNum)
{

	// check the name of the object in the tmx file, and create the object accordingly

	if (gameObj.name == "SolidTile")
		createTile(gameObj.rect, Solid);

	else if ((gameObj.name == "CoinTile"))
		createTile(gameObj.rect, coinTile, paths::sh_coinTile);

	else if ((gameObj.name == "RemovableTile"))
		createTile(gameObj.rect, Removable, paths::sh_removableTile);

	if (gameObj.name == "Mario")
		createMario(paths::sh_animation_mario, paths::anim_mario, gameObj.rect);

	if (gameObj.name == "Turtle")
		createTurtle(paths::sh_animation_turtle, paths::anim_turtle, gameObj.rect);

	if (gameObj.name == "Gumba")
		createGumba(paths::sh_animation_gumba, paths::anim_gumba, gameObj.rect);

	if (gameObj.name == "NonGround")
		createNonGround(gameObj.rect);

	if (gameObj.name == "Door")
		createDoor(gameObj.rect);

	if (gameObj.name == "Elevator")
		createElevator(paths::sh_animation_elevator, paths::anim_elevator, gameObj.rect);
}

//===================================================================================

void Board::createTile(const sf::FloatRect& objectRect, const enum TileType type, const std::string& textureName)
{
	sf::Texture texture;
	sf::RectangleShape rect;

	if (type != Solid)
		texture.loadFromFile(textureName);

	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition({ objectRect.left, objectRect.top });
	rect.setSize({ objectRect.width, objectRect.height });
	rect.setTexture(&texture);

	if (type == Solid)
		m_staticObjects.push_back(std::make_unique<SolidTile>(objectRect));
	else if (type == Removable)
		m_staticObjects.push_back(std::make_unique<RemovableTile>(rect, objectRect, texture));
	else if (type == coinTile)
		m_staticObjects.push_back(std::make_unique<CoinTile>(rect, objectRect, texture));
}

//======================================================================================

void Board::createMario(const std::string& textureName, const std::string& animationName, const sf::FloatRect& objectRect)
{
	sf::View gameView(sizes::viewSize);  
	sf::RectangleShape rect;

	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition({ objectRect.left, objectRect.top });
	rect.setSize({ objectRect.width, objectRect.height });

	gameView.setCenter(rect.getPosition());  // this view track the mario

	m_activeObjects.push_back(std::make_unique<Mario>(rect, textureName, animationName, gameView));
}

//===========================================================================================

void Board::createTurtle(const std::string& textureName, const std::string& animationName, const sf::FloatRect& objectRect)
{
	AnimationManager anim;
	sf::RectangleShape rect;

	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition({ objectRect.left, objectRect.top });
	rect.setSize({ objectRect.width, objectRect.height });

	m_activeObjects.push_back(std::make_unique<Turtle>(rect, textureName, animationName));
}
//==================================================================================

void Board::createGumba(const std::string& textureName, const std::string& animationName, const sf::FloatRect& objectRect)
{
	AnimationManager anim;
	sf::RectangleShape rect;

	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition({ objectRect.left, objectRect.top });
	rect.setSize({ objectRect.width, objectRect.height });

	m_activeObjects.push_back(std::make_unique<Gumba>(rect, textureName, animationName));
}
//===========================================================================================

void Board::createElevator(const std::string& textureName, const std::string& animationName, const sf::FloatRect& objectRect)
{
	AnimationManager anim;
	sf::RectangleShape rect;

	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition({ objectRect.left, objectRect.top });
	rect.setSize({ objectRect.width, objectRect.height });

	m_activeObjects.push_back(std::make_unique<Elevator>(rect, textureName, animationName));
}
//==================================================================================

void Board::createNonGround(const sf::FloatRect & objectRect)
{
	m_staticObjects.push_back(std::make_unique<NonGround>(objectRect));
}

//==================================================================================

void Board::createDoor(const sf::FloatRect & objectRect)
{
	m_staticObjects.push_back(std::make_unique<Door>(objectRect));
}

//===================================================================================

void Board::TurtleDead(Enemy & enemy)
{
	if (enemy.getMode() != Dead) // collide can accured multiple times
	{
		enemy.updateMode(Dead);

		Sounds::play("killEnemy");
        // add score when enemy is killed
		m_info.m_score.setScore(m_info.m_score.getScore() + sizes::killValue);
	}
}

//====================================================================================

void Board::checkCollision(GameObject & movingObj, const float velocity)
{
	sf::FloatRect movingRect = movingObj.getRect();
	sf::FloatRect intersectionRect;

	movingRect.height -= 4.5;
	movingRect.width -= 4.5;

	for (unsigned int i = 0; i < m_activeObjects.size(); ++i)  // collision of active with active
		if (movingRect.intersects(m_activeObjects[i]->getRect(), intersectionRect))
			processCollision(movingObj, *m_activeObjects[i], *this, intersectionRect);

	for (unsigned int i = 0; i < m_staticObjects.size(); ++i)  // collision of active with static 
		if (movingRect.intersects(m_staticObjects[i]->getRect(), intersectionRect))
		{
			// to avoid jiterring 
			switch (intersectionType(movingRect, m_staticObjects[i]->getRect(), intersectionRect))
			{
			case Up:
				movingRect.top += velocity;
				break;
			case Down:
				movingRect.top -= velocity;
				break;
			case Right:
				movingRect.left -= velocity;
				break;
			case Left:
				movingRect.left += velocity;
				break;
			}
			processCollision(movingObj, *m_staticObjects[i], *this, intersectionRect);
		}
}

//==========================================================================================

void Board::marioGotCoin(const sf::FloatRect& coinTileRect)
{
	sf::FloatRect coinRect = coinTileRect;

	m_info.m_score.setScore(m_info.m_score.getScore() + sizes::CoinValue);

	// add coin and it's animation
	createCoin(paths::sh_animation_coin, paths::anim_coin, coinRect);
}

//==========================================================================================

void Board::createCoin(const std::string & textureName, const std::string& animationName, sf::FloatRect & objectRect)
{
	AnimationManager anim;
	sf::RectangleShape rect;

	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition({ objectRect.left, objectRect.top - 32 });
	rect.setSize({ objectRect.width, objectRect.height });

	Sounds::play("coin");
	m_activeObjects.push_back(std::make_unique<Coin>(rect, textureName, animationName));
}

//===========================================================================================

void Board::marioHit()
{
	Sounds::play("KillMario");
	m_info.setLives(m_info.getLives() - 1);

	for (auto & e : m_activeObjects)  // reset all the active objects
	{
		e->resetPosition();
		e->setSpeed(260);
		e->restartClock();
		e->updateMode(Falling);
	}

	if (!m_info.getLives())  // player is out of lives
	{
		m_gameOver = true;
		Sounds::play("endLevel");
	}
	else
		Sounds::play("KillMario");

}

//================================================================================

void Board::deleteObject(const GameObject & object, bool isActive)
{
	if (isActive)   // if the game object is an active object
	{
		for (unsigned int i = 0; i < m_activeObjects.size(); ++i)
			if (m_activeObjects[i]->getPosition() == object.getPosition())
			{
				m_activeObjects.erase(m_activeObjects.begin() + i);
				return;
			}
	}

	for (unsigned int i = 0; i < m_staticObjects.size(); ++i)
		if (m_staticObjects[i]->getPosition() == object.getPosition())
		{
			m_staticObjects.erase(m_staticObjects.begin() + i);
			break;
		}
}

//================================================================================

Board::~Board()
{
}

//================================================================================