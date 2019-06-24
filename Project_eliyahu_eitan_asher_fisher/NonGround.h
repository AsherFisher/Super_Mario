#pragma once
#include "StaticObject.h"

//======================================================================

class NonGround :
	public StaticObject
{
public:

	// c'tor
	NonGround(const sf::FloatRect & objectRect);
	// d'tor
	~NonGround();
};

