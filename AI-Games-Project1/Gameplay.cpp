#include "Gameplay.h"

Gameplay::Gameplay(GameScreen& t_gameScreen) :
	Screen(t_gameScreen),
	m_board(sf::Vector2u(800, 600))
{
	initialise();

	m_players[0] = new Player(PieceType::RED, "Red");
	m_players[1] = new Player(PieceType::GREEN, "Green");

	for (int i = 0; i < 2; i++)
	{
		m_ai[i] = new Algorithm(m_players[i], &m_board);
	}

	addPiecesToPlayers();
}

void Gameplay::update(sf::Time t_dt)
{
	backgroundAnimation();

	if (!m_isGameOver)
	{
		if (m_players[m_currentTurn]->getControlledByAI())
		{
			m_ai[m_currentTurn]->makeMove(t_dt);
		}

		if (m_players[m_currentTurn]->getMadeMove())
		{
			if (!m_board.checkForWin(m_players[m_currentTurn]->getOwnedPieceType()))
			{
				m_currentTurn = (m_currentTurn + 1) % 2;
				m_players[m_currentTurn]->setMadeMove(false);
				m_currentTurnText.setString(m_players[m_currentTurn]->getPlayerName() + "'s turn");
			}

			else
			{
				m_isGameOver = true;

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
	t_window.draw(m_currentTurnText);

	for (int i = 0; i < 2; i++)
	{
		m_players[i]->render(t_window);
	}

	if (m_isGameOver)
	{
		t_window.draw(m_gameoverHud);
		t_window.draw(m_gameoverText);
		t_window.draw(m_returnButton);
		t_window.draw(m_returnText);
	}
}

void Gameplay::processEvents(sf::Event& t_event, sf::Vector2f t_pos)
{
	if (t_event.type == sf::Event::MouseButtonPressed)
	{
		if (t_event.key.code == sf::Mouse::Left)
		{
			if (!m_isGameOver)
			{
				if (!m_players[m_currentTurn]->getControlledByAI())
				{
					Tile* selectedTile = m_board.selectTile(t_pos);

					if (selectedTile != nullptr)
					{
						m_selectSound.play();
						m_players[m_currentTurn]->processTile(selectedTile);
					}
				}
			}
			else
			{
				if (m_returnButton.getGlobalBounds().contains(t_pos))
				{
					m_animationState = AnimationMode::Disappear;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_isGameOver = true;
	}
}

void Gameplay::start()
{
	m_isGameOver = false;
	m_currentTurn = 0;
	m_board.restart();

	switch (s_gameplayState)
	{
	case GameplayStates::PlayerVsAi:
		m_players[0]->setControlledByAI(false);
		m_players[1]->setControlledByAI(true);
		break;
	case GameplayStates::AiVsAi:
		m_players[0]->setControlledByAI(true);
		m_players[1]->setControlledByAI(true);
		break;
	case GameplayStates::PlayerVsPlayer:
		m_players[0]->setControlledByAI(false);
		m_players[1]->setControlledByAI(false);
		break;
	default:
		break;
	}

	switch (s_difficulty)
	{
	case Difficulty::Easy:
		Algorithm::setPredictionDepth(1);
		break;
	case Difficulty::Normal:
		Algorithm::setPredictionDepth(3);
		break;
	default:
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		m_ai[i]->reset();
		m_players[i]->clearSelection();
	}

	m_currentTurnText.setString(m_players[m_currentTurn]->getPlayerName() + "'s turn");
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

	m_currentTurnText.setString("");
	m_currentTurnText.setFillColor(sf::Color::White);
	m_currentTurnText.setCharacterSize(20.0f);
	m_currentTurnText.setFont(m_font);
	textRect = m_currentTurnText.getLocalBounds();
	m_currentTurnText.setOrigin(0, textRect.height / 1.5f);
	m_currentTurnText.setPosition(20, 20);

	//select sound
	if (!m_soundBuff.loadFromFile("Audio/select.ogg"))
	{
		std::cout << "select sound did not load" << std::endl;
	}
	m_selectSound.setBuffer(m_soundBuff);
}

void Gameplay::addPiecesToPlayers()
{
	for (int i = 0; i < 2; i++)
	{
		std::vector<Piece*> pieces = m_board.getPieces(static_cast<PieceType>(i));

		for (Piece* piece : pieces)
		{
			m_players[i]->addPiece(piece);
		}
	}
}

void Gameplay::backgroundAnimation()
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

		else
		{
			m_gameScreen = GameScreen::MainScreen;
			m_animationState = AnimationMode::Appear;
		}
	}
}
