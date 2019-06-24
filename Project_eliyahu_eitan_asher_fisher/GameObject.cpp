#include "GameObject.h"
//====================================================================================

GameObject::GameObject()
{
}

//====================================================================================

GameObject::GameObject(const sf::RectangleShape & shape, const sf::Texture& txtre)
	: m_shape(shape), m_texture(txtre)
{
	m_shape.setTexture(&m_texture);
}

//====================================================================================

sf::Vector2f GameObject::getPosition() const
{
	return m_shape.getPosition();
}

//====================================================================================

void GameObject::setTexture(const std::string& textureName)
{
	if(!m_texture.loadFromFile(textureName))
		throw(std::ios_base::failure("cant load Game Object texture"));
	m_shape.setTexture(&m_texture);
}

//====================================================================================

void GameObject::draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

//====================================================================================

GameObject::~GameObject()
{
}
