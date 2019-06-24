#pragma once
#include "Constants.h"

//============================================================================

class Utilities
{
public:

	// c'tor
	Utilities();
	// d'tor
	~Utilities();
};


// func to check from witch side the intersection accured
Direction intersectionType(const sf::FloatRect& first, const sf::FloatRect& second, const sf::FloatRect& intersectionRect);
