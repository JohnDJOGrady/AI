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
			float w = window.x / WIDTH;
			float h = window.y / HEIGHT;
			float x = j * w;
			float y = i * h;
			m_field[i][j] = new Node(x,y,w,h);
			m_field[i][j]->setFont(&m_font);
			m_field[i][j]->setWeight(0);
			m_field[i][j]->setID(nodeID);
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
