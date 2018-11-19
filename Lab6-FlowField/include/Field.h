#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <Node.h>
#include <iostream>
#include <list>
#include <algorithm>

static const int WIDTH = 25;
static const int HEIGHT = 25;

class Field
{
public:
	Field();
	Field(sf::Vector2f window);
	~Field();

	// algorithm logic
	void assignNeighbours(); // assign neighbours of each node for algo
	void moddedDijkstra(); // generate cost map
	void createFlowField(); // Create vectors
	void resetCostField();

	// utility functions
	void createObstacle(sf::Vector2i mouse);
	void select(sf::Vector2i mouse);
	void update(float dt); // update
	void render(sf::RenderWindow &window); // render the grid of entities
	void cleanup(); // clean up any elements put on the heap ("new" elements)

private:
	Node* m_field[WIDTH][HEIGHT];
	Node* m_start;
	Node* m_destination;

	sf::Font m_font;
	sf::Color m_first = sf::Color::Green;
	sf::Color m_second = sf::Color::Cyan;

	int m_currentSelection = 0;
	int m_tileH, m_tileW;
};

#endif // !FIELD_H
