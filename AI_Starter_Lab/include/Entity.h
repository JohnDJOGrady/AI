#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MathHelper.h"

static const float MAX_VEL = 6.f;
static const float ACCELERATION = .1f;
static const float ROTATION_SPEED = .1f;

static const float SCREEN_WIDTH = 1600.f;
static const float SCREEN_HEIGHT = 900.f;

class Entity
{
public:
	Entity();
	Entity(sf::Vector2f pos);
	~Entity();

	virtual void render(sf::RenderWindow &window);
	virtual void setTexture(sf::Texture &texture);
	virtual void boundry();
	virtual void friction();
	virtual void limit();

	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getVelocity();
	virtual sf::Vector2f getAcceleration();

	virtual void setPosition(sf::Vector2f pos);
	virtual void setVelocity(sf::Vector2f vel);
	virtual void setAcceletation(sf::Vector2f acc);

protected:
	virtual double getNewOrientation();

	float m_orientation;
	float m_rotation;
	float m_speed;
	float m_targetOrientation;

	sf::Vector2f m_dir;
	sf::Vector2f m_pos;
	sf::Vector2f m_acc;
	sf::Vector2f m_vel;
	sf::Vector2f m_scaledSize;

	sf::Text m_text;
	sf::Font m_font;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};
#endif // !ENTITY_H