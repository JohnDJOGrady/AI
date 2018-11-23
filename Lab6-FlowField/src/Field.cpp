#include <Field.h>

Field::Field()
{
	// default
}

///<summary>
/// generate the field
///</summary>
Field::Field(sf::Vector2f window)
{

	if (!m_font.loadFromFile("resources//font//AGENCYR.TTF"))
	{
		std::cout << "-- Error loading font file -- " << std::endl;
	}

	int nodeID = 0;
	// filling the field with nodes
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			m_tileW = window.x / WIDTH;
			m_tileH = window.y / HEIGHT;
			float x = j * m_tileW;
			float y = i * m_tileH;
			int weight = HEIGHT * WIDTH;
			m_field[i][j] = new Node(x,y, m_tileW, m_tileH, weight);
			m_field[i][j]->setFont(&m_font);
			m_field[i][j]->setID(nodeID);
			nodeID++;
		}
	}

	assignNeighbours();
}

Field::~Field()
{
	// nothing. . .
}

/// <summary>
/// modded Dijkstra's algorithim to generate a cost field
/// </summary>
void Field::moddedDijkstra()
{
	resetCostField(); // reset the cost field each time

	if (m_destination != 0)
	{
		sf::Clock clock;
		std::list<Node*> nodeList;
		m_destination->setWeight(0);
		nodeList.push_back(m_destination);

		while (nodeList.size() > 0)
		{
			Node* currentID = nodeList.front();
			nodeList.pop_front();
			std::vector<Node*> neighbours = currentID->getNeighbours(); // get the NWSE nodes if applicable
			for (int i = 0; i < neighbours.size(); i++)
			{
				Node* n = neighbours[i];
				int endNodeCost = currentID->getWeight() + 1; // weight to be plus one of the previous node indicating one step was taken to get there
				if (n->getWeight() < INT_MAX && endNodeCost < n->getWeight())
				{
					if (std::find(nodeList.begin(), nodeList.end(), n) != nodeList.end() == false)
					{
						nodeList.push_back(n);
					}
					n->setWeight(endNodeCost);
				}
			}
		}
		createFlowField(); // create vector flow field after integration field complete
		// calculating efficieny
		sf::Time elapsed = clock.getElapsedTime();
		system("CLS");

		
		std::cout << "Time to create weight and flow in Milliseconds: " << elapsed.asMilliseconds() << std::endl;
	}
}

///<summary>
/// generate a flow field by create a vector based off the value of its neighbouring nodes
/// Top and bottom represnting the y component while left and right represent the component
/// if the node you are checking is on the outer edge avoid checking the node either N W S E
/// depending on its location
///
///</summary>
void Field::createFlowField()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Node* n = m_field[i][j];
			if (!n->getImpassable() && n->getWeight() != 0)
			{
				int topN = n->getWeight();
				int bottomN = n->getWeight();
				int leftN = n->getWeight();
				int rightN = n->getWeight();
				if (i < HEIGHT - 1)
				{
					Node* bottom = m_field[i + 1][j];
					if (!bottom->getImpassable())
					{
						bottomN = bottom->getWeight();
					}
				}
				if (i > 0)
				{
					Node* top = m_field[i - 1][j];
					if (!top->getImpassable())
					{
						topN = top->getWeight();
					}
				}
				if (j < WIDTH - 1)
				{
					Node* right = m_field[i][j + 1];
					if (!right->getImpassable())
					{
						rightN = right->getWeight();
					}
				}
				if (j > 0)
				{
					Node* left = m_field[i][j - 1];
					if (!left->getImpassable())
					{
						leftN = left->getWeight();
					}
				}

				float x = leftN - rightN;
				float y = topN - bottomN;
				float mag = (x * x) + (y * y);
				n->setFlow(sf::Vector2f(x / mag, y / mag)); // get the normalised vector and set it as the direction vector for the flow field
			}
			else
			{
				n->setFlow(sf::Vector2f(0,0));
			}
		}
	}
}

