#include "GameButton.h"
#include "Constants.h"
#include "Sounds.h"

//	Assigns the position.
GameButton::GameButton(const sf::Vector2f & pos)
	:
	m_mouseHover(false)
{
	m_sprite.setPosition(pos);
}

GameButton::~GameButton()
{}

//	Sets the button's texture.
void GameButton::setTexture(const sf::Texture & texture)
{
	m_sprite.setTexture(texture);
}

//	Draws the button down to the window.
void GameButton::draw(sf::RenderWindow & win)
{
	win.draw(m_sprite);
}
sf::FloatRect GameButton::bounds() const
{
	return m_sprite.getGlobalBounds();
}
//	Returns whether the game-button contains the given point or not.
bool GameButton::contains(const sf::Vector2f & point) const
{
	return bounds().contains(point);
}

//	Returns whether the button was pressed or not, and if it was then plays the 'click' sound.
bool GameButton::pressed(const sf::Vector2i & mousePos) const
{
	if (contains(sf::Vector2f{ mousePos }))
	{
		Sounds::play("click");
		return true;
	}
	return false;
}

//	Sets the mouse-hover effect on.
void GameButton::hover()
{
	if (!m_mouseHover)
	{
		m_sprite.setColor({ 255, 255, 255, 140 });
		m_mouseHover = true;
		Sounds::play("hover");
	}
}

//	Sets the mouse-hover effect off.
void GameButton::nonHover()
{
	if (m_mouseHover)
	{
		m_sprite.setColor({ 255, 255, 255, 255 });
		m_mouseHover = false;
	}
}
