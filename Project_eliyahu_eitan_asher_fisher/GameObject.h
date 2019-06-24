#pragma once

#include <SFML\Graphics.hpp>
#include "Constants.h"


//=========================================================================

class GameObject
{
public:

	// c'tor
	GameObject();
	// c'tor
	GameObject(const sf::RectangleShape& shape, const sf::Texture& texture);
	// get the position of the shape
	sf::Vector2f getPosition() const;
	// func to get the global bounds of the shape
	virtual sf::FloatRect getRect() const = 0;
	// set texture to the shape
	void setTexture(const std::string& textureName);
	// virtual func to draw the shape
	virtual void draw(sf::RenderWindow& window);
	// d'tor
	virtual ~GameObject();

protected:

	// the bounds of the shape
	sf::RectangleShape m_shape;
	// the texture of the shape
	sf::Texture m_texture;
};
