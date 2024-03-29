#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <Node.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <math.h>

static const int WIDTH = 50;
static const int HEIGHT = 50;

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
	void getBestPath(); // calculate best path to goal from start
	void resetCostField();

	// utility functions
	void createObstacle(sf::Vector2i mouse);
	void select(sf::Vector2i mouse);
	void render(sf::RenderWindow &window); // render the grid of entities
	sf::Vector2f getFieldPos(Node* node); 

private:
	Node* m_field[WIDTH][HEIGHT];
	Node* m_start;
	Node* m_destination;

	sf::Font m_font;

	int m_currentSelection = 0; // differentiate the left mouse clicks
	int m_tileH, m_tileW;
};

#endif // !FIELD_H
