#include "Node.h"

Node::Node()
{
}

Node::Node(float x, float y, float w, float h, int weight)
{
	m_fill = sf::Color(0, 255, 175);
	m_tile = sf::RectangleShape();
	m_tile.setSize(sf::Vector2f(w, h));
	m_tile.setPosition(sf::Vector2f(x, y));
	m_tile.setOutlineColor(sf::Color::Black);
	m_tile.setOutlineThickness(2);
	m_impassable = false;
	m_maxWeight = weight;
	setFill();
	m_centre = sf::Vector2f(x + (w / 2), y + (h / 2));
	m_flow = m_centre - sf::Vector2f(w / 3,h / 3);
}

Node::Node(sf::Vector2f pos, sf::Vector2f size, int weight)
{
	Node::Node(pos.x, pos.y, size.x, size.y, weight);
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
		sf::Vertex line[] =
		{
			sf::Vertex(m_centre, sf::Color::Red),
			sf::Vertex(m_flow, sf::Color::Red)
		};
		window.draw(line, 2, sf::Lines);
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
	m_lblWeight.setCharacterSize(m_tile.getLocalBounds().width / 4);
	m_lblWeight.setFillColor(sf::Color::Magenta);
	setWeight(m_maxWeight);
}

void Node::setID(int id)
{
	m_id = id;
}

void Node::setWeight(int weight)
{
	m_weight = weight;
	setFill();
	m_lblWeight.setString(std::to_string(m_weight));
	m_lblWeight.setPosition(m_tile.getPosition().x, m_tile.getPosition().y);
	//m_lblWeight.setPosition(sf::Vector2f(m_centre.x - m_lblWeight.getLocalBounds().width / 2, m_centre.y - m_lblWeight.getLocalBounds().height / 2)); // center the text on the point
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

void Node::setFill()
{
	if (!m_impassable )
	{
		float g = (float)m_maxWeight / 255.f * (float)m_weight / 2;
		float b = (float)m_maxWeight / 255.f * (float)m_weight / 2;

		if (g > 255.f)
		{
			g = 255.f;
		}
		if (b > 200.f)
		{
			b = 200.f;
		}

		m_fill = sf::Color(0,g,b);
		m_tile.setFillColor(m_fill);
	}
	else
	{
		m_tile.setFillColor(m_fill);
	}
}

void Node::setImpasse()
{
	m_impassable = true;
	setWeight(INT_MAX);
	m_fill = sf::Color(125,125,125);
	setFill();
}

void Node::setGoal()
{
	m_fill = sf::Color::Green;
	setFill();
}

void Node::setStart()
{
	m_fill = sf::Color::Cyan;
	setFill();
}
