#pragma once

#include "GameObject.h"
#include "Board.h"
#include <typeinfo>

//=========================================================================

// this will be thrown if an unknown collision is accured

struct UnknownCollision        
{
	UnknownCollision(GameObject& a, GameObject& b) : first(a), second(b)
	{
		std::cout << "Unkown collision of " << typeid(a).name() << " and "
			<< typeid(b).name() << std::endl;
	}
	GameObject& first;
	GameObject& second;
};

void processCollision(GameObject& object1, GameObject& object2, Board& board, const sf::FloatRect& interRect);