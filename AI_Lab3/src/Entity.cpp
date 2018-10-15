#include "Entity.h"
#include <iostream>

Entity::Entity()
{
	m_orientation = 0;
	if (!m_font.loadFromFile("resources//font//ariblk.ttf"))
	{
		std::cout << "Error loading font, diagnose issue" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(24);
}

Entity::Entity(sf::Vector2f pos) :
	Entity()
{
	m_pos = pos;
	m_sprite.setRotation(m_orientation);
}

Entity::~Entity()
{
	delete this;
}

/// <summary>
/// Setting up the texture and dimensions of the sprite object.
/// </summary>
/// <param name="texture">Texture to apply to the sprite</param>
void Entity::setTexture(sf::Texture &texture)
{
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setTexture(m_texture);
	m_pos = m_pos - sf::Vector2f(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().width / 2);
	m_sprite.setPosition(m_pos);
	if (m_sprite.getLocalBounds().width > 200 && m_sprite.getLocalBounds().width < 400)
	{
		m_sprite.setScale(.5, .5);
	}
	if (m_sprite.getLocalBounds().width > 400)
	{
		m_sprite.setScale(.25, .25);
	}
	m_scaledSize = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}

///<summary>
/// limit the velocity to a pre-defined max speed
/// </summary>
void Entity::limit()
{
	float speed = sqrt(mag(m_vel));
	if (speed > MAX_VEL)
	{
		m_vel.x *= speed;
		m_vel.y *= speed;
	}
}

double Entity::getNewOrientation()
{
	if (mag(m_vel) > 0)
	{
		return atan2(m_vel.y, m_vel.x)*(180 / PI);
	}
	else
	{
		return m_orientation;
	}
}

sf::Vector2f Entity::getPosition()
{
	return m_pos;
}

sf::Vector2f Entity::getVelocity()
{
	return m_vel;
}

sf::Vector2f Entity::getAcceleration()
{
	return m_acc;
}

void Entity::setPosition(sf::Vector2f pos)
{
	m_pos = pos;
	m_sprite.setPosition(m_pos);
}

void Entity::setVelocity(sf::Vector2f vel)
{
	m_vel = vel;
}

void Entity::setAcceletation(sf::Vector2f acc)
{
	m_acc = acc;
}

/// <summary>
/// Wrap around boundry
/// </summary>
void Entity::boundry()
{
	sf::Vector2f dimension = sf::Vector2f(m_scaledSize.x, m_scaledSize.y);
	if (m_pos.x < 0.0f)
	{
		m_pos.x = 1600.f;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 900.f;
	}
	if (m_pos.x > 1600.f)
	{
		m_pos.x = 0.0f;
	}
	if (m_pos.y > 900.f)
	{
		m_pos.y = 0.0f;
	}
}

void Entity::friction()
{
	m_vel.x *= .95f;
	m_vel.y *= .95f;
}

void Entity::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	window.draw(m_text);
}
