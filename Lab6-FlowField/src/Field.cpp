#include <Field.h>

Field::Field()
{
	// default
}

Field::Field(sf::Vector2f window)
{
	if (!m_font.loadFromFile("resources//font//AGENCYR.TTF"))
	{
		std::cout << "-- Error loading font file -- " << std::endl;
	}

	int nodeID = 0;
	// filling the grid
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
			m_field[i][j]->setFieldPos(i, j);
			m_field[i][j]->setFont(&m_font);
			m_field[i][j]->setID(nodeID);
			nodeID++;
			//std::cout << "[Node " << nodeID << "] Row: " << i << " - Column: " << j << " - Weight: " << m_field[i][j]->getWeight() << std::endl;;
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
			std::vector<Node*> neighbours = currentID->getNeighbours();
			for (int i = 0; i < neighbours.size(); i++)
			{
				Node* n = neighbours[i];
				int endNodeCost = currentID->getWeight() + 1;
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

		// calculating efficieny
		sf::Time elapsed = clock.getElapsedTime();
		std::cout << elapsed.asMilliseconds() << std::endl;
	}
}

void Field::createFlowField()
{
	
}

void Field::resetCostField()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
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

void Field::assignNeighbours()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i - 1 >= 0)
			{
				m_field[i][j]->addNeighbour(m_field[i - 1][j]); // top
			}
			if (i + 1 < HEIGHT)
			{
				m_field[i][j]->addNeighbour(m_field[i + 1][j]); // bottom
			}
			if (j - 1 >= 0)
			{
				m_field[i][j]->addNeighbour(m_field[i][j - 1]); // left
			}
			if (j + 1 < WIDTH)
			{
				m_field[i][j]->addNeighbour(m_field[i][j + 1]); // right
			}
		}
	}

	// - redone
}

/// <summary>
/// Function that lets the player select where the start and goal nodes are
/// @args mouse - vector representing the x and y co-ordinates of the mouse
/// </summary>
void Field::select(sf::Vector2i mouse)
{
	if (m_currentSelection < 2)
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			//std::cout << "Row: " << i << std::endl;
			if (mouse.y > i * m_tileH && mouse.y < (i + 1) * m_tileH)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					if (mouse.x > j * m_tileW && mouse.x < (j + 1) * m_tileW)
					{
						if (m_currentSelection == 0)
						{
							m_field[i][j]->setGoal();
							m_destination = m_field[i][j];
							m_currentSelection++;
							moddedDijkstra();
						}
						else if (m_currentSelection == 1)
						{
							m_field[i][j]->setStart();
							m_start = m_field[i][j];
							m_currentSelection++;
						}
						break; // once node selected break out of loop
					}
					//std::cout << " Column: " << j << std::endl;
				}
				break; // once node selected break out of loop
			}
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
		//std::cout << "Row: " << i << std::endl;
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
				//std::cout << " Column: " << j << std::endl;
			}
			break; // once node selected break out of loop
		}
	}
}

void Field::update(float dt)
{
}

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

// TODO: cleanup
void Field::cleanup()
{
}
