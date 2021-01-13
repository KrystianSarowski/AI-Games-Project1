#include "Gameplay.h"

Gameplay::Gameplay(GameScreen& t_gameScreen) :
	Screen(t_gameScreen),
	m_board(sf::Vector2u(800, 600))
{
	initialise();
	m_players[0] = new Player(PieceType::RED, "Red");
	m_players[1] = new Player(PieceType::GREEN, "Green");

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
		else if (m_hud.getColor().a <= 0)
		{
			m_gamescreen = GameScreen::MainScreen;
			m_animationState = AnimationMode::Appear;
		}
	}
	
	if (!isGameWon)
	{
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
			if (!m_board.checkForWin(m_players[m_currentTurn]->m_ownedType))
			{
				m_currentTurn = (m_currentTurn + 1) % 2;
				m_players[m_currentTurn]->setMadeMove(false);
			}
			else
			{
				isGameWon = true;

				m_gameoverText.setString(m_players[m_currentTurn]->getPlayerName() + " Won");
				sf::FloatRect textRect = m_gameoverText.getLocalBounds();
				m_gameoverText.setOrigin( textRect.width / 2.0f, textRect.height / 1.5f);
				m_gameoverText.setPosition(400, 200);
			}
		}
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

	if (isGameWon)
	{
		t_window.draw(m_gameoverHud);
		t_window.draw(m_gameoverText);
		t_window.draw(m_returnButton);
		t_window.draw(m_returnText);
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
				if (!isGameWon) 
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
	if (isGameWon) 
	{
		if (m_returnButton.getGlobalBounds().contains(t_pos))
		{
			if (t_event.type == sf::Event::MouseButtonPressed)
			{
				if (t_event.key.code == sf::Mouse::Left)
				{
					m_animationState = AnimationMode::Disappear;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		isGameWon = true;
	}
}

void Gameplay::start(GameScreen t_previousState)
{
	isGameWon = false;
	m_board.restart();
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
	//gameover text
	m_gameoverText.setFillColor(sf::Color::White);
	m_gameoverText.setCharacterSize(40.0f);
	m_gameoverText.setFont(m_font);

	m_gameoverHud.setFillColor(sf::Color(0, 0, 0, 170));
	m_gameoverHud.setSize(sf::Vector2f(800.0f, 600.0f));

	m_returnButton.setSize(sf::Vector2f(200.0f, 40.0f));
	m_returnButton.setFillColor(sf::Color::Blue);
	m_returnButton.setOutlineThickness(5.0f);
	m_returnButton.setOutlineColor(sf::Color::Black);
	m_returnButton.setOrigin(m_returnButton.getSize().x / 2, m_returnButton.getSize().y / 2);
	m_returnButton.setPosition(400.0f, 350.0f);

	m_returnText.setString("Return to Menu");
	m_returnText.setFillColor(sf::Color::White);
	m_returnText.setCharacterSize(20.0f);
	m_returnText.setFont(m_font);
	sf::FloatRect textRect = m_returnText.getLocalBounds();
	m_returnText.setOrigin(textRect.width / 2.0f, textRect.height / 1.5f);
	m_returnText.setPosition(400, 350);
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
