#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Field.h>

// custom sizing for the window
static const float WIN_WIDTH = 1600.f;
static const float WIN_HEIGHT = 900.f;

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

	bool m_mouseDown;
};

#endif // !GAME_H

