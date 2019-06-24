#include "Collision.h"
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Board.h"
#include "Mario.h"
#include "CoinTile.h"
#include "RemovableTile.h"
#include "SolidTile.h"
#include "Utilities.h"


//==========================================================================

namespace {


	void mario_mario(GameObject& mario,
		GameObject& mario2, Board& board, const sf::FloatRect& interRect) {}

	//=================================================================================

	void elevator_elevator(GameObject& elevator,
		GameObject& elevator2, Board& board, const sf::FloatRect& interRect) {}

	//===============================================================================
	void gumba_gumba(GameObject& gumba1,
		GameObject& gumba2, Board& board, const sf::FloatRect& interRect) {}

	//=============================================================================
	void mario_turtle(GameObject& mario,
		GameObject& turtle, Board& board, const sf::FloatRect& interRect)
	{

		Mario & marioRef = dynamic_cast<Mario&>(mario);
		Turtle & turtleRef = dynamic_cast<Turtle&>(turtle);

		// when collide, mario has a bit time to run and not hit again
		if (turtleRef.c.getElapsedTime().asSeconds() < 0.7)
			return;

		// check from what side the collition accured
		Direction intersectDir = intersectionType(mario.getRect(), turtle.getRect(), interRect);

		// if it's the first jump on the turtle
		if (turtleRef.getMode() != Smash && turtleRef.getMode() != Dead && intersectDir == Down)
		{
			turtleRef.setSpeed(500);
			turtleRef.c.restart();
			turtleRef.updateMode(Smash);
		}

		if (turtleRef.getMode() == Smash)
		{
			// if it's the second jump on the turtle
			if (intersectDir == Down && turtleRef.c.getElapsedTime().asSeconds() > 0.5)
			{
				turtleRef.setSpeed(300);
				board.TurtleDead(turtleRef);
			}
		}

		// if the turtle killed the mario
		if (intersectDir != Down && marioRef.getMode() != Dead && turtleRef.getMode() != Dead)
		{
			marioRef.updateMode(Dead);
			board.marioHit();
		}
	}
	//======================================================================================

	void mario_gumba(GameObject& mario,
		GameObject& gumba, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);
		Gumba & gumbaRef = dynamic_cast<Gumba&>(gumba);

		Direction intersectDir = intersectionType(mario.getRect(), gumba.getRect(), interRect);

		// mario jump on the gumba
		if (intersectDir == Down)
			board.TurtleDead(gumbaRef);

