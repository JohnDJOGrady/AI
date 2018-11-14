#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <Node.h>
#include <iostream>

static const int WIDTH = 15;
static const int HEIGHT = 15;

class Field
{
public:
	Field();
	Field(sf::Vector2f window);
	~Field();
	void createFlowField(); // Create obstacles
	void calculateBestPath(); // Djikstra's
	void update(float dt); // update
	void render(sf::RenderWindow &window); // render the grid of entities

	void cleanup(); // clean up any elements put on the heap ("new" elements)

private:
	Node* m_field[WIDTH][HEIGHT];
	sf::Font m_font;
};

#endif // !FIELD_H
