#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <string>

class Node
{
public:
	Node();
	Node(float x, float y, float w ,float h);
	Node(sf::Vector2f pos, sf::Vector2f size);
	~Node();
	void render(sf::RenderWindow &window);

	// Setters
	void setFont(sf::Font* font); 
	void setID(int id);
	void setWeight(float weight); // weight to determine best path
	void setDimensions(sf::Vector2f v);
	void setPos(sf::Vector2f v);
	void setFill(sf::Color c);
	void setImpasse();

	// Getters
	int getID() { return m_id; };
	int getWeight() { return m_weight; };

private:
	sf::RectangleShape m_tile;
	sf::Vector2f m_centre;
	sf::Vector2f m_flow; // represents 

	float m_weight;
	sf::Text m_lblWeight; // label for the node weight
	sf::Font* m_font;

	int m_id;
};

#endif // !NODE_H

