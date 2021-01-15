#include "OpponentScreen.h"

OpponentScreen::OpponentScreen(GameScreen& t_gameScreen) :
	Screen(t_gameScreen)
{
	initialise();
}

void OpponentScreen::update(sf::Time t_dt)
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
			if (s_gameplayState == GameplayStates::PlayerVsPlayer)
			{
				m_gameScreen = GameScreen::Gameplay;
			}
			else
				m_gameScreen = GameScreen::Difficulty;

			m_animationState = AnimationMode::Appear;
		}
	}
}

void OpponentScreen::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_hud);
	t_window.draw(m_pvcButton);
	t_window.draw(m_cvcButton);
	t_window.draw(m_pvpButton);
	t_window.draw(m_pvcText);
	t_window.draw(m_cvcText);
	t_window.draw(m_pvpText);
}

void OpponentScreen::processEvents(sf::Event& t_event, sf::Vector2f t_pos)
{
	//player vs ai
	if (m_pvcButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_animationState = AnimationMode::Disappear;
				s_gameplayState = GameplayStates::PlayerVsAi;
			}
		}
	}

	//ai vs ai
	if (m_cvcButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_animationState = AnimationMode::Disappear;
				s_gameplayState = GameplayStates::AiVsAi;
			}
		}
	}

	//player vs player
	if (m_pvpButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_animationState = AnimationMode::Disappear;
				s_gameplayState = GameplayStates::PlayerVsPlayer;
			}
		}
	}
}

void OpponentScreen::initialise()
{
	if (!m_texture.loadFromFile("Images/basicScreen.png"))
	{
		std::cout << "Screen did not load" << std::endl;
	}
	setupButtons();
	setupText();

	m_hud.setTexture(m_texture);
	m_hud.setColor(m_hud.getColor() - sf::Color{ 0,0,0,255 });
}

void OpponentScreen::setupButtons()
{
	//player vs ai
	m_pvcButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_pvcButton.setFillColor(sf::Color::Blue);
	m_pvcButton.setOutlineThickness(5.0f);
	m_pvcButton.setOutlineColor(sf::Color::Black);
	m_pvcButton.setOrigin(m_pvcButton.getSize().x / 2, m_pvcButton.getSize().y / 2);
	m_pvcButton.setPosition(400.0f, 200.0f);

	//ai vs ai
	m_cvcButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_cvcButton.setFillColor(sf::Color::Blue);
	m_cvcButton.setOutlineThickness(5.0f);
	m_cvcButton.setOutlineColor(sf::Color::Black);
	m_cvcButton.setOrigin(m_cvcButton.getSize().x / 2, m_cvcButton.getSize().y / 2);
	m_cvcButton.setPosition(400.0f, 300.0f);

	//player vs player
	m_pvpButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_pvpButton.setFillColor(sf::Color::Blue);
	m_pvpButton.setOutlineThickness(5.0f);
	m_pvpButton.setOutlineColor(sf::Color::Black);
	m_pvpButton.setOrigin(m_pvpButton.getSize().x / 2, m_pvpButton.getSize().y / 2);
	m_pvpButton.setPosition(400.0f, 400.0f);
}

void OpponentScreen::setupText()
{
	//p vs ai
	m_pvcText.setString("Player vs AI");
	m_pvcText.setFillColor(sf::Color::White);
	m_pvcText.setCharacterSize(20.0f);
	m_pvcText.setFont(m_font);
	sf::FloatRect textRect = m_pvcText.getLocalBounds();

	m_pvcText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_pvcText.setPosition(400.0f, 200.0f);

	//ai vs ai
	m_cvcText.setString("AI vs AI");
	m_cvcText.setFillColor(sf::Color::White);
	m_cvcText.setCharacterSize(20.0f);
	m_cvcText.setFont(m_font);
	textRect = m_cvcText.getLocalBounds();

	m_cvcText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_cvcText.setPosition(400.0f, 300.0f);

	//player vs player
	m_pvpText.setString("Player vs Player");
	m_pvpText.setFillColor(sf::Color::White);
	m_pvpText.setCharacterSize(20.0f);
	m_pvpText.setFont(m_font);
	textRect = m_pvpText.getLocalBounds();

	m_pvpText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_pvpText.setPosition(400.0f, 400.0f);
}

