#include "Screen.h"

GameplayStates Screen::s_gameplayState = GameplayStates::PlayerVsPlayer;

Difficulty Screen::s_difficulty = Difficulty::Medium;

Screen::Screen(GameScreen& t_gamescreen) : m_gameScreen(t_gamescreen)
{
	initialise();
}

void Screen::update(sf::Time t_dt)
{

}

void Screen::render(sf::RenderWindow& t_window)
{

}

void Screen::processEvents(sf::Event& t_event, sf::Vector2f t_pos)
{

}

void Screen::start()
{

}

void Screen::initialise()
{
	if (!m_font.loadFromFile("Fonts/ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
}

void Screen::setPosition(sf::Vector2f t_postion)
{
	m_postion = t_postion;
}