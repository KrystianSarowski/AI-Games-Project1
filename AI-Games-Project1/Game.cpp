#include "Game.h"

Game::Game() : m_window{ sf::VideoMode{ 800, 600, 32 }, "Project 1" }
{
	m_points[0].color = sf::Color(5, 5, 5);
	m_points[1].color = sf::Color(255, 92, 203);

	createTileGrid(10.0f, 13);
	connectTiles(10.0f);
}

void Game::start()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);	//60 fps

	while (m_window.isOpen())
	{
		processEvents();								//As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();							//At least 60 fps
			update(timePerFrame);						//60 fps
		}
		render();										//As many as possible
	}
}

void Game::update(sf::Time dt)
{
}

void Game::createTileGrid(float t_tileRadius, int t_maxRowLength)
{
	float offSetX = t_tileRadius + 1.0f;
	float offSetY = offSetX * sinf(3.14f / 3);

	sf::Vector2f startPos = sf::Vector2f(200.0f, 200.0f);

	for (int count = t_maxRowLength; count > 0; count--)
	{
		for (int x = 0; x < count; x++)
		{
			Tile* tile = new Tile;

			sf::Vector2f pos;

			pos.x = startPos.x + (x * (offSetX * 2)) + offSetX * (t_maxRowLength - count);
			pos.y = startPos.y + (offSetY * 2) * (t_maxRowLength - count);

			if (count < 5)
			{
				tile->setOwnerColour(OwnerColour::GREEN);
			}

			tile->setPosition(pos);

			m_grid.push_back(tile);
		}
	}

	startPos.y = startPos.y + (offSetY * 2) * (t_maxRowLength - 5);

	for (int count = t_maxRowLength; count > 0; count--)
	{
		for (int x = 0; x < count; x++)
		{
			Tile* tile = new Tile;

			sf::Vector2f pos;

			pos.x = startPos.x + (x * (offSetX * 2)) + offSetX * (t_maxRowLength - count);
			pos.y = startPos.y - (offSetY * 2) * (t_maxRowLength - count);

			tile->setPosition(pos);

			auto it = std::find_if(m_grid.begin(), m_grid.end(), [=](const Tile* obj)
			{
				return obj->getPosition() == tile->getPosition();
			});

			if (it == m_grid.end())
			{
				if (count < 5)
				{
					tile->setOwnerColour(OwnerColour::RED);
				}

				m_grid.push_back(tile);
			}
		}
	}
}

void Game::connectTiles(float t_tileRadius)
{
	float maxTileOffset = (t_tileRadius + 1.0f) * 2;

	for (int i = 0; i < m_grid.size(); i++)
	{
		for (int j = 0; j < m_grid.size(); j++)
		{
			if (i != j)
			{
				if (maxTileOffset >= distance(m_grid[i]->getPosition(), m_grid[j]->getPosition()))
				{
					m_grid[i]->addNeighbour(m_grid[j]);
				}
			}
		}
	}
}

float Game::distance(sf::Vector2f t_vect1, sf::Vector2f t_vect2)
{
	return sqrt(powf(t_vect1.x - t_vect2.x, 2) + powf(t_vect1.y - t_vect2.y, 2));
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}

		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
	}
}

void Game::render()
{
	m_window.clear();

	sf::CircleShape node;

	node.setRadius(10);
	node.setOrigin(sf::Vector2f(10.0f, 10.0f));
	node.setFillColor(sf::Color::Yellow);

	for (int i = 0; i < m_grid.size(); i++)
	{
		switch (m_grid[i]->getOwnerColour())	
		{
		case OwnerColour::BLANK:
			node.setFillColor(sf::Color::Yellow);
			break;
		case OwnerColour::RED:
			node.setFillColor(sf::Color::Red);
			break;
		case OwnerColour::GREEN:
			node.setFillColor(sf::Color::Green);
			break;
		default:
			break;
		}

		node.setPosition(m_grid[i]->getPosition());
		m_window.draw(node);
	}

	for (int i = 0; i < m_grid.size(); i++)
	{
		std::list<Tile*> neighbours = m_grid[i]->getNeighbours();

		for (auto it = neighbours.begin(); it != neighbours.end(); it++)
		{
			m_points[0].position = m_grid[i]->getPosition();
			m_points[1].position = (*it)->getPosition();
			m_window.draw(m_points);
		}
	}

	m_window.display();
}
