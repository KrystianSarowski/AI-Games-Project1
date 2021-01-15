#include "DifficultyScreen.h"

DifficultyScreen::DifficultyScreen(GameScreen& t_gameScreen) :
	Screen(t_gameScreen)
{
	initialise();
}

void DifficultyScreen::update(sf::Time t_dt)
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
			m_gameScreen = GameScreen::Gameplay;
			m_animationState = AnimationMode::Appear;
		}
	}
}

void DifficultyScreen::render(sf::RenderWindow& t_window)
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_hud);
	t_window.draw(m_eButton);
	t_window.draw(m_mButton);
	t_window.draw(m_eText);
	t_window.draw(m_mText);
}

void DifficultyScreen::processEvents(sf::Event& t_event, sf::Vector2f t_pos)
{
	//easy
	if (m_eButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_animationState = AnimationMode::Disappear;
				s_difficulty = Difficulty::Easy;
			}
		}
	}

	//medium
	if (m_mButton.getGlobalBounds().contains(t_pos))
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
			{
				m_animationState = AnimationMode::Disappear;
				s_difficulty = Difficulty::Medium;
			}
		}
	}
}

void DifficultyScreen::initialise()
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

void DifficultyScreen::setupButtons()
{
	//easy
	m_eButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_eButton.setFillColor(sf::Color::Blue);
	m_eButton.setOutlineThickness(5.0f);
	m_eButton.setOutlineColor(sf::Color::Black);
	m_eButton.setOrigin(m_eButton.getSize().x / 2, m_eButton.getSize().y / 2);
	m_eButton.setPosition(400.0f, 250.0f);

	//medium
	m_mButton.setSize(sf::Vector2f(200.0f, 30.0f));
	m_mButton.setFillColor(sf::Color::Blue);
	m_mButton.setOutlineThickness(5.0f);
	m_mButton.setOutlineColor(sf::Color::Black);
	m_mButton.setOrigin(m_mButton.getSize().x / 2, m_mButton.getSize().y / 2);
	m_mButton.setPosition(400.0f, 350.0f);
}

void DifficultyScreen::setupText()
{
	//easy
	m_eText.setString("Easy");
	m_eText.setFillColor(sf::Color::White);
	m_eText.setCharacterSize(20.0f);
	m_eText.setFont(m_font);
	sf::FloatRect textRect = m_eText.getLocalBounds();

	m_eText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_eText.setPosition(400.0f, 250.0f);

	//med
	m_mText.setString("Normal");
	m_mText.setFillColor(sf::Color::White);
	m_mText.setCharacterSize(20.0f);
	m_mText.setFont(m_font);
	textRect = m_mText.getLocalBounds();

	m_mText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_mText.setPosition(400.0f, 350.0f);

}

