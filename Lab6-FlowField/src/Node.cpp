#include "Node.h"

Node::Node()
{
}

Node::Node(float x, float y, float w, float h)
{
	m_fill = sf::Color(0, 0, 255);
	m_tile = sf::RectangleShape();
	m_tile.setSize(sf::Vector2f(w, h));
	m_tile.setPosition(sf::Vector2f(x, y));
	m_tile.setFillColor(m_fill);
	m_tile.setOutlineColor(sf::Color::Black);
	m_tile.setOutlineThickness(2);
	m_impassable = false;

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
	if (!m_impassable)
	{
		window.draw(m_lblWeight);
	}
}

void Node::addNeighbour(Node * neighbour)
{
	if (neighbour != nullptr)
	{
		m_neighbours.push_back(neighbour);
	}
}

void Node::setFont(sf::Font * font)
{
	m_font = font;
	m_lblWeight.setFont(*m_font);
	m_lblWeight.setCharacterSize(24);
	m_lblWeight.setFillColor(sf::Color::White);
}

void Node::setID(int id)
{
	m_id = id;
}

void Node::setWeight(int weight)
{
	m_weight = weight;
	m_lblWeight.setString(std::to_string(m_weight));
	m_lblWeight.setPosition(sf::Vector2f(m_centre.x - m_lblWeight.getLocalBounds().width / 2, m_centre.y - m_lblWeight.getLocalBounds().height / 2)); // center the text on the point
}

void Node::setDimensions(sf::Vector2f v)
{
	m_tile.setSize(v);
}

void Node::setPos(sf::Vector2f v)
{
	m_tile.setPosition(v);
}

void Node::setFieldPos(int i, int j)
{
	m_fieldPos = sf::Vector2f(i, j);
}

void Node::setFill(sf::Color c)
{
	m_fill = c;
	m_tile.setFillColor(m_fill);
}

void Node::setImpasse()
{
	m_impassable = true;
	setWeight(INT_MAX);
	setFill(sf::Color::White);
}
