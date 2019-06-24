#include "Utilities.h"

//=========================================================================

Utilities::Utilities()
{
}

//==========================================================================

// check from what direction the collition accured
Direction intersectionType(const sf::FloatRect & first, const sf::FloatRect & second, const sf::FloatRect& intersectionRect)
{
	if (intersectionRect.width + 2 > intersectionRect.height)
		return (first.top < second.top ? Down : Up);

	return (first.left < second.left ? Right : Left);
}

//=======================================================================

Utilities::~Utilities()
{
}
