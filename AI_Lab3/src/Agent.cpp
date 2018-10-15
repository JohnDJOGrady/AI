#include "Agent.h"

Agent::Agent()
{
	m_null = true;
}

Agent::Agent(sf::Vector2f pos, algorithim behaviour) : Entity(pos)
{
	m_null = false;
	// seed random number srand(0);
	m_behaviour = behaviour;
	if (m_behaviour == SEEK)
	{
		if (!m_texture.loadFromFile("resources//images//player.png"))
		{
			std::cout << "problem loading texture file" << std::endl;
		}
		setTexture(m_texture);
		m_text.setString("Seek");
		m_sprite.setColor(sf::Color::Green);
		m_sprite.setScale(.5, .5);
	}
	if (m_behaviour == ARRIVE)
	{
		if (!m_texture.loadFromFile("resources//images//player.png"))
		{
			std::cout << "problem loading texture file" << std::endl;
		}
		m_text.setString("Arrive");
		setTexture(m_texture);
		m_sprite.setScale(.25, .25);
	}
	if (m_behaviour == FLEE)
	{
		if (!m_texture.loadFromFile("resources//images//alien.png"))
		{
			std::cout << "problem loading texture file" << std::endl;
		}
		m_text.setString("Flee");
		setTexture(m_texture);
		m_sprite.setScale(.25, .25);
	}
	if (m_behaviour == WANDER)
	{
		if (!m_texture.loadFromFile("resources//images//wander.png"))
		{
			std::cout << "problem loading texture file" << std::endl;
		}
		m_text.setString("Wander");
		setTexture(m_texture);
		m_sprite.setScale(.25, .25);
	}
	if (m_behaviour == PURSUE)
	{
		if (!m_texture.loadFromFile("resources//images//wander.png"))
		{
			std::cout << "problem loading texture file" << std::endl;
		}
		m_text.setString("Wander");
		setTexture(m_texture);
		m_sprite.setScale(.25, .25);
	}
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	std::cout << m_scaledSize.x << ", " << m_scaledSize.y << std::endl;
}

void Agent::update(double dt, sf::Vector2f target, std::vector<Agent*> allies)
{
	if (m_behaviour != WANDER)
	{
		m_target = target;
	}

	if (m_behaviour == SEEK)
	{
		seek();
	}
	if (m_behaviour == FLEE)
	{
		flee();
	}
	if (m_behaviour == WANDER)
	{
		wander();
	}
	if (m_behaviour == ARRIVE)
	{
		arrive();
	}
	if (m_behaviour == PURSUE)
	{
		pursue();
	}

	avoid(allies);

	m_vel += m_acc;

	friction();
	boundry();

	m_pos += m_vel;

	m_orientation = getNewOrientation();

	m_text.setPosition(m_pos.x, m_pos.y + (m_scaledSize.y / 2));
	m_sprite.setRotation(m_orientation);
	m_sprite.setPosition(m_pos);
	m_acc = sf::Vector2f(0, 0);
}

// TODO: adjust behaviour so that it seeks to a random point (if initial target is null or it has come within a certian distance of target
// then create a new point for it to wander to
void Agent::wander()
{
	if (m_target != sf::Vector2f() && distance(m_target, m_pos) > 100)
	{
		sf::Vector2f wander;
		wander = m_target - m_pos;
		wander = normalize(wander);
		m_orientation = getNewOrientation();
		int r = std::rand() % (1 - (-1)) + (-1);
		m_orientation = m_orientation + MAX_ROT * r;
		wander = sf::Vector2f(-sin(m_orientation), cos(m_orientation)) * MAX_SPEED;
		m_acc += wander;
	}
	else
	{
		float x = .0f + (float)(rand()) / (float)(RAND_MAX / (SCREEN_WIDTH - 0));
		float y = .0f + (float)(rand()) / (float)(RAND_MAX / (SCREEN_HEIGHT - 0));
		m_target = sf::Vector2f(x, y);
	}
}

void Agent::arrive()
{
	sf::Vector2f target = m_target - m_pos;
	if (mag(target) < ARRIVAL_RAD)
	{
		// Do Nothing
	}
	else
	{
		sf::Vector2f vel = target * TIME_TO_TARGET;
		if (mag(vel) > MAX_VEL)
		{
			vel = normalize(vel);
			sf::Vector2f steer = vel - m_vel; // steering force
			steer = limitForce(steer, MAX_STEER); // keep the steering force within believeable range
			m_acc += steer; // adding to the overall acceleration
		}
	}
}

void Agent::seek()
{
	sf::Vector2f target = m_target - m_pos;
	target = normalize(target);
	target *= MAX_VEL;
	sf::Vector2f steer = target - m_vel; // steering force
	steer = limitForce(steer, MAX_STEER); // keep the steering force within believeable range
	m_acc += steer; // adding to the overall acceleration
}

void Agent::flee()
{
	// inverse of seek, m_pos and m_target inversed, finally steering force SUBTRACTED from acceleration
	sf::Vector2f target = m_pos - m_target;
	if (mag(target) < ARRIVAL_RAD)
	{
		target = normalize(target);
		target *= MAX_VEL;
		sf::Vector2f steer = m_vel - target;
		steer = limitForce(steer, MAX_STEER);
		m_acc -= steer;
	}
}

// TODO: dynamic pursue
void Agent::pursue()
{
}

void Agent::lookAhead(sf::Vector2f target)
{
	sf::Vector2f direction = target - m_pos;
	sf::Vector2f orientation = normalize(m_vel);
	direction = normalize(direction);
	float angle = dotProduct(orientation, direction);
	if (angle < AVOID_CONE / 2)
	{
	}
}

void Agent::avoid(std::vector<Agent*> allies)
{
	sf::Vector2f sum = sf::Vector2f();
	float count = 0.f;
	for (auto ally : allies)
	{
		if (ally != this)
		{
			float dis = distance(ally->getPosition(), m_pos);
			if (dis > 0 && dis < COLL_RAD)
			{
				sf::Vector2f avoid = ally->getPosition() - m_pos;
				avoid = normalize(avoid);
				avoid = avoid / dis;
				sum += avoid;
				count += 1.f;
			}
		}
	}
	if (count > 0.f)
	{
		sum = sum / count;
		sum = normalize(sum);
		sum = limitForce(sum,MAX_VEL);
		sf::Vector2f steer = sum - m_vel;
		steer = limitForce(steer, MAX_STEER);
		m_acc -= steer;
	}
}

bool Agent::isNull()
{
	return m_null;
}
