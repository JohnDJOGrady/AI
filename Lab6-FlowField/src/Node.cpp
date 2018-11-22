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

	m_flow = sf::Vector2f(0,0);
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
			sf::Vertex(sf::Vector2f(m_centre.x + (m_flow.x * (m_tile.getSize().x / 2)), m_centre.y + (m_flow.y * (m_tile.getSize().y / 2))),  sf::Color::Red)
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

	m_lblWeight.setString(std::to_string(m_id));
	m_lblWeight.setPosition(m_tile.getPosition().x, m_tile.getPosition().y);
}

void Node::setWeight(int weight)
{
	m_weight = weight;
	if (!m_end && !m_start)
	{
		setFill();
	}
	//m_lblWeight.setPosition(sf::Vector2f(m_centre.x - m_lblWeight.getLocalBounds().width / 2, m_centre.y - m_lblWeight.getLocalBounds().height / 2)); // center the text on the point
}

void Node::setFill()
{
	if (!m_impassable && !m_path && !m_end && !m_start)
	{
		float r = 225.f - m_weight / 2;
		float g = 255.f;
		float b = 255.f - m_weight;

		if (r < 0.f)
		{
			r = 0.f;
		}
		if (g < 0.f)
		{
			g = 0.f;
		}
		if (b < 0.f)
		{
			b = 0.f;
		}

		m_fill = sf::Color(r,g,b);
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
	m_end = true;
	m_fill = sf::Color::Magenta;
	setFill();
}

void Node::setStart()
{
	m_start = true;
	m_fill = sf::Color::Cyan;
	setFill();
}

void Node::setPath()
{
	m_path = true;
	m_fill = sf::Color::Yellow;
	setFill();
}

void Node::setFlow(sf::Vector2f v)
{
	m_flow = sf::Vector2f(v);
}
