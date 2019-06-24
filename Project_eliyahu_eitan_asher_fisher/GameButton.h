#pragma once
#include "GameObject.h"
#include "Animation.hpp"


//============================================================================

class GameButton 
{

public:
	GameButton(const sf::Vector2f & pos);
	~GameButton();
	void setTexture(const sf::Texture & texture);
	virtual void draw(sf::RenderWindow & win);
	virtual bool contains(const sf::Vector2f & point) const;
	virtual sf::FloatRect bounds() const;
	bool pressed(const sf::Vector2i & mousePos) const;
	void hover();
	void nonHover();

private:

	bool m_mouseHover;
	sf::Sprite m_sprite;
};
