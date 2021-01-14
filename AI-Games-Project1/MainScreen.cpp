#include "MainScreen.h"

MainScreen::MainScreen(GameScreen & t_gameScreen) :
	Screen(t_gameScreen)
{
	initialise();
}

void MainScreen::update(sf::Time t_dt)
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
			m_gameScreen = GameScreen::OpponentSelect;
			m_animationState = AnimationMode::Appear;
		}
	}
}

void MainScreen::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_hud);
	t_window.draw(m_playButton);
	t_window.draw(m_quitButton);
	t_window.draw(m_playText);
	t_window.draw(m_quitText);
}

void MainScreen::processEvents(sf::Event& t_event, sf::Vector2f t_pos)
{
	if (m_playButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_animationState = AnimationMode::Disappear;
			}
		}
	}
	if (m_quitButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_gameScreen = GameScreen::Quit;
			}
		}
	}
}

void MainScreen::start(GameScreen t_previousState)
{
}

void MainScreen::end()
{
}

void MainScreen::initialise()
{
	if (!m_texture.loadFromFile("Images/mainScreen.png"))
	{
		std::cout << "Main Screen did not load" << std::endl;
	}
	setupButtons();
	setupText();
	
	m_hud.setTexture(m_texture);
	m_hud.setColor(m_hud.getColor() - sf::Color{ 0,0,0,255 });
}

void MainScreen::setupButtons()
{
	m_playButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_playButton.setFillColor(sf::Color::Blue);
	m_playButton.setOutlineThickness(5.0f);
	m_playButton.setOutlineColor(sf::Color::Black);
	m_playButton.setOrigin(m_playButton.getSize().x / 2, m_playButton.getSize().y / 2);
	m_playButton.setPosition(400.0f, 350.0f);

	m_quitButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_quitButton.setFillColor(sf::Color::Blue);
	m_quitButton.setOutlineThickness(5.0f);
	m_quitButton.setOutlineColor(sf::Color::Black);
	m_quitButton.setOrigin(m_quitButton.getSize().x / 2, m_quitButton.getSize().y / 2);
	m_quitButton.setPosition(400.0f, 450.0f);
}

void MainScreen::setupText()
{
	m_playText.setString("Play");
	m_playText.setFillColor(sf::Color::White);
	m_playText.setCharacterSize(20.0f);
	m_playText.setFont(m_font);
	sf::FloatRect textRect = m_playText.getLocalBounds();

	m_playText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_playText.setPosition(400.0f, 350.0f);

	m_quitText.setString("Quit");
	m_quitText.setFillColor(sf::Color::White);
	m_quitText.setCharacterSize(20.0f);
	m_quitText.setFont(m_font);
	textRect = m_quitText.getLocalBounds();

	m_quitText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_quitText.setPosition(400.0f, 450.0f);
}

