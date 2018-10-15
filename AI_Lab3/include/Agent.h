#ifndef AGENT_H
#define AGENT_H

#include "Entity.h"
#include <limits>

static const float TIME_TO_TARGET = .15f;

static const float ARRIVAL_RAD = 200.f;
static const float OUTER_ARRIVAL_RAD = 275.f;

static const float MAX_SPEED = .5f;
static const float MAX_ROT = 5.f;
static const float MAX_STEER = .75f;

static const float AVOID_CONE = 70.0f;
static const float COLL_RAD = 150.f;

enum algorithim
{
	WANDER,
	SEEK,
	FLEE,
	ARRIVE,
	PURSUE
};


class Agent : public Entity
{
public:
	// expand upon - diversify class - spread out dependencies
	Agent();
	Agent(sf::Vector2f pos, algorithim behaviour);
	void update(double dt, sf::Vector2f target, std::vector<Agent*> allies);

	void wander();
	void arrive();
	void seek();
	void flee();
	void pursue();

	// cone of avoidance - scan for entities that are in (are about to enter), check their path
	// and check time to arrive to see if a collision  wil happen and avoid
	void lookAhead(sf::Vector2f target);
	void avoid(std::vector<Agent*> allies);

	bool isNull();

private:
	sf::Vector2f m_target;
	bool m_null;

	double time;
	algorithim m_behaviour;
};


#endif // !AGENT_H