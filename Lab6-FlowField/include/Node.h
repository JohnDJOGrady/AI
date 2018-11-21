#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <string>

class Node
{
public:
	Node();
	Node(float x, float y, float w ,float h, int weight);
	~Node();
	void render(sf::RenderWindow &window);
	void addNeighbour(Node* neighbour);

	// Setters
	void setFont(sf::Font* font); 
	void setID(int id);
	void setWeight(int weight); // weight to determine best path
	void setFill();
	void setImpasse();
	void setGoal();
	void setStart();
	void setFlow(sf::Vector2f v);

	// Getters
	int getID() { return m_id; };
	int getWeight() { return m_weight; };
	bool getImpassable() { return m_impassable; };
	std::vector<Node*> getNeighbours() { return m_neighbours; };

private:
	std::vector<Node*> m_neighbours;
	sf::RectangleShape m_tile;
	sf::Color m_fill;

	sf::Vector2f m_centre;
	sf::Vector2f m_flow; // represents vector
	int m_id;
	int m_weight;
	int m_maxWeight;
	bool m_impassable;

	sf::Text m_lblWeight; // label for the node weight
	sf::Font* m_font;
};

#endif // !NODE_H

