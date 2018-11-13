#include "Player.h"

Player::Player(sf::Vector2f pos) : Entity(pos)
{
	if (!m_texture.loadFromFile("resources//images//player.png"))
	{
		std::cout << "problem loading texture file" << std::endl;
	}
	setTexture(m_texture);
}

void Player::update(double dt)
{
	handleInput(dt);
	m_vel += m_acc;

	limit();
	friction();
	boundry();

	m_pos += m_vel;
	m_sprite.setRotation(m_orientation);
	m_sprite.setPosition(m_pos);
	m_acc = sf::Vector2f(0, 0);
}

void Player::handleInput(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_acc.x += ACCELERATION * cos(m_orientation*(PI / 180)) * dt;
		m_acc.y += ACCELERATION * sin(m_orientation*(PI / 180)) * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_acc.x -= ACCELERATION * cos(m_orientation*(PI / 180)) * dt;
		m_acc.y -= ACCELERATION * sin(m_orientation*(PI / 180)) * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_orientation += ROTATION_SPEED * dt;
		if (m_orientation >= 360.f)
		{
			m_orientation = .0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_orientation -= ROTATION_SPEED * dt;
		if (m_orientation <= .0f)
		{
			m_orientation = 360.f;
		}
	}
}
