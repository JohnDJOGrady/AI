#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();
	void update(float dt);
	void render();
private:
	sf::RenderWindow m_window;
};

#endif // !GAME_H

