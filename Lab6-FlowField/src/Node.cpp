#include "Node.h"

Node::Node()
{
}

///<summary>
/// Creating node entity
/// @paarm x
/// @paarm y
/// @paarm w - width
/// @paarm h - height
/// @paarm weight - the weight value of the node in the field
///</summary>
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

///<summary>
/// render the rectangle as well as a label representing its weight and a line representing its flow vector drawn from the cente of the rectangle
///</summary>
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

///<summary>
/// add node pointer to vector list of neighbours
/// @param neighbour - pointer to node
///</summary>
void Node::addNeighbour(Node * neighbour)
{
	if (neighbour != nullptr)
	{
		m_neighbours.push_back(neighbour);
	}
}

///<summary>
/// set the font using a pointer to a font object then generate the text to be used, ensure the character size scales well
///</summary>
void Node::setFont(sf::Font * font)
{
	m_font = font;
	m_lblWeight.setFont(*m_font);
	m_lblWeight.setCharacterSize(m_tile.getLocalBounds().width / 4);
	m_lblWeight.setFillColor(sf::Color::Magenta);
	setWeight(m_maxWeight);
}

///<summary>
/// set its location in the grid
///</summary>
void Node::setID(int id)
{
	m_id = id;
}

///<summary>
/// set the weight value of the node
///</summary>
void Node::setWeight(int weight)
{
	m_weight = weight;
	if (!m_end && !m_start)
	{
		setFill();
	}

	m_lblWeight.setString(std::to_string(m_weight));
	m_lblWeight.setPosition(m_tile.getPosition().x, m_tile.getPosition().y);
}


///<summary>
/// used to set the fill of the node object using thee m_fill global variable
///</summary>
void Node::setFill()
{
	if (!m_impassable && !m_path && !m_end && !m_start) // "heatmap" generation - goal node is white and colour moves towards green the higher the weight
	{
		float r = 225.f - m_weight ;
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
		m_tile.setFillColor(m_fill); // avoid modifying starting node, obstacles and path nodes
	}
}

///<summary>
/// Set the node to be an impassable obstacle
///</summary>
void Node::setImpasse()
{
	m_impassable = true;
	setWeight(INT_MAX);
	m_fill = sf::Color(125,125,125);
	setFill();
}

///<summary>
/// set the node to be the goal / destination node
///</summary>
void Node::setGoal()
{
	m_end = true;
	m_fill = sf::Color::Magenta;
	setFill();
}

///<summary>
/// set the start or beginnning node
///</summary>
void Node::setStart()
{
	m_start = true;
	m_fill = sf::Color::Cyan;
	setFill();
}

///<summary>
/// set the node to represent the path from destination to start
///</summary>
void Node::setPath()
{
	m_path = true;
	m_fill = sf::Color::Yellow;
	setFill();
}

///<summary>
/// set the vector for the flow graph logic
///</summary>
void Node::setFlow(sf::Vector2f v)
{
	m_flow = sf::Vector2f(v);
}
