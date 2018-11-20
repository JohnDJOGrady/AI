#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <string>

class Node
{
public:
	Node();
	Node(float x, float y, float w ,float h, int weight);
	Node(sf::Vector2f pos, sf::Vector2f size, int weight);
	~Node();
	void render(sf::RenderWindow &window);
	void addNeighbour(Node* neighbour);

	// Setters
	void setFont(sf::Font* font); 
	void setID(int id);
	void setWeight(int weight); // weight to determine best path
	void setDimensions(sf::Vector2f v);
	void setPos(sf::Vector2f v);
	void setFieldPos(int i, int j);
	void setFill();
	void setImpasse();
	void setGoal();
	void setStart();

	// Getters
	int getID() { return m_id; };
	int getWeight() { return m_weight; };
	bool getImpassable() { return m_impassable; };
	sf::Vector2f getFieldPos() { return m_fieldPos; };
	std::vector<Node*> getNeighbours() { return m_neighbours; };

private:
	std::vector<Node*> m_neighbours;
	sf::RectangleShape m_tile;
	sf::Color m_fill;
	sf::Vector2f m_centre;
	sf::Vector2f m_fieldPos; // relative position within the field
	sf::Vector2f m_flow; // represents vector

	int m_weight, m_maxWeight;
	sf::Text m_lblWeight; // label for the node weight
	sf::Font* m_font;

	int m_id;
	bool m_impassable;
};

#endif // !NODE_H

