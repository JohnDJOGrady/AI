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
			nodeID++;
			m_tileW = window.x / WIDTH;
			m_tileH = window.y / HEIGHT;
			float x = j * m_tileW;
			float y = i * m_tileH;
			m_field[i][j] = new Node(x,y, m_tileW, m_tileH);
			m_field[i][j]->setFont(&m_font);
			m_field[i][j]->setWeight(WIDTH * HEIGHT);
			m_field[i][j]->setID(nodeID);
			std::cout << "[Node " << nodeID << "] Row: " << i << " - Column: " << j << " - Weight: " << m_field[i][j]->getWeight() << std::endl;;
		}
	}
}

Field::~Field()
{
	// nothing. . .
}

void Field::createFlowField()
{
}

void Field::calculateBestPath()
{

}

// selecting the nodes
void Field::select(sf::Vector2i mouse)
{
	if (m_currentSelection < 2)
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			std::cout << "Row: " << i << std::endl;
			if (mouse.y > i * m_tileH && mouse.y < (i + 1) * m_tileH)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					if (mouse.x > j * m_tileW && mouse.x < (j + 1) * m_tileW)
					{
						if (m_currentSelection == 0)
						{
							m_field[i][j]->setFill(m_first);
							m_start = m_field[i][j];
							m_currentSelection++;
						}
						else if (m_currentSelection == 1)
						{
							m_field[i][j]->setFill(m_second);
							m_destination = m_field[i][j];
							m_currentSelection++;
						}
						break; // once node selected break out of loop
					}
					std::cout << " Column: " << j << std::endl;
				}
				break; // once node selected break out of loop
			}
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
