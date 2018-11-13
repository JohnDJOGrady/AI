#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f pos);
	Player(float x, float y) : Player(sf::Vector2f(x, y)) {};
	void update(double dt);

private:
	void handleInput(double dt);
};

#endif // !PLAYER_H

