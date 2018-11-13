#include "Game.h"

static sf::Int32 MS_PER_UPDATE = 10.0;

Game::Game() :
	m_window(sf::VideoMode(1600.f, 900.f), "AI_Lab", sf::Style::Default),
	m_player(800.f, 400.f),
	m_seek(sf::Vector2f(300.f, 300.f), SEEK),
	m_flee(sf::Vector2f(1200.f, 500.f), FLEE),
	m_wander(sf::Vector2f(500.f, 700.f), WANDER),
	m_arriveA(sf::Vector2f(900.f, 700.f), ARRIVE),
	m_arriveB(sf::Vector2f(200.f, 700.f), ARRIVE),
	m_pursue(sf::Vector2f(900.f, 100.f), PURSUE)
{
	srand((int)time(0));
	m_agents.push_back(&m_seek);
	m_agents.push_back(&m_flee);
	m_agents.push_back(&m_wander);
	m_agents.push_back(&m_arriveA);
	m_agents.push_back(&m_arriveB);
	m_agents.push_back(&m_pursue);
}

Game::~Game()
{
	delete this;
}

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

void Game::update(double ms)
{
	m_player.update(ms);
	for (auto agent : m_agents)
	{
		agent->update(ms, m_player, m_agents);
	}
}

void Game::render()
{
	m_window.clear();
	m_player.render(m_window);
	for (auto agent : m_agents)
	{
		agent->render(m_window);
	}
	m_window.display();
}