///<summary>
/// For each node check the flow direction vector
///</summary>
void Field::getBestPath()
{
	std::list<Node*> nodeList;
	nodeList.push_back(m_start);

	while (nodeList.size() > 0 && nodeList.front() != m_destination) // make sure its between the start and destination nodes
	{
		Node* node = nodeList.front(); // get the next node in the iteration
		if (node != m_start)
		{
			node->setPath();
		}
		nodeList.pop_front();
		sf::Vector2f nodeFlow = node->getFlow(); // get the direction vector which indicates what the next node in the flow will be
		sf::Vector2f fieldPos = getFieldPos(node);
		int x = fieldPos.x;
		int y = fieldPos.y;

		if (nodeFlow.x > 0.f)
		{
			x = fieldPos.x + 1;

			if (x > WIDTH - 1)
			{
				x = WIDTH - 1; // edge detection
			}
			if (m_field[y][x]->getImpassable()) // avoid following the flow in to obstacles
			{
				x = fieldPos.x;
			}
		}
		else if (nodeFlow.x < 0.f)
		{
			x = fieldPos.x - 1;
			if (x < 0)
			{
				x = 0;
			}
			if (m_field[y][x]->getImpassable())
			{
				x = fieldPos.x;
			}
		}

		if (nodeFlow.y > 0.f)
		{
			y = fieldPos.y + 1;

			if (y > HEIGHT - 1)
			{
				y = HEIGHT - 1;
			}
			if (m_field[y][x]->getImpassable())
			{
				y = fieldPos.y;
			}
		}
		else if (nodeFlow.y < 0.f)
		{
			y = fieldPos.y - 1;

			if (y < 0)
			{
				y = 0;
			}
			if (m_field[y][x]->getImpassable())
			{
				y = fieldPos.y;
			}
		}

		nodeList.push_front(m_field[y][x]); // push the next node in the flow field to the front of the list
											// NOTE: due to the loop and the structure of 2d arrays 
											// where the first element represents a "row" and the second a "column"
											// the y component establishes its row location and the x its column location
	}
}

///<summary>
/// reset the values of eaach node
///</summary>
void Field::resetCostField()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			m_field[i][j]->m_end = false;
			m_field[i][j]->m_start = false;
			m_field[i][j]->m_path = false;
			if (m_field[i][j]->getImpassable())
			{
				m_field[i][j]->setWeight(INT_MAX);
			}
			else
			{
				
				m_field[i][j]->setWeight(HEIGHT * WIDTH);
			}
		}
	}
}

///<summary>
/// cycle through each node and check its N, W, S, E neighbours and check if they
/// are valid and add them to the Node's neighbour vector 
///</summary>
void Field::assignNeighbours()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i - 1 >= 0)
			{
				m_field[i][j]->addNeighbour(m_field[i - 1][j]); // North
			}
			if (i + 1 < HEIGHT)
			{
				m_field[i][j]->addNeighbour(m_field[i + 1][j]); // South
			}
			if (j - 1 >= 0)
			{
				m_field[i][j]->addNeighbour(m_field[i][j - 1]); // West
			}
			if (j + 1 < WIDTH)
			{
				m_field[i][j]->addNeighbour(m_field[i][j + 1]); // East
			}
		}
	}
}

/// <summary>
/// Function that lets the player select where the start and goal nodes are
/// @args mouse - vector representing the x and y co-ordinates of the mouse
/// </summary>
void Field::select(sf::Vector2i mouse)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		if (mouse.y > i * m_tileH && mouse.y < (i + 1) * m_tileH)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (mouse.x > j * m_tileW && mouse.x < (j + 1) * m_tileW)
				{
					if (m_currentSelection == 0)
					{
						m_field[i][j]->setGoal(); // set this as the destination / goal node
						m_destination = m_field[i][j];
						m_currentSelection++;
						moddedDijkstra();
					}
					else if (m_currentSelection == 1)
					{
						m_field[i][j]->setStart(); // set this to be the starting node from 
						m_start = m_field[i][j];
						m_currentSelection = 0;
						getBestPath();
					}
					break; // once node selected break out of loop
				}
			}
			break; // once node selected break out of loop
		}
	}
}
/// <summary>
/// Allows the user to create objects on the fly to create their own custom path to test the algorithm
/// @args mouse represents the x and y co-ordinates of the mouse
/// </summary>
/// <param name="mouse"></param>
void Field::createObstacle(sf::Vector2i mouse)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		if (mouse.y > i * m_tileH && mouse.y < (i + 1) * m_tileH)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (mouse.x > j * m_tileW && mouse.x < (j + 1) * m_tileW)
				{
					m_field[i][j]->setImpasse();
					moddedDijkstra();
					break; // once node selected break out of loop
				}
			}
			break; // once node selected break out of loop
		}
	}
}

///<summary>
/// render each node passing it a reference to the window
///</summary>
void Field::render(sf::RenderWindow & window)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			m_field[i][j]->render(window);
		}
	}
}

///<summary>
/// translate the nodes window co-ordinates in to a location in the array grid
///</summary>
sf::Vector2f Field::getFieldPos(Node * node)
{
	return sf::Vector2f(node->getPos().x / m_tileW, node->getPos().y / m_tileH);
}
