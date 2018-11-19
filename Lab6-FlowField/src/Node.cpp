#include "Node.h"

Node::Node()
{
}

Node::Node(float x, float y, float w, float h)
{
	m_tile = sf::RectangleShape();
	m_tile.setSize(sf::Vector2f(w, h));
	m_tile.setPosition(sf::Vector2f(x, y));
	m_tile.setFillColor(sf::Color::White);
	m_tile.setOutlineColor(sf::Color::Black);
	m_tile.setOutlineThickness(2);

	m_centre = sf::Vector2f(x + (w / 2), y + (h / 2));
}

Node::Node(sf::Vector2f pos, sf::Vector2f size)
{
	Node::Node(pos.x, pos.y, size.x, size.y);
}

Node::~Node()
{
	// TODO: cleanup
}

void Node::render(sf::RenderWindow &window)
{
	window.draw(m_tile);
	window.draw(m_lblWeight);
}

void Node::setFont(sf::Font * font)
{
	m_font = font;
	m_lblWeight.setFont(*m_font);
	m_lblWeight.setCharacterSize(24);
	m_lblWeight.setFillColor(sf::Color::Red);
}

void Node::setID(int id)
{
	m_id = id;
	m_lblWeight.setString(std::to_string(m_id));
	m_lblWeight.setPosition(sf::Vector2f(m_centre.x - m_lblWeight.getLocalBounds().width / 2, m_centre.y - m_lblWeight.getLocalBounds().height / 2)); // center the text on the point
}

void Node::setWeight(float weight)
{
	m_weight = weight;
}

void Node::setDimensions(sf::Vector2f v)
{
	m_tile.setSize(v);
}

void Node::setPos(sf::Vector2f v)
{
	m_tile.setPosition(v);
}

void Node::setFill(sf::Color c)
{
	m_tile.setFillColor(c);
}

void Node::setImpasse()
{
	setWeight(0);
	setFill(sf::Color::Black);
}
