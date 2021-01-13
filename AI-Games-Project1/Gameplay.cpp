#include "Gameplay.h"

Gameplay::Gameplay(GameScreen& t_gameScreen) :
	Screen(t_gameScreen),
	m_board(sf::Vector2u(800, 600))
{
	initialise();
	m_players[0] = new Player(PieceType::RED);
	m_players[1] = new Player(PieceType::GREEN);

	m_ai = new Algorithm(m_players[0], &m_board);

	m_theCoolerAI = new Algorithm(m_players[1], &m_board);

	addPiecesToPlayers();
}

void Gameplay::update(sf::Time t_dt)
{
	if (m_animationState == AnimationMode::Appear)
	{
		if (m_hud.getColor().a < 255)
		{
			m_hud.setColor(m_hud.getColor() + sf::Color{ 0,0,0,5 });
		}
		else
		{
			m_animationState = AnimationMode::None;
		}
	}

	if (m_animationState == AnimationMode::Disappear)
	{
		if (m_hud.getColor().a > 0)
		{
			m_hud.setColor(m_hud.getColor() - sf::Color{ 0,0,0,5 });
		}
	}
	if (m_hud.getColor().a <= 0)
	{
		m_gamescreen = GameScreen::Gameplay;
	}

	if (m_currentTurn == 0)
	{
		m_ai->makeMove(t_dt);
	}
	else
	{
		m_theCoolerAI->makeMove(t_dt);
	}

	if (m_players[m_currentTurn]->getMadeMove())
	{
		m_currentTurn = (m_currentTurn + 1) % 2;
		m_players[m_currentTurn]->setMadeMove(false);
	}
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_hud);
	t_window.draw(m_boardSprite);
	m_board.render(t_window);

	for (int i = 0; i < 2; i++)
	{
		m_players[i]->render(t_window);
	}
}

void Gameplay::processEvents(sf::Event& t_event, sf::Vector2f t_pos)
{
	if (m_currentTurn != 0)
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				Tile* selectedTile = m_board.selectTile(t_pos);

				if (selectedTile != nullptr)
				{
					m_players[m_currentTurn]->processTile(selectedTile);
				}
			}
		}
	}
}

void Gameplay::start(GameScreen t_previousState)
{
}

void Gameplay::end()
{
}

void Gameplay::initialise()
{
	if (!m_texture.loadFromFile("Images/basicScreen.png"))
	{
		std::cout << "Screen did not load" << std::endl;
	}
	
	m_hud.setTexture(m_texture);
	m_hud.setColor(m_hud.getColor() - sf::Color{ 0,0,0,255 });

	if (!m_boardTexture.loadFromFile("Images/gameplayBoard.png"))
	{
		std::cout << "board did not load" << std::endl;
	}

	m_boardSprite.setTexture(m_boardTexture);
	m_boardSprite.setPosition(400, 300);
	m_boardSprite.setOrigin(m_boardSprite.getGlobalBounds().width / 2, m_boardSprite.getGlobalBounds().height / 2);
	m_boardSprite.setScale(0.8, 0.8);
}

void Gameplay::addPiecesToPlayers()
{
	std::vector<Piece*> pieces = m_board.getPieces(PieceType::RED);

	for (Piece* piece : pieces)
	{
		m_players[0]->addPiece(piece);
	}

	pieces = m_board.getPieces(PieceType::GREEN);

	for (Piece* piece : pieces)
	{
		m_players[1]->addPiece(piece);
	}
}