		// gumba killed the mario
		if (intersectDir != Down && marioRef.getMode() != Dead && gumbaRef.getMode() != Dead)
		{
			marioRef.updateMode(Dead);
			board.marioHit();
		}
	}

	//======================================================================================

	void mario_coin(GameObject& mario,
		GameObject& coin, Board& board, const sf::FloatRect& interRect) {}

	//===================================================================================

	void mario_coinTile(GameObject& mario,
		GameObject& coinTile, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead)
			return;

		CoinTile & CoinTileRef = dynamic_cast<CoinTile&>(coinTile);
		Direction intersectDir = intersectionType(mario.getRect(), coinTile.getRect(), interRect);

		// if mario jump to the coin from below
		if (intersectDir == Up)
		{
			if (CoinTileRef.getCoins() && marioRef.getMode() != Falling)
			{
				board.marioGotCoin(coinTile.getRect());
				CoinTileRef.reduceCoins();
			}
		}
		else if (intersectDir == Down)
			marioRef.updateMode(OnGround);

		marioRef.moveBack(intersectDir);

		if (!CoinTileRef.getCoins())  // if there is no more coins, change the image
			CoinTileRef.setTexture(paths::sh_used_tile);
	}

	//=================================================================================

	void mario_removableTile(GameObject& mario,
		GameObject& rTile, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead)
			return;

		RemovableTile & rTileRef = dynamic_cast<RemovableTile&>(rTile);
		Direction intersectDir = intersectionType(mario.getRect(), rTile.getRect(), interRect);

		if (intersectDir == Up)
		{
			if (marioRef.getMode() != Falling)
			{
				Sounds::play("explodeTile");
				board.deleteObject(rTileRef, false);
			}
		}
		else if (intersectDir == Down)
			marioRef.updateMode(OnGround);

		marioRef.moveBack(intersectDir);
	}

	//=====================================================================================

	void mario_SolidTile(GameObject& mario,
		GameObject& sTile, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(mario.getRect(), sTile.getRect(), interRect);

		if (intersectDir == Down)
			marioRef.updateMode(OnGround);

		marioRef.moveBack(intersectDir);
	}

	//=====================================================================================
	void mario_elevator(GameObject& mario,
		GameObject& elevator, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);
		Elevator &elevatorRef = dynamic_cast<Elevator&>(elevator);

		if (marioRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(mario.getRect(), elevator.getRect(), interRect);
		marioRef.updateMode(OnGround);
		
		marioRef.moveBack(intersectDir);
	}

	//=================================================================================
	void mario_door(GameObject& mario,
		GameObject& gate, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead)
			return;

		board.successLevel();
	}

	//==================================================================================

	void mario_nonGround(GameObject& mario,
		GameObject& nonGround, Board& board, const sf::FloatRect& interRect)
	{
		Mario & marioRef = dynamic_cast<Mario&>(mario);

		marioRef.updateMode(Dead);
		board.marioHit();
	}

	//=================================================================================

	void turtle_turtle(GameObject& turtle1,
		GameObject& turtle2, Board& board, const sf::FloatRect& interRect) {}

	//=================================================================================

	void turtle_solidTile(GameObject& turtle,
		GameObject& sTile, Board& board, const sf::FloatRect& interRect)
	{
		Turtle & turtleRef = dynamic_cast<Turtle&>(turtle);

		if (turtleRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(turtle.getRect(), sTile.getRect(), interRect);


		turtleRef.changeDirection(intersectDir);
	}

	//===========================================================================
	void turtle_nonGround(GameObject& turtle,
		GameObject& nonGround, Board& board, const sf::FloatRect& interRect)
	{
		board.deleteObject(turtle, true);
	}

	//=====================================================================================
	
	void gumba_nonGround(GameObject& gumba,
		GameObject& nonGround, Board& board, const sf::FloatRect& interRect)
	{
		board.deleteObject(gumba, true);
	}

	//=====================================================================================

	void gumba_solidTile(GameObject& gumba,
		GameObject& sTile, Board& board, const sf::FloatRect& interRect)
	{
		Gumba & gumbaRef = dynamic_cast<Gumba&>(gumba);

		if (gumbaRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(gumba.getRect(), sTile.getRect(), interRect);

		gumbaRef.changeDirection(intersectDir);
	}
	//==================================================================================

	void coin_coin(GameObject& coin1,
		GameObject& coin2, Board& board, const sf::FloatRect& interRect)
	{}

	//=====================================================================================

	void coin_coinTile(GameObject& coin,
		GameObject& coinBrick, Board& board, const sf::FloatRect& interRect)
	{
		Coin & coinRef = dynamic_cast<Coin&>(coin);
		board.deleteObject(coinRef, true);
	}

	//===================================================================================

	void coin_solidTile(GameObject& coin,
		GameObject& coinTile, Board & board, const sf::FloatRect& interRect)
	{}

	//===================================================================================

	void turtle_mario(GameObject& turtle,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_turtle(mario, turtle, board, interRect);
	}
	//=======================================================================================
	void gumba_mario(GameObject& gumba,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_gumba(mario, gumba, board, interRect);
	}
	//=======================================================================================

	void coin_mario(GameObject& coin,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_coin(mario, coin, board, interRect);
	}

	//====================================================================================

	void coinTile_mario(GameObject& coinTile,
		GameObject& hero, Board& board, const sf::FloatRect& interRect)
	{
		mario_coinTile(hero, coinTile, board, interRect);
	}

	//=====================================================================================

	void removableTile_mario(GameObject& rTile,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_removableTile(mario, rTile, board, interRect);
	}

	//=====================================================================================

	void solidTile_mario(GameObject& sTile,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_SolidTile(mario, sTile, board, interRect);
	}

	//====================================================================================

	void elevator_mario(GameObject& elevator,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_elevator(mario, elevator, board, interRect);
	}

	//================================================================================

	void nonGround_mario(GameObject& nonGroud,
		GameObject& mario, Board& board, const sf::FloatRect& interRect)
	{
		mario_nonGround(mario, nonGroud, board, interRect);
	}


	//=================================================================================
	void solidTile_turtle(GameObject& sTile,
		GameObject& turtle, Board& board, const sf::FloatRect& interRect)
	{
		turtle_solidTile(turtle, sTile, board, interRect);
	}

	//==========================================================================================

	void coinTile_coin(GameObject& cTile,
		GameObject& coin, Board& board, const sf::FloatRect& interRect)
	{
		coin_coinTile(coin, cTile, board, interRect);
	}


	//=========================================================================================
	using HitFunctionPtr = void(*)(GameObject&, GameObject&, Board&, const sf::FloatRect&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;

		phm[Key(typeid(Mario), typeid(Mario))] = &mario_mario;
		phm[Key(typeid(Gumba), typeid(Gumba))] = &gumba_gumba;
		phm[Key(typeid(Mario), typeid(Turtle))] = &mario_turtle;
		phm[Key(typeid(Mario), typeid(Gumba))] = &mario_gumba;
		phm[Key(typeid(Mario), typeid(Coin))] = &mario_coin;
		phm[Key(typeid(Mario), typeid(CoinTile))] = &mario_coinTile;
		phm[Key(typeid(Mario), typeid(RemovableTile))] = &mario_removableTile;
		phm[Key(typeid(Mario), typeid(SolidTile))] = &mario_SolidTile;
		phm[Key(typeid(Mario), typeid(NonGround))] = &mario_nonGround;
		phm[Key(typeid(Mario), typeid(Elevator))] = &mario_elevator;
		phm[Key(typeid(Turtle), typeid(Turtle))] = &turtle_turtle;
		phm[Key(typeid(Turtle), typeid(RemovableTile))] = &turtle_solidTile;
		phm[Key(typeid(Turtle), typeid(NonGround))] = &turtle_nonGround;
		phm[Key(typeid(Turtle), typeid(Turtle))] = &turtle_turtle;
		phm[Key(typeid(Turtle), typeid(SolidTile))] = &turtle_solidTile;
		phm[Key(typeid(Turtle), typeid(CoinTile))] = &turtle_solidTile;
		phm[Key(typeid(Gumba), typeid(SolidTile))] = &gumba_solidTile;
		phm[Key(typeid(Gumba), typeid(NonGround))] = &gumba_nonGround;
		phm[Key(typeid(Gumba), typeid(CoinTile))] = &gumba_solidTile;
		phm[Key(typeid(Gumba), typeid(Turtle))] = &turtle_turtle;
		phm[Key(typeid(Turtle), typeid(Gumba))] = &turtle_turtle;
		phm[Key(typeid(Turtle), typeid(Elevator))] = &turtle_turtle;
		phm[Key(typeid(Gumba), typeid(RemovableTile))] = &gumba_solidTile;
		phm[Key(typeid(Coin), typeid(Coin))] = &coin_coin;
		phm[Key(typeid(Coin), typeid(CoinTile))] = &coin_coinTile;
		phm[Key(typeid(Coin), typeid(SolidTile))] = &coin_solidTile;
		phm[Key(typeid(Mario), typeid(Door))] = &mario_door;
		phm[Key(typeid(Elevator), typeid(Elevator))] = &elevator_elevator;


		// symmetry
		phm[Key(typeid(Turtle), typeid(Mario))] = &turtle_mario;
		phm[Key(typeid(Gumba), typeid(Mario))] = &gumba_mario;
		phm[Key(typeid(Coin), typeid(Mario))] = &coin_mario;
		phm[Key(typeid(CoinTile), typeid(Mario))] = &coinTile_mario;
		phm[Key(typeid(RemovableTile), typeid(Mario))] = &removableTile_mario;
		phm[Key(typeid(SolidTile), typeid(Mario))] = &solidTile_mario;
		phm[Key(typeid(NonGround), typeid(Mario))] = &nonGround_mario;
		phm[Key(typeid(Elevator), typeid(Mario))] = &elevator_mario;
		phm[Key(typeid(SolidTile), typeid(Turtle))] = &solidTile_turtle;
		phm[Key(typeid(CoinTile), typeid(Coin))] = &coinTile_coin;

		return phm;
	}


	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace


//=============================================================================================

void processCollision(GameObject& object1, GameObject& object2, Board& board, const sf::FloatRect& interRect)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2, board, interRect);
}