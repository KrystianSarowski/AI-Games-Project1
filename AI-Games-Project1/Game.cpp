#include "Game.h"

Game::Game() : m_window{ sf::VideoMode{ 800, 600, 32 }, "Project 1" },
	m_board(sf::Vector2u(800, 600))
{
	m_players[0] = new Player(PieceType::RED);
	m_players[1] = new Player(PieceType::GREEN);

	m_playerAI = new PlayerAI(m_players[0]);

	addPiecesToPlayers();
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
	if (m_currentTurn == 0)
	{
		m_playerAI->makeAMove();
	}

	if (m_players[m_currentTurn]->getMadeMove())
	{
		m_currentTurn = (m_currentTurn + 1) % 2;
		m_players[m_currentTurn]->setMadeMove(false);
	}
}

void Game::processEvents()
{
	sf::Event event;

	sf::Vector2f m_pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	while (m_window.pollEvent(event))
	{
		if (m_currentTurn != 0)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					Tile* selectedTile = m_board.selectTile(m_pos);

					if (selectedTile != nullptr)
					{
						m_players[m_currentTurn]->processTile(selectedTile);
					}
				}
			}
		}

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

	m_board.render(m_window);

	for (int i = 0; i < 2; i++)
	{
		m_players[i]->render(m_window);
	}

	m_window.display();
}

void Game::addPiecesToPlayers()
{
	std::vector<Piece*> pieces = m_board.getPieces();

	for(Piece* piece : pieces)	
	{
		m_players[static_cast<int>(piece->getType())]->addPiece(piece);
	}
}
