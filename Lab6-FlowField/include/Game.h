#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Field.h>

static const float WIN_WIDTH = 1080.f;
static const float WIN_HEIGHT = 1080.f;

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
	Field m_field;
};

#endif // !GAME_H

