#include <Game.h>

Game::Game() : m_window(sf::VideoMode(1600.f, 900.f), "Flow Field", sf::Style::Default)
{
	// TODO: Initialize entities
}

Game::~Game()
{
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

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
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
	// TODO: Update the grid in real time
}

void Game::render()
{
	m_window.clear();
	// TODO: Render Grid
	m_window.display();
}