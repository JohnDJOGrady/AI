#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "MathHelper.h"
#include "Player.h"
#include "Agent.h"

class Game
{

public:
	Game();
	~Game();
	void run();

private:
	void update(double ms);
	void render();

	Player m_player;
	Agent m_seek;
	Agent m_flee;
	Agent m_wander;
	Agent m_arriveA;
	Agent m_arriveB;
	Agent m_pursue;

	std::vector<Agent*> m_agents;

	sf::RenderWindow m_window;
};

#endif //GAME_H!
