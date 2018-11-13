#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>

class Field
{
public:
	Field();
	~Field();
	void createFlowField(); // Create obstacles
	void calculateBestPath(); // Djikstra's
	void update(float dt); // update
	void render(sf::RenderWindow &window); // render the grid of entities

private:
	int width, height;
};

#endif // !FIELD_H
