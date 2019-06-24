#pragma once
#include "StaticObject.h"

//=======================================================================

class Door :
	public StaticObject
{
public:

	//c'tor
	Door(const sf::FloatRect& objectRect);
	// d'tor
	~Door();
};

