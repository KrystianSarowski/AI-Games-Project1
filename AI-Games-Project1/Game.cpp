#include "Game.h"

Game::Game() : m_window{ sf::VideoMode{ 800, 600, 32 }, "Chinese Checkers" }
{
	m_previousState = GameScreen::MainScreen;
	m_currentState = GameScreen::MainScreen;
	m_screens.push_back(new MainScreen(m_currentState));
	m_screens.push_back(new OpponentScreen(m_currentState));
	m_screens.push_back(new DifficultyScreen(m_currentState));
	m_screens.push_back(new Gameplay(m_currentState));
	
	if (!m_bgMusic.openFromFile("Audio/bgMusic.ogg"))
	{
		std::cout << "Music did not load" << std::endl;
	}
	m_bgMusic.setLoop(true);
	m_bgMusic.play();
	m_bgMusic.setVolume(10);
}


void Game::start()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);	//60 fps

	while (m_window.isOpen())
	{
		processEvents();								//As many as possible
		timeSinceLastUpdate += clock.getElapsedTime();
		
		if (timeSinceLastUpdate > timePerFrame)
		{
			processEvents();							//At least 60 fps
			update(timePerFrame);						//60 fps
			timeSinceLastUpdate -= timePerFrame;
			clock.restart();
		}
		render();										//As many as possible
	}
}

void Game::update(sf::Time dt)
{
	
	if (m_currentState != GameScreen::Quit)
	{
		m_screens[static_cast<int>(m_currentState)]->update(dt);

		if (m_currentState != m_previousState && m_currentState != GameScreen::Quit)
		{
			m_screens[static_cast<int>(m_previousState)]->end();
			m_screens[static_cast<int>(m_currentState)]->start(m_previousState);

			m_previousState = m_currentState;
		}
	}

}

void Game::processEvents()
{
	sf::Event event;

	sf::Vector2f m_pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || m_currentState == GameScreen::Quit)
		{
			m_window.close();
		}
		else
		{
			sf::Vector2f m_pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

			m_screens[static_cast<int>(m_currentState)]->processEvents(event, m_pos);
		}
	}
}

void Game::render()
{
	m_window.clear();
	if (m_currentState != GameScreen::Quit)
	{
		m_screens[static_cast<int>(m_currentState)]->render(m_window);
	}
	m_window.display();

}

