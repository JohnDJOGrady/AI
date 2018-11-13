#ifndef GRID_H
#define GRID_H

class Grid
{
public:
	Grid();
	~Grid();
	void createFlowField(); // Create obstacles
	void calculateBestPath(); // Djikstra's
	void update(); // update
	void render(); // render the grid of entities
	
private:

};

#endif // !GRID_H
