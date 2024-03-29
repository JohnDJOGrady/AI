#include <Game.h>

Game::Game() : 
	m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Flow Field", sf::Style::Default),
	m_field(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT)),
	m_mouseDown(false)
{
	// TODO: Initialize entities
}

Game::~Game()
{
	// nothing. . .
}

/// <summary>
/// SFML Game Loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time frameRate = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = clock.restart();

	std::cout << "Right click to create and obstacle." << std::endl;
	std::cout << "Left click to create the goal node and left click again to create the starting point. This resets." << std::endl << std::endl;


	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) // close the window if a key is pressed
			{
				m_window.close();
			}
			if (sf::Event::MouseButtonReleased)
			{
				m_mouseDown = false;
			}
		}

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > frameRate)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}
		
		render();
	}
}

void Game::update(float dt)
{ 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mouseDown == false)
	{
		// left click...
		m_mouseDown = true;
		m_field.select(sf::Mouse::getPosition(m_window));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_mouseDown == false)
	{
		// right click...
		m_mouseDown = true;
		m_field.createObstacle(sf::Mouse::getPosition(m_window));
	}
}

void Game::render()
{
	m_window.clear();
	m_field.render(m_window);
	m_window.display();
}